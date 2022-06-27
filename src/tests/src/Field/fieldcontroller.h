#ifndef FIELDCONTROLLER_H
#define FIELDCONTROLLER_H

#include <SFML/Graphics.hpp>

#include "fieldmodel.h"
#include "fieldview.h"

class FieldController
{

private:
    FieldModel m_model;
    FieldView m_view;

public:
    FieldController();

    void setWindow(sf::RenderWindow* ptr);

    FieldModel& getModel() { return m_model; };
    FieldView& getView() { return m_view; };

    void reset();
    int move(Direction dir);

    bool isGameOver() {
        return m_model.isGameOver();
    }
    bool isWin(){
        return m_model.isWin();
    }

    void draw();
};

#endif // FIELDCONTROLLER_H
