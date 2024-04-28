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
double weighted_levenshtein(const std::string& word1, const std::string& word2, bool print_matrix,
                            const std::vector<char>& change_special_chars,
                            bool transposition, double transposition_cost, 
                            double substitution_cost, double insertion_cost, double deletion_cost) {

    size_t len1 = word1.size(), len2 = word2.size();
    std::vector<std::vector<double>> dp(len1 + 1, std::vector<double>(len2 + 1));

    // Initialize the matrix
    for (size_t i = 0; i <= len1; i++)
        dp[i][0] = i * deletion_cost;
    for (size_t j = 0; j <= len2; j++)
        dp[0][j] = j * insertion_cost;

    // Fill the matrix
    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            double substitutionCost = (word1[i - 1] == word2[j - 1]) ? 0 : substitution_cost;
            dp[i][j] = std::min({dp[i - 1][j] + deletion_cost, 
                                 dp[i][j - 1] + insertion_cost, 
                                 dp[i - 1][j - 1] + substitutionCost});

            if (transposition && i > 1 && j > 1 && word1[i - 1] == word2[j - 2] && word1[i - 2] == word2[j - 1])
                dp[i][j] = std::min(dp[i][j], dp[i - 2][j - 2] + transposition_cost); 
        }
    }

    // Print the matrix if required
    if (print_matrix) {
        for (const auto &row : dp) {
            for (const auto &cell : row)
                std::cout << cell << ' ';
            std::cout << '\n';
        }
    }

    return dp[len1][len2];
}

