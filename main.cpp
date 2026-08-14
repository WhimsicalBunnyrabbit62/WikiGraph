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

int bfs(uint32_t startNode, uint32_t target, const std::vector<uint32_t> &neighbors, const std::vector<uint32_t> &offsets, std::vector<int> &predecessor) {
    if (startNode == target) return 0;

    std::vector<int> distance(1791489, -1);
    std::queue<uint32_t> q;

    q.push(startNode);
    distance[startNode] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (size_t i{offsets[u]}; i < offsets[u+1]; ++i) {
            uint32_t n = neighbors[i];
            if (distance[n] == -1) {
                distance[n] = distance[u]+1;
                q.push(n);
                predecessor[n] = u;

                if (n == target) return distance[n];
            }
        }
    }

    return -1;
}

std::vector<std::string> buildNameList() {
    std::ifstream inputFile("wiki-topcats-page-names.txt");
    if (!inputFile.is_open()) { std::cout<<"sumtinwong"; return {}; }

    std::vector<std::string> result;
    result.resize(1791489); // HARD CODED FIX IF CHANGING DATASETS

    uint32_t id;
    std::string name;

    while (inputFile >> id) {
        std::getline(inputFile, result[id]);
    }

    return result;
}

int main() {
    std::ifstream inputFile("wiki-topcats.txt");
    if (!inputFile.is_open()) { std::cout<<"sumtinwong"; return 1; }

    int maximumId = INT_MIN;
    std::vector<uint32_t> outdegrees;
    outdegrees.resize(1791489); // HARD CODED FIX IF CHANGING DATASETS

    std::vector<std::string> names = buildNameList();

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
    

    std::vector<int> predecessor;
    predecessor.resize(1791489);

    int START = 1;
    int TARGET = 1748792;
    int result = bfs(START, TARGET, neighbors, offsets, predecessor);

    int indu = TARGET;

    if (result != -1) {
        std::vector<int> path;
        while (indu != START) {
            path.push_back(indu);
            indu = predecessor[indu];
        }

        path.push_back(START);
        std::reverse(path.begin(), path.end());

        for (size_t i{0}; i < path.size(); ++i) {
            std::cout << names[path[i]];
            if (i != path.size()-1) std::cout << " =>";
        }

        std::cout << std::endl;
    }

    return 0;
}