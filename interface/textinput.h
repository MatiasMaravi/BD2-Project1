//
// Created by JLeandroJM on 16/09/23.
//

#ifndef BD2_PROJECT1_TEXTINPUT_H
#define BD2_PROJECT1_TEXTINPUT_H


#include <SFML/Graphics.hpp>
#include <iostream>

class TextInput : public sf::Drawable {
private:
    sf::RectangleShape rectangle;
    sf::Text text;
    sf::Font font;
    std::string inputText;
    bool isPassword;
    bool isSelected;


public:
    TextInput(float x, float y, float width, float height, bool password = false)
            : isPassword(password), isSelected(false) {
        rectangle.setPosition(x, y);
        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineThickness(2);
        rectangle.setOutlineColor(sf::Color::Black);

        if (!font.loadFromFile("../interfaz/Arial.ttf")) {
            std::cerr << "No se pudo cargar la fuente Arial.ttf" << std::endl;
        }

        text.setFont(font);
        text.setCharacterSize(static_cast<unsigned int>(height * 0.09f));
        text.setFillColor(sf::Color::Black);
        text.setPosition(x + 5, y);

        if (isPassword) {
            // If it's a password field, show asterisks instead of text
            text.setString("");
        }
    }

    void handleEvent(sf::Event event, sf::Vector2f mousePosition) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (rectangle.getGlobalBounds().contains(mousePosition)) {
                isSelected = true;
            } else {
                isSelected = false;
            }
        } else if (event.type == sf::Event::TextEntered && isSelected) {
            if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                inputText += static_cast<char>(event.text.unicode);
            } else if (event.text.unicode == 8 && !inputText.empty()) {
                inputText.pop_back();
            } else if (event.text.unicode == '\n') { // Enter
                inputText += '\n'; // Agregar una nueva línea
            }
            updateText();
        }
    }


    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(rectangle, states);
        target.draw(text, states);
    }

    std::string getText() const {
        return inputText;
    }

    void clearText() {
        inputText.clear();
        updateText();
    }

private:
    void updateText() {
        text.setString(inputText);
    }
};

#endif //BD2_PROJECT1_TEXTINPUT_H
