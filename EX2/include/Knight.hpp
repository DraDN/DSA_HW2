#pragma once

#include <cstring>


namespace RK {

    struct Knight {
            int braveryScore = 0;
            unsigned int battlesWon = 0;
            char* name = nullptr;
            char* house = nullptr;

            Knight() {}

            Knight(const char* name, int braveryScore, unsigned int battlesWon, const char* house) : braveryScore(braveryScore), battlesWon(battlesWon) {
                this->name = new char[strlen(name) + 1];
                this->house = new char[strlen(house) + 1];
                strcpy(this->name, name);
                strcpy(this->house, house);
            }

            Knight(int braveryScore) : braveryScore(braveryScore) {}

            ~Knight() {
                delete[] name;
                delete[] house;
            }

            Knight(const Knight& other) {
                braveryScore = other.braveryScore;
                battlesWon = other.battlesWon;
                name = other.name ? new char[strlen(other.name) + 1] : nullptr; // check if the other's name is not nullptr
                house = other.house ? new char[strlen(other.house) + 1] : nullptr;
                if (name) strcpy(name, other.name);
                if (house) strcpy(house, other.house);
            }

            Knight& operator=(const Knight& other) {
                braveryScore = other.braveryScore;
                battlesWon = other.battlesWon;
                delete[] name;
                delete[] house;
                name = other.name ? new char[strlen(other.name) + 1] : nullptr;
                house = other.house ? new char[strlen(other.house) + 1] : nullptr;
                if (name) strcpy(name, other.name);
                if (house) strcpy(house, other.house);
                return *this;
            }


            // smaller and lower operator overloading for comparison inside the binary search tree
            bool operator>(const Knight& other) const {
                return braveryScore > other.braveryScore;
            }

            bool operator<(const Knight& other) const {
                return braveryScore < other.braveryScore;
            }

    };

}
