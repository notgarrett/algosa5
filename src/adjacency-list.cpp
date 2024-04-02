#include <fstream>
#include <math.h>
#include <algorithm>
#include "headers/adjacency-list.hpp"

template <typename keyType>
Edge<keyType>::Edge(Vertex<keyType> srcIn, Vertex<keyType> destIn)
{
  src = srcIn;
  dest = destIn;
  weight = srcIn.distanceFrom(destIn);
}

template <typename keyType>
Edge<keyType>::Edge(Vertex<keyType> srcIn, Vertex<keyType> destIn, float weightIn)
{
  src = srcIn;
  dest = destIn;
  weight = weightIn;
}

template <typename keyType>
Vertex<keyType>::Vertex(keyType vertKey)
{
  key = vertKey;
}

template <typename keyType>
Vertex<keyType>::Vertex(keyType vertKey, int x, int y)
    : Vertex(vertKey)
{
    coords = std::make_pair(x, y);
}


template <typename keyType>
float Vertex<keyType>::distanceFrom(Vertex<keyType> other)
{
  int difx = other.coords.first - coords.first;
  int dify = other.coords.second - coords.second;
  return sqrt(difx * difx + dify * dify);
}

template <typename keyType>
void Adj_List_Graph<keyType>::setIsDirected(bool isDirectedIn){
  isDirected = isDirectedIn;
}

template <typename keyType>
void Adj_List_Graph<keyType>::addEdge(Vertex<keyType> srcIn, Vertex<keyType> destIn, float weightIn)
{
  // Find the source vertex in the adjacency list
  auto srcIt = std::find_if(adjList.begin(), adjList.end(), [&](const Vertex<keyType> &v)
                            { return v.key == srcIn.key; });

  // Find the source vertex in the adjacency list
  auto destIt = std::find_if(adjList.begin(), adjList.end(), [&](const Vertex<keyType> &v)
                            { return v.key == destIn.key; });

  // src not in graph
  if (srcIt == adjList.end())
  {
    std::cerr << "Source vertex not found in the adjacency list." << std::endl;
    return;
  }

  // dest not in graph
  if (destIt == adjList.end())
  {
    std::cerr << "Destination vertex not found in the adjacency list." << std::endl;
    return;
  }


  // Create a new edge
  Edge<keyType> newEdge;
  if(weightIn != 0)
    newEdge(srcIt, destIt, weightIn);
  else 
    newEdge(srcIt, destIt);

  // Add the edge to the source vertex's edges vector
  srcIt->edges.push_back(newEdge);
}

template <typename keyType>
void Adj_List_Graph<keyType>::PrintGraph(){
  // Iterate over each vertex in the adjList
  std::for_each(adjList.begin(), adjList.end(), [&](const Vertex<keyType>& vertex) {
        // Print the key of the current vertex
        std::cout << "Vertex: " << vertex.key << std::endl;

        // Print all edges and adjacent vertices of the current vertex
        std::for_each(vertex.edges.begin(), vertex.edges.end(), [&](const Edge<keyType>& edge) {
            std::cout << "  -> Connected to vertex with key: " << edge.dest.key << " (Weight: " << edge.weight << ")" << std::endl;
        });
    });
}

