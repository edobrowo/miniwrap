#include "application.hpp"
#include "math.hpp"
#include "noise.hpp"

class Grid : public Component {
public:
    const Size width;
    const Size height;
    const Size cellSize;

    noise::Perlin perlin;
    std::vector<f64> noiseGrid;
    f64 tick;

    Timer stepper;
    u64 stepDuration;

    Grid()
        : width(128),
          height(128),
          cellSize(5),
          perlin(),
          noiseGrid(width * height),
          tick(0.1),
          stepper(),
          stepDuration(100) {
        stepper.start();
    }

    void update() override {
        if (stepper.elapsed() >= stepDuration) {
            fill(tick);
            tick += 0.1;
            stepper.restart();
        }
    }

    void draw(const Canvas& canvas) override {
        for (Index y = 0; y < width; ++y) {
            for (Index x = 0; x < height; ++x) {
                const f64 g = noiseGrid[y * width + x];
                canvas.setColor(Color(g / 1.5, g / 3.0, g * 1.5));
                canvas.rect(x * cellSize, y * cellSize, cellSize, cellSize);
            }
        }
    }

private:
    void fill(const f64 zf) {
        for (Index y = 0; y < width; ++y) {
            for (Index x = 0; x < height; ++x) {
                const f64 xf = math::map(static_cast<f64>(x), 0.0,
                                         static_cast<f64>(width), 0.0, 10.0);
                const f64 yf = math::map(static_cast<f64>(y), 0.0,
                                         static_cast<f64>(height), 0.0, 10.0);
                noiseGrid[y * width + x] = perlin.octave(xf, yf, zf, 5, 0.5);
            }
        }
    }
};

int main() {
    Application app;

    try {
        app.init("Perlin noise", 640, 640);
    } catch (const std::runtime_error& e) {
        eprintln("{}", e.what());
        return 1;
    }

    std::unique_ptr<Grid> grid = std::make_unique<Grid>();
    app.add(std::move(grid));

    app.start(60.0);
}
