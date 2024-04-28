// distcalc.h header file

#ifndef DISTCALC_H
#define DISTCALC_H

#include <string>
#include <vector>

double weighted_levenshtein(const std::string& word1, const std::string& word2, bool print_matrix,
                            const std::vector<char>& change_special_chars = {},
                            bool transposition=false, double transposition_cost=1, 
                            double substitution_cost=1, double insertion_cost=1, double deletion_cost=1);


#endif

