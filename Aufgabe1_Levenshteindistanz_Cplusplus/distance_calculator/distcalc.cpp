#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

/*
distcalc takes two strings and 
calculates the levensteindistance between them
as a double that gets returned.

it can take optional parameters to change the cost of all operations. 

print_matrix is an optional parameter that can be set to true to print out the calculation matrix.

takes an optional list of unkown-characters that always need a distance of 0 added.

MKL. 2024
*/
double weighted_levenshtein(const std::string word1, const std::string word2, bool print_matrix,
                 std::vector<char> change_special_chars,
                 bool transposition, int transposition_cost, 
                 int substitution_cost, int insertion_cost, int deletion_cost) {

    std::vector<std::vector<int>> matrix(word2.size() + 1, std::vector<int>(word1.size() + 1, 0));

    for (size_t i = 0; i <= word1.size(); ++i)
        matrix[0][i] = i * deletion_cost;
    for (size_t i = 0; i <= word2.size(); ++i)
        matrix[i][0] = i * insertion_cost;

    for (size_t i = 1; i <= word2.size(); ++i) {
        for (size_t j = 1; j <= word1.size(); ++j) {

            int cost;
            if (word1[j - 1] == '?' || word2[i - 1] == '?') {
                cost = substitution_cost/2; 
            } else {
                cost = (word1[j - 1] == word2[i - 1]) ? 0 : substitution_cost;
            }

            int del = matrix[i - 1][j] + deletion_cost;
            if (del < 0) del = 0;

            int ins = matrix[i][j - 1] + insertion_cost;
            if (ins < 0) ins = 0;

            int sub = matrix[i - 1][j - 1] + cost;
            if (sub < 0) sub = 0;

            matrix[i][j] = std::min({del, ins, sub});

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
