#include <SFML/Graphics.hpp>
#include <iostream>
#include <iostream>
#include <cstdlib>

class Gems {
private:
    int id;
    int coords[2];
    sf::Vector2f position;
    sf::Texture texture;
    sf::RectangleShape hitBox;
    bool isSelected;

public:
    Gems() {
        id = 0;
        coords[0] = 0; coords[1] = 0;
        hitBox.setSize(sf::Vector2f(34.f, 34.f));
        hitBox.setPosition(145.f, 45.f);
        if (!texture.loadFromFile("assets/textures/Chip.png")) {
            texture.loadFromFile("assets/textures/thumbnail.png");
            std::cerr << "No se pudo cargar la textura Chip.png\n";
        }
        hitBox.setTexture(&texture);
        hitBox.setOutlineThickness(2.f);
        isSelected = false;
    }
    Gems(int newId, int x, int y, sf::Vector2f newPosition) : id(newId) {
        coords[0] = x; coords[1] = y;
        hitBox.setSize(sf::Vector2f(34.f, 34.f));
        hitBox.setPosition(newPosition);
        position = newPosition;
        changeTexture();
        hitBox.setOutlineThickness(2.f);
        isSelected = false;
    }
    ~Gems() {}

    void setId(int newId) {
        id = newId;
        changeTexture();
    }
    void setX(int x) { coords[0] = x; }
    void setY(int y) { coords[1] = y; }
    void setPosition(sf::Vector2f newPosition) {
        hitBox.setPosition(newPosition);
        position = newPosition;
    }
    void setCoords(int x, int y) {
        coords[0] = x;
        coords[1] = y;
    }

    int getId() const { return id; }
    int getX() { return coords[0]; }
    int getY() { return coords[1]; }
    sf::Vector2f getPosition() { return position; }
    sf::RectangleShape getHitBox() { return hitBox; }

