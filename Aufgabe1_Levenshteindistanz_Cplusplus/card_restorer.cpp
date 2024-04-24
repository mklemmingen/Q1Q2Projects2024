/*
This program runs the Levenshtein distance algorithm from distance_calculator to restore a card from a deck of cards and 
subsequently tries to fix the corrupted card deck.

MKL. 2024
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <sstream>
#include <iomanip>
#include "distance_calculator/distcalc.h"

/*
data structure for a card

Name der Karte | Manakosten | Kummulative Manakosten | Typ | Anzahl im Besitz des Sammlers

MKL. 2024
*/
struct Card {
    std::string name;
    std::string manacost;
    int cumulativemanacost;
    std::string type;
    int amount;
};

int main() {

    // reading the corrupted card deck from a file
    std::vector<Card> cards = create_card_list("corrupted.txt");

    // reading the reference card deck from a file
    std::vector<Card> reference = create_card_list("reference.txt");

    // comparing the corrupted card deck to the reference card deck
    compare_and_change(&cards, &reference);

    // writing the corrected card deck to a file
    write_card_list(cards, "corrected.txt");

}

/*
used to create a list of cards out of a card database in the format of struct Card.
the different attributes of file must be seperated by | and different cards by newline.
returns the list

MKL. 2024
*/
std::vector<Card> create_card_list(std::string filename) {

    std::ifstream file(filename);
    std::string line;
    std::vector<Card> cards;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, manacost, type;
        int cumulativemanacost, amount;
        std::getline(iss, name, '|');
        std::getline(iss, manacost, '|');
        iss >> cumulativemanacost;
        std::getline(iss, type, '|');
        iss >> amount;
        Card card = { name, manacost, cumulativemanacost, type, amount };
        cards.push_back(card);
    }
    return cards;
}

/*
used to write a list of Cards back into a suitable txt format.
takes the list of cards and the filename as input.
Seperates different attributes of card by | and different cards by newline.

MKL. 2024
*/
void write_card_list(std::vector<Card> cards, std::string filename) {
    std::ofstream file(filename);
    for (Card card : cards) {
        file << card.name << " | " << card.manacost << " | " << card.cumulativemanacost << " | " << card.type << " | " << card.amount << std::endl;
    }
}

/*
comparing a list of cards (corrupt) to another list (reference) to find partner with LD smaller 
than 26,75% of the length of the corrupt name. 
replacing the corrupted cards name with the reference name.

takes two pointers to the lists of cards as input.

MKL. 2024
*/
void compare_and_change(std::vector<Card>* corrupt, std::vector<Card>* reference) {

    // unknown characters are "?"
    std::vector<std::pair<char, char>> unknown_chars = { {'?', '?'} };

    for (Card& corrupt_card : *corrupt) {
        for (Card& reference_card : *reference) {
            if (calc_dist_int(corrupt_card.name, reference_card.name, false, unknown_chars) < corrupt_card.name.size() * 0.2675) {
                corrupt_card.name = reference_card.name;
            }
        }
    }
}



