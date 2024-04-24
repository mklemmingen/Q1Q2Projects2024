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
int calc_dist_int(const std::string word1, const std::string word2, bool print_matrix = false,
                 std::vector<std::pair<char, char>> change_special_chars = {},
                 bool transposition = false,
                 int transposition_cost = 1) {

    //creating a matrix with the size of the two words
    std::vector<std::vector<int>> matrix(word2.size() + 1, std::vector<int>(word1.size() + 1));

    //filling the first row and column
    for (size_t i = 0; i <= word1.size(); ++i)
        matrix[0][i] = i;
    for (size_t i = 0; i <= word2.size(); ++i)
        matrix[i][0] = i;

    // iterating over matrix, filling as we go dynamically. 
    // If the letters are the same, the distance is 0, else 1.
    // if either the word1 or the word2 character is in the list of change_special_characters, the distance is a 0, since it could be the same. 

    for (size_t i = 1; i <= word2.size(); ++i) {
        for (size_t j = 1; j <= word1.size(); ++j) {
            int cost = (word1[j - 1] == word2[i - 1] ? 0 : 1);
            if (std::find(change_special_chars.begin(), change_special_chars.end(), std::make_pair(word1[j - 1], word2[i - 1])) != change_special_chars.end())
                cost = 0;
            matrix[i][j] = std::min({matrix[i - 1][j] + 1, matrix[i][j - 1] + 1, matrix[i - 1][j - 1] + cost});

            if(transposition){
                // using transposition according to damerau-levenshteiin (if current letter is the same as the previous letter of the other word, we can skip it.)
                // assuming cost of transposition is same as cost of substitution.
                if (i > 1 && j > 1 && word1[j - 1] == word2[i - 2] && word1[j - 2] == word2[i - 1]) 
                {
                matrix[i][j] = std::min(matrix[i][j], matrix[i - 2][j - 2] + cost);
                }
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
