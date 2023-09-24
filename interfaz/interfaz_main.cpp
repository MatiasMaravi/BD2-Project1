#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "button.h"
#include "textinput.h"
#include "label.h"
#include "interfaz_sequential.h"

using namespace std;

int main(){

    // Define las dimensiones de la tabla
    const int numRows = 7;
    const int numColumns = 6;
    const float cellWidth = 160.f;
    const float cellHeight = 30.f;

    // Crear una ventana de SFML
    sf::RenderWindow window(sf::VideoMode(1100, 720), "Tabla de Registros");
    TextInput input(240, 42, 858, 300);
    std::string savedText;
    const char* nombre_archivo;
    Button button_execute(180.f, 280.f, 50.f, 50.f,"../interfaz/execute.png");
    Button button_equis(1040.f, 2.f, 35.f, 35.f,"../interfaz/close-icon-30.png");
    Button button_tabla_1(40.f, 70.f, 50.f, 40.f,"../interfaz/tabla.png");
    Button button_tabla_2(40.f, 120.f, 50.f, 40.f,"../interfaz/tabla.png");
    Button button_tabla_3(40.f, 170.f, 50.f, 40.f,"../interfaz/tabla.png");
    Button button_tabla_4(40.f, 220.f, 50.f, 40.f,"../interfaz/tabla.png");
    Button button_limpiar(120.f, 280.f, 50.f, 50.f,"../interfaz/clear-icon-29.png");
    Label label(20.f, 12.f, "Mi SGBD", 20, sf::Color::Black);
    Label label_tabla_1(100.f, 80.f, "Tabla de 1k", 20, sf::Color::Black);
    Label label_tabla_2(100.f, 130.f, "Tabla de 10k", 20, sf::Color::Black);
    Label label_tabla_3(100.f, 180.f, "Tabla de 50k", 20, sf::Color::Black);
    Label label_tabla_4(100.f, 230.f, "Tabla de 100k", 20, sf::Color::Black);
    Label label_tiempo(100.f, 690.f, "Tiempo de ejecucion: ", 20, sf::Color::White);
    Label label_numero(700.f, 690.f, "Nro de filas: ", 20, sf::Color::White);
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
    std::size_t longitud = std::strlen(nombre_archivo);
    vector<Record> values;

    button_execute.setOnClick([&input, &savedText,&values,&button_limpiar]() {
        std::string text = input.getText();
        savedText = text;
        std::cout << "Botón clickeado. Texto guardado: " << savedText << std::endl;

        input.clearText();
      //  values  = ordenar_sequential();
      // values = buscar_sequential(246118);
      values = buscar_range_sequential(244196,264347);
        button_limpiar.setOnClick([&values]() {
            values.clear();
            cout<<"registros_limpios"<<endl;

        });


    });



    button_tabla_1.setOnClick([&nombre_archivo]() {
        nombre_archivo = "../CSV/datos_10.csv";
        std::cout<<nombre_archivo<<endl;
        std::size_t longitud = std::strlen(nombre_archivo);
        insertar_sequential(nombre_archivo);
        cout<<longitud;

    });

    button_tabla_2.setOnClick([&nombre_archivo]() {

        nombre_archivo = "../CSV/datos_1000.csv";
        std::cout<<nombre_archivo<<endl;
        std::size_t longitud = std::strlen(nombre_archivo);
        insertar_sequential(nombre_archivo);
        cout<<longitud;

    });

    button_tabla_3.setOnClick([&nombre_archivo]() {

        nombre_archivo = "../CSV/datos_50000.csv";
        std::cout<<nombre_archivo<<endl;
        std::size_t longitud = std::strlen(nombre_archivo);
        insertar_sequential(nombre_archivo);
        cout<<longitud;

    });

    button_tabla_4.setOnClick([&nombre_archivo]() {

        nombre_archivo = "../CSV/datos_100000.csv";
        std::cout<<nombre_archivo<<endl;
        std::size_t longitud = std::strlen(nombre_archivo);
        insertar_sequential(nombre_archivo);
        cout<<longitud;

    });


    // Crear una fuente para el texto
    sf::Font font;
    if (!font.loadFromFile("../interfaz/Arial.ttf")) {
        std::cerr << "No se pudo cargar la fuente Arial.ttf" << std::endl;
        return 1;
    }



    // Nombres de las cabeceras
    std::vector<std::string> columnHeaders = {"Player ID", "Short Name", "Value EUR", "Age", "Club Name", "Nationality Name"};

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
                button_tabla_1.handleEvent(event, sf::Vector2f(sf::Mouse::getPosition(window)));
                button_tabla_2.handleEvent(event, sf::Vector2f(sf::Mouse::getPosition(window)));
                button_tabla_3.handleEvent(event, sf::Vector2f(sf::Mouse::getPosition(window)));
                button_tabla_4.handleEvent(event, sf::Vector2f(sf::Mouse::getPosition(window)));
                button_limpiar.handleEvent(event, sf::Vector2f(sf::Mouse::getPosition(window)));
                input.handleEvent(event, sf::Vector2f(sf::Mouse::getPosition(window)));
            }

        }

        window.clear(sf::Color(255, 240, 196));


        // Dibujar las cabeceras de las columnas
        for (int j = 0; j < numColumns; ++j) {
            sf::RectangleShape headerCell(sf::Vector2f(cellWidth, cellHeight));
            headerCell.setPosition((j * cellWidth)+50, 360);
            headerCell.setOutlineColor(sf::Color::Black);
            headerCell.setOutlineThickness(1);
            window.draw(headerCell);

            sf::Text headerText;
            headerText.setFont(font);
            headerText.setString(columnHeaders[j]);
            headerText.setCharacterSize(14);
            headerText.setFillColor(sf::Color::Black);
            headerText.setPosition((j * cellWidth )+ 70, 362);
            window.draw(headerText);
        }




        for (int i = 0; i < values.size(); ++i) {
            std::vector<std::string> recordValues;
            recordValues.emplace_back(to_string(values[i].player_id));
            recordValues.emplace_back(values[i].short_name);
            recordValues.emplace_back(to_string(values[i].value_eur));
            recordValues.emplace_back(to_string(values[i].age));
            recordValues.emplace_back(values[i].club_name);
            recordValues.emplace_back(values[i].nationality_name);


            for (int j = 0; j < numColumns; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
                cell.setPosition((j * cellWidth)+50, ((i + 1) * cellHeight)+350); // Offset por la cabecera
                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(1);
                window.draw(cell);

                sf::Text text;
                text.setFont(font);
                text.setString(recordValues[j]);
                text.setCharacterSize(14);
                text.setFillColor(sf::Color::Black);
                text.setPosition((j * cellWidth) + 70, ((i + 1) * cellHeight + 10)+350); // Offset por la cabecera
                window.draw(text);
            }

}
        window.draw(button_execute);
        window.draw(button_tabla_1);
        window.draw(button_tabla_2);
        window.draw(button_tabla_3);
        window.draw(button_tabla_4);
        window.draw(button_limpiar);
        window.draw(rectangle_arriba);
        window.draw(rectangle_abajo);
        window.draw(button_equis);

        window.draw(label);
        window.draw(label_tabla_1);
        window.draw(label_tabla_2);
        window.draw(label_tabla_3);
        window.draw(label_tabla_4);
        window.draw(label_tiempo);
        window.draw(label_numero);


        window.draw(input);


        window.display();
    }
    return 0;

}