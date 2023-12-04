#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cmath>

// Function declaration
double evaluateExpression(const std::string& expression);

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 600), "Calculator");

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/arial.ttf")) {
        std::cerr << "Font not found. Please provide the correct path to arial.ttf." << std::endl;
        return -1;
    }

    sf::Text displayText("", font, 40);
    displayText.setPosition(20, 20);
    displayText.setFillColor(sf::Color::Blue);

    std::ostringstream displayString;
    std::string expression;
    bool hasError = false;

    sf::RectangleShape numericButtons[10];
    for (int i = 0; i < 10; ++i) {
        numericButtons[i].setSize(sf::Vector2f(80, 80));
        numericButtons[i].setPosition((i % 3) * 100, (i / 3 + 3) * 100);
        numericButtons[i].setOutlineThickness(2);
        numericButtons[i].setOutlineColor(sf::Color::Black);
        numericButtons[i].setFillColor(sf::Color::White);
    }

    char operationSymbols[] = {'+', '-', '*', '/', '=', 'C'};  // Added 'C' for clear
    sf::RectangleShape operationButtons[6];  // Updated size to 6
    for (int i = 0; i < 6; ++i) {
        operationButtons[i].setSize(sf::Vector2f(80, 80));
        operationButtons[i].setPosition(300, i * 100);
        operationButtons[i].setOutlineThickness(2);
        operationButtons[i].setOutlineColor(sf::Color::Black);
        operationButtons[i].setFillColor(sf::Color::White);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                for (int i = 0; i < 10; ++i) {
                    if (numericButtons[i].getGlobalBounds().contains(mouseX, mouseY)) {
                        displayString << i;
                        expression += std::to_string(i);
                        break;
                    }
                }

                for (int i = 0; i < 6; ++i) {  // Updated to 6
                    if (operationButtons[i].getGlobalBounds().contains(mouseX, mouseY)) {
                        if (operationSymbols[i] == '=') {
                            try {
                                double result = evaluateExpression(expression);
                                displayString.str("");
                                displayString << result;
                                expression = std::to_string(result);
                            } catch (const std::exception& e) {
                                displayString.str("Error");
                                hasError = true;
                            }
                        } else if (operationSymbols[i] == 'C') {
                            displayString.str("");
                            expression.clear();
                            hasError = false;
                        } else {
                            displayString << operationSymbols[i];
                            expression += operationSymbols[i];
                        }
                        break;
                    }
                }
            }
        }

        window.clear();

        for (int i = 0; i < 10; ++i) {
            window.draw(numericButtons[i]);
            sf::Text buttonText(std::to_string(i), font, 40);
            buttonText.setPosition((i % 3) * 100 + 30, (i / 3 + 3) * 100 + 15);
            buttonText.setFillColor(sf::Color::Blue);
            window.draw(buttonText);
        }

        for (int i = 0; i < 6; ++i) {  // Updated to 6
            window.draw(operationButtons[i]);
            sf::Text operationText(std::string(1, operationSymbols[i]), font, 40);
            operationText.setPosition(315, i * 100 + 15);
            operationText.setFillColor(sf::Color::Blue);
            window.draw(operationText);
        }

        if (!hasError) {
            displayText.setString(displayString.str());
            window.draw(displayText);
        } else {
            sf::Text errorText("Error", font, 40);
            errorText.setPosition(20, 20);
            errorText.setFillColor(sf::Color::Red);
            window.draw(errorText);
        }

        window.display();
    }

    return 0;
}

double evaluateExpression(const std::string& expression) {
    std::istringstream iss(expression);
    double result;
    iss >> result;

    char op;
    while (iss >> op) {
        double operand;
        iss >> operand;

        switch (op) {
            case '+':
                result += operand;
                break;
            case '-':
                result -= operand;
                break;
            case '*':
                result *= operand;
                break;
            case '/':
                if (operand != 0) {
                    result /= operand;
                } else {
                    throw std::runtime_error("Division by zero");
                }
                break;
            default:
                throw std::runtime_error("Invalid operator");
        }
    }

    return result;
}
