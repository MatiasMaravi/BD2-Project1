
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "button.h"
#include "textinput.h"
#include "../Parser/Parser.hpp"

int main(){
    // Inicializa la semilla del generador de números aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Define las dimensiones de la tabla
    const int numRows = 10;
    const int numColumns = 6;
    const float cellWidth = 100.f;
    const float cellHeight = 30.f;

    // Crear una ventana de SFML
    sf::RenderWindow window(sf::VideoMode(1100, 700), "Tabla de Registros");
    TextInput input(200, 40, 870, 300);
    std::string savedText;
    Button button(500, 0, 100, 40, "Execute");

    button.setOnClick([&input, &savedText]() {
        std::string text = input.getText();
        savedText = text;
        std::cout << "Botón clickeado. Texto guardado: " << savedText << std::endl;
        Scanner scanner(savedText.c_str());
        Parser parser(&scanner);
        if(!parser.parse()) cout << "Parse error" << endl;
        else cout << "Parse success" << endl;
        input.clearText();
    });


    // Crear una fuente para el texto
    sf::Font font;
    if (!font.loadFromFile("../interfaz/Arial.ttf")) {
        std::cerr << "No se pudo cargar la fuente Arial.ttf" << std::endl;
        return 1;
    }

    // Crear objetos Record y almacenarlos en un vector
//     std::vector<Record> records;
//     for (int i = 0; i < numRows; ++i) {
//         Record record('A' + i, "Texto " + std::to_string(i), i * 10, i * 20, i * 30, i * 40);
//         records.push_back(record);
//     }
// // 
    // Nombres de las cabeceras
    std::vector<std::string> columnHeaders = {"Char", "String", "Int1", "Int2", "Int3", "Int4"};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }else {
                button.handleEvent(event, sf::Vector2f(sf::Mouse::getPosition(window)));
                input.handleEvent(event, sf::Vector2f(sf::Mouse::getPosition(window)));
            }

        }

        window.clear(sf::Color::White);


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
        // for (int i = 0; i < numRows; ++i) {
        //     std::vector<std::string> recordValues = records[i].toVector();
        //     for (int j = 0; j < numColumns; ++j) {
        //         sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
        //         cell.setPosition((j * cellWidth)+100, ((i + 1) * cellHeight)+350); // Offset por la cabecera
        //         cell.setOutlineColor(sf::Color::Black);
        //         cell.setOutlineThickness(1);
        //         window.draw(cell);

        //         sf::Text text;
        //         text.setFont(font);
        //         text.setString(recordValues[j]);
        //         text.setCharacterSize(14);
        //         text.setFillColor(sf::Color::Black);
        //         text.setPosition((j * cellWidth) + 110, ((i + 1) * cellHeight + 10)+350); // Offset por la cabecera
        //         window.draw(text);
        //     }
        // }
        window.draw(button);
        window.draw(input);

        window.display();
    }
return 0;

}

