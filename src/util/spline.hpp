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

    virtual void add(const Vector2D& knot) = 0;
    virtual Vector2D operator()(const Index segment, const f64 t) = 0;

protected:
    std::vector<Vector2D> m_knots;
};

namespace catmull_rom_tag {
struct Uniform {
} constexpr uniform;
struct Centripetal {
} constexpr centripetal;
struct Chordal {
} constexpr chordal;
};

// https://qroph.github.io/2018/07/30/smooth-paths-using-catmull-rom-splines.html
class CatmullRomSpline2D : public Spline2D {
public:
    static constexpr f64 uniformAlpha = 0.0;
    static constexpr f64 centripetalAlpha = 0.5;
    static constexpr f64 chordalAlpha = 1.0;

    CatmullRomSpline2D() = default;

    CatmullRomSpline2D(catmull_rom_tag::Uniform)
        : Spline2D(), m_alpha(uniformAlpha), m_tension(0.0) {}
    CatmullRomSpline2D(catmull_rom_tag::Centripetal)
        : Spline2D(), m_alpha(centripetalAlpha), m_tension(0.0) {}
    CatmullRomSpline2D(catmull_rom_tag::Chordal)
        : Spline2D(), m_alpha(chordalAlpha), m_tension(0.0) {}

    CatmullRomSpline2D(catmull_rom_tag::Uniform,
                       const std::vector<Vector2D>& knots)
        : Spline2D(), m_alpha(uniformAlpha), m_tension(0.0) {
        solveAllSegments(knots);
    }
    CatmullRomSpline2D(catmull_rom_tag::Centripetal,
                       const std::vector<Vector2D>& knots)
        : Spline2D(), m_alpha(centripetalAlpha), m_tension(0.0) {
        solveAllSegments(knots);
    }
    CatmullRomSpline2D(catmull_rom_tag::Chordal,
                       const std::vector<Vector2D>& knots)
        : Spline2D(), m_alpha(chordalAlpha), m_tension(0.0) {
        solveAllSegments(knots);
    }

    ~CatmullRomSpline2D() = default;

    void add(const Vector2D& knot) override {
        if (!m_knots.empty() && knot == m_knots.back())
            return;

        m_knots.push_back(knot);
        if (m_knots.size() == 1)
            return;
        if (m_knots.size() == 2)
            // First sentinel point
            m_knots.insert(m_knots.begin(), 2.0 * (m_knots[0] - m_knots[1]));

        // Last sentinel point
        m_knots.push_back(
            2.0 * (m_knots[m_knots.size() - 1] - m_knots[m_knots.size() - 2]));

        solveSegment(m_knots.size() - 4);

        if (m_segments.size() > 1)
            // Re-solve second-last segment
            solveSegment(m_segments.size() - 2);

        m_knots.pop_back();
    }

    Vector2D operator()(const Index segment, const f64 t) override {
        assert(segment >= 0);
        assert(segment < m_segments.size());
        assert(t >= 0.0);
        assert(t <= 1.0);

        const Segment& s = m_segments[segment];

        return (((s.a * t + s.b) * t + s.c) * t) + s.d;
    }

    Size segments() const { return m_segments.size(); }

    bool isUniform() const { return m_alpha == uniformAlpha; }
    bool isCentripetal() const { return m_alpha == centripetalAlpha; }
    bool isChordal() const { return m_alpha == chordalAlpha; }

    f64 alpha() const { return m_alpha; }
    void setAlpha(const f64 alpha) {
        assert(alpha >= 0.0);
        assert(alpha <= 1.0);
        m_alpha = alpha;
    }

    f64 tension() const { return m_tension; }
    void setTension(const f64 tension) {
        assert(tension >= 0.0);
        assert(tension <= 1.0);
        m_tension = tension;
    }

private:
    void solveAllSegments(const std::vector<Vector2D>& knots) {
        for (Index i = 0; i < knots.size(); ++i) add(knots[i]);
    }

    void solveSegment(const Index i) {
        const Size n = m_knots.size();
        assert(i < n - 3);

        const Vector2D p0 = m_knots[i];
        const Vector2D p1 = m_knots[i + 1];
        const Vector2D p2 = m_knots[i + 2];
        const Vector2D p3 = m_knots[i + 3];

        const f64 alpha = 1.0;
        const f64 tension = 0.0;

        const f64 t01 = std::pow((p1 - p0).length(), alpha);
        const f64 t12 = std::pow((p2 - p1).length(), alpha);
        const f64 t23 = std::pow((p3 - p2).length(), alpha);

        const Vector2D m1 =
            (1.0 - tension) *
            (p2 - p1 + t12 * ((p1 - p0) / t01 - (p2 - p0) / (t01 + t12)));
        const Vector2D m2 =
            (1.0 - tension) *
            (p2 - p1 + t12 * ((p3 - p2) / t23 - (p3 - p1) / (t12 + t23)));

        Segment segment;
        segment.a = 2.0 * (p1 - p2) + m1 + m2;
        segment.b = -3.0 * (p1 - p2) - m1 - m1 - m2;
        segment.c = m1;
        segment.d = p1;

        if (i < m_segments.size())
            m_segments[i] = segment;
        else
            m_segments.push_back(segment);
    }
    struct Segment {
        Vector2D a, b, c, d;
    };

    std::vector<Segment> m_segments;
    f64 m_alpha;
    f64 m_tension;
};

// TODO : not fully continuous, need to fix
class CubicSpline2D : public Spline2D {
public:
    CubicSpline2D() = default;
    CubicSpline2D(const std::vector<Vector2D>& knots) : Spline2D(knots) {}
    ~CubicSpline2D() = default;

    void add(const Vector2D& knot) override {
        m_knots.push_back(knot);
        solve();
    }

    Vector2D operator()(const Index i, const f64 t) override {
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

private:
    void solve() {
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

    std::vector<f64> m_x;
};
