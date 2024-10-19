#include <random>

#include "application.hpp"
#include "math.hpp"

class HoveringCircle : public Component {
public:
    HoveringCircle(const i32 radius, const i32 x, const i32 y,
                   const i32 amplitude)
        : m_radius(radius),
          m_center(x, y),
          m_offset(0),
          m_amplitude(amplitude),
          m_frame(0) {}

    void update() override {
        m_offset = m_amplitude *
                   std::sin(static_cast<f64>(m_frame) / 180.0 * math::Pi);
        ++m_frame;
    }

    void draw(const Canvas& canvas) override {
        canvas.setColor(Color(1.0, 0.0, 0.0));
        canvas.circle(m_center + Point2I(0, m_offset), m_radius);
    }

private:
    i32 m_radius;
    Point2I m_center;
    i32 m_offset;
    i32 m_amplitude;
    u64 m_frame;
};

int main() {
    Application app;
    constexpr u32 width = 640;
    constexpr u32 height = 640;

    try {
        app.init("Circles", width, height);
    } catch (const std::runtime_error& e) {
        eprintln("{}", e.what());
        return 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < 10; ++i) {
        const i32 radius = dist(gen);
        const i32 amplitude = dist(gen);

        std::uniform_int_distribution<> center_dist(
            1, std::min(width, height) - radius);
        const i32 x = center_dist(gen);
        const i32 y = center_dist(gen);

        std::unique_ptr<HoveringCircle> circle =
            std::make_unique<HoveringCircle>(radius, x, y, amplitude);
        app.add(std::move(circle));
    }

    app.start(60.0);
}
