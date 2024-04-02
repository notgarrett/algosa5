#pragma once

#include <vector>

class Matrix {
  std::vector<std::vector<bool>> matrix;

public:
  Matrix();
  void add_node();
  void delete_node();
};

class Graph {
  Matrix matrix;

public:
  Graph();
};
