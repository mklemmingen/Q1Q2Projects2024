#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

/*
distcalc takes two strings and 
calculates the levensteindistance between them
as an int that gets returned.

print_matrix is an optional parameter that can be set to true to print out the calculation matrix.

takes a list of unkown-characters that always need a distance of 0 added.

MKL. 2024
*/
int calc_dist_int(const std::string word1, const std::string word2, bool print_matrix,
                 std::vector<char> change_special_chars,
                 bool transposition, int transposition_cost, 
                 int substitution_cost, int insertion_cost, int deletion_cost) {

    std::vector<std::vector<int>> matrix(word2.size() + 1, std::vector<int>(word1.size() + 1));

    for (size_t i = 0; i <= word1.size(); ++i)
        matrix[0][i] = i * deletion_cost;
    for (size_t i = 0; i <= word2.size(); ++i)
        matrix[i][0] = i * insertion_cost;

    for (size_t i = 1; i <= word2.size(); ++i) {
        for (size_t j = 1; j <= word1.size(); ++j) {

            if (std::find(change_special_chars.begin(), change_special_chars.end(), word1[j - 1]) != change_special_chars.end() ||
                std::find(change_special_chars.begin(), change_special_chars.end(), word2[i - 1]) != change_special_chars.end()) {
                matrix[i][j] = 0;
                continue;
            }

            int cost = (word1[j - 1] == word2[i - 1]) ? 0 : substitution_cost;

            matrix[i][j] = std::min({matrix[i - 1][j] + deletion_cost, 
                                     matrix[i][j - 1] + insertion_cost, 
                                     matrix[i - 1][j - 1] + cost});

            if (transposition && i > 1 && j > 1 && word1[j - 1] == word2[i - 2] && word1[j - 2] == word2[i - 1]) {
                matrix[i][j] = std::min(matrix[i][j], matrix[i - 2][j - 2] + transposition_cost);
            }
        }
    }
    
    if (print_matrix)
    {
        //printing the matrix
        for (size_t i = 0; i <= word2.size(); ++i) {
            for (size_t j = 0; j <= word1.size(); ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    //returning the distance as an int at the end of the matrix
    return matrix[word2.size()][word1.size()];
}
