#ifndef SRC_S21_GRAPH_H_
#define SRC_S21_GRAPH_H_

#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace s21 {
class Graph {
 public:
  Graph() : size_(0), check_error_(false) {}
  Graph(int size) : size_(size), check_error_(false) {}
  Graph(unsigned the_size,
        std::function<unsigned(unsigned, unsigned)> generation);
  ~Graph() = default;

  int operator()(int row, int column) { return adjacency_matrix_[row][column]; }
  bool LoadGraphFromFile(std::string path);
  void ExportGraphToDot(std::string filename);

  void Alter(size_t from, size_t to, std::function<void(unsigned&)> alterator) {
    alterator(adjacency_matrix_[from][to]);
  }

  std::vector<std::vector<unsigned>> GetAdjacencyMatrix() {
    return adjacency_matrix_;
  }

  unsigned GetSize() { return size_; }

 private:
  std::vector<std::vector<unsigned>> adjacency_matrix_;
  unsigned size_;
  bool check_error_;

  void FillingVectors(std::string line);

  inline void SetAdjacencyMatrix(std::vector<unsigned> vec) {
    adjacency_matrix_.push_back(vec);
  }

  void SetSize(std::string line);
  void Clear();
};

}  // namespace s21

#endif  // SRC_S21_GRAPH_H_
