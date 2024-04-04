#pragma once

#include <fstream>
#include <string>
#include <vector>

class Matrix {

  std::vector<std::vector<int>> matrix;

public:
  Matrix();
  void add_vector();
  void set_node(int x, int y, int value);
  void delete_node(int index);
  int get_distance();
  std::vector<std::vector<int>> get_matrix();
};

class MatrixGraph {
  Matrix matrix;
  bool directed;

  std::vector<std::pair<std::string, int>> indexs;

  std::string dijkstra_helper(std::string a, std::string b,
                              std::vector<std::vector<int>> matrix,
                              std::string prev);

public:
  MatrixGraph(bool directed);
  void generate(std::ifstream);
  void add_node(std::string node_name, int coord);
  void delete_node(std::string node_name);
  void add_distance(std::string a, std::string b, int distance);
  int get_index(std::string node_name);
  std::string dijkstra(std::string a, std::string b);
};
