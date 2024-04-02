#include <fstream>
#include "adjacency-list.hpp"




Adj_List_Graph::Adj_List_Graph(int vertices)
{
  numVertices = vertices;
}


void Adj_List_Graph::addEdge(int src, int dest)
{
  adjLists[src].push_back(dest);
}
