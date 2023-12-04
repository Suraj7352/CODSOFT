#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(400, 300), "Number Guessing Game");

    // Seed for random number generation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate a random number between 1 and 100 for each game
    int targetNumber = std::rand() % 100 + 1;

    // GUI elements
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/arial.ttf")) {
        std::cerr << "Error loading font file." << std::endl;
        return -1;
    }

    sf::Text message;
    message.setFont(font);
    message.setCharacterSize(20);
    message.setPosition(10, 10);

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(20);
    inputText.setPosition(10, 50);

    sf::RectangleShape submitButton(sf::Vector2f(100, 40));
    submitButton.setPosition(10, 200);
    submitButton.setFillColor(sf::Color::Green);

    sf::Text submitButtonText;
    submitButtonText.setFont(font);
    submitButtonText.setCharacterSize(16);
    submitButtonText.setPosition(30, 210);
    submitButtonText.setString("Submit");

    sf::RectangleShape restartButton(sf::Vector2f(100, 40));
    restartButton.setPosition(120, 200);
    restartButton.setFillColor(sf::Color::Blue);

    sf::Text restartButtonText;
    restartButtonText.setFont(font);
    restartButtonText.setCharacterSize(16);
    restartButtonText.setPosition(140, 210);
    restartButtonText.setString("Restart");

    // Number buttons
    sf::RectangleShape numberButtons[10];
    sf::Text numberButtonTexts[10];

    for (int i = 0; i < 10; ++i) {
        numberButtons[i] = sf::RectangleShape(sf::Vector2f(40, 40));
        numberButtons[i].setPosition(120 + (i % 5) * 50, 50 + (i / 5) * 50);
        numberButtons[i].setFillColor(sf::Color::Yellow);

        numberButtonTexts[i].setFont(font);
        numberButtonTexts[i].setCharacterSize(16);
        numberButtonTexts[i].setPosition(140 + (i % 5) * 50, 60 + (i / 5) * 50);
        numberButtonTexts[i].setString(std::to_string(i));
    }

    // Game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                // Handle text input events
                if (std::isdigit(event.text.unicode)) {
                    inputText.setString(inputText.getString() + static_cast<char>(event.text.unicode));
                } else if (event.text.unicode == 13) { // Enter key pressed
                    // Check the guessed number
                    int guessedNumber = std::stoi(inputText.getString().toAnsiString());
                    if (guessedNumber == targetNumber) {
                        message.setString("Congratulations! You guessed the correct number!");
                    } else if (guessedNumber < targetNumber) {
                        message.setString("Too low! Try again.");
                    } else {
                        message.setString("Too high! Try again.");
                    }

                    // Generate a new random number for the next round
                    targetNumber = std::rand() % 100 + 1;
                    inputText.setString("");
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                // Check if the submit button is pressed
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (submitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    // Check the guessed number
                    int guessedNumber = std::stoi(inputText.getString().toAnsiString());
                    if (guessedNumber == targetNumber) {
                        message.setString("Congratulations! You guessed the correct number!");
                    } else if (guessedNumber < targetNumber) {
                        message.setString("Too low! Try again.");
                    } else {
                        message.setString("Too high! Try again.");
                    }

                    // Generate a new random number for the next round
                    targetNumber = std::rand() % 100 + 1;
                    inputText.setString("");
                }

                // Check if the restart button is pressed
                if (restartButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    // Restart the game by generating a new random number
                    targetNumber = std::rand() % 100 + 1;
                    message.setString("Guess a number between 1 and 100:");
                    inputText.setString("");
                }

                // Check if a number button is pressed
                for (int i = 0; i < 10; ++i) {
                    if (numberButtons[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        inputText.setString(inputText.getString() + std::to_string(i));
                    }
                }
            }
        }

        // Clear the window
        window.clear();

        // Draw GUI elements
        window.draw(message);
        window.draw(inputText);
        window.draw(submitButton);
        window.draw(submitButtonText);
        window.draw(restartButton);
        window.draw(restartButtonText);

        // Draw number buttons
        for (int i = 0; i < 10; ++i) {
            window.draw(numberButtons[i]);
            window.draw(numberButtonTexts[i]);
        }

        // Display the window
        window.display();
    }

    return 0;
}
