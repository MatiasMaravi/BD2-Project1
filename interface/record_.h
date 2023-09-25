//
// Created by JLeandroJM on 16/09/23.
//

#ifndef BD2_PROJECT1_RECORD_H
#define BD2_PROJECT1_RECORD_H
#include <iostream>
#include <string>
#include <vector>


class Record {
public:
    char charAttribute;
    std::string stringAttribute;
    int intAttribute1;
    int intAttribute2;
    int intAttribute3;
    int intAttribute4;

    Record(char c, const std::string& str, int i1, int i2, int i3, int i4)
            : charAttribute(c),
              stringAttribute(str),
              intAttribute1(i1),
              intAttribute2(i2),
              intAttribute3(i3),
              intAttribute4(i4) {}

    // Función para exportar los atributos a un vector
    std::vector<std::string> toVector() const {
        std::vector<std::string> recordVector;
        recordVector.push_back(std::string(1, charAttribute));
        recordVector.push_back(stringAttribute);
        recordVector.push_back(std::to_string(intAttribute1));
        recordVector.push_back(std::to_string(intAttribute2));
        recordVector.push_back(std::to_string(intAttribute3));
        recordVector.push_back(std::to_string(intAttribute4));
        return recordVector;
    }
};
#endif //BD2_PROJECT1_RECORD_H
