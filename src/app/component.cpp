#include "component.hpp"

Component::Component() : m_running{true} {}

Component::~Component() {}

void Component::event(const Event* event) {}

void Component::update() {}

void Component::render(const Renderer& renderer) {}

bool Component::isRunning() { return m_running; }

void Component::quit() { m_running = false; }
