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

    sf::Sprite sprite;
    std::function<void()> onClick;
    sf::Texture buttonTexture;


public:
    Button(float x, float y, float width, float height,const std::string& texturePath)
            : onClick(nullptr) {


        if (!buttonTexture.loadFromFile(texturePath)) {
            // Manejar un error si la carga de textura falla
            std::cerr << "Error al cargar la textura desde " << texturePath << std::endl;
        }

        sprite.setTexture(buttonTexture);
        sprite.setPosition(x, y);
        sprite.setScale(width / buttonTexture.getSize().x, height / buttonTexture.getSize().y);

        onClick = []() {};
    }

    void handleEvent(sf::Event event, sf::Vector2f mousePosition) {
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            if (sprite.getGlobalBounds().contains(mousePosition)) {
                // Llama a la función de clic si el botón se presiona
                onClick();
            }
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

        target.draw(sprite, states);
        ;
    }

    void setOnClick(std::function<void()> clickFunction) {
        onClick = clickFunction;
    }

    sf::FloatRect getGlobalBounds() const {
        return sprite.getGlobalBounds();
    }

};
#endif //BD2_PROJECT1_BUTTON_H