#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <SFML/Graphics.hpp>

#include "../constants.h"

class FieldView
{
private:
    sf::Font m_font;

    sf::RenderWindow* m_windowPtr;
    sf::RectangleShape m_fieldRect;
    sf::RectangleShape m_blocks[FIELD_SIZE * FIELD_SIZE];
    sf::Text m_numbers[FIELD_SIZE * FIELD_SIZE];

    sf::Vector2f m_fieldPos;
    float m_fieldPadding;
    float m_fieldSize;
    float m_blockSize;

    void centerNumbers(sf::Vector2f pos, sf::Text& text);

public:
    FieldView();

    sf::Vector2f getPosition() { return m_fieldPos; }

    void setWindow(sf::RenderWindow* ptr);
    void setPosition(sf::Vector2i pos);
    void setPadding(float padding);

    void draw(std::vector<std::vector<int>> field);
};

#endif // FIELDVIEW_H
