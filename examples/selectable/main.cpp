#include <optional>

#include "application.hpp"
#include "color.hpp"
#include "math.hpp"
#include "noise.hpp"
#include "spline.hpp"

class Knot {
public:
    static constexpr f64 radius = 5;
    static Color base;
    static Color prehighlight;
    static Color highlight;

    Point2I center;

    Knot() = default;
    Knot(const i32 x, const i32 y) : center(x, y) {}
    Knot(const Point2I pos) : center(pos) {}

    bool contains(const Point2I pos) const {
        return std::sqrt(math::sqr(pos.x - center.x) +
                         math::sqr(pos.y - center.y)) <= radius;
    }
};

Color Knot::base = Color(0.0, 0.0, 1.0);
Color Knot::prehighlight = Color(1.0, 0.0, 0.0);
Color Knot::highlight = Color(0.0, 1.0, 0.0);

class Selectables : public Component {
public:
    Selectables() = default;

    void onMouseClick(const MouseClickEvent* event) override {
        std::optional<Index> new_selection = std::nullopt;
        f64 min_dist = upper_bound<f64>();

        if (event->isPressed()) {
            for (Index i = 0, n = m_knots.size(); i < n; ++i) {
                const f64 dist = (event->pos - m_knots[i].center).length();
                if (m_knots[i].contains(event->pos) && dist < min_dist) {
                    new_selection = i;
                    min_dist = dist;
                }
            }

            if (!new_selection.has_value()) {
                m_knots.push_back(event->pos);
                m_selected.clear();
            }
        }

        m_dragging = event->isPressed();

        if (new_selection.has_value() &&
            std::find(m_selected.begin(), m_selected.end(), new_selection) ==
                m_selected.end()) {
            if (!m_adding)
                m_selected.clear();
            m_selected.push_back(new_selection.value());
        }
    }

    void onMouseMove(const MouseMoveEvent* event) override {
        m_preselected = std::nullopt;
        f64 min_dist = upper_bound<f64>();

        for (Index i = 0, n = m_knots.size(); i < n; ++i) {
            const f64 dist = (event->pos - m_knots[i].center).length();
            if (m_knots[i].contains(event->pos) && dist < min_dist) {
                m_preselected = i;
                min_dist = dist;
            }
        }

        if (m_dragging)
            for (const Index i : m_selected)
                m_knots[i].center += event->pos - m_prevMousePos;

        m_prevMousePos = event->pos;
    }

    void onKeyPress(const KeyboardEvent* event) override {
        m_adding = event->isPressed() && event->modifiers.shift();

        if (!event->isPressed())
            return;

        switch (event->keycode) {
        case Keycode::R:
            m_knots.clear();
            m_selected.clear();
            m_preselected = std::nullopt;
            break;
        default:
            break;
        }
    }

    void update() override {}

    void draw(const Canvas& canvas) override {
        canvas.fill(Color(1.0));

        canvas.setColor(Color(0.0));
        std::vector<Point2I> pts;
        for (const Knot knot : m_knots) pts.push_back(knot.center);
        canvas.curve(pts, 50);

        canvas.setColor(Knot::base);
        for (auto knot : m_knots) canvas.circle(knot.center, Knot::radius);

        canvas.setColor(Knot::prehighlight);
        if (m_preselected.has_value())
            canvas.circle(m_knots[m_preselected.value()].center, Knot::radius);

        canvas.setColor(Knot::highlight);
        for (auto i : m_selected)
            canvas.circle(m_knots[i].center, Knot::radius);
    }

private:
    std::vector<Knot> m_knots;

    std::optional<Index> m_preselected;
    std::vector<Index> m_selected;

    Point2I m_prevMousePos;
    bool m_dragging;
    bool m_adding;
};

int main() {
    const char* title = "Selectables";
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

    std::unique_ptr<Selectables> selectables = std::make_unique<Selectables>();
    app.add(std::move(selectables));

    app.start(fps);
}
