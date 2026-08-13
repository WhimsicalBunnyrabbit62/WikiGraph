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

    std::vector<uint32_t> offsets;
    std::vector<uint32_t> cursors;
    offsets.resize(maximumId+1);
    cursors.resize(maximumId+1);

    offsets[0] = cursors[0] = 0;
    offsets[1] = cursors[1]= outdegrees[0];

    for (size_t i{2}; i <= maximumId+1; ++i) 
        cursors[i] = offsets[i] = offsets[i-1] + outdegrees[i-1];

    std::cout << offsets[maximumId+1] << std::endl;

    std::vector<uint32_t> neighbors;
    neighbors.resize(28511807); // HARD CODED FIX IF CHANGING DATASETS

    return 0;
}