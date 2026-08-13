#include <iostream>
#include <charconv>
#include <system_error>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <vector>
#include <cstdint>

int main() {
    std::ifstream inputFile("wiki-topcats.txt");
    if (!inputFile.is_open()) { std::cout<<"sumtinwong"; return 1; }

    int maximumId = INT_MIN;
    std::vector<uint32_t> outdegrees;
    outdegrees.resize(1791489); // HARD CODED FIX IF CHANGING DATASETS


    int firstNum, secondNum;
    while (inputFile >> firstNum >> secondNum) {
        maximumId = std::max(maximumId, firstNum);
        outdegrees[firstNum]++;
    }

    std::cout << maximumId << std::endl;

    return 0;
}