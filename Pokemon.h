//
// Kathryn Finlayson
// Project 3
// CS 2240C
//

#ifndef PROJECT1_POKEMON_H
#define PROJECT1_POKEMON_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using std::cout, std::endl, std::ifstream, std::string, std::vector;

class Pokemon {
private:
    int number, total, hp, attack, defense, sp_attack, sp_defense, speed, generation;
    string name, type1, type2;
    bool legendary;

public:
    //Constructors
    Pokemon() {
        number = -1;
        name = "????";
        type1 = "????";
        type2 = "????";
        total = hp = attack = defense = sp_attack = sp_defense = speed = generation = -1;
        legendary = false;
    }

    Pokemon(int number, string name, string type1, string type2, int total, int hp, int attack, int defense, int sp_attack, int sp_defense, int speed, int generation, bool legendary) {
        this->number = number;
        this->name = name;
        this->type1 = type1;
        this->type2 = type2;
        this->total = total;
        this->hp = hp;
        this->attack = attack;
        this->defense = defense;
        this->sp_attack = sp_attack;
        this->sp_defense = sp_defense;
        this->speed = speed;
        this->generation = generation;
        this->legendary = legendary;
    }

    // Getters
    int getNumber() {
        return number;
    }
    string getName() {
        return name;
    }
    string getType1() {
        return type1;
    }
    string getType2() {
        return type2;
    }
    int getTotal() {
        return total;
    }
    int getHp() {
        return hp;
    }
    int getAttack() {
        return attack;
    }
    int getDefense() {
        return defense;
    }
    int getSPAttack() {
        return sp_attack;
    }
    int getSPDefense() {
        return sp_defense;
    }
    int getSpeed() {
        return speed;
    }
    int getGeneration() {
        return generation;
    }
    bool isLegendary() {
        return legendary;
    }

    // Setters
    void setNumber(int number) {
        this->number = number;
    }
    void setName(string name) {
        this->name = name;
    }
    void setType1(string type1) {
        this->type1 = type1;
    }
    void setType2(string type2) {
        this->type2 = type2;
    }
    void setTotal(int total) {
        this->total = total;
    }
    void setHP(int hp) {
        this->hp = hp;
    }
    void setAttack(int attack) {
        this->attack = attack;
    }
    void setDefense(int defense) {
        this->defense = defense;
    }
    void setSPAttack(int sp_attack) {
        this->sp_attack = sp_attack;
    }
    void setSPDefense(int sp_defense) {
        this->sp_defense = sp_defense;
    }
    void setSpeed(int speed) {
        this->speed = speed;
    }
    void setGeneration(int generation) {
        this->generation = generation;
    }
    void setLegendary(bool legendary) {
        this->legendary = legendary;
    }

    // Operator Overloads
    bool operator == (const Pokemon & other) const {
        if (number == other.number && name == other.name) {
            return true;
        }
        return false;
    }

    bool operator > (const Pokemon & other) const {
        if (number > other.number || (number == other.number && name > other.name)) {
            return true;
        }
        return false;
    }

    bool operator < (const Pokemon & other) const {
        if (number < other.number || (number == other.number && name < other.name)) {
            return true;
        }
        return false;
    }

    bool operator >= (const Pokemon & other) const {
        return !(*this < other);
    }

    bool operator <= (const Pokemon & other) const {
        return !(*this > other);
    }
};

// File Reader
bool getDataFromFile(vector<Pokemon> & pokemon) {
    ifstream fileIn;
    fileIn.open("../Pokemon.csv");
    if (fileIn) {
        // Declare vars to be read in
        string header, newstring; // created separately for clarity
        int number, total, hp, attack, defense, sp_attack, sp_defense, speed, generation;
        string name, type1, type2, str_legendary;
        bool legendary;
        char delimiter = ','; // Named delimiter instead of comma for clarity

        // Read header
        getline(fileIn, header);
        // cout << header << endl;
        while (fileIn && fileIn.peek() != EOF) {
            // Read in data per line
            fileIn >> number >> delimiter;
            getline(fileIn, name, delimiter);
            getline(fileIn, type1, delimiter);
            getline(fileIn, type2, delimiter);
            fileIn >> total >> delimiter;
            fileIn >> hp >> delimiter;
            fileIn >> attack >> delimiter;
            fileIn >> defense >> delimiter;
            fileIn >> sp_attack >> delimiter;
            fileIn >> sp_defense >> delimiter;
            fileIn >> speed >> delimiter;
            fileIn >> generation >> delimiter;
            // Workaround for fstream not reading bools - not pretty, but functional
            getline(fileIn, str_legendary);
            legendary = (str_legendary == "TRUE");

            //cout << number << name << type1 << type2 << total << hp << attack << defense << sp_attack << sp_defense << speed << generation << legendary << endl;
            // Get rid of newline
            //getline(fileIn, newstring); // Removing this prevented skipping every other line.

            // Add line to vector
            pokemon.push_back(Pokemon(number, name, type1, type2, total, hp, attack, defense, sp_attack, sp_defense, speed, generation, legendary));
        }
        fileIn.close();
        return true;
    }
    return false;
}

#endif //PROJECT1_POKEMON_H