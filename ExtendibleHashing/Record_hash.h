//
// Created by JLeandroJM on 24/09/23.
//

#ifndef BD2_PROJECT1_RECORD_HASH_H
#define BD2_PROJECT1_RECORD_HASH_H
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <functional>

using namespace std;

struct Record_hash{
    int player_id;
    char short_name[50];
    int value_eur;
    int age;
    char club_name[50];
    char nationality_name[50];


    void setData(int player_id_, const char* short_name_, int value_eur_, int age_, const char* club_name_, const char* nationality_name_) {
        this->player_id = player_id_;
        strcpy(this->short_name, short_name_);
        this->value_eur = value_eur_;
        this->age = age_;
        strcpy(this->club_name, club_name_);
        strcpy(this->nationality_name, nationality_name_);

    }


    void showData() {
        cout << "Player ID: " << player_id << "\n";
        cout << "Short Name: " << short_name << "\n";
        cout << "Value EUR: " << value_eur << "\n";
        cout << "Age: " << age << "\n";
        cout << "Club Name: " << club_name << "\n";
        cout << "Nationality Name: " << nationality_name << "\n";

    }
};


#endif //BD2_PROJECT1_RECORD_HASH_H
