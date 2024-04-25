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

    // map of letters and their frequency in the name
    std::map<char, int> letter_freq;
};

std::vector<Card> create_card_list(std::string filename);
void write_card_list(std::vector<Card> cards, std::string filename);
void compare_and_change(std::vector<Card>* corrupt, std::vector<Card>* reference);
void char_quantity_similarity(Card* corrupt_card, std::vector<Card>* reference, bool user_self_decided, int range);
void check_correctness(std::string corrected_filename, std::string perfect_filename);
std::string user_decide(std::vector<std::string> cards);

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

    // asking the user if he wants to check if the restored deck is correct
    std::cout << "DEBUG: Do you want to check if the restored deck is correct? (y/n): ";
    char choice;
    do
    {
        std::cin >> choice;
    } while (choice != 'y' && choice != 'n');

    if(choice == 'y'){
        check_correctness("corrected.txt", "perfectly_restored.txt");
    }

    return 0;
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

        // creating a map of the letters and their frequency in the name
        std::map<char, int> letter_freq;
        for (char c : name) {
            if (letter_freq.find(c) == letter_freq.end()) {
                letter_freq[c] = 1;
            } else {
                letter_freq[c]++;
            }
        }
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

    // choosing the bool value for using char quantity similarity or not
    std::cout << "Do you want to use an additional algorithm for checking character numbers to find fits above your selected percentage? (y/n): ";
    bool use_similarity_algorithm;
    char choice;
    do
    {
        std::cin >> choice;
    } while (choice != 'y' && choice != 'n');

    // declare variables for the user_self_decided and range
    bool user_self_decided;
    int range;

    if(choice == 'y'){
        use_similarity_algorithm = true;

        // checking if user wants to decide himself at multiple same similiarity cards which cards comes closest    
        std::cout << "Do you want to decide yourself which card comes closest if multiple cards have the same similarity? (y/n): ";
        bool user_self_decided;
        char choice_self_decided;
        do
        {
            std::cin >> choice_self_decided;
        } while (choice_self_decided != 'y' && choice_self_decided != 'n'); 
        if(choice_self_decided == 'y'){
            user_self_decided = true;
            // checking which range in int is allowed to be listed astray from the lowest for the user to choose from
            std::cout << "Enter the range as integer at which names are allowed to be above the lowest distance in order to be listed: ";
            std::cin >> range;
        } else {
            user_self_decided = false;
        } 
    }
    else{
        use_similarity_algorithm = false;
    }

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
                std::cout << "-----\n" << algo_abrev << ": Found under " << percentage << "% :\nCorrupted card: " << corrupt_card.name << "\nReference card: " << reference_card.name << std::endl;
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
            if(use_similarity_algorithm){
                // using similarity_algorithm to find a fitting card
                char_quantity_similarity(&corrupt_card, reference, user_self_decided, range);
            } else {
            std::cout << "-----\n" << algo_abrev << ": None under  " << percentage << "% :\nCorrupted card: " << corrupt_card.name << "\nReference card: " << closest_card << std::endl;
            corrupt_card.name = closest_card;
            }
        }
    }
}

