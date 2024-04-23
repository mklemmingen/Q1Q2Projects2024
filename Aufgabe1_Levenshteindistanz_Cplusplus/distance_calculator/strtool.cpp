#include <string>

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