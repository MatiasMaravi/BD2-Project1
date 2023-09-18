//
// Created by JLeandroJM on 16/09/23.
//

#ifndef BD2_PROJECT1_BUTTON_H
#define BD2_PROJECT1_BUTTON_H
// Button.hpp
#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <functional>

class Button : public sf::Drawable {
private:
    sf::RectangleShape rectangle;
    sf::Text text;
    sf::Font font;
    std::function<void()> onClick;

public:
    Button(float x, float y, float width, float height, const std::string& buttonText)
            : onClick(nullptr) {
        rectangle.setPosition(x, y);
        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setFillColor(sf::Color::Blue);

        if (!font.loadFromFile("../interfaz/Arial.ttf")) {
            std::cerr << "No se pudo cargar la fuente Arial.ttf" << std::endl;
        }

        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setString(buttonText);
        text.setPosition(x + 10, y + 10); // Ajusta la posición del texto dentro del botón

        // Añade un evento de clic vacío por defecto
        onClick = []() {};
    }

    void handleEvent(sf::Event event, sf::Vector2f mousePosition) {
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            if (rectangle.getGlobalBounds().contains(mousePosition)) {
                // Llama a la función de clic si el botón se presiona
                onClick();
            }
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(rectangle, states);
        target.draw(text, states);
    }

    void setOnClick(std::function<void()> clickFunction) {
        onClick = clickFunction;
    }
};
#endif //BD2_PROJECT1_BUTTON_H
