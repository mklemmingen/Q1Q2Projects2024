// distcalc.h header file

#ifndef DISTCALC_H
#define DISTCALC_H

#include <string>
#include <vector>

double weighted_levenshtein(const std::string word1, const std::string word2, bool print_matrix = false, 
std::vector<char> change_special_chars = {},
bool transposition = false, int transposition_cost = 1,
int insertion_cost = 1, int deletion_cost = 1, int substitution_cost = 1);

#endif

