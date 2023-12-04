#include <SFML/Graphics.hpp>
#include <iostream>

enum class Player { None, X, O };

class TicTacToe {
public:
    TicTacToe() : currentPlayer(Player::X), winner(Player::None) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = Player::None;
            }
        }
    }

    void handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (winner != Player::None) {
                // If the game is already won, reset the board
                resetGame();
            } else {
                // Get the clicked position and make a move
                int x = event.mouseButton.x / 100;
                int y = event.mouseButton.y / 100;
                makeMove(x, y);
            }
        }
    }

    void update() {
        // Check for a winner after each move
        checkWinner();
    }

    void draw(sf::RenderWindow& window) const {
        // Draw the game board
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                sf::RectangleShape cell(sf::Vector2f(100, 100));
                cell.setPosition(i * 100, j * 100);
                cell.setOutlineThickness(2);
                cell.setOutlineColor(sf::Color::Black);
                window.draw(cell);

                if (board[i][j] == Player::X) {
                    drawX(window, i, j);
                } else if (board[i][j] == Player::O) {
                    drawO(window, i, j);
                }
            }
        }

        // Display the winner
        if (winner != Player::None) {
            sf::Font font;
            font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/arial.ttf");

            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(50);
            text.setFillColor(sf::Color::Red);
            text.setStyle(sf::Text::Bold);

            if (winner == Player::X) {
                text.setString("Player X wins!");
            } else if (winner == Player::O) {
                text.setString("Player O wins!");
            } else {
                text.setString("It's a draw!");
            }

            text.setPosition(20, 320);
            window.draw(text);
        }
    }

private:
    Player currentPlayer;
    Player winner;
    Player board[3][3];

    void makeMove(int x, int y) {
        // Check if the cell is empty and the game is not already won
        if (board[x][y] == Player::None && winner == Player::None) {
            board[x][y] = currentPlayer;
            togglePlayer();
        }
    }

    void togglePlayer() {
        currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
    }

    void drawX(sf::RenderWindow& window, int x, int y) const {
        sf::VertexArray lines(sf::Lines, 4);

        lines[0].position = sf::Vector2f(x * 100 + 20, y * 100 + 20);
        lines[1].position = sf::Vector2f((x + 1) * 100 - 20, (y + 1) * 100 - 20);

        lines[2].position = sf::Vector2f((x + 1) * 100 - 20, y * 100 + 20);
        lines[3].position = sf::Vector2f(x * 100 + 20, (y + 1) * 100 - 20);

        lines[0].color = sf::Color::Black;
        lines[1].color = sf::Color::Black;
        lines[2].color = sf::Color::Black;
        lines[3].color = sf::Color::Black;

        window.draw(lines);
    }

    void drawO(sf::RenderWindow& window, int x, int y) const {
        sf::CircleShape circle(40);
        circle.setPosition(x * 100 + 10, y * 100 + 10);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::Black);
        circle.setFillColor(sf::Color::Transparent);

        window.draw(circle);
    }

    void checkWinner() {
        // Check rows, columns, and diagonals for a winner
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] != Player::None && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
                winner = board[i][0];
                return;
            }

            if (board[0][i] != Player::None && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
                winner = board[0][i];
                return;
            }
        }

        if (board[0][0] != Player::None && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
            winner = board[0][0];
            return;
        }

        if (board[0][2] != Player::None && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
            winner = board[0][2];
            return;
        }

        // Check for a draw
        bool draw = true;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == Player::None) {
                    draw = false;
                    break;
                }
            }
        }

        if (draw) {
            winner = Player::None;
        }
    }

    void resetGame() {
        currentPlayer = Player::X;
        winner = Player::None;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = Player::None;
            }
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 400), "Tic Tac Toe");

    TicTacToe game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            game.handleEvent(event);
        }

        game.update();

        window.clear(sf::Color::White);
        game.draw(window);
        window.display();
    }

    return 0;
}
