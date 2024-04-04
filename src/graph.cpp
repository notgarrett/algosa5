#include "headers/graph.hpp"
#include <fstream>
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

void MatrixGraph::add_node(std::string node_name, int coord = 0) {
  matrix.add_vector();
  indexs.push_back({node_name, coord});
}

MatrixGraph::MatrixGraph(bool directed) { this->directed = directed; }

void MatrixGraph::generate(std::ifstream file) {}

int MatrixGraph::get_index(std::string node_name) {

  int index = -1;
  for (int i = 0; i < indexs.size(); i++)
    if (indexs[i].first == node_name) {
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

std::string MatrixGraph::dijkstra_helper(std::string a, std::string b,
                                         std::vector<std::vector<int>> matrix,
                                         std::string prev) {

  int a_index = get_index(a);

  std::string return_string = "";

  if (a_index == get_index(b))
    return_string.append(b);
  else
    return_string.append(a + " -> ");

  for (int i = 0; i < matrix[a_index].size(); i++) {

    if (i == a_index)
      continue;
    std::string path = dijkstra_helper(indexs[i].first, b, matrix, a);
    if (path.back() == b.back()) {
      return_string.append(path);
    }
  };

  return return_string;
}

std::string MatrixGraph::dijkstra(std::string a, std::string b) {
  std::vector<bool> visited_indices = std::vector<bool>();

  for (auto i : matrix.get_matrix()) {
    visited_indices.push_back(false);
  }

  std::vector<std::vector<int>> dijkstra_matrix =
      std::vector<std::vector<int>>();
  int a_index = get_index(a);
  visited_indices.push_back(a_index);
  std::vector<std::vector<int>> matrix_copy = matrix.get_matrix();
  std::vector<std::vector<int>> d_matrix = std::vector<std::vector<int>>();

  for (int i = 0; i < matrix_copy.size(); i++) {
    d_matrix.push_back(std::vector<int>());
    for (auto j : matrix_copy[i])
      d_matrix[i].push_back(-1);
  }

  for (int i = 0; i < matrix_copy.size(); i++) {
    int smallest = -1;
    int index = 0;
    for (int j = 0; j < matrix_copy[i].size(); j++) {
      if (smallest == -1)
        smallest = matrix_copy[i][j];
      if (visited_indices[j] == true)
        continue;
      if (matrix_copy[i][j] < smallest) {
        smallest = matrix_copy[i][j];
        index = j;
      }
    }
    visited_indices[index] = true;
    d_matrix[i][index] = smallest;
    if (!directed)
      d_matrix[index][i] = smallest;
  }

  return dijkstra_helper(a, b, d_matrix, a);
}
