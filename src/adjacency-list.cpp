/**
 * @file adjacency-list.cpp
 * @author Lilith Moon
 * @brief
 * @version 0.1
 * @date 2024-03-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <fstream>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <queue>
#include <limits>
#include <unordered_map>
#include "headers/adjacency-list.hpp"

// * Helper Function =============
/**
 * @brief Helper function to convert a string to the correct keyTyppe
 *
 * @tparam keyType
 * @param str
 * @return keyType
 */
template <typename keyType>
keyType convertToKeyType(const std::string &str)
{
  std::stringstream ss(str);
  keyType value;
  ss >> value;
  return value;
}

// * Vertex Definitions =============
/**
 * @brief Add an edge to edge vector
 *
 * @tparam keyType
 * @param edge
 */
template <typename keyType>
void Vertex<keyType>::addEdge(const Edge<keyType> &edge) const
{
  // * Is source vertex for edge this vertex
  if (edge.getSource()->getKey() == key)
    edges->push_back(edge);
  else
    std::cerr << "Error: Can't add edge, Incorrect Source." << std::endl;
}

/**
 * @brief Return the coordinate based distance from this Vertex to another Vertex
 *
 * @tparam keyType
 * @param other
 * @return float
 */
template <typename keyType>
float Vertex<keyType>::distanceFrom(const Vertex<keyType> &other) const
{
  int difx = other.coords.first - coords.first;
  int dify = other.coords.second - coords.second;
  return sqrt(difx * difx + dify * dify);
}

/**
 * @brief Prints Vertex and it's edges
 *
 * @tparam keyType
 */
template <typename keyType>
void Vertex<keyType>::PrintVertex() const
{
  // Print vertex information
  std::cout << "Vertex with key: " << key << " at coordinates (" << coords.first << ", " << coords.second << ")" << std::endl;

  // Print edges
  for (const Edge<keyType> &edge : *edges)
  {
    std::cout << "         |> ";
    edge.printEdge();
  }
}

// * Edge Definitions =============

/**
 * @brief Print's edge
 *
 * @tparam keyType
 */
template <typename keyType>
void Edge<keyType>::printEdge() const
{
  std::cout << "Edge from vertex with key: " << src->getKey() << " to vertex with key: " << dest->getKey() << " (Weight: " << weight << ")" << std::endl;
}

// * Adjacency List Graph Definitions ============
/**
 * @brief Attempts to retrieve a vertex reference via key
 * 
 * @tparam keyType 
 * @param vertexKey 
 * @return const Vertex<keyType>* 
 */
template <typename keyType>
const Vertex<keyType> *Adj_List_Graph<keyType>::getVertex(keyType vertexKey) const
{
  for (const Vertex<keyType> &vertex : *adjList)
    if (vertex.getKey() == vertexKey)
      return &vertex; // Found the vertex

  // No vertex
  std::cout << "Vertex: " << vertexKey << " Not in graph." << std::endl;
  return nullptr;
}


/**
 * @brief Adds edge between 2 vertices so long as both exist in graph
 *
 * @tparam keyType
 * @param srcKey
 * @param destKey
 * @param weightIn
 */
template <typename keyType>
void Adj_List_Graph<keyType>::addEdge(keyType srcKey, keyType destKey, float weightIn)
{
  const Vertex<keyType> *srcVertex = getVertex(srcKey);
  const Vertex<keyType> *destVertex = getVertex(destKey);

  if (srcVertex == nullptr || destVertex == nullptr)
  {
    cerr << "Source or destination vertex not in graph." << endl;
    return;
  }

  // Both vertices exist in graph
  if (weightIn != 0)
  {
    Edge<keyType> newEdge(srcVertex, destVertex, weightIn);
    srcVertex->addEdge(newEdge);
  }
  else
  {
    Edge<keyType> newEdge(srcVertex, destVertex);
    srcVertex->addEdge(newEdge);
  }
}

/**
 * @brief Adds Vertex to graph
 *
 * @tparam keyType
 * @param vertexIn
 */
template <typename keyType>
void Adj_List_Graph<keyType>::addVertex(Vertex<keyType> vertexIn)
{
  adjList->push_back(vertexIn);
}

/**
 * @brief Prints whole graph
 *
 * @tparam keyType
 */
template <typename keyType>
void Adj_List_Graph<keyType>::PrintGraph()
{
  std::cout << "<==================================================================>" << std::endl;
  // Print graph info
  std::cout << "Number of vertices: " << numVertices << std::endl;
  std::cout << "Number of edges: " << numEdges << std::endl;
  std::cout << "Directed graph: " << (isDirected ? "Yes" : "No") << std::endl;

  // Print vertices and their edges
  for (const Vertex<keyType> &vertex : *adjList)
  {
    std::cout << "<+++++++++++++++++++++++++++++>" << std::endl;
    vertex.PrintVertex();
  }
  std::cout << "<==================================================================>" << std::endl;
}

/**
 * @brief Construct a new Adj_List_Graph<keyType>::Adj_List_Graph object
 *
 * @tparam keyType
 * @param file data file
 */
