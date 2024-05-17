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

struct CloseCard
{
    std::string name;
    double LS_Dist;
    double SA_Dist;
    double LS_times_SA;
};

// card data handling methods ---
std::vector<Card> create_card_list(std::string filename);
void write_card_list(std::vector<Card> cards, std::string filename);

// distance algorithms ---
double char_quantity_similarity(std::string corrupt_card, std::string reference);
// also, see distcalc.cpp for the Levenshtein distance calculator

// quality assurance methods ---
void check_correctness(std::string corrected_filename, std::string perfect_filename);

// user decision methods ---
CloseCard user_decide(std::vector<CloseCard> cards);
bool user_choose(std::string text_to_be_displayed);
int user_choose_int(std::string text_to_be_displayed);
double user_choose_double(std::string text_to_be_displayed);
std::vector<char> user_choose_chars_vector(std::string text_to_be_displayed);

// output methods
void shoutout(std::string algo_abrev, std::string best_option, std::string corrupt_card_name, 
                double LS_Dist, double SA_Dist, double Accumulated_Dist);

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

    // --------------------------------------------------------

    // Idea for restructure (putting compare and change into either main and/or different methods) 

    // get user input for the different user parameters, put them into variables

    // declare all the variables that are needed for the user input, so that they are declared even if they end up in a if-statement

    double insertion_weight;
    double deletion_weight;
    double substitution_weight;
    double transposition_cost;
    double range_SA;        
    std::vector<char> unknown_chars;

    // get: percentage needed

    double percentage = user_choose_double("Enter the percentage similarity needed for the distance calculator:  ");

    // print: .....
    std::cout << "------------------------------------" << std::endl;

    // get: transposition
    bool use_transposition = user_choose("Do you want to use transposition for the levenshtein calculator?: ");

    // get: do you want to change the weights for each operation of the Levenshtein Algo?
    bool change_weights = user_choose("Do you want to change the weights for each operation of the Levenshtein Algo?: ");

        if(change_weights){
            std::cout <<"--------------- WEIGHTS ------------ " << std::endl;
            // get: insertion
            insertion_weight = user_choose_double("Enter the insertion weight for the levenshtein calculator: ");
            // get: deletion
            deletion_weight = user_choose_double("Enter the deletion weight for the levenshtein calculator: ");
            // get: substitution? 
            substitution_weight = user_choose_double("Enter the substitution weight for the levenshtein calculator: ");

            if(use_transposition){
                // if use_transposition 
                // get: transposition cost
                transposition_cost = user_choose_double("Enter the transposition cost for the levenshtein calculator: ");
                std::cout << "------------------------------------" << std::endl;
            }
        } else {
            // set all weights to 1
            insertion_weight = 1;
            deletion_weight = 1;
            substitution_weight = 1;
            transposition_cost = 1;
        }

    // get: do you want to set unique characters who are universal and who never cost? (ex. "?")
    bool use_unknown_chars = user_choose("Do you want to use wildcard characters? (ex. '?'): ");

        if(use_unknown_chars){

            std::cout << "--------------- UNKWNOWN CHARS ---------------------" << std::endl;

            // get: unknown chars as vector
            unknown_chars = user_choose_chars_vector("Entering the unknown characters... ");

            std::cout << "------------------------------------" << std::endl;
            
        }

    // get: do you want to decide yourself what the best fit for a corrupted card is in the Levenshtein-Distance-Algorithm?

    bool user_decision_LS = user_choose("Do you want to decide yourself on the best Card?: ");
    
    // get: do you want to use a range in which a reference word is still valid in the Levenshtein-Distance-Algorithm?

    double range_LS = user_choose_double("Enter the range a card is allowed to be distant from the lowest dist: ");
    
    // print: "------- Similarity Algorithm -------"

    // do you want to use a similiarity algorithm to try and improve the result?

    bool use_similarity_algorithm = user_choose("Do you want to use a similiarity algorithm (SA) to improve the result?: ");

    // ask if debug mode should be turned on:
    bool debug_mode = user_choose("Do you want to turn on debug mode?");

    // debug information

    if(debug_mode){

    std::cout << "------------------ DEBUG INFO FOR START ------------------" << std::endl;

    std::cout << "Percentage: " << percentage << std::endl;
    
    // size of reference card

    std::cout << "Size of reference card: " << reference.size() << std::endl;

    // size of corrupt card

    std::cout << "Size of corrupt card: " << cards.size() << std::endl;

    std::cout << "------------------ DEBUG INFO END ------------------" << std::endl;

    }

    // print: "------------------------------------"
    std::cout << "------------------ START OF RESTORATION ------------------" << std::endl;

    // set the correct algorithm abbreviation
    std::string algo_abrev;
    if(use_transposition){
        algo_abrev = "DL";
    } else {
        algo_abrev = "LS";
    }
    if(use_similarity_algorithm){
        algo_abrev += ":SA";
    }

    // ----------------- GO OVER THE CORRUPT CARDS; FOR EACH CORRUPT CARD, GO OVER ALL REFERENCE CARDS -----------------

    // loop over all reference cards with every corrupted card
    for (Card& corrupt_card : cards) {
        bool found = false;
        
        // at every new corrupt card, we create new variables for its process -------------------------------------
        
        // close cards final
        // the closest cards that we found
        std::vector<CloseCard> close_cards_final = {};

        // int closest distance for LS
        double closest_dist_LS = 1000;

        // int closest distance for SA
        double closest_dist_SA = 1000;

        // ------------------------ going over corrupt cards -----------------------

        // loop through all reference cards
        for (Card& reference_card : reference) {

            // using the Levenshtein distance calculator first -----------------------
            // getting distance between corrupt card and reference card
            double found_dist_LS = weighted_levenshtein(corrupt_card.name, reference_card.name, false, unknown_chars, use_transposition, transposition_cost, 
                                                insertion_weight, deletion_weight, substitution_weight);

            // assign reference card if levenshtein distance is smaller than size_of_reference_card * percentage
            if (found_dist_LS <= (reference_card.name.size() * (percentage/100))) {
                corrupt_card.name = reference_card.name;
                found = true;
                shoutout(algo_abrev, reference_card.name, corrupt_card.name, found_dist_LS, 0, found_dist_LS);
                break;
            } 

            // if either lower than closest distance or in range ---- which always puts it into the vector of close cards
            if(found_dist_LS <= (closest_dist_LS+range_LS)){
                // if the distance is within the range, we add it to the vector of close cards
                double distance_LS = found_dist_LS;
                double distance_SA = 0;
                CloseCard card;

                // ---- CREATING CARD, OPT: USING SIMILIARITY ALGORITHM ----
                if(use_similarity_algorithm){
                    distance_SA = char_quantity_similarity(corrupt_card.name, reference_card.name);
                    card = {reference_card.name, distance_LS, distance_SA, distance_LS*distance_SA};
                } else {
                card = {reference_card.name, distance_SA, 0, distance_LS};
                }

                close_cards_final.push_back(card);

                // checking if distance is new closest distance - if it is, remove all above range cards
                if (found_dist_LS < closest_dist_LS) {

                    // set the new closest distance
                    closest_dist_LS = found_dist_LS;

                    // remove all cards in the vector that are above new closest + range
                    for (auto it = close_cards_final.begin(); it != close_cards_final.end(); ) {
                        if (it->LS_Dist > (closest_dist_LS+range_LS)) {
                            it = close_cards_final.erase(it);
                        } else {
                            ++it;
                        }
                    }

                }
            }
            // next reference card
        }
        // reference cards for this specific corrupt card are done

        // if debug, print out the distance of ls and then wait for any user input to continue
        if(debug_mode){
            std::cout << "Closest distance for LS: " << closest_dist_LS << std::endl;
        // wait for any input including an enter push
            std::cin.get();
        }

        // ------------------------- SORT ------------------------- IF PERCENTAGE NOT APPLICABLE

        if(!found){

        // DEBUG

        if(debug_mode){
        // sizes of the vectors
        std::cout << "LS: " << close_cards_final.size() << " SA: " << close_cards_final.size() << std::endl;
        }

        // sort the close_cards_final by the Accumulated_Dist
        std::sort(close_cards_final.begin(), close_cards_final.end(), [](CloseCard a, CloseCard b) {
            return a.LS_times_SA < b.LS_times_SA;
        });

        // debug: size after sorting

        if(debug_mode){
            std::cout << "Size after sorting: " << close_cards_final.size() << std::endl;
        }


        // depending on if the user wants to decide for themself, we either
        // print out options and let user decide, or choose the first one in the sorted map

        // ------------------------- DECIDE -------------------------

        if(close_cards_final.empty()) {

            // TODO ADD EXCEPTION HANDLING WITH EXTRA CLASS ------------------------------------------------------------------------------------ TODO

            // if close cards is empty, we dont have any options and we just keep the corrupt card
            // however, we give out that this is an ERROR

            std::cout << "ERROR: No close cards found for corrupt card, which should be impossible: " << corrupt_card.name << std::endl;
            return 1;
        }
        else {
            if(user_decision_LS){
                // print out the best options ( all of user_decide )

                // declare that choosing is starting and what the corrupt card is:
                std::cout << "!- Attention -!" << std::endl;
                std::cout << "Choosing for corrupt card: " << corrupt_card.name << std::endl;

                CloseCard best_option = user_decide(close_cards_final);

                // shoutout
                shoutout(algo_abrev, best_option.name, corrupt_card.name, best_option.LS_Dist, best_option.SA_Dist,
                best_option.LS_times_SA);

                // assign the string to the card
                corrupt_card.name = best_option.name;
            } else {
                // choose the one with the lowest distance

                // shoutout
                shoutout(algo_abrev, close_cards_final[0].name, corrupt_card.name, close_cards_final[0].LS_Dist, close_cards_final[0].SA_Dist, 
                close_cards_final[0].LS_times_SA);

                corrupt_card.name = close_cards_final[0].name;
            }
        }
        }
        // next corrupt card
    }

    // --------------------------------------------------------

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
using a simple comparison of the strings by number of individual characters. 

