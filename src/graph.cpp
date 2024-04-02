#include "headers/graph.hpp"
#include <vector>

Matrix::Matrix() {}

void Matrix::set_node(int x, int y, int value) { matrix[x][y] = value; }

void Matrix::delete_node(int index) {
  for (auto i : matrix) {
    i.erase(i.begin() + index);
  }

  matrix.erase(matrix.begin() + index);
}

void Matrix::add_vector() {
  std::vector new_vec = std::vector<int>();
  for (auto i : matrix) {
    i.push_back(-1);
    new_vec.push_back(-1);
  }
  this->matrix.push_back(new_vec);
}

void MatrixGraph::add_node(std::string node_name) {
  matrix.add_vector();
  indexs.push_back(node_name);
}

MatrixGraph::MatrixGraph(bool directed) { this->directed = directed; }

int MatrixGraph::get_index(std::string node_name) {

  int index = -1;
  for (int i = 0; i < indexs.size(); i++)
    if (indexs[i] == node_name) {
      index = i;
      break;
    }
  return index;
}

void MatrixGraph::delete_node(std::string node_name) {
  int index = get_index(node_name);

  if (index == -1)
    return;

  matrix.delete_node(index);
  indexs.erase(indexs.begin() + index);
}

void MatrixGraph::add_distance(std::string a, std::string b, int distance) {
  int index_a = get_index(a);
  int index_b = get_index(b);

  if (index_a == -1 || index_b == -1)
    return;

  matrix.set_node(index_a, index_b, distance);

  if (!directed)
    matrix.set_node(index_b, index_a, distance);
}
