#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Field/fieldcontroller.h"

#include "constants.h"

class Game
{
    enum Screen { MenuScreen, GameScreen };

private:
    FieldController m_controller;

    int m_score = 0;

    Screen m_screenState = Screen::MenuScreen;
    sf::RenderWindow m_window;

    sf::Font m_font;

    std::map<sf::Keyboard::Key, bool> m_keyPressed;

    sf::Text m_menuTitleText;
    sf::Text m_menuScoreText;
    sf::Text m_menuHintText;

    sf::Text m_gameScoreText;

    void initUI();

    void drawMenuScreen();
    void drawGameScreen();

    void centerText(sf::Text &text);

    void handleKeyPress(sf::Event event);

    void changeMenuText();

public:
    Game();
    ~Game();

    void run();
};

#endif // GAME_H
