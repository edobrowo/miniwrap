#pragma once

#include "common.hpp"
#include "format.hpp"
#include "vector.hpp"

// Inspired by https://stackoverflow.com/a/23258882
class Spline2D {
public:
    Spline2D() = default;
    Spline2D(const std::vector<Vector2D>& knots) : m_knots(knots) {}
    ~Spline2D() = default;

    void add(const Vector2D& knot) { m_knots.push_back(knot); }
    void clear() { m_knots.clear(); }

    virtual void solve() {};

protected:
    std::vector<Vector2D> m_knots;
};

// https://www.mvps.org/directx/articles/catmull/
// https://qroph.github.io/2018/07/30/smooth-paths-using-catmull-rom-splines.html
class CatmullRomSpline2D : public Spline2D {
public:
    CatmullRomSpline2D() = default;
    CatmullRomSpline2D(const std::vector<Vector2D>& knots) : Spline2D(knots) {}
    ~CatmullRomSpline2D() = default;

    Vector2D operator()(const Index segment, const f64 t) {
        assert(segment > 0);
        assert(segment < m_knots.size() - 1);
        assert(t >= 0.0);
        assert(t <= 1.0);

        const Vector2D a = -m_knots[segment - 1] + 3.0 * m_knots[segment] -
                           3.0 * m_knots[segment + 1] + m_knots[segment + 2];
        const Vector2D b = 2.0 * m_knots[segment - 1] - 5.0 * m_knots[segment] +
                           4.0 * m_knots[segment + 1] - m_knots[segment + 2];
        const Vector2D c = -m_knots[segment - 1] + m_knots[segment + 1];
        const Vector2D d = 2.0 * m_knots[segment];

        return 0.5 * ((((a * t + b) * t + c) * t) + d);
    }
};

class CubicSpline2D : public Spline2D {
public:
    CubicSpline2D() = default;
    CubicSpline2D(const std::vector<Vector2D>& knots) : Spline2D(knots) {}
    ~CubicSpline2D() = default;

    Vector2D operator()(const Index i, const f64 t) {
        assert(i >= 0);
        assert(i < m_knots.size() - 1);
        assert(t >= 0.0);
        assert(t <= 1.0);

        const f64 h = m_knots[i + 1].x - m_knots[i].x;
        const f64 x = t * h + m_knots[i].x;
        const f64 xi1_x = m_knots[i + 1].x - x;
        const f64 x_xi = x - m_knots[i].x;

        const f64 t1 = m_x[i] * xi1_x * xi1_x * xi1_x / (6.0 * h);
        const f64 t2 = m_x[i + 1] * x_xi * x_xi * x_xi / (6.0 * h);

        const f64 b = m_knots[i].y / h - m_x[i] * h / 6.0;
        const f64 t3 = b * xi1_x;

        const f64 c = m_knots[i + 1].y / h - m_x[i + 1] * h / 6.0;
        const f64 t4 = c * x_xi;

        const f64 y = t1 + t2 + t3 + t4;

        return {x, y};
    }

    void solve() override {
        m_x.resize(m_knots.size());

        std::vector<f64> diag(m_knots.size());
        std::vector<f64> off_diag(m_knots.size());
        std::vector<f64> rhs(m_knots.size());

        Index n = m_knots.size();

        // Create the system
        off_diag[0] = m_knots[1].x - m_knots[0].x;
        for (Index i = 1; i < n - 1; ++i) {
            diag[i] = 2.0 * (m_knots[i + 1].x - m_knots[i - 1].x);

            off_diag[i] = m_knots[i + 1].x - m_knots[i].x;

            // off_diag[i] corresponds to h_i
            const f64 l = (m_knots[i + 1].y - m_knots[i].y) / off_diag[i];
            const f64 r = (m_knots[i].y - m_knots[i - 1].y) / off_diag[i - 1];
            rhs[i] = 3.0 * (l - r);
        }

        // Boundary conditions
        diag[0] = 2.0 * (m_knots[1].x - m_knots[0].x);
        diag[n - 1] = 2.0 * (m_knots[n - 1].x - m_knots[n - 2].x);

        // Use natural spline conditions (v_0 = v_n = 0)
        rhs[0] = 3.0 * (m_knots[1].y - m_knots[0].y) / off_diag[0];
        rhs[n - 1] =
            -3.0 * (m_knots[n - 1].y - m_knots[n - 2].y) / off_diag[n - 2];

        // Solve using in-place Thomas algorithm.
        // https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm
        for (Index i = 1; i < n; ++i) {
            const f64 w = off_diag[i - 1] / diag[i - 1];
            diag[i] -= w * diag[i - 1];
            rhs[i] -= w * rhs[i - 1];
        }

        // Back substitution
        m_x[n - 1] = rhs[n - 1] / diag[n - 1];
        for (Index i = n - 1; i-- > 1;) {
            m_x[i] = (rhs[i] - off_diag[i] * m_x[i + 1]) / diag[i];
        }
    }

private:
    std::vector<f64> m_x;
};
