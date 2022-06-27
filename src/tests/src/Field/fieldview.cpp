#include "fieldview.h"

#include <cmath>

FieldView::FieldView()
{
    m_windowPtr = nullptr;

    m_font.loadFromFile("Fonts/Comic Sans MS.ttf");

    m_fieldPadding = 10;

    m_fieldSize = 400;
    m_fieldPos = sf::Vector2f( (WINDOW_WIDTH - m_fieldSize) / 2, (WINDOW_HEIGHT - m_fieldSize) / 2 );

    m_fieldRect.setSize({m_fieldSize, m_fieldSize});
    m_fieldRect.setPosition(m_fieldPos);
    m_fieldRect.setFillColor(sf::Color(200, 200, 200));

    m_blockSize = (m_fieldSize - m_fieldPadding * (FIELD_SIZE + 1)) / FIELD_SIZE;

    for (int i = 0; i < FIELD_SIZE; ++i) {
        for (int j = 0; j < FIELD_SIZE; ++j) {
            float x = m_fieldPadding + m_fieldPos.x + (m_fieldPadding + m_blockSize) * j;
            float y = m_fieldPadding + m_fieldPos.y + (m_fieldPadding + m_blockSize) * i;

            m_blocks[i * FIELD_SIZE + j].setPosition(x, y);
            m_blocks[i * FIELD_SIZE + j].setSize({ m_blockSize, m_blockSize });

            m_numbers[i * FIELD_SIZE + j].setPosition(x, y);
            m_numbers[i * FIELD_SIZE + j].setFont(m_font);
            m_numbers[i * FIELD_SIZE + j].setCharacterSize((int)(m_blockSize * 0.35));
        }
    }
}

void FieldView::setWindow(sf::RenderWindow* ptr) {
    m_windowPtr = ptr;
}

void FieldView::centerNumbers(sf::Vector2f pos, sf::Text& text) {
    float w = text.getLocalBounds().width;
    float h = text.getLocalBounds().height;

    float x = (m_blockSize - w) / 2;
    float y = (m_blockSize - h) / 2;

    text.setPosition(pos.x + x, pos.y + y - 5);
}

void FieldView::draw(std::vector<std::vector<int>> field) {
    if (m_windowPtr == nullptr) return;

    m_windowPtr->draw(m_fieldRect);

    for (int i = 0; i < FIELD_SIZE * FIELD_SIZE; ++i) {
        int val = field[i / FIELD_SIZE][i % FIELD_SIZE];

        if (val != 0) {
            m_numbers[i].setString(std::to_string(val));
            float lev = log(val) / log(2.0);

            m_blocks[i].setFillColor(
                            sf::Color(20 + 200.0 * lev/11.0, 255 - (255.0 * lev/11.0), 255 * lev/3.0)
                        );
            centerNumbers(m_blocks[i].getPosition(), m_numbers[i]);
        } else {
            m_numbers[i].setString("");
            m_blocks[i].setFillColor(sf::Color(150, 150, 150));
        }

        m_windowPtr->draw(m_blocks[i]);
        m_windowPtr->draw(m_numbers[i]);
    }
}
