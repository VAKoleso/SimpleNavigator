#ifndef SRC_CONSOLE_INTERFACE_H_
#define SRC_CONSOLE_INTERFACE_H_

#include <iostream>
#include <string>

#include "s21_graph.h"
#include "s21_graph_algorithms.h"

namespace s21 {
class ConsoleInterface {
 public:
  void Start();

 private:
  void DisplayMenu();
  int PerformChoice();

  void LoadGraphFromFile();
  void DepthFirstSearch();
  void BreadthFirstSearch();
  void GetShortestPathBetweenVertices();
  void GetShortestPathsBetweenAllVertices();
  void GetLeastSpanningTree();
  void SolveTravelingSalesmanProblem();

  int StartVertex();
  void PrintMatrix(std::vector<std::vector<unsigned>> vec);

 private:
  s21::Graph graph_;
  s21::GraphAlgorithms graph_algorithms_;
};
}  // namespace s21

#endif  // SRC_CONSOLE_INTERFACE_H_