takes two strings

MKL. 2024
*/
double char_quantity_similarity(std::string corrupt_card, std::string reference){
    // comparing two strings by the number of individual characters and returning distance value
    double distance = 0;

    // if the strings are the same, return 0
    if(corrupt_card == reference){
        return 0;
    }

    // use a map to store: char -> count
    std::map<char, int> corrupt_chars;
    std::map<char, int> reference_chars;

    // fill the maps with the characters and their count
    for(char c : corrupt_card){
        corrupt_chars[c]++;
    }

    for(char c : reference){
        reference_chars[c]++;
    }

    // loop over the corrupt card map and check ifbh the character is in the reference map
    // if it is, add the difference of the two counts to the distance
    // if it is not, add the count of the corrupt card to the distance
    for(auto it = corrupt_chars.begin(); it != corrupt_chars.end(); it++){
        if(reference_chars.find(it->first) != reference_chars.end()){
            distance += abs(it->second - reference_chars[it->first]);
        } else {
            distance += it->second;
        }
    }

    // loop over the reference map and check if the character is in the corrupt map
    // if it is not, add the count of the reference card to the distance
    for(auto it = reference_chars.begin(); it != reference_chars.end(); it++){
        if(corrupt_chars.find(it->first) == corrupt_chars.end()){
            distance += it->second;
        }
    }

    // create a value between 0 and 1 by dividing the distance by the length of the reference card
    distance = distance / reference.size();

    return distance;
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

    // if an exception has occured, that a file doesnt have any more indices, throw error to output and end method

    if(corrected_cards.size() != perfect_cards.size()){
        std::cerr << "Error: The two files do not have the same amount of cards." << std::endl;
        return;
    }

    // checking how many cards are the same
    for(int i = 0; i < corrected_cards.size(); i++){
        if(corrected_cards[i].name == perfect_cards[i].name){
            correct++;
        }
    }

    double percentage = (double)correct / (double)total * 100;

    std::cout << "------/nThe restored deck is " << std::fixed << std::setprecision(2) << percentage << "% correct.\n" << std::endl;
}

