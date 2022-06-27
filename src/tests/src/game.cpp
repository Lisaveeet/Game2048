#include "game.h"

Game::Game() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2048")
{
    m_controller.setWindow(&m_window);

    m_keyPressed[sf::Keyboard::Up] = false;
    m_keyPressed[sf::Keyboard::Down] = false;
    m_keyPressed[sf::Keyboard::Left] = false;
    m_keyPressed[sf::Keyboard::Right] = false;

    initUI();
}

Game::~Game() {}

void Game::initUI() {
    m_font.loadFromFile("./Fonts/Comic Sans MS.ttf");

    m_menuTitleText.setFont(m_font);
    m_menuTitleText.setFillColor(sf::Color::Black);
    m_menuTitleText.setCharacterSize(60);
    m_menuTitleText.setString("2048");
    m_menuTitleText.setPosition(50, 200);

    centerText(m_menuTitleText);

    m_menuHintText.setFont(m_font);
    m_menuHintText.setFillColor(sf::Color::Black);
    m_menuHintText.setCharacterSize(24);
    m_menuHintText.setString(L"Нажмите Space чтобы начать!");
    m_menuHintText.setPosition(50, WINDOW_HEIGHT - 100);

    centerText(m_menuHintText);

    m_gameScoreText.setFont(m_font);
    m_gameScoreText.setPosition(m_controller.getView().getPosition().x, 20);
    m_gameScoreText.setFillColor(sf::Color::Black);
    m_gameScoreText.setCharacterSize(24);
    m_gameScoreText.setString(L"Очки:\n0");

    m_menuScoreText.setFont(m_font);
    m_menuScoreText.setPosition(20, 300);
    m_menuScoreText.setFillColor(sf::Color::Black);
    m_menuScoreText.setCharacterSize(24);
    m_menuScoreText.setString(L"");
}

void Game::centerText(sf::Text &text) {
    int w = text.getLocalBounds().width;

    int x = (WINDOW_WIDTH - w) / 2;

    text.setPosition(x, text.getPosition().y);
}

void Game::run() {
    while (m_window.isOpen()) {

        sf::Event event;

        while (m_window.pollEvent(event))
        {
            handleKeyPress(event);

            if (event.type == sf::Event::Closed)
                m_window.close();
        }

        if (m_controller.isGameOver()) {
            m_menuTitleText.setString(L"Игра окончена!");
            changeMenuText();
            m_screenState = Screen::MenuScreen;
        }
        if (m_controller.isWin()) {
            m_menuTitleText.setString(L"Вы победили!");
            changeMenuText();
            m_screenState = Screen::MenuScreen;
        }

        m_window.clear(sf::Color(230, 230, 230));

        if (m_screenState == Screen::MenuScreen)
            drawMenuScreen();
        if (m_screenState == Screen::GameScreen) {
            drawGameScreen();
        }

        m_window.display();
    }
}

void Game::changeMenuText() {
    m_menuScoreText.setString(L"Очки: " + std::to_wstring(m_score));
    m_menuHintText.setString(L"Нажмите Space, чтобы сыграть снова");

    centerText(m_menuHintText);
    centerText(m_menuTitleText);
    centerText(m_menuScoreText);
}

void Game::handleKeyPress(sf::Event event) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_screenState != GameScreen) {
        m_controller.reset();
        m_gameScoreText.setString(L"Очки:\n0");
        m_score = 0;
        m_screenState = GameScreen;
    }

    if (m_screenState != GameScreen) return;

    if (event.type == sf::Event::KeyPressed)
    {
        if (m_keyPressed.find(event.key.code) != m_keyPressed.end() && m_keyPressed[event.key.code] == false)
        {
            m_keyPressed[event.key.code] = true;

            Direction dir = Direction::None;

            switch(event.key.code) {
                case sf::Keyboard::Up: dir = Direction::Up; break;
                case sf::Keyboard::Down: dir = Direction::Down; break;
                case sf::Keyboard::Left: dir = Direction::Left; break;
                case sf::Keyboard::Right: dir = Direction::Right; break;
                default: break;
            }

            m_score += m_controller.move(dir);
            m_gameScoreText.setString(L"Очки:\n" + std::to_wstring(m_score));
        }
    }

    if (event.type == sf::Event::KeyReleased)
    {
        if (m_keyPressed.find(event.key.code) != m_keyPressed.end())
            m_keyPressed[event.key.code] = false;
    }
}

void Game::drawMenuScreen() {
    m_window.draw(m_menuTitleText);
    m_window.draw(m_menuScoreText);
    m_window.draw(m_menuHintText);
}

void Game::drawGameScreen() {
    m_controller.draw();

    m_window.draw(m_gameScoreText);
}
