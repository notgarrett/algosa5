<<<<<<< HEAD
=======
#include "headers/adjacency-list.hpp"
#include "headers/graph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
>>>>>>> 2fa214d (time for merge..)

#include "adjacency-list.cpp"

<<<<<<< HEAD
int main()
{
  Adj_List_Graph<int> adjGraph1("../include/input-graph.txt");
  adjGraph1.dijkstra(3, 1);
  std::cout << "PRINTING GRAPH 1" << std::endl;
  adjGraph1.PrintGraph();
=======
  std::string line;
  int rowCount = 0;
  Adj_List_Graph<keyType> newGraph;
  while (std::getline(inputFile, line)) {
    ++rowCount;
    std::istringstream iss(line);
    std::string token;
    if (rowCount == 1 || rowCount == 2) {
      // Process first two rows differently
      if (rowCount == 1 && line == "directed")
        newGraph.setIsDirected(true);
      else {
        while (iss >> token) {
          // Process each token in the line here
          std::cout << "Token: " << token << std::endl;
        }
      }
>>>>>>> 2fa214d (time for merge..)

  printf("\n");

  Adj_List_Graph<char> adjGraph2("../include/canada.txt");
  adjGraph2.dijkstra('t', 't');
  adjGraph2.dijkstra('t', 'm');
  adjGraph2.dijkstra('e', 't');

<<<<<<< HEAD
  std::cout << "PRINTING GRAPH 2" << std::endl;
  adjGraph2.PrintGraph();
=======
MatrixGraph parseFileToMatrix(string file, bool directed) {
  MatrixGraph graph = MatrixGraph(directed);

  ifstream inputFile();

  return graph;
}

int main() {
  parseFileToAdjList<int>("../include/input-graph.txt");
>>>>>>> 2fa214d (time for merge..)
  return 0;
}
