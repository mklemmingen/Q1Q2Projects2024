#include <iostream>
#include "distcalc.h"

// Function prototypes
bool check_latin(std::string word);
void to_lowercase(std::string* word);

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

		// receiving both words, 

		std::cout << "Enter the first word: ";
		std::cin >> word1;
		std::cout << "Enter the second word: ";
		std::cin >> word2;

		allowed = true;

		// check if the words contain only latin letters
		if (!check_latin(word1) || !check_latin(word2)) {
			std::cout << "ERROR: The words should contain only latin letters." << std::endl;
			allowed = false;
		}
		
	}

	//convert the words to lowercase
	to_lowercase(&word1);
	to_lowercase(&word2);

	std::cout << "The Levenhstein distance between " << word1 << " and " << word2 << " is: " << calc_dist_int(word1, word2) << std::endl;
	return 0;
}

/*
checking if the words contain only latin letters.
takes the string of the words and returns a boolean value.

MKL. 2024
*/
bool check_latin(std::string word) {
	for (int i = 0; i < word.length(); i++) {
		if (word[i] < 65 || word[i] > 122 || (word[i] > 90 && word[i] < 97)) {
			return false;
		}
	}
	return true;
}


/*
turning a word into lowercase using the ASCII values 
and the pointer to the string.

MKL. 2024
*/
void to_lowercase(std::string* word) {
	for (int i = 0; i < word->length(); i++) {
		if ((*word)[i] >= 65 && (*word)[i] <= 90) {
			(*word)[i] += 32;
		}
	}
}