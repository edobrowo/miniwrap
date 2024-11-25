#include <algorithm>
#include <random>

#include "application.hpp"
#include "math.hpp"
#include "noise.hpp"
#include "spline.hpp"

// https://www.tylerxhobbs.com/words/flow-fields
class FlowField2D {
public:
    FlowField2D(const u32 rows, const u32 cols, const f64 width,
                const f64 height)
        : m_rows(rows),
          m_cols(cols),
          m_width(width),
          m_height(height),
          m_resolution(m_width / static_cast<f64>(cols),
                       m_height / static_cast<f64>(rows)),
          m_angles(rows * cols) {}

    u32 rows() const { return m_rows; }
    u32 cols() const { return m_cols; }
    f64 width() const { return m_width; }
    f64 height() const { return m_height; }

    f64 operator()(const Vector2D vec) const {
        const Index x = static_cast<Index>(vec.x / m_resolution.x);
        const Index y = static_cast<Index>(vec.y / m_resolution.y);
        return (*this)(x, y);
    }

    f64 operator()(const Index row, const Index col) const {
        const Index r = math::clamp(row, Index(0), Index(m_rows));
        const Index c = math::clamp(col, Index(0), Index(m_rows));
        return m_angles[r * m_rows + c];
    }

    f64& operator()(const Index row, const Index col) {
        assert(row < m_rows);
        assert(col < m_cols);
        return m_angles[row * m_rows + col];
    }

    void constant(const f64 angle) {
        std::fill(m_angles.begin(), m_angles.end(), angle);
    }

    void random() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(0.0, 2.0 * math::Pi);
        for (Index row = 0; row < m_rows; ++row) {
            for (Index col = 0; col < m_cols; ++col) {
                m_angles[row * m_rows + col] = dist(gen);
            }
        }
    }

    void perlin(const f64 z = 0.0) {
        noise::Perlin p;
        for (Index row = 0; row < m_cols; ++row) {
            for (Index col = 0; col < m_rows; ++col) {
                const f64 x = math::map(static_cast<f64>(col), 0.0,
                                        static_cast<f64>(m_rows), 0.0, 2.0);
                const f64 y = math::map(static_cast<f64>(row), 0.0,
                                        static_cast<f64>(m_cols), 0.0, 2.0);
                const f64 pv = p.gen(x, y, z);
                m_angles[row * m_rows + col] =
                    math::map(pv, 0.0, 1.0, 0.0, 2.0 * math::Pi);
            }
        }
    }

private:
    u32 m_rows;
    u32 m_cols;
    f64 m_width;
    f64 m_height;
    Vector2D m_resolution;
    std::vector<f64> m_angles;
};

class Vectors : public Component {
public:
    Vectors(const u32 rows, const u32 cols, const f64 width, const f64 height)
        : m_field(rows, cols, width, height) {
        // m_field.perlin(0.2433);
        // m_field.constant(0.25 * math::Pi);
        for (Index row = 0; row < m_field.rows(); ++row) {
            for (Index col = 0; col < m_field.cols(); ++col) {
                m_field(row, col) =
                    col / static_cast<f64>(m_field.rows()) * math::Pi;
            }
        }
    }

    void update() override {}

    void draw(const Canvas& canvas) override {
        canvas.fill(Color(1.0));

        // canvas.setColor(Color(0.8, 0.1, 0.15));
        // for (Index row = 0; row < m_field.rows(); ++row)
        //     for (Index col = 0; col < m_field.cols(); ++col)
        //         drawVector(canvas, col, row);

        canvas.setColor(Color(0.15, 0.1, 0.8));
        for (Index row = 0; row < 10; ++row) {
            for (Index col = 0; col < 10; ++col) {
                Vector2D vertex(row * 10.0, col * 10.0);
                std::vector<Point2I> pts;
                pts.emplace_back(vertex);

                f64 step_size = 5.0;
                for (Index i = 0; i < 100; ++i) {
                    const f64 angle = m_field(vertex);
                    const Vector2D step =
                        step_size * Vector2D(std::cos(angle), std::sin(angle));
                    vertex += step;
                    if (step != Vector2D(0.0, 0.0))
                        pts.emplace_back(vertex);
                }

                canvas.curve(pts, 50);
            }
        }
    }

private:
    void drawVector(const Canvas& canvas, const u32 row, const u32 col) {
        const u32 radius = canvas.width() / m_field.cols() / 2;
        const u32 tail_radius = 3;
        const Point2I tail(row * canvas.width() / m_field.cols() + radius,
                           col * canvas.height() / m_field.rows() + radius);

        const f64 angle = m_field(row, col);
        const Point2I head(tail +
                           static_cast<f64>(radius) *
                               Vector2D(std::cos(angle), std::sin(angle)));

        canvas.line(tail, head);
        canvas.circle(tail, tail_radius);
    }
    FlowField2D m_field;
};

int main() {
    const char* title = "Flow fields";
    constexpr u64 width = 640;
    constexpr u64 height = 640;
    constexpr u64 fps = 60;

    Application app;

    try {
        app.init(title, width, height);
    } catch (const std::runtime_error& e) {
        eprintln("{}", e.what());
        return 1;
    }

    std::unique_ptr<Vectors> flow_field =
        std::make_unique<Vectors>(20, 20, width, height);
    app.add(std::move(flow_field));

    app.start(fps);
}
