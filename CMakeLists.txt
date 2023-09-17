cmake_minimum_required(VERSION 3.25)
project(BD2_Project1)

set(CMAKE_CXX_STANDARD 14)
set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@3)

find_package(OpenSSL REQUIRED)
include_directories(Parser)
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(BD2_Project1
#        Parser/Parser.hpp
#        Parser/Scanner.hpp
#        Parser/Token.hpp
#        "Sequential file/prueba.cpp"
#        "Sequential file/sequential_file.cpp"
       main.cpp
        interfaz/record.h
        interfaz/textinput.h
        interfaz/button.h

        interfaz/interfaz_main.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
# Enlazar la librería OpenSSL
target_link_libraries(BD2_Project1 OpenSSL::Crypto sfml-system
        sfml-window
        sfml-graphics
        sfml-audio)