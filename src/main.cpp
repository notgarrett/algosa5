#include "headers/graph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>

#include "adjacency-list.cpp"

int main()
{
  // Adj_List_Graph<int> adjGraph1("../include/input-graph.txt");
  // adjGraph1.dijkstra(3, 1);
  // std::cout << "PRINTING GRAPH 1" << std::endl;
  // adjGraph1.PrintGraph();

  // printf("\n Graph 2: \n");

  // Adj_List_Graph<char> adjGraph2("../include/canada.txt");
  // adjGraph2.dijkstra('t', 't');
  // adjGraph2.dijkstra('t', 'm');
  // adjGraph2.dijkstra('e', 't');

  // std::cout << "PRINTING GRAPH 2" << std::endl;
  // adjGraph2.PrintGraph();

  // * Loop

  std::cout << "My input files are slightly modified. Here are the paths to enter:" << std::endl;
  std::cout << "\"../include/input-graph.txt\" - Int Keys\n\"../include/canada.txt\" - Char Keys" << std::endl;

  std::string filename;
  char keyChoice;
  char implementationChoice;

  while (true)
  {
    std::cout << "Enter the graph filename: ";
    std::cin >> filename;

    std::cout << "Adj List or Adj Matrix? (L/M): ";
    std::cin >> implementationChoice;

    if (implementationChoice == 'L' || implementationChoice == 'l')
    {
      Adj_List_Graph<int> adjGraphInt;
      Adj_List_Graph<char> adjGraphChar;

      std::cout << "Are the keys in the graph integers or characters? (I/C): ";
      std::cin >> keyChoice;

      if (keyChoice == 'I' || keyChoice == 'i')
      {
        if (adjGraphInt.parseFile(filename))
        {
          std::cout << "\nVertices in the graph:  ";
          adjGraphInt.PrintVertexKeys();
          std::cout << std::endl;

          int source, dest;
          // * Loop for src dest pairs
          while (true)
          {
            std::cout << "Enter source and destination vertices (separated by space): ";
            std::cin >> source >> dest;

            auto start = std::chrono::steady_clock::now();
            adjGraphInt.dijkstra(source, dest);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            std::cout << "Time taken to find the shortest path: " << elapsed_seconds.count() << " seconds\n\n";
          }
          break;
        }
        else
        {
          std::cout << "Error loading graph from file! Please enter a valid filename.\n";
        }
      }
      else if (keyChoice == 'C' || keyChoice == 'c')
      {
        if (adjGraphChar.parseFile(filename))
        {
          std::cout << "\nVertices in the graph:  ";
          adjGraphChar.PrintVertexKeys();
          std::cout << std::endl;
          char source, dest;
          // * Loop for src dest pairs
          while (true)
          {
            std::cout << "Enter source and destination vertices (separated by space): ";
            std::cin >> source >> dest;

            auto start = std::chrono::steady_clock::now();
            adjGraphChar.dijkstra(source, dest);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            std::cout << "Time taken to find the shortest path: " << elapsed_seconds.count() << " seconds\n\n";
          }
          break;
        }
        else
        {
          std::cout << "Error loading graph from file! Please enter a valid filename.\n";
        }
      }
      else
      {
        std::cout << "Invalid choice! Please enter 'I' for integers or 'C' for characters.\n";
      }
    }
    else if (implementationChoice == 'M' || implementationChoice == 'm')
    {
      // TODO: Garret you go here
    }
    else
    {
      std::cout << "Invalid choice! Please enter 'L' for Adjacency List or 'M' for Adjacency Matrix.\n";
    }
  }
  return 0;
}
