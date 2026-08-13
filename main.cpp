#include <iostream>
#include <charconv>
#include <system_error>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <vector>
#include <cstdint>
#include <queue>
#include <unordered_set>

int bfs(uint32_t startNode, uint32_t target, const std::vector<uint32_t> &neighbors, const std::vector<uint32_t> &offsets) {
    if (startNode == target) return 0;

    std::vector<int> distance(1791489, -1);
    std::vector<bool> visited(1791489, false);
    std::queue<uint32_t> q;

    q.push(startNode);
    visited[startNode] = true;
    distance[startNode] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (size_t i{offsets[u]}; i < offsets[u+1]; ++i) {
            uint32_t n = neighbors[i];
            if (!visited[n]) {
                visited[n] = true;
                distance[n] = distance[u]+1;
                q.push(n);

                if (n == target) return distance[n];
            }
        }
    }

    return -1;
}

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

    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    int u, v;
    while (inputFile >> u >> v) 
        neighbors[cursors[u]++] = v;
    

    return 0;
}