    void mouseIsOn() {
        if (!isSelected) {
            hitBox.setOutlineColor(sf::Color::Yellow);
        }
    }
    void mouseIsNotOn() {
        if (!isSelected) {
            hitBox.setOutlineColor(sf::Color::Transparent);
        }
    }
    void select() {
        isSelected = true;
        hitBox.setFillColor(sf::Color::Green);
    }
    void deselect() {
        hitBox.setFillColor(sf::Color::White);
        isSelected = false;
    }
    void changeTexture() {
        switch (id) {
        case 0:
            if (!texture.loadFromFile("assets/textures/Chip.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura Chip.png\n";
            }
            hitBox.setTexture(&texture);
            break;
        case 1:
            if (!texture.loadFromFile("assets/textures/ChipOne.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura ChipOne.png\n";
            }
            hitBox.setTexture(&texture);
            break;
        case 2:
            if (!texture.loadFromFile("assets/textures/ChipTwo.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura ChipTwo.png\n";
            }
            hitBox.setTexture(&texture);
            break;
        case 3:
            if (!texture.loadFromFile("assets/textures/ChipThree.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura ChipThree.png\n";
            }
            hitBox.setTexture(&texture);
            break;
        case 4:
            if (!texture.loadFromFile("assets/textures/ChipFour.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura ChipFour.png\n";
            }
            hitBox.setTexture(&texture);
            break;
        case 5:
            if (!texture.loadFromFile("assets/textures/ChipFive.png")) {
                texture.loadFromFile("assets/textures/thumbnail.png");
                std::cerr << "No se pudo cargar la textura ChipFive.png\n";
            }
            hitBox.setTexture(&texture);
            break;
        default:
            texture.loadFromFile("assets/textures/thumbnail.png");
            hitBox.setTexture(&texture);
            break;
        }
    }
};

class Board {
private:
    Gems* board[8][8];
    bool isOneSelect;
    int movesAllowed;
    int GO[2];
    int GT[2];
    int score;

public:
    Board() {
        initialize();
    }
    ~Board() {}

    void initialize() {
        sf::Vector2f position(10.f, -23.f); // 77.f, -23.f
        for (int i = 0; i < 8; i++) {
            position.y = 20.f; // 23.f
            position.x += 60.f; // 68.f
            for (int j = 0; j < 8; j++) {
                position.y += 60.f; // 68.f
                board[i][j] = new Gems(getRandId(i, j), i, j, position);
            }
        }
        for (int i = 0; i < 2; i++) {
            GO[i] = 0;
            GT[i] = 0;
        }
        isOneSelect = false;
        movesAllowed = 3;
        score = 0;
    }
    int getMovesAllowed() const { return movesAllowed; }
    int getScore() const { return score; }

    int getRandId(int i, int j) {
        int id;
        do {
            id = (rand() % 5) + 1;
        } while ((j >= 2 && id == board[i][j - 2]->getId()) || (i >= 2 && id == board[i - 2][j]->getId()));
        return id;
    }
    void printBoard(sf::RenderWindow& window) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                window.draw(board[i][j]->getHitBox());
            }
        }
    }
    void ifMouseIsOn(sf::Vector2f mousePosition) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j]->getHitBox();
                if (board[i][j]->getHitBox().getGlobalBounds().contains(mousePosition)) {
                    board[i][j]->mouseIsOn();
                } else {
                    board[i][j]->mouseIsNotOn();
                }
            }
        }
    }
    void select(sf::Vector2f mousePosition) {
        if (movesAllowed == 0) {
            std::cout << "No quedan movimientos" << std::endl;
            return;
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j]->getHitBox().getGlobalBounds().contains(mousePosition) && !isOneSelect) {
                    board[i][j]->select();
                    isOneSelect = true;
                    GO[0] = i;
                    GO[1] = j;
                } else if (board[i][j]->getHitBox().getGlobalBounds().contains(mousePosition) && isOneSelect) {
                    board[i][j]->select();
                    GT[0] = i;
                    GT[1] = j;
                    verifyChange();
                    return;
                }
            }
        }
    }
    void verifyChange() {
        int X = board[GO[0]][GO[1]]->getX() - board[GT[0]][GT[1]]->getX();
        int Y = board[GO[0]][GO[1]]->getY() - board[GT[0]][GT[1]]->getY();
        bool isX = (X == 1 || X == -1);
        bool isY = (Y == 1 || Y == -1);
        if ((isX && Y == 0) || (isY && X == 0)) {
            changeGemsPositions();
            if (findMacht()) {
                movesAllowed--;
                deselectAll();
                macht();
                return;
            }
            changeGemsPositions();
            deselectAll();
            return;
        } else {
            deselectAll();
            return;
        }
    }
    void changeGemsPositions() {
        int GemId = board[GO[0]][GO[1]]->getId();
        board[GO[0]][GO[1]]->setId(board[GT[0]][GT[1]]->getId());
        board[GT[0]][GT[1]]->setId(GemId);
    }
    void changeByIndex(int i, int j, int k, int h) {
        int GemId = board[i][j]->getId();
        board[i][j]->setId(board[k][h]->getId());
        board[k][h]->setId(GemId);
    }
    void deselectAll() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j]->deselect();
            }
        }
        isOneSelect = false;
        for (int i = 0; i < 2; i++) {
            GO[i] = 0;
            GT[i] = 0;
        }
    }
    bool findMacht() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (j < 6)
                    if (board[j][i]->getId() == board[j + 1][i]->getId() && board[j][i]->getId() == board[j + 2][i]->getId()) {
                        return true;
                    }
                if (i < 6)
                    if (board[j][i]->getId() == board[j][i + 1]->getId() && board[j][i]->getId() == board[j][i + 2]->getId()) {
                        return true;
                    }
            }
        }
        return false;
    }
    void deleteGems() {
        int countJ, countI;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                countJ, countI = 0;
                if (j < 7) {
                    deleteJ(i, j);
                }
                if (i < 7) {
                    deleteI(i, j);
                }
            }
        }
    }
    void deleteJ(int i, int j) {
        int count = 0;
        for (int k = j + 1; k < 8 && board[j][i]->getId() == board[k][i]->getId(); k++) {
            count++;
        }
        if (1 < count) {
            for (int k = j; k <= j + count; k++) {
                score += 10;
                board[k][i]->setId(0);
            }
        }
    }
    void deleteI(int i, int j) {
        int count = 0;
        for (int k = i + 1; k < 8 && board[j][i]->getId() == board[j][k]->getId(); k++) {
            count++;
        }
        if (1 < count) {
            for (int h = i; h <= i + count; h++) {
                board[j][h]->setId(0);
                score += 10;
            }
        }
    }
    void macht() {
        while (findMacht()) {
            deleteGems();
            while (findZeros()) {
                gravity();
            }
        }
    }
    bool findZeros() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j]->getId() == 0) {
                    return true;
                }
            }
        }
        return false;
    }
    void gravity() {
        int count;
        for (int i = 0; i < 8; i++) {
            if (board[i][0]->getId() == 0) {
                board[i][0]->setId(getRandId(0, i));
            }
        }
        for (int i = 7; i > -1; i--) {
            for (int j = 0; j < 8; j++) {
                count = 0;
                if (board[j][i]->getId() == 0) {
                    for (int k = i; k > 0 && board[j][k]->getId() == 0; k--) {
                        count++;
                    }
                    changeByIndex(j, i, j, i - count);
                }
            }
        }
    }
};

