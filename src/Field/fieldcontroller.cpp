#include "fieldcontroller.h"

#include <iostream>

FieldController::FieldController()
{

}

void FieldController::setWindow(sf::RenderWindow* ptr) {
    m_view.setWindow(ptr);
}

void FieldController::draw() {
    m_view.draw(m_model.getField());
}

void FieldController::reset() {
    m_model.clear();
    m_model.generateNumber();
    m_model.generateNumber();
}

int FieldController::move(Direction dir) {
    int ret = m_model.move(dir);

    if (ret >= 0)
        m_model.generateNumber();

    draw();
    return std::max(ret, 0);
}
