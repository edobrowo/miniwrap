#include "widget.hpp"

Widget::Widget() : m_running{true} {}

Widget::~Widget() {}

void Widget::event(const SDL_Event& event) {
}

void Widget::update() {
}

void Widget::render(const Renderer& renderer) {
}

bool Widget::isRunning() {
    return m_running;
}

void Widget::quit() {
    m_running = false;
}
