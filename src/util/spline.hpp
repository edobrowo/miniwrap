#pragma once

#include "common.hpp"
#include "format.hpp"
#include "vector.hpp"

class Spline2D {
public:
    Spline2D() = default;
    Spline2D(const std::vector<Vector2D>& knots) : m_knots(knots) {}
    ~Spline2D() = default;

    void add(const Vector2D& knot) { m_knots.push_back(knot); }
    void clear() { m_knots.clear(); }

    virtual void solve() = 0;

protected:
    std::vector<Vector2D> m_knots;
};

// https://stackoverflow.com/a/23258882
class CubicSpline2D : public Spline2D {
public:
    CubicSpline2D() = default;
    CubicSpline2D(const std::vector<Vector2D>& knots) : Spline2D(knots) {}
    ~CubicSpline2D() = default;

    Vector2D operator()(const Index segment, const f64 t) {
        assert(segment >= 0);
        assert(segment < m_knots.size() - 1);
        assert(t >= 0.0);
        assert(t <= 1.0);

        const f64 dx = m_knots[segment + 1].x - m_knots[segment].x;
        const f64 x = t * dx + m_knots[segment].x;

        const f64 t3 = t * t * t - t;
        const f64 t_inv = 1.0 - t;
        const f64 t_inv3 = t_inv * t_inv * t_inv - t_inv;
        const f64 mix = t * m_knots[segment + 1].y + t_inv * m_knots[segment].y;
        const f64 y = mix + 1.0 / 6.0 * dx * dx *
                                (t3 * m_x[segment + 1] - t_inv3 * m_x[segment]);

        return {x, y};
    }

    void solve() override {
        m_diag.resize(m_knots.size());
        m_offDiag.resize(m_knots.size());
        m_x.resize(m_knots.size());
        m_b.resize(m_knots.size());

        Index n = m_knots.size();

        // Use the Thomas algorithm to solve the tridiagonal matrix
        // https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm
        for (Index i = 1; i < n - 1; ++i)
            m_diag[i] = 2.0 * (m_knots[i + 1].x - m_knots[i - 1].x);
        m_diag[0] = 2.0 * (m_knots[1].x - m_knots[0].x);
        m_diag[n - 1] = 2.0 * (m_knots[n - 1].x - m_knots[n - 2].x);

        for (Index i = 0; i < n - 1; ++i)
            m_offDiag[i] = m_knots[i + 1].x - m_knots[i].x;

        for (Index i = 1; i < n - 1; ++i) {
            // m_offDiag[i] corresponds to h_i
            const f64 l = (m_knots[i + 1].y - m_knots[i].y) / m_offDiag[i];
            const f64 r = (m_knots[i].y - m_knots[i - 1].y) / m_offDiag[i - 1];
            m_b[i] = 6.0 * (l - r);
        }

        // Use natural spline conditions (v_0 = v_n = 0)
        m_b[0] = 6.0 * (m_knots[1].y - m_knots[0].y) / m_offDiag[0];

        // Replace m_diag and m_b in-place
        for (Index i = 1; i < n; ++i) {
            const f64 w = m_offDiag[i] / m_diag[i - 1];
            m_diag[i] -= w * m_diag[i - 1];
            m_b[i] -= w * m_b[i - 1];
        }

        // Back substitution
        m_x[n - 1] = m_b[n - 1] / m_diag[n - 1];
        for (i64 i = n - 1; i-- > 0;) {
            m_x[i] = (m_b[i] - m_offDiag[i] * m_x[i + 1]) / m_diag[i];
        }
    }

private:
    std::vector<f64> m_diag;
    std::vector<f64> m_offDiag;
    std::vector<f64> m_x;
    std::vector<f64> m_b;
};
