#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

const int tetrominoes[7][16] = {
    {0,0,0,0, 1,1,1,1, 0,0,0,0, 0,0,0,0}, // I
    {1,0,0,0, 1,1,1,0, 0,0,0,0, 0,0,0,0}, // J
    {0,0,1,0, 1,1,1,0, 0,0,0,0, 0,0,0,0}, // L
    {0,1,1,0, 0,1,1,0, 0,0,0,0, 0,0,0,0}, // O
    {0,1,1,0, 1,1,0,0, 0,0,0,0, 0,0,0,0}, // S
    {0,1,0,0, 1,1,1,0, 0,0,0,0, 0,0,0,0}, // T
    {1,1,0,0, 0,1,1,0, 0,0,0,0, 0,0,0,0}  // Z
};

int rotateIndex(int x, int y, int rotation) {
    switch (rotation % 4) {
        case 0: return y * 4 + x;
        case 1: return 12 + y - (x * 4);
        case 2: return 15 - (y * 4) - x;
        case 3: return 3 - y + (x * 4);
    }
    return 0;
}

bool checkCollision(int pieceID, int rotation, int gridX, int gridY, const int board[20][10]) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            int pi = rotateIndex(x, y, rotation);
            if (tetrominoes[pieceID][pi] != 0) {
                int targetX = gridX + x;
                int targetY = gridY + y;

                if (targetX < 0 || targetX >= 10 || targetY >= 20) return false;
                if (targetY >= 0 && board[targetY][targetX] != 0) return false;
            }
        }
    }
    return true;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));

    sf::RenderWindow window(sf::VideoMode(300, 600), "Tetris with Score!");
    window.setFramerateLimit(60);

    // --- OUR NEW SAFETY NET ---
    sf::Font font;
    bool fontLoaded = font.loadFromFile("PressStart2P.ttf"); 

    sf::Text scoreText;
    if (fontLoaded) {
        scoreText.setFont(font);
        scoreText.setCharacterSize(20);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10.f, 10.f);
    }

    int board[20][10] = {0};

    int currentPiece = std::rand() % 7;
    int currentRotation = 0;
    int pieceX = 3;
    int pieceY = 0;

    sf::Clock timer;
    float dropDelay = 0.5f;
    int score = 0;

    bool isGameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (isGameOver) {
                    if (event.key.code == sf::Keyboard::R) {
                        for (int r = 0; r < 20; r++) {
                            for (int c = 0; c < 10; c++) board[r][c] = 0;
                        }
                        score = 0;
                        isGameOver = false;
                        timer.restart();
                    }
                }
                else {
                    if (event.key.code == sf::Keyboard::Left) {
                        if (checkCollision(currentPiece, currentRotation, pieceX - 1, pieceY, board)) pieceX--;
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        if (checkCollision(currentPiece, currentRotation, pieceX + 1, pieceY, board)) pieceX++;
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        if (checkCollision(currentPiece, currentRotation + 1, pieceX, pieceY, board)) currentRotation++;
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        if (checkCollision(currentPiece, currentRotation, pieceX, pieceY + 1, board)) pieceY++;
                    }
                    if (event.key.code == sf::Keyboard::Space) {
                        while (checkCollision(currentPiece, currentRotation, pieceX, pieceY + 1, board)) pieceY++;
                    }
                }
            }
        }

        if (!isGameOver && timer.getElapsedTime().asSeconds() > dropDelay) {
            if (checkCollision(currentPiece, currentRotation, pieceX, pieceY + 1, board)) {
                pieceY++;
            } else {
                for (int y = 0; y < 4; y++) {
                    for (int x = 0; x < 4; x++) {
                        int pi = rotateIndex(x, y, currentRotation);
                        if (tetrominoes[currentPiece][pi] != 0) {
                            board[pieceY + y][pieceX + x] = currentPiece + 1;
                        }
                    }
                }

                for (int r = 19; r >= 0; r--) {
                    bool lineFull = true;
                    for (int c = 0; c < 10; c++) {
                        if (board[r][c] == 0) { lineFull = false; break; }
                    }
                    if (lineFull) {
                        score += 100;
                        for (int pull = r; pull > 0; pull--) {
                            for (int c = 0; c < 10; c++) board[pull][c] = board[pull - 1][c];
                        }
                        for (int c = 0; c < 10; c++) board[0][c] = 0;
                        r++; 
                    }
                }

                currentPiece = std::rand() % 7;
                currentRotation = 0;
                pieceX = 3;
                pieceY = 0;

                if (!checkCollision(currentPiece, currentRotation, pieceX, pieceY, board)) {
                    isGameOver = true;
                }
            }
            timer.restart();
        }

        // --- RENDER ---
        window.clear(sf::Color::Black);

        // Draw a subtle background grid representing all cell outlines
        sf::RectangleShape gridCell(sf::Vector2f(30.f, 30.f));
        gridCell.setFillColor(sf::Color::Transparent);
        gridCell.setOutlineThickness(-1.f); // Inner outline to prevent offset
        gridCell.setOutlineColor(sf::Color(40, 40, 40)); // Subtle dark grey outline

        for (int r = 0; r < 20; r++) {
            for (int c = 0; c < 10; c++) {
                gridCell.setPosition(c * 30.f, r * 30.f);
                window.draw(gridCell);
            }
        }

        // Setup filled block style with a black outline border
        sf::RectangleShape block(sf::Vector2f(30.f, 30.f));
        block.setOutlineThickness(-1.f);
        block.setOutlineColor(sf::Color::Black);

        sf::Color colors[8] = {
            sf::Color::Black,
            sf::Color::Cyan, sf::Color::Blue, sf::Color(255, 165, 0),
            sf::Color::Yellow, sf::Color::Green, sf::Color::Magenta, sf::Color::Red
        };

        for (int r = 0; r < 20; r++) {
            for (int c = 0; c < 10; c++) {
                if (board[r][c] != 0) {
                    block.setFillColor(isGameOver ? sf::Color(180, 0, 0) : colors[board[r][c]]);
                    block.setPosition(c * 30.f, r * 30.f);
                    window.draw(block);
                }
            }
        }

        if (!isGameOver) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    int pi = rotateIndex(x, y, currentRotation);
                    if (tetrominoes[currentPiece][pi] != 0) {
                        block.setFillColor(colors[currentPiece + 1]);
                        block.setPosition((pieceX + x) * 30.f, (pieceY + y) * 30.f);
                        window.draw(block);
                    }
                }
            }
        }

        // ONLY draw text if the font actually succeeded in loading!
        if (fontLoaded) {
            std::stringstream ss;
            if (isGameOver) {
                ss << "GAME OVER\nScore: " << score << "\nPress 'R'";
                scoreText.setPosition(80.f, 250.f);
            } else {
                ss << "Score: " << score;
                scoreText.setPosition(10.f, 10.f);
            }
            scoreText.setString(ss.str());
            window.draw(scoreText);
        }

        window.display();
    }
    return 0;
}