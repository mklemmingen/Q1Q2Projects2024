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
    double Accumulated_Dist;
};

std::vector<Card> create_card_list(std::string filename);
void write_card_list(std::vector<Card> cards, std::string filename);
int char_quantity_similarity(std::string corrupt_card, std::string reference);
void check_correctness(std::string corrected_filename, std::string perfect_filename);
CloseCard user_decide(std::vector<CloseCard> cards);
bool user_choose(std::string text_to_be_displayed);
int user_choose_int(std::string text_to_be_displayed);
double user_choose_double(std::string text_to_be_displayed);
std::vector<char> user_choose_chars_vector(std::string text_to_be_displayed);
void shoutout(std::string algo_abrev, std::string best_option, std::string corrupt_card_name, 
                int LS_Dist, int SA_Dist, int Accumulated_Dist);

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

    int insertion_weight;
    int deletion_weight;
    int substitution_weight;
    int transposition_cost;
    int range_SA;        
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
            insertion_weight = user_choose_int("Enter the insertion weight for the levenshtein calculator: ");
            // get: deletion
            deletion_weight = user_choose_int("Enter the deletion weight for the levenshtein calculator: ");
            // get: substitution? 
            substitution_weight = user_choose_int("Enter the substitution weight for the levenshtein calculator: ");
        }

    if(use_transposition){
        // if use_transposition 
        // get: transposition cost
        transposition_cost = user_choose_int("Enter the transposition cost for the levenshtein calculator: ");
    }

    std::cout << "------------------------------------" << std::endl;

    // get: do you want to set unique characters who are universal and who never cost? (ex. "?")
    bool use_unknown_chars = user_choose("Do you want to set unique characters who are universal and who never cost? (ex. '?'): ");

        if(use_unknown_chars){

            std::cout << "--------------- UNKWNOWN CHARS ---------------------" << std::endl;

            // get: unknown chars as vector
            unknown_chars = user_choose_chars_vector("Entering the unknown characters... ");

            std::cout << "------------------------------------" << std::endl;
            
        }

    // get: do you want to decide yourself what the best fit for a corrupted card is in the Levenshtein-Distance-Algorithm?

    bool user_decision_LS = user_choose("Do you want to decide yourself what the best fit for a corrupted card is in the Levenshtein-Distance-Algorithm?: ");
    
    // get: do you want to use a range in which a reference word is still valid in the Levenshtein-Distance-Algorithm?

    int range_LS = user_choose_int("Enter the range in which a reference word is still valid in the Levenshtein-Distance-Algorithm: ");
    
    // print: "------- Similarity Algorithm -------"

    // do you want to use a similiarity algorithm to try and improve the result?

    bool use_similarity_algorithm = user_choose("Do you want to use a similiarity algorithm (SA) to try and improve the result?: ");

        // get: do you want to use a range in which cards are still valid to the shortest found distance?
        if(use_similarity_algorithm){
            // get: range
            range_SA = user_choose_int("Enter the range in which cards are still valid to the shortest found distance in the SA: ");
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

    // -----------------

    // loop over all reference cards with every corrupted card
    for (Card& corrupt_card : cards) {
        bool found = false;
        
        // map of all the close cards with "name : <distance_LS:distance_SA>"
        std::map<std::string, int> close_cards_LS;

        // SA map of all the close cards with "name : distance_SA"
        std::map<std::string, int> close_cards_SA;

        // close cards final
        // the final close cards is a vector of structs with: name, LS_Dist, SA_Dist, Accumulated_Dist
        std::vector<CloseCard> close_cards_final;


        // int closest distance for LS
        int closest_dist_LS = 1000;

        // int closest distance for SA
        int closest_dist_SA = 1000;

        // loop through all reference cards
        for (Card& reference_card : reference) {

            // using the Levenshtein distance calculator first -----------------------
            // getting distance between corrupt card and reference card
            int found_dist_LS = calc_dist_int(corrupt_card.name, reference_card.name, false, unknown_chars, use_transposition, transposition_cost, 
                                                insertion_weight, deletion_weight, substitution_weight);

            // ------- SHORTCUT

            // if the distance is 0, we can be sure that the card is the same and we can skip the rest of the loop
            // if the distance is under the percentage (by length of word) we automatically assign it aswell

            if(found_dist_LS == 0){
                corrupt_card.name = reference_card.name;
                shoutout(algo_abrev, reference_card.name, corrupt_card.name, found_dist_LS, 0, 0);
                break;
            } else if(found_dist_LS < (corrupt_card.name.length() * (percentage/100))){
                corrupt_card.name = reference_card.name;
                shoutout(algo_abrev, reference_card.name, corrupt_card.name, found_dist_LS, 0, 0);
                break;
            }

            // -------

            // checking if distance is new closest distance
            if (found_dist_LS < closest_dist_LS) {
                closest_dist_LS = found_dist_LS;
                // add the name and distance to the map
                close_cards_LS[reference_card.name] = found_dist_LS;
                // remove all cards in map that are above new closest + range
                for (auto it = close_cards_LS.begin(); it != close_cards_LS.end(); ) {
                    if (it->second > (closest_dist_LS+range_LS)) {
                        it = close_cards_LS.erase(it);
                    } else {
                        ++it;
                    }
                }
            } else if (found_dist_LS <= (closest_dist_LS+range_LS)) {
                // add card to list
                close_cards_LS[reference_card.name] = found_dist_LS;
            }

            // using the SA algorithm if allowed --------------------------------------

            if (use_similarity_algorithm){
                // using similarity_algorithm to find a fitting card
                int distance = char_quantity_similarity(corrupt_card.name, reference_card.name);

                // same procedure as in the LS
                if (distance < closest_dist_SA) {
                    closest_dist_SA = distance;
                    // add the name and distance to the map
                    close_cards_SA[reference_card.name] = distance;
                    // remove all cards in map that are above new closest + range
                    for (auto it = close_cards_SA.begin(); it != close_cards_SA.end(); ) {
                        if (it->second > (closest_dist_SA+range_SA)) {
                            it = close_cards_SA.erase(it);
                        } else {
                            ++it;
                        }
                    }
                } else if (distance <= (closest_dist_SA+range_SA)) {
                    // add card to list
                    close_cards_SA[reference_card.name] = distance;
                }
            }
            // next reference card
        }

        // ------------------------- SORT -------------------------
        // if user doesnt want the similarity algorithm, we only use the levenshtein distance map, sort it by distance into close_cards_final
        // if he wants to, we sort both into one close_cards_final

        // putting the LS Map into close_cards_final
        // going over ls map

        for(auto it = close_cards_LS.begin(); it != close_cards_LS.end(); ++it){
        CloseCard close_card;
        close_card.name = it->first;
        close_card.LS_Dist = it->second;
        close_card.SA_Dist = 0.0;
        close_card.Accumulated_Dist = it->second;
        close_cards_final.push_back(close_card);
        }

        if(!use_similarity_algorithm){
            // sorting the card deck by accumulated distance (which is only LS, respectfully)

            std::sort(close_cards_final.begin(), close_cards_final.end(), 
            [](CloseCard a, CloseCard b) { return a.Accumulated_Dist < b.Accumulated_Dist; });

        } else {
            // if user wants to use the similarity algorithm, we additionally put in the SA Map at respective positions

            // our SA is a : name : distance map
            // iterating over the SA map

            for(auto it = close_cards_SA.begin(); it != close_cards_SA.end(); it++){
                // if the name is already in the LS map, we add the distance to the respective card
                for(CloseCard& card : close_cards_final){
                    if(card.name == it->first){
                        card.SA_Dist = it->second;
                        card.Accumulated_Dist = card.LS_Dist + card.SA_Dist;
                    }
                }
            }

            // sort the card deck by accumulated distance
            // The lowest distance LS + SA is at the top and the highest at the bottom
            std::sort(close_cards_final.begin(), close_cards_final.end(), 
            [](CloseCard a, CloseCard b) { return a.Accumulated_Dist < b.Accumulated_Dist; });

        }

        // depending on if the user wants to decide for themself, we either
        // print out options and let user decide, or choose the first one in the sorted map

        if(user_decision_LS){
            // print out the best options ( all of user_decide )

            // declare that choosing is starting and what the corrupt card is:
            std::cout << "!- Attention -!" << std::endl;
            std::cout << "Choosing for corrupt card: " << corrupt_card.name << std::endl;

            CloseCard best_option = user_decide(close_cards_final);

            // shoutout
            shoutout(algo_abrev, best_option.name, corrupt_card.name, best_option.LS_Dist, best_option.SA_Dist,
            best_option.Accumulated_Dist);

            // assign the string to the card
            corrupt_card.name = best_option.name;
        } else {
            // choose the one with the lowest distance, if after it is another one with the same distance, use the first ( if there is ) 
            // with the same starting character. If there is none with the same starting character, use the first one

            int closest_dist = 1000;
            std::string closest_card = "";

            closest_dist = close_cards_final[0].Accumulated_Dist;

            bool still_same_distance = true;
            std::vector<CloseCard> same_distance_cards;
               
            while(still_same_distance){
                for(CloseCard card : close_cards_final){
                    if(card.Accumulated_Dist == closest_dist){
                        same_distance_cards.push_back(card);
                    } else {
                        still_same_distance = false;
                    }
                }
                closest_dist++;
            }

            // if there are multiple cards with the same distance, we choose the first one with the same starting character
            // as the corrupt card

            if(same_distance_cards.size() > 1){
                for(CloseCard card : same_distance_cards){
                    if(card.name[0] == corrupt_card.name[0]){

                        // shoutout
                        shoutout(algo_abrev, card.name, corrupt_card.name, card.LS_Dist, card.SA_Dist, card.Accumulated_Dist);
                        closest_card = card.name;
                        break;
                    }
                }
            } else {    
                // shoutout
                shoutout(algo_abrev, closest_card, corrupt_card.name, 
                same_distance_cards[0].LS_Dist, same_distance_cards[0].SA_Dist, same_distance_cards[0].Accumulated_Dist);
                closest_card = same_distance_cards[0].name;
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
int char_quantity_similarity(std::string corrupt_card, std::string reference){
    // comparing two strings by the number of individual characters and returning distance value
    int distance = 0;

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

    // loop over the corrupt card map and check if the character is in the reference map
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
MKL. 2024
*/
CloseCard user_decide(std::vector<CloseCard> cards){

    // prints out options with 
    // number | LS: LS_Dist | SA: SA_Dist | Accumulated_Dist | Name

    for(int i = 0; i < cards.size(); i++){
        std::cout << i+1 << " | LS: " << cards[i].LS_Dist << " SA: " << cards[i].SA_Dist << " Accu.Dist: " << cards[i].Accumulated_Dist << " | " << cards[i].name << std::endl;
    }

    // let user choose a number
    int choice;

    do
    {
        std::cin >> choice;
    } while (choice < 1 && choice > cards.size());

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
void shoutout(std::string algo_abrev, std::string best_option, std::string corrupt_card_name, int LS_Dist, int SA_Dist, int Accumulated_Dist){
    std::cout << "  ---- Card restored ---  \n"
    "  Algorithm: " << algo_abrev << "\n" <<
    "  Corrupt Card: " << corrupt_card_name << "\n" <<
    "  New Name: " << best_option << "\n" <<
    "  LS: " << LS_Dist << " | SA: " << SA_Dist << " | Accu.Dist: " << Accumulated_Dist <<
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