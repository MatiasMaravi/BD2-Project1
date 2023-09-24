//
// Created by JLeandroJM on 24/09/23.
//

#ifndef BD2_PROJECT1_LABEL_H
#define BD2_PROJECT1_LABEL_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Label : public sf::Drawable {
private:
    sf::Text text;
    sf::Font font;
    sf::Color textColor;

public:
    Label(float x, float y, const std::string& labelText, unsigned int fontSize, const sf::Color& color)
            : textColor(color) {
        if (!font.loadFromFile("../interfaz/Arial.ttf")) {
            // Manejar un error si no se puede cargar la fuente
            std::cerr << "Error al cargar la fuente." << std::endl;
        }

        text.setFont(font);
        text.setString(labelText);
        text.setCharacterSize(fontSize);
        text.setFillColor(textColor);
        text.setPosition(x, y);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(text, states);
    }

    // Puedes agregar más funciones para modificar el texto, el tamaño, el color, etc., según tus necesidades.
};

#endif //BD2_PROJECT1_LABEL_H
