#include "headers/adjacency-list.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

template <typename keyType> void parseFileToAdjList(string file) {
  std::ifstream inputFile(file);
  if (!inputFile.is_open()) {
    std::cerr << "Failed to open file: " << file << std::endl;
    return;
  }

  std::string line;
  int rowCount = 0;
  Adj_List_Graph<keyType> newGraph;
  while (std::getline(inputFile, line)) {
    ++rowCount;
    std::istringstream iss(line);
    std::string token;
    if (rowCount == 1 || rowCount == 2) {
      // Process first two rows differently
      if (rowCount == 1) {
        if (line == "directed")
          newGraph.setIsDirected(true);
      } else {
        while (iss >> token) {
          // Process each token in the line here
          std::cout << "Token: " << token << std::endl;
        }
      }

      std::cout << "Header " << rowCount << ": " << line << std::endl;
    } else {
      // Process other rows
      // For example, you can parse the line using std::istringstream
      while (iss >> token) {
        // Process each token in the line here
        std::cout << "Token: " << token << std::endl;
      }
    }
  }

  inputFile.close();
}

int main() {
  parseFileToAdjList<int>("../include/input-graph.txt");
  return 0;
}
