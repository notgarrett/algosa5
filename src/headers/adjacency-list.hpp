/**
 * @file adjacency-list.hpp
 * @author  Lilith Moon
 */

#pragma once
#include <vector>
using namespace std;

// * Forward Declarations ============

template <typename keyType>
class Vertex;

template <typename keyType>
class Edge;

template <typename keyType>
class Adj_List_Graph;

// * Vertex Definition ===============

template <typename keyType>
class Vertex
{
  keyType key;
  pair<int, int> coords;
  vector<Edge<keyType>> *edges;

public:
  // * Constructors
  Vertex() : key(), coords(), edges(new vector<Edge<keyType>>()) {}
  Vertex(keyType vertKey) : key(vertKey), edges(new vector<Edge<keyType>>()), coords({0, 0}) {}
  Vertex(keyType vertKey, int x, int y) : key(vertKey), coords(std::make_pair(x, y)), edges(new std::vector<Edge<keyType>>()) {}
  Vertex(const Vertex &other) : key(other.key), coords(other.coords), edges(new std::vector<Edge<keyType>>(*(other.edges))) {}

  // * Functions
  void addEdge(const Edge<keyType> &edge) const;
  float distanceFrom(const Vertex<keyType> &other) const;
  void PrintVertex() const;
  void PrintVertexWithEdges() const;

  // * Getters
  keyType getKey() const { return key; };
  const vector<Edge<keyType>> &getEdges() const { return *edges; };


  bool operator==(const Vertex<keyType> &other) const
  {
    return key == other.key && coords == other.coords;
  }
};

// * Edge Definition ==================
template <typename keyType>
class Edge
{
  const Vertex<keyType> *src;
  const Vertex<keyType> *dest;
  float weight;

public:
  // * Constructors
  Edge(const Vertex<keyType> *srcIn, const Vertex<keyType> *destIn) : src(srcIn), dest(destIn), weight(srcIn->distanceFrom(*destIn)) {}
  Edge(const Vertex<keyType> *srcIn, const Vertex<keyType> *destIn, float weightIn) : src(srcIn), dest(destIn), weight(weightIn) {}

  // * Functions
  void printEdge() const;

  // * Getters
  float getWeight() const { return weight; }
  const Vertex<keyType> *getSource() const { return src; }
  const Vertex<keyType> *getDestination() const { return dest; }
};

// * Adjacency List Graph Definition ==============
template <typename keyType>
class Adj_List_Graph
{
  int numVertices = -1;
  int numEdges = -1;
  bool isDirected = false;
  bool graphIsLoaded = false;
  vector<Vertex<keyType>> *adjList = new vector<Vertex<keyType>>();

public:
  // * Constructor
  Adj_List_Graph(){};
  Adj_List_Graph(string file) {graphIsLoaded = parseFile(file);};

  // * Functions
  bool parseFile(string file);
  void addEdge(keyType srcKey, keyType destKey, float weightIn = 0);
  void addVertex(Vertex<keyType> vertexIn);
  void PrintGraph();
  void PrintVertices();
  void PrintVertexKeys();
  void dijkstra(keyType srcKey, keyType destKey);

  // * Getters
  const Vertex<keyType> *getVertex(keyType vertexKey) const;
  bool isGraphLoaded() {return graphIsLoaded;};
};