template <typename keyType>
Adj_List_Graph<keyType>::Adj_List_Graph(string file)
{
  std::ifstream inputFile(file);

  if (!inputFile.is_open())
  { // * File not found
    std::cerr << "Failed to open file: " << file << std::endl;
    return;
  }

  std::string line;
  int rowCount = 0;

  while (std::getline(inputFile, line))
  { // * Read file line by line
    std::istringstream iss(line);
    std::string token;
    rowCount++;
    int colCount = 0;

    if (rowCount == 1 || rowCount == 2)
    { // * Process first two rows differently
      if (rowCount == 1)
      { // * Row 1, read if directed
        if (line == "directed")
          isDirected = true;
      }
      else
      { // * Row 2, get number of vertices and edges
        while (iss >> token)
        {
          if (colCount == 0) // First col is verts
            numVertices = stoi(token);
          else if (colCount == 1) // Second col is edges
            numEdges = stoi(token);
          colCount++;
        }
      }
    }
    else
    { // * Process Vertices and Edges
      if (rowCount <= numVertices + 2)
      { // * Handle Vertices
        keyType key;
        int x;
        int y;

        while (iss >> token)
        {
          switch (colCount)
          {
          case 0:
            if (token == "vertex")
            { // This will disregard word Vertex and treat col 1 as col 0
              colCount--;
              break;
            }
            key = convertToKeyType<keyType>(token);
            break;
          case 1:
            x = stoi(token);
            break;
          case 2:
            y = stoi(token);
            break;

          default:
            std::cout << "Ayyo how did we get here? Failed to make vertex. colCount: " << colCount << " token: " << token << std::endl;
            break;
          }
          colCount++;
        }
        // * Create and add new Vertex
        Vertex<keyType> newVertex(key, x, y);
        adjList->push_back(newVertex);
      }
      else if (rowCount <= numVertices + numEdges + 2)
      { // * Handle Edges
        keyType srcKey;
        keyType destKey;
        float weight;

        while (iss >> token)
        {
          switch (colCount)
          {
          case 0:
            if (token == "edge")
            { // This will disregard word edge and treat col 1 as col 0
              colCount--;
              break;
            }
            srcKey = convertToKeyType<keyType>(token);
            break;
          case 1:
            destKey = convertToKeyType<keyType>(token);
            break;
          case 2:
            weight = stof(token);
            break;
          default:
            std::cout << "Ayyo how did we get here? Failed to make edge. colCount: " << colCount << " token: " << token << std::endl;
            break;
          }
          colCount++;
        }

        if (weight)
        {
          if (!isDirected) // * Bidirectional, add edge to both verts
            addEdge(destKey, srcKey, weight);
          addEdge(srcKey, destKey, weight);
        }
        else
        {
          if (!isDirected)
            addEdge(destKey, srcKey);
          addEdge(srcKey, destKey);
        }
      }
      else
      { // * Execute djkstras for given vertices
        keyType srcKey;
        keyType destKey;

        while (iss >> token)
        {
          switch (colCount)
          {
          case 0:
            if (token == "dijkstra")
            { // This will disregard word dijkstra and treat col 1 as col 0
              colCount--;
              break;
            }
            srcKey = convertToKeyType<keyType>(token);
            break;
          case 1:
            destKey = convertToKeyType<keyType>(token);
            break;
          default:
            break;
          }
          colCount++;
        }
        // * Call dijkstra's algo
        dijkstra(srcKey, destKey);
      }
    }
  }

  inputFile.close();
}

/**
 * @brief Find shorted path between 2 vertices
 *
 * @tparam keyType
 * @param srcKey
 * @param destKey
 */
template <typename keyType>
void Adj_List_Graph<keyType>::dijkstra(keyType srcKey, keyType destKey)
{
  // * Make sure keys exists in graph
  if (getVertex(srcKey) == nullptr || getVertex(destKey) == nullptr)
    return;

  // * Initialize distances
  std::unordered_map<keyType, float> dist;
  std::unordered_map<keyType, bool> visited;
  std::unordered_map<keyType, keyType> parent;

  for (const Vertex<keyType> &vertex : *adjList)
  { // * Init each map for the number of verts in graph
    dist[vertex.getKey()] = std::numeric_limits<float>::infinity();
    visited[vertex.getKey()] = false;
    parent[vertex.getKey()] = -1;
  }
  dist[srcKey] = 0;

  // * Priority Queue sorted by distance
  std::priority_queue<std::pair<float, keyType>, std::vector<std::pair<float, keyType>>, std::greater<std::pair<float, keyType>>> pq;
  pq.push(std::make_pair(0, srcKey));

  while (!pq.empty())
  {
    // * Remove vertex
    keyType u = pq.top().second;
    pq.pop();

    // * Mark vertex as visited
    visited[u] = true;

    // * Stop if destination reached
    if (u == destKey)
      break;

    // * Update distances of connected verts
    const Vertex<keyType> *uVertex = getVertex(u);
    for (const Edge<keyType> &edge : uVertex->getEdges())
    {
      keyType v = edge.getDestination()->getKey();
      float weight = edge.getWeight();
      if (!visited[v] && dist[u] + weight < dist[v])
      { // Is distance to v from u shorter than current best distance to v
        dist[v] = dist[u] + weight;
        pq.push(std::make_pair(dist[v], v));
        parent[v] = u;
      }
    }
  }

  // Create path vector starting from destination to source
  keyType currentVertex = destKey;
  std::vector<keyType> path;
  while (currentVertex != -1)
  {
    path.push_back(currentVertex);
    currentVertex = parent[currentVertex];
  }

  // Print the path in reverse order
  std::cout << "Shortest path from vertex " << srcKey << " to " << destKey << ": ";
  for (auto it = path.rbegin(); it != path.rend(); ++it)
    std::cout << *it << " ";
  std::cout << "with cost " << dist[destKey] << std::endl;
}
