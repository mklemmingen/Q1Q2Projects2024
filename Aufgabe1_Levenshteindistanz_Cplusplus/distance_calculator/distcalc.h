// distcalc.h header file

#ifndef DISTCALC_H
#define DISTCALC_H

#include <string>
#include <vector>

int calc_dist_int(const std::string word1, const std::string word2, bool print_matrix = false, std::vector<std::pair<char, char>> change_special_chars = {});

#endif