/*
user_decide is a simple method that takes a map of cards with a "string: <int:int>" prints out each of the indicies value one line by another in the terminal accompanied by a number like:
1 | Banana
2 | Oranges
etc.
and letting the user choose a value inbetween this. 
Returns the string that is choosen. 

Only allows for the first 50 to be displayed. Always give a sorted top to bottom list of the cards.

MKL. 2024
*/
CloseCard user_decide(std::vector<CloseCard> cards){

    // prints out options with 
    // number | LS: LS_Dist | SA: SA_Dist | Accumulated_Dist | Name

    int end = 50;

    if(cards.size() < 50){
        end = cards.size();
    }

    for(int i = 0; i < end; i++){
        std::cout << i+1 << " | LS: " << cards[i].LS_Dist << " SA: " << cards[i].SA_Dist << " LS*SA: " << cards[i].LS_times_SA << " | " << cards[i].name << std::endl;
    }

    // let user choose a number
    int choice;

    do
    {
        std::cin >> choice;
    } while (choice < 1 || choice > end+1);

    return cards[choice-1];
}

/*
user choose is a method that displays a parameter given text and allows receiving either a 

y  -> returns true
or
n  -> returns false

MKL. 2024
*/
bool user_choose(std::string text_to_be_displayed){
    std::cout << text_to_be_displayed << " (y|n)" << std::endl;
    char choice;
    do
    {
        std::cin >> choice;
    } while (choice != 'y' && choice != 'n');

    if(choice == 'y'){
        return true;
    } else {
        return false;
    }
}
    
