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
void find_jaro_winkler_distance(std::string* corrupt_name, std::vector<Card>* reference, double percentage);
double calc_jaro_winkler(const std::string& s1, const std::string& s2);

int main() {


    std::cout << "\n _____               _  ______          _                      \n"
    "/  __ \\             | | | ___ \\        | |                     \n"
    "| /  \\/ __ _ _ __ __| | | |_/ /___  ___| |_ ___  _ __ ___ _ __ \n"
    "| |    / _` | '__/ _` | |    // _ \\/ __| __/ _ \\| '__/ _ \\ '__|\n"
    "| \\__/\\ (_| | | | (_| | | |\\ \\  __/\\__ \\ || (_) | | |  __/ |   \n"
    " \\____/\\__,_|_|  \\__,_| \\_| \\_\\___||___/\\__\\___/|_|  \\___|_|   \n"
    "\n" << std::endl;

    std::cout << "Restoring the corrupted card deck" << std::endl;
    std::cout << "-------------" << std::endl;

    std::cout << "Reading the corrupted card deck from a file..." << std::endl;
    // reading the corrupted card deck from a file
    std::vector<Card> cards = create_card_list("scrambled.txt");

    std::cout << "Reading the reference card deck from a file..." << std::endl;
    // reading the reference card deck from a file
    std::vector<Card> reference = create_card_list("reference.txt");
    
    std::cout << "Restoring the corrupted card deck..." << std::endl;
    std::cout << "-------------" << std::endl;
    // comparing the corrupted card deck to the reference card deck
    compare_and_change(&cards, &reference);

    std::cout << "-------------" << std::endl;
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

    // ------------------- USER INPUT BEGIN -------------------
    // getting the needed percentage similarity for the distance calculator
    std::cout << "Enter the percentage similarity needed for the distance calculator:  ";
    double percentage;
    // making sure the number is between 0 and 100
    do {
        std::cin >> percentage;
    } while (percentage < 0 || percentage > 100);

    // seeing if user wants to use transposition for the distance calculator
    std::cout << "Do you want to use transposition for the levenshtein calculator? (y/n): ";
    bool use_transposition;
    char choice_transposition;
    do
    {
        std::cin >> choice_transposition;
    } while (choice_transposition != 'y' && choice_transposition != 'n');

    std::string algo_abrev;
    if(choice_transposition == 'y'){
        algo_abrev = "DL";
        use_transposition = true;
    }
    else{
        algo_abrev = "LS";
        use_transposition = false;
    }

    int transposition_cost = 1;
    if(use_transposition){
    // getting the transposition cost for the distance calculator
    std::cout << "Enter the transposition cost for the levenshtein calculator: ";
    std::cin >> transposition_cost;
    }

    // choosing the bool value for using jaro-winkler similarity or not
    std::cout << "Do you want to use Jaro-Winkler similarity to find fits under your selected percentage? (y/n): ";
    bool use_jaro_winkler;
    char choice;
    do
    {
        std::cin >> choice;
    } while (choice != 'y' && choice != 'n');

    if(choice == 'y'){
        use_jaro_winkler = true;
    }
    else{
        use_jaro_winkler = false;
    }
    std::cout << "-------------" << std::endl;

    // ------------------- USER INPUT END -------------------

    for (Card& corrupt_card : *corrupt) {
        bool found = false;
        std::string closest_card;
        int closest_dist = 1000;
        for (Card& reference_card : *reference) {
            // getting distance between corrupt card and reference card
            int found_dist = calc_dist_int(corrupt_card.name, reference_card.name, false, unknown_chars, use_transposition, transposition_cost);

            // checking if distance is under the choosen percentage of the length of the corrupt name
            if (found_dist < corrupt_card.name.size() * (percentage/100.0)) {
                std::cout << algo_abrev << ": Found under " << percentage << "% : Corrupted card: " << corrupt_card.name << " | Reference card: " << reference_card.name << std::endl;
                corrupt_card.name = reference_card.name;
                found = true;
                break;
            }

            // checking if new closest distance
            if (found_dist < closest_dist) {
                closest_dist = found_dist;
                closest_card = reference_card.name;
            }
        }

        if (!found) {
            if(use_jaro_winkler){
                // using jaro-winkler similarity to find the closest card
                find_jaro_winkler_distance(&corrupt_card.name, reference, percentage);
            } else {
            std::cout << algo_abrev << ": None under  " << percentage << "% : Corrupted card: " << corrupt_card.name << " | Reference card: " << closest_card << std::endl;
            corrupt_card.name = closest_card;
            }
        }
    }
}

/*
using a jaro_winkler similarity algorithm to find the closest card to the corrupt name.

takes the corrupt name as pointer and a pointer to a vector of cards that serve as reference, and a percentage.

if the jaro-winkler similarity is under the percentage, the name is replaced with the closest card.

MKL. 2024
*/
void find_jaro_winkler_distance(std::string* corrupt_name, std::vector<Card>* reference, double percentage) {

    bool found;
    std::string closest_card;
    double closest_dist = 0.0;

    for (Card& reference_card : *reference) {
        double found_dist = calc_jaro_winkler(*corrupt_name, reference_card.name);
        if (found_dist < (percentage/100)) {
            std::cout << "JW: Found under " << percentage << "% : Corrupted card: " << *corrupt_name << " | Reference card: " << reference_card.name << std::endl;
            *corrupt_name = reference_card.name;
            return;;
        }
        if (found_dist > closest_dist) {
            closest_dist = found_dist;
            closest_card = reference_card.name;
        }
    }

    if(!found){
        std::cout << "JW: None under " << percentage << "% : Corrupted card: " << *corrupt_name << " | Reference card: " << std::endl;
    }
}

/*
method that calculates the jaro-winkler similiarity between two strings

returns double value of the similarity between 1 (no simi. at all) and 0 (exact match)

MKL. 2024
*/
double calc_jaro_winkler(const std::string& s1, const std::string& s2) {
    // Jaro-Winkler similarity algorithm
    // https://en.wikipedia.org/wiki/Jaro%E2%80%93Winkler_distance
    // https://rosettacode.org/wiki/Jaro-Winkler_distance#C.2B.2B

    double jaro_dist = 0.0;

    // if the strings are equal, the distance is 0
    if (s1 == s2) {
        return 0.0;
    }
    


    return jaro_dist;
}