
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "record.h"
#include "button.h"
#include "textinput.h"


int main(){



    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Define las dimensiones de la tabla
    const int numRows = 10;
    const int numColumns = 6;
    const float cellWidth = 100.f;
    const float cellHeight = 30.f;

    // Crear una ventana de SFML
    sf::RenderWindow window(sf::VideoMode(1100, 720), "Tabla de Registros");
    TextInput input(240, 42, 858, 300);
    std::string savedText;

    Button button_execute(180.f, 280.f, 50.f, 50.f,"../interfaz/execute.png");
    Button button_equis(1040.f, 2.f, 35.f, 35.f,"../interfaz/close-icon-30.png");
    Button button_tabla_1(40.f, 100.f, 60.f, 50.f,"../interfaz/tabla.png");
    Button button_tabla_2(40.f, 200.f, 60.f, 50.f,"../interfaz/tabla.png");
    sf::RectangleShape rectangle_arriba;
    rectangle_arriba.setSize(sf::Vector2f(1100, 8));
    rectangle_arriba.setPosition(0, 0);
    rectangle_arriba.setFillColor(sf::Color(236, 190, 58));
    rectangle_arriba.setOutlineThickness(2);
    rectangle_arriba.setOutlineColor(sf::Color::Black);

    sf::RectangleShape rectangle_abajo;
    rectangle_abajo.setSize(sf::Vector2f(1100, 40));
    rectangle_abajo.setPosition(0, 682);
    rectangle_abajo.setFillColor(sf::Color(141, 105, 0));
    rectangle_abajo.setOutlineThickness(2);
    rectangle_abajo.setOutlineColor(sf::Color::Black);

    sf::RectangleShape rectangle_medio;
    rectangle_arriba.setSize(sf::Vector2f(1100, 40));
    rectangle_arriba.setPosition(0, 0);
    rectangle_arriba.setFillColor(sf::Color(236, 190, 58));




    button_execute.setOnClick([&input, &savedText]() {
        std::string text = input.getText();
        savedText = text;
        std::cout << "Botón clickeado. Texto guardado: " << savedText << std::endl;

        input.clearText();
    });



    // Crear una fuente para el texto
    sf::Font font;
    if (!font.loadFromFile("../interfaz/Arial.ttf")) {
        std::cerr << "No se pudo cargar la fuente Arial.ttf" << std::endl;
        return 1;
    }

    // Crear objetos Record y almacenarlos en un vector
    std::vector<Record> records;
    for (int i = 0; i < numRows; ++i) {
        Record record('A' + i, "Texto " + std::to_string(i), i * 10, i * 20, i * 30, i * 40);
        records.push_back(record);
    }

    // Nombres de las cabeceras
    std::vector<std::string> columnHeaders = {"Char", "String", "Int1", "Int2", "Int3", "Int4"};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            else {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (button_equis.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        window.close();
                    }}

                button_execute.handleEvent(event, sf::Vector2f(sf::Mouse::getPosition(window)));
                input.handleEvent(event, sf::Vector2f(sf::Mouse::getPosition(window)));
            }

        }

        window.clear(sf::Color(255, 240, 196));


        // Dibujar las cabeceras de las columnas
        for (int j = 0; j < numColumns; ++j) {
            sf::RectangleShape headerCell(sf::Vector2f(cellWidth, cellHeight));
            headerCell.setPosition((j * cellWidth)+100, 360);
            headerCell.setOutlineColor(sf::Color::Black);
            headerCell.setOutlineThickness(1);
            window.draw(headerCell);

            sf::Text headerText;
            headerText.setFont(font);
            headerText.setString(columnHeaders[j]);
            headerText.setCharacterSize(14);
            headerText.setFillColor(sf::Color::Black);
            headerText.setPosition((j * cellWidth )+ 110, 360);
            window.draw(headerText);
        }

        // Dibujar los registros en la tabla
        for (int i = 0; i < numRows; ++i) {
            std::vector<std::string> recordValues = records[i].toVector();
            for (int j = 0; j < numColumns; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
                cell.setPosition((j * cellWidth)+100, ((i + 1) * cellHeight)+350); // Offset por la cabecera
                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(1);
                window.draw(cell);

                sf::Text text;
                text.setFont(font);
                text.setString(recordValues[j]);
                text.setCharacterSize(14);
                text.setFillColor(sf::Color::Black);
                text.setPosition((j * cellWidth) + 110, ((i + 1) * cellHeight + 10)+350); // Offset por la cabecera
                window.draw(text);
            }
        }
        window.draw(button_execute);
        window.draw(rectangle_arriba);
        window.draw(rectangle_abajo);
        window.draw(button_equis);
        window.draw(button_tabla_1);
        window.draw(button_tabla_2);

       window.draw(input);


        window.display();
    }
return 0;

}