/*
user_choose_int is a method that displays a parameter given text and allows receiving an integer

MKL. 2024
*/
int user_choose_int(std::string text_to_be_displayed){
    std::cout << text_to_be_displayed << std::endl;
    int choice;
    std::cin >> choice;
    return choice;
}

/*
user_choose_double is a method that displays a parameter given text and allows receiving a double

MKL. 2024
*/
double user_choose_double(std::string text_to_be_displayed){
    std::cout << text_to_be_displayed << std::endl;
    double choice;
    std::cin >> choice;
    return choice;
}
 
/*
shoutout correctly and in the same way formats out the shoutout for the user to see.
MKL. 2024
*/
void shoutout(std::string algo_abrev, std::string best_option, std::string corrupt_card_name, double LS_Dist, double SA_Dist, double Accumulated_Dist){
    std::cout << "  ---- Card restored ---  \n"
    "  Algorithm: " << algo_abrev << "\n" <<
    "  Corrupt Card: " << corrupt_card_name << "\n" <<
    "  New Name: " << best_option << "\n" <<
    // print out only the first 3 after decimal numbers of the double values
    "  LS_Dist: " << std::fixed << std::setprecision(3) << LS_Dist << " | " <<
    "  SA_Dist: " << std::fixed << std::setprecision(3) << SA_Dist << " | " <<
    "  Accumulated_Dist: " << std::fixed << std::setprecision(3) << Accumulated_Dist <<
    "\n-----------------" << std::endl;
}

/*
user choose chars vector lets the user input a series of char symbols. 
First, they are asked how many they are going to input, then, they input as many 
as before set
MKL. 2024
*/
std::vector<char> user_choose_chars_vector(std::string text_to_be_displayed){
    std::cout << text_to_be_displayed << std::endl;
    int amount;
    std::cout << "How many characters are you going to input?" << std::endl;
    std::cin >> amount;
    std::vector<char> chars;
    for(int i = 0; i < amount; i++){
        char c;
        std::cout << "Enter character " << i+1 << ": ";
        std::cin >> c;
        chars.push_back(c);
    }
    return chars;
}