class Game {
private:
    sf::RenderWindow& window;
    Board board;
    sf::Font font;
    sf::Text scoreText;
    sf::Text movesText;
    sf::Text gameFinish;
    sf::RectangleShape scoreShape;
    sf::RectangleShape button;
    sf::RectangleShape quit;
    sf::Texture quitTexture;
    sf::Texture backgroundTextureOne;
    sf::Texture backgroundTextureTwo;
    sf::Sprite backgroundOne;
    sf::Sprite backgroundTwo;
    sf::Clock clock;
    float lastClickTime;
    const float minDelay = 0.25f; // 250 ms
    int currentScreen;

public:
    Game(sf::RenderWindow& newWindow) : window(newWindow) {
        button.setSize(sf::Vector2f(100.f, 50.f));
        button.setPosition(400.f, 300.f);
        button.setFillColor(sf::Color::Blue);
        button.setOutlineThickness(1.f);
        quit.setSize(sf::Vector2f(50.f, 50.f));
        quit.setPosition(5.f, 5.f);
        quit.setOutlineThickness(3.f);
        if (!font.loadFromFile("assets/fonts/m6x11plus.ttf")) {
            std::cerr << "No se pudo cargar la fuente aptos.ttf\n";
        }
        if (!quitTexture.loadFromFile("assets/textures/Quit.jpg")) {
            quitTexture.loadFromFile("assets/textures/thumbnail.png");
            std::cerr << "No se pudo cargar la textura Quit.png\n";
        }
        if (!backgroundTextureTwo.loadFromFile("assets/textures/backgroundTwo.jpg")) {
            backgroundTextureTwo.loadFromFile("assets/textures/thumbnail.png");
            std::cerr << "No se pudo cargar la textura backgroundTwo.png\n";
        }
        if (!backgroundTextureTwo.loadFromFile("assets/textures/backgroundTwo.jpg")) {
            backgroundTextureTwo.loadFromFile("assets/textures/thumbnail.png");
            std::cerr << "No se pudo cargar la textura backgroundTwo.png\n";
        }
        quit.setTexture(&quitTexture);
        backgroundOne.setTexture(backgroundTextureOne);
        backgroundTwo.setTexture(backgroundTextureTwo);
        backgroundTwo.setPosition(0.f, 0.f);
        currentScreen = 1;
        lastClickTime = -1.f;
    }
    Game(sf::RenderWindow& newWindow, int newCurrentScreen) : window(newWindow) {
        button.setSize(sf::Vector2f(300.f, 100.f));
        button.setFillColor(sf::Color::Blue);
        button.setOrigin(150.f, 50.f);
        button.setPosition(400.f, 430.f);
        button.setOutlineThickness(1.f);
        button.setOutlineColor(sf::Color::Yellow);
        quit.setSize(sf::Vector2f(50.f, 50.f));
        quit.setPosition(5.f, 5.f);
        quit.setOutlineThickness(3.f);
        quit.setOutlineColor(sf::Color::Transparent);
        if (!font.loadFromFile("assets/fonts/m6x11plus.ttf")) {
            std::cerr << "No se pudo cargar la fuente aptos.ttf\n";
        }
        if (!quitTexture.loadFromFile("assets/textures/Quit.png")) {
            quitTexture.loadFromFile("assets/textures/thumbnail.png");
            std::cerr << "No se pudo cargar la textura Quit.png\n";
        }
        if (!backgroundTextureOne.loadFromFile("assets/textures/backgroundOne.jpg")) {
            backgroundTextureOne.loadFromFile("assets/textures/thumbnail.png");
            std::cerr << "No se pudo cargar la textura backgroundOne.png\n";
        }
        if (!backgroundTextureTwo.loadFromFile("assets/textures/backgroundTwo.jpg")) {
            backgroundTextureTwo.loadFromFile("assets/textures/thumbnail.png");
            std::cerr << "No se pudo cargar la textura backgroundTwo.png\n";
        }
        scoreText.setFont(font);
        movesText.setFont(font);
        gameFinish.setFont(font);
        scoreText.setString("Hello World");
        scoreText.setCharacterSize(50);
        scoreText.setFillColor(sf::Color::Green);
        scoreText.setStyle(sf::Text::Bold | sf::Text::Italic);
        scoreText.setOutlineThickness(2.f);
        scoreText.setOutlineColor(sf::Color::Black);
        scoreText.setPosition(sf::Vector2f(600.f, 100.f));
        movesText.setString("Hello World");
        movesText.setCharacterSize(50);
        movesText.setFillColor(sf::Color::Green);
        movesText.setStyle(sf::Text::Bold | sf::Text::Italic);
        movesText.setOutlineThickness(2.f);
        movesText.setOutlineColor(sf::Color::Black);
        movesText.setPosition(sf::Vector2f(600.f, 200.f));
        scoreText.setString("El Juego Termino");
        scoreText.setCharacterSize(50);
        scoreText.setFillColor(sf::Color::Green);
        scoreText.setStyle(sf::Text::Bold | sf::Text::Italic);
        scoreText.setOutlineThickness(2.f);
        scoreText.setOutlineColor(sf::Color::Black);
        scoreText.setPosition(sf::Vector2f(600.f, 100.f));
        quit.setTexture(&quitTexture);
        backgroundOne.setTexture(backgroundTextureOne);
        backgroundTwo.setTexture(backgroundTextureTwo);
        currentScreen = newCurrentScreen;
        lastClickTime = -1.f;
    }
    ~Game() {}

