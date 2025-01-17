#include <iostream>
#include "distcalc.h"
#include "strtool.h"

/*
This is a terminal-based c++ program that takes two words and
calculates the levenhstein distance between them.

It only accepts latin-script words. It automatically convertes all 
the letters to lowercase.                      

It uses the methods in file 'distcalcmeth.cpp' to calculate the distance.

MKL. 2024
*/
int main() {

	std::string word1, word2;

	bool allowed_words = false;
	while (!allowed_words) {

		// receiving both words

		std::cout << "Enter the first word: ";
		std::cin >> word1;
		std::cout << "Enter the second word: ";
		std::cin >> word2;

		allowed_words = true;

		if (!check_latin(word1) || !check_latin(word2)) {
			std::cout << "ERROR: The words should contain only latin letters." << std::endl;
			allowed_words = false;
		}
		
	}

	bool print_matrix = false;

	bool allowed_print = false;
	while (!allowed_print) {

		std::cout << "Would you like to print the matrix after the calculation? (y/n):" << std::flush;
		char answer;
		std::cin >> answer;
		if (answer == 'n') {
			allowed_print = true;
		}
		else if (answer == 'y') {
			print_matrix = true;
			allowed_print = true;
		}
		else {
			std::cout << "ERROR: Please enter 'y' or 'n'." << std::endl;
		}
	}

	to_lowercase(&word1);
	to_lowercase(&word2);

	std::cout << "The Levenhstein distance between " << word1 << " and " << word2 << " is: " << weighted_levenshtein(word1, word2, print_matrix) << std::endl;
	return 0;
}