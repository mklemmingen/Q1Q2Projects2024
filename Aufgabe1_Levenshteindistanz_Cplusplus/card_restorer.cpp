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

std::vector<Card> create_card_list(std::string filename);
void write_card_list(std::vector<Card> cards, std::string filename);
void compare_and_change(std::vector<Card>* corrupt, std::vector<Card>* reference);
bool compare_for_switched_arounds(std::string* corrupt_name, std::vector<Card>* reference);

int main() {

    std::cout << "Card Restorer" << std::endl;
    std::cout << "Restoring the corrupted card deck" << std::endl;
    std::cout << "-------------" << std::endl;

    std::cout << "Reading the corrupted card deck from a file..." << std::endl;
    // reading the corrupted card deck from a file
    std::vector<Card> cards = create_card_list("scrambled.txt");

    std::cout << "Reading the reference card deck from a file..." << std::endl;
    // reading the reference card deck from a file
    std::vector<Card> reference = create_card_list("reference.txt");

    std::cout << "Restoring the corrupted card deck..." << std::endl;
    // comparing the corrupted card deck to the reference card deck
    compare_and_change(&cards, &reference);

    std::cout << "Writing the corrected card deck to a file..." << std::endl;
    // writing the corrected card deck to a file
    write_card_list(cards, "corrected.txt");

    std::cout << "The corrupted card deck has been restored." << std::endl;
}

/*
used to create a list of cards out of a card database in the format of struct Card.
the different attributes of file must be seperated by | and different cards by newline.
returns the list

MKL. 2024
*/
std::vector<Card> create_card_list(std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return {};
    }

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

    if (cards.empty()) {
        std::cout << "No cards were read from the file." << std::endl;
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
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    for (Card card : cards) {
        file << card.name << " | " << card.manacost << " | " << card.cumulativemanacost << " | " << card.type << " | " << card.amount << std::endl;
    }
    
    file.close();
    if (file.fail()) {
        std::cerr << "Error: Could not write to file " << filename << std::endl;
    } else {
        std::cout << "Successfully wrote to file " << filename << std::endl;
    }
}

/*
comparing a list of cards (corrupt) to another list (reference) to find partner 
when LD smaller than 26,75% of the length of the corrupt name -> add name.
if none found, the smallest distance is taken and the name is replaced with the reference name.

takes two pointers to the lists of cards as input.

MKL. 2024
*/
void compare_and_change(std::vector<Card>* corrupt, std::vector<Card>* reference) {

    // unknown characters are "?"
    std::vector<std::pair<char, char>> unknown_chars = { {'?', '?'} };

    for (Card& corrupt_card : *corrupt) {
        bool found = false;
        std::string closest_card;
        int closest_dist = 1000;
        for (Card& reference_card : *reference) {
            int found_dist = calc_dist_int(corrupt_card.name, reference_card.name, false, unknown_chars);
            if (found_dist < closest_dist) {
                closest_dist = found_dist;
                closest_card = reference_card.name;
            }
            if (calc_dist_int(corrupt_card.name, reference_card.name, false, unknown_chars) < corrupt_card.name.size() * 0.2675) {
                std::cout << "Found under 26,75% : Corrupted card: " << corrupt_card.name << " | Reference card: " << reference_card.name << std::endl;
                corrupt_card.name = reference_card.name;
                found = true;
                break;
            }
        }
        if (!found) {
            // either we use the closest card, which would result in a lot of wrong names, or we check again using a strategy that includes
            // not only corrupted ("?") characters but also length of name as well as letters having switched up to three places to either side. 

            // if a switch has happened in compare_for_switched_arounds, we print the result, if not, print and choose closest levensthein distance card
            std::string old_name = corrupt_card.name;
            if(!compare_for_switched_arounds(&corrupt_card.name, reference)) {
                std::cout << "None under 26,75% : Corrupted card: " << old_name << " | Reference card: " << closest_card << std::endl;
                corrupt_card.name = closest_card;
            } else {
                std::cout << "Letters Scrambled : Corrupted card: " << old_name << " | Reference card: " << corrupt_card.name << std::endl;
            }
        }
    }
}

/*
takes a pointer to a string and a pointer to a vector of cards as input.
the string is a corrupt name from which the levenshtein distance was not sufficient to determine a close relative. 
we therefore go through the reference cards again and check if the corrupt name has a close relative with under 26,75% if we
- switch two letters around every other letter. We do not switch around "?" characters, as they are unknown and we hypothesise that these were not switched around.

returns true if a close relative was found, false if not.

At worst, this could be a O(n^2) operation, but we can optimize it by checking the length of the names first.

MKL. 2024
*/
bool compare_for_switched_arounds(std::string* corrupt_name, std::vector<Card>* reference) {
    std::string name = *corrupt_name;
    std::vector<std::pair<char, char>> unknown_chars = { {'?', '?'} };

    for (Card& reference_card : *reference) {
        std::string ref_name = reference_card.name;
        for (int i = 0; i < name.size(); i++) {
            for (int j = 0; j < name.size(); j++) {
                if (i != j) {
                    std::string temp = ref_name;
                    std::swap(temp[i], temp[j]);
                    if (calc_dist_int(name, temp, false, unknown_chars) < name.size() * 0.2675) {
                        *corrupt_name = ref_name;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}