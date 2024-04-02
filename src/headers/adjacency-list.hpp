#pragma once

#include <vector>

using namespace std;

// Template 
template <typename keyType>
class Vertex;

template <typename keyType>
class Edge;

template <typename keyType>
class Adj_List_Graph;


template <typename keyType>
class Vertex{
  keyType key;
  pair<int,int> coords;
  vector<Edge<keyType>> *edges;


public:
  Vertex(keyType vertKey);
  Vertex(keyType vertKey, int x, int y);
  float distanceFrom(Vertex<keyType> other);
};

template <typename keyType>
class Edge{
  Vertex<keyType> src;
  Vertex<keyType> dest;
  float weight;

public:
  Edge(Vertex<keyType> srcIn, Vertex<keyType> destIn);
  Edge(Vertex<keyType> srcIn, Vertex<keyType> destIn, float weightIn);
};

template <typename keyType>
class Adj_List_Graph {
  vector<Vertex<keyType>> *adjList;
  bool isDirected = false;

public:
  Adj_List_Graph();
  void setIsDirected(bool isDirectedIn);
  void addEdge(Vertex<keyType> srcIn, Vertex<keyType> destIn, float weightIn = 0);
  void PrintGraph();
};