/*
using a simple comparison of the strings by number of individual characters. 

takes a pointer to the corrupt card, a pointer to the reference list and the percentage as input.

MKL. 2024
*/
void char_quantity_similarity(Card* corrupt_card, std::vector<Card>* reference, bool user_self_decided, int range){
    // iterating over the reference cards to find the best fitting card by least number of characters different to map of corrupt card

    std::map<char, int> corrupt_letter_freq = corrupt_card->letter_freq;
    int smallest_dist = 1000;

    // map of all the close cards with "name : distance"
    std::map<std::string, int> close_cards;

    for (Card& reference_card : *reference) {
        std::map<char, int> reference_letter_freq = reference_card.letter_freq;
        int dist = 0;

        // calculating the number of characters that are not the same in the two maps
        // for all characters in the corrupt card freq list
        // if the character of the corrupt card is a ?, we skip adding dist to the distance
        for (std::pair<char, int> corrupt_char : corrupt_letter_freq) {
            // if the character is in the reference card freq list (!= so end() is not reached)
            if (reference_letter_freq.find(corrupt_char.first) != reference_letter_freq.end()) {
                // add the difference in frequency to the distance (abs to make sure it is positive)
                dist += std::abs(corrupt_char.second - reference_letter_freq[corrupt_char.first]);
            } else {
                if(corrupt_char.first == '?'){
                    continue;
                }
                // if the character is not in the reference card freq list, and not a ?, add the frequency of the character in the corrupt card to the distance
                dist += corrupt_char.second;
            }
        }

        if (dist < smallest_dist) {
            // if we have a new smallest distance, we go through the vector and remove any entries that have a distance larger than the new smallest distance + range
            smallest_dist = dist;
            
            // for each card in the map, if the distance is larger than the smallest distance + range, we remove the card from the map
            for (auto it = close_cards.begin(); it != close_cards.end(); ) {
                if (it->second > (smallest_dist+range)) {
                    it = close_cards.erase(it);
                } else {
                    ++it;
                }
            }
            
        } else if (dist <= (smallest_dist+range)) {
            // if we have the same distance as the smallest distance or inside the range, we put the name : distance into the map
            close_cards[reference_card.name] = dist;
        }
    }

    // out of the created map of names : distance , we create a vector of only the names
    std::vector<std::string> closest_cards;
    for (auto it = close_cards.begin(); it != close_cards.end(); ++it) {
        closest_cards.push_back(it->first);
    }

    // if the vector only has one entry, we can immediately assign corrupt_card.name the closest_cards name. If there are multiple, 
    // we use the already existing Levenstein calculator to find the closest LS card among the ones in the vector.
    if (closest_cards.size() == 1) {
        std::cout << "-----\nSA:   Closest Match :\nCorrupted card: " << corrupt_card->name << "\nReference card: " << closest_cards[0] << std::endl;
        corrupt_card->name = closest_cards[0];
    } else {

        // we use the same principle as before with the similarity algorithm, but with the levenshtein calculator. 
        // we only keep cards with distance smaller than the smallest distance + range

        // map of all the cards with the new ls distance
        std::map<std::string, int> close_ls_cards;

        int closest_dist = 1000;
        for (std::string card : closest_cards) {
            // giving the name of the corrupt card, the reference card, no print matrix, ? as unkwnown char, no transposition and transposition cost 1
            int found_dist = calc_dist_int(corrupt_card->name, card, false, { {'?', '?'} }, false, 1);

            if (found_dist < closest_dist) {
                closest_dist = found_dist;
                for (auto it = close_ls_cards.begin(); it != close_ls_cards.end(); ) {
                    if (it->second > (closest_dist+range)) {
                        it = close_ls_cards.erase(it);
                    } else {
                        ++it;
                    }
                }
            } else if (found_dist <= (closest_dist+range)) {
                close_ls_cards[card] = found_dist;
            }
        }

        // converting map close_ls_cards to vector
        std::vector<std::string> closest_cards;
        for (auto it = close_ls_cards.begin(); it != close_ls_cards.end(); ++it) {
            closest_cards.push_back(it->first);
        }

        if(user_self_decided){
            // depending on if the user wants to decide for themself, we either true: print out the closest cards and let the user decide, 
            // or false: use the already existing Levenstein calculator to find the closest LS card among the ones in the vector.        
            
            std::cout << "-----\n SA: Decide by typing in the number of the card | Corrupted Card:  " << corrupt_card->name << std::endl;

            // method that takes a vector of strings, prints them out and lets the user choose one by typing in the number of the card and returns the string of the card
            std::string closest_card = user_decide(closest_cards);

            // print out the result
            std::cout << "SA:   Choosen Match :\nCorrupted card: " << corrupt_card->name << "\nReference card: " << closest_card << std::endl;
            corrupt_card->name = closest_card;

        } else {

        // print out the result
        std::cout << "-----\nSA:   Closest Match :\nCorrupted card: " << corrupt_card->name << "\nReference card: " << closest_cards[0] << std::endl;
        corrupt_card->name = closest_cards[0];

        }
    }
}

/*
This method takes a card deck that is known to be perfectly restored as txt 
and the card deck file that has been restored by the programm
and gives out a percentage of how much of the restored file was actually restored correctly.

MKL. 2024
*/
void check_correctness(std::string corrected_filename, std::string perfect_filename){

    // reading the two files into vectors of cards
    std::vector<Card> corrected_cards = create_card_list(corrected_filename);

    std::vector<Card> perfect_cards = create_card_list(perfect_filename);

    // the equivalent cards should always be at the same indice
    int correct = 0;
    int total = corrected_cards.size();

    for(int i = 0; i < corrected_cards.size(); i++){
        if(corrected_cards[i].name == perfect_cards[i].name){
            correct++;
        }
    }

    double percentage = (double)correct / (double)total * 100;

    std::cout << "------/nThe restored deck is " << std::fixed << std::setprecision(2) << percentage << "% correct.\n" << std::endl;
}

/*
user_decide is a simple method that takes a vector, prints out each of the indicies value one line by another in the terminal accompanied by a number like:
1 | Banana
2 | Oranges
etc.
and letting the user choose a value inbetween this. 
Returns the string that is choosen. 
MKL. 2024
*/
std::string user_decide(std::vector<std::string> cards){
    int i = 1;
    for(std::string card : cards){
        std::cout << i << " | " << card << std::endl;
        i++;
    }

    int choice;
    do
    {
        std::cin >> choice;
    } while (choice < 1 || choice > cards.size());

    return cards[choice-1];
}
    
    