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

	bool allowed = false;
	while (!allowed) {

		// receiving both words

		std::cout << "Enter the first word: ";
		std::cin >> word1;
		std::cout << "Enter the second word: ";
		std::cin >> word2;

		allowed = true;

		if (!check_latin(word1) || !check_latin(word2)) {
			std::cout << "ERROR: The words should contain only latin letters." << std::endl;
			allowed = false;
		}
		
	}

	bool print_matrix = false;

	bool allowed = false;
	while (!allowed) {

		std::cout << "Would you like to print the matrix after the calculation? (Y/n):";
		char answer;
		std::cin >> answer;
		if (answer == 'n') {
			allowed = true;
		}
		else if(answer == '\n'){
			print_matrix = true;
			allowed = true;
		}
		else if (answer == 'y') {
			print_matrix = true;
			allowed = true;
		}
		else {
			std::cout << "ERROR: Please enter 'y' or 'n'." << std::endl;
	}

	to_lowercase(&word1);
	to_lowercase(&word2);

	std::cout << "The Levenhstein distance between " << word1 << " and " << word2 << " is: " << calc_dist_int(word1, word2, print_matrix) << std::endl;
	return 0;
}