    void run() {
        setBackgrounds();
        window.setFramerateLimit(60);
        while (window.isOpen()) {
            if (currentScreen == 1)
                firstScreen();
            else if (currentScreen == 2)
                secondScreen();

            drawScreen();
        }
    }
    void setBackgrounds() {
        sf::Vector2u textureSize1 = backgroundTextureOne.getSize();
        sf::Vector2u windowSize = window.getSize();
        backgroundOne.setScale(
            float(windowSize.x) / textureSize1.x,
            float(windowSize.y) / textureSize1.y
        );

        sf::Vector2u textureSize2 = backgroundTextureTwo.getSize();
        backgroundTwo.setScale(
            float(windowSize.x) / textureSize2.x,
            float(windowSize.y) / textureSize2.y
        );
    }
    void firstScreen() {
        sf::Event event;
        sf::Vector2i mousePosInt = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosition(static_cast<float>(mousePosInt.x), static_cast<float>(mousePosInt.y));
        if (button.getGlobalBounds().contains(mousePosition)) {
            button.setFillColor(sf::Color::Green);
            button.setOutlineThickness(1.f);
            button.setOutlineColor(sf::Color::Yellow);
        } else if (quit.getGlobalBounds().contains(mousePosition)) {
            quit.setOutlineColor(sf::Color::Green);
        } else {
            button.setFillColor(sf::Color::Blue);
            button.setOutlineColor(sf::Color::Blue);
            quit.setOutlineColor(sf::Color::Transparent);
        }
        while (window.pollEvent(event)) {
            if ((event.type == sf::Event::Closed)) {
                window.close();
                printf("FIN DEL PROGRAMA");
            }
            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (button.getGlobalBounds().contains(mousePosition)) {
                    currentScreen = 2;
                    printf("IR PANTALLA 2\n");
                    board.initialize();
                } else if (quit.getGlobalBounds().contains(mousePosition)) {
                    window.close();
                    printf("FIN DEL PROGRAMA");
                }
            }
        }
    }
    void secondScreen() {
        sf::Event event;
        sf::Vector2i mousePosInt = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosition(static_cast<float>(mousePosInt.x), static_cast<float>(mousePosInt.y));
        std::string score = std::to_string(board.getScore());
        std::string moves = std::to_string(board.getMovesAllowed());

        scoreText.setString(score);
        movesText.setString(moves);

        if (board.getMovesAllowed() == 0)
            currentScreen == 3;
        if (button.getGlobalBounds().contains(mousePosition)) {
            button.setFillColor(sf::Color::Green);
        } else {
            button.setFillColor(sf::Color::Blue);
        }
        board.ifMouseIsOn(mousePosition);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                currentScreen = 1;
                printf("IR PANTALLA 1\n");
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                board.select(mousePosition);
                std::cout << "Clic\n";
            }
        }
    }
    void thirdScreen() {
        sf::Event event;
        sf::Vector2i mousePosInt = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosition(static_cast<float>(mousePosInt.x), static_cast<float>(mousePosInt.y));

    }
    void drawScreen() {
        window.clear();
        if (currentScreen == 1) {
            window.draw(backgroundOne);
            window.draw(button);
            window.draw(quit);
        } else if (currentScreen == 2) {
            if (board.getMovesAllowed() != 0) {
                window.draw(backgroundTwo);
                board.printBoard(window);
                window.draw(scoreText);
                window.draw(movesText);
            } else {
                window.draw(backgroundTwo);
                window.draw(scoreText);
            }
        } else if (currentScreen == 3) {
            window.draw(backgroundOne);
        }
        window.display();
    }
    void drawScreenTwo() {
        window.clear();

        if (currentScreen == 0) { // Options
            window.draw(backgroundOne);
        } else if (currentScreen == 1) { // Main menu
            window.draw(backgroundOne);
            window.draw(button);
            window.draw(quit);
        } else if (currentScreen == 2) { // Game
            window.draw(backgroundTwo);
            board.printBoard(window);
            window.draw(scoreText);
            window.draw(movesText);
        } else if (currentScreen == 3) { // Game over
            window.draw(backgroundTwo);
            window.draw(scoreText);
        }

        window.display();
    }
};

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Proyecto Dominique");
    Game gameOne(window, 1);
    gameOne.run();
    return 0;
}