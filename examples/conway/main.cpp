#include "application.hpp"
#include "bitarray.hpp"
#include "math.hpp"

class Conway {
public:
    Conway(const Size width, const Size height)
        : m_width(width),
          m_height(height),
          m_cells(width * height),
          m_temp(width * height) {}
    ~Conway() = default;

    bool operator()(const Index x, const Index y) {
        return m_cells[y * m_width + x];
    }

    void set(const Index x, const Index y, const bool b) {
        assert(x < m_width);
        assert(y < m_height);
        m_cells.set(y * m_width + x, b);
    }

    void toggle(const Index x, const Index y) {
        assert(x < m_width);
        assert(y < m_height);
        m_cells.toggle(y * m_width + x);
    }

    void step() {
        for (Index y = 0; y < m_height; ++y) {
            for (Index x = 0; x < m_width; ++x) {
                Size alive = countAlive(x, y);
                Index i = y * m_width + x;
                bool b = (m_cells[i] && (alive == 2 || alive == 3)) ||
                         (!m_cells[i] && alive == 3);
                m_temp.set(i, b);
            }
        }
        m_cells.copyFrom(m_temp);
    }

    void clear() { m_cells.clear(); }

private:
    Size countAlive(const Index x, const Index y) {
        Point2I center(x, y);
        Size count = 0;
        for (auto offset : m_offsets) {
            Point2I cell = center + offset;
            if (cell.x < 0 || cell.x >= m_width || cell.y < 0 ||
                cell.y >= m_height)
                continue;
            Index i = cell.y * m_width + cell.x;
            count += m_cells[i];
        }
        return count;
    }

    Size m_width;
    Size m_height;
    BitArray m_cells;
    BitArray m_temp;

    static const std::vector<Point2I> m_offsets;
};

const std::vector<Point2I> Conway::m_offsets{
    Point2I(-1, -1), Point2I(0, -1), Point2I(1, -1), Point2I(-1, 0),
    Point2I(1, 0),   Point2I(-1, 1), Point2I(0, 1),  Point2I(1, 1),
};

class Grid : public Component {
public:
    const Size width;
    const Size height;
    const Size cellSize;

    Conway conway;
    Timer stepper;
    u64 stepDuration;

    bool dragging;
    bool clickedCellState;

    Grid()
        : width(64),
          height(64),
          cellSize(10),
          conway(64, 64),
          stepper(),
          stepDuration(200),
          dragging(false),
          clickedCellState(false) {
        stepper.start();
    }

    void onKeyPress(const KeyboardEvent* event) override {
        if (event->isPressed()) {
            if (event->keycode == Keycode::P)
                stepper.toggle();
            else if (event->keycode == Keycode::R)
                conway.clear();
        }
    }

    void onMouseClick(const MouseClickEvent* event) override {
        dragging = event->isPressed();

        if (event->isPressed()) {
            Point2I p = event->pos / i32(cellSize);
            if (p.x < 0 || p.x >= 64 || p.y < 0 || p.y >= 64)
                return;

            clickedCellState = !conway(p.x, p.y);
            conway.toggle(p.x, p.y);
        }
    }

    void onMouseMove(const MouseMoveEvent* event) override {
        if (dragging) {
            Point2I p = event->pos / i32(cellSize);
            if (p.x < 0 || p.x >= 64 || p.y < 0 || p.y >= 64)
                return;

            conway.set(p.x, p.y, clickedCellState);
        }
    }

    void update() override {
        if (stepper.elapsed() >= stepDuration) {
            conway.step();
            stepper.restart();
        }
    }

    void draw(const Canvas& canvas) override {
        const Color background(0.0, 0.0, 0.0);
        const Color cell(1.0, 1.0, 1.0);

        canvas.setColor(cell);
        for (Index y = 0; y < width; ++y) {
            for (Index x = 0; x < height; ++x) {
                if (conway(x, y)) {
                    canvas.rect(x * cellSize, y * cellSize, cellSize, cellSize);
                }
            }
        }
    }
};

int main() {
    Application app;

    try {
        app.init("Conway's Game of Life", 640, 640);
    } catch (const std::runtime_error& e) {
        eprintln("{}", e.what());
        return 1;
    }

    std::unique_ptr<Grid> grid = std::make_unique<Grid>();
    app.add(std::move(grid));

    app.start(60.0);
}
