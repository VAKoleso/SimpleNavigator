#include "s21_graph.h"

namespace s21 {
Graph::Graph(unsigned the_size,
             std::function<unsigned(unsigned, unsigned)> generation) {
  adjacency_matrix_.resize(the_size);

  for (unsigned i{}; i < the_size; ++i) {
    adjacency_matrix_[i].resize(the_size);

    for (unsigned j{}; j < the_size; ++j) {
      adjacency_matrix_[i][j] = generation(i, j);
    }
  }
}

void Graph::ExportGraphToDot(std::string filename) {
  std::string file_path{filename + ".dot"};
  std::fstream file;
  file.open(file_path, std::fstream::out);
  if (!file.is_open()) {
    throw std::runtime_error("Unable to write file");
  }
  std::string dot_separator;
  std::string dot_graph_type;

  dot_separator = " -- ";
  dot_graph_type = "graph ";

  file << dot_graph_type << "dotfile"
       << " {" << std::endl;
  for (unsigned i{}; i < size_; ++i) {
    for (unsigned j{}; j < size_; ++j) {
      if (adjacency_matrix_[i][j] == 1) {
        file << "\t" << i + 1 << dot_separator << j + 1 << ";" << std::endl;
      } else if (adjacency_matrix_[i][j] > 1) {
        file << "\t" << i + 1 << dot_separator << j + 1
             << " [label=" << adjacency_matrix_[i][j] << "];" << std::endl;
      }
    }
  }

  file << "}\n";
}

bool Graph::LoadGraphFromFile(std::string path) {
  Clear();
  check_error_ = false;
  std::ifstream file(path);
  std::string line;
  getline(file, line);
  SetSize(line);

  while (getline(file, line)) {
    if (!line.empty()) {
      FillingVectors(line);
    }
  }
  if (check_error_ || adjacency_matrix_.size() != size_) {
    Clear();
    return true;
  }
  return check_error_;
}

void Graph::FillingVectors(std::string line) {
  std::vector<unsigned> tmp_vector;
  size_t pos{};
  while (line.begin() != line.end()) {
    tmp_vector.push_back(stoi(line, &pos));
    line.erase(0, pos);
  }
  if (tmp_vector.size() != size_) {
    check_error_ = true;
    return;
  }
  SetAdjacencyMatrix(tmp_vector);
}

void Graph::SetSize(std::string line) {
  if (*line.begin() < '1' || *line.begin() > '9') {
    check_error_ = true;
    return;
  }
  size_ = stoi(line);
}

void Graph::Clear() {
  adjacency_matrix_.clear();
  size_ = 0;
}
}  // namespace s21
