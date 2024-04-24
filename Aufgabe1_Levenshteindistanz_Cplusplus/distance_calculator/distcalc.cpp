#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

/*
distcalc takes two strings and 
calculates the levensteindistance between them
as an int that gets returned

MKL. 2024
*/
int calc_dist_int(const std::string word1, const std::string word2, bool print_matrix = false) {

    //creating a matrix with the size of the two words
    std::vector<std::vector<int>> matrix(word2.size() + 1, std::vector<int>(word1.size() + 1));

    //filling the first row and column
    for (size_t i = 0; i <= word1.size(); ++i)
        matrix[0][i] = i;
    for (size_t i = 0; i <= word2.size(); ++i)
        matrix[i][0] = i;

    //iterating over matrix, filling as we go dynamically
    for (size_t i = 1; i <= word2.size(); ++i) {
        for (size_t j = 1; j <= word1.size(); ++j) {
            // checking surroundings and adding 1 if the letters are different
            if (word1[j - 1] == word2[i - 1])
                matrix[i][j] = matrix[i - 1][j - 1];
            else
                matrix[i][j] = std::min({ matrix[i - 1][j - 1], matrix[i - 1][j], matrix[i][j - 1] }) + 1;
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
