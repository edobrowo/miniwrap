#include "application.hpp"
#include "spline.hpp"

class Splines : public Component {
public:
    std::vector<Vector2D> m_knots;

    Splines() : m_knots() {}

    void onMouseClick(const MouseClickEvent* event) override {
        if (event->isPressed()) {
            Point2I p = event->pos;
            m_knots.push_back(Vector2D(p.x, p.y));
        }
    }

    void draw(const Canvas& canvas) override {
        canvas.fill(Color(1.0));

        CatmullRomSpline2D spline(catmull_rom_tag::centripetal, m_knots);

        std::vector<Point2I> knot_pts;
        std::vector<Point2I> pts;

        for (auto it = m_knots.begin(); it != m_knots.end(); ++it)
            knot_pts.emplace_back(*it);

        const u64 divisions = 10;
        for (Index i = 0, n = spline.segments(); i < n; ++i) {
            for (Index d = 0; d <= divisions; ++d) {
                const f64 t = static_cast<f64>(d) / static_cast<f64>(divisions);
                pts.emplace_back(spline(i, t));
            }
        }

        canvas.setColor(Color(0.15, 0.1, 0.8));
        canvas.polyline(pts);

        canvas.setColor(Color(0.8, 0.1, 0.15));
        // canvas.circles(pts, 2);
        canvas.circles(knot_pts, 2);
    }
};

int main() {
    const char* title = "Splines";
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

    std::unique_ptr<Splines> empty = std::make_unique<Splines>();
    app.add(std::move(empty));

    app.start(fps);
}
