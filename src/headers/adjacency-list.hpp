#pragma once

#include <vector>

using namespace std;

class Vertices{
  int key;
  pair<int,int> coords;

public:
  Vertices(int Key, int x, int y);
};


class Adj_List_Graph {
  int numVertices;
  vector<int> *adjLists;

public:
  Adj_List_Graph(int vertices);
  void addEdge(int src, int dest);
};


