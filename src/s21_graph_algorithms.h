#ifndef SRC_S21_GRAPH_ALGORITHMS_H_
#define SRC_S21_GRAPH_ALGORITHMS_H_

#include <limits>

#include "containers/queue.h"
#include "containers/stack.h"
#include "s21_graph.h"
#include "swarm.h"

namespace s21 {
struct TsmResult {
  std::vector<unsigned> vertices;
  double distance;
};

class GraphAlgorithms {
 public:
  GraphAlgorithms() = default;
  ~GraphAlgorithms() = default;

  std::vector<unsigned> DepthFirstSearch(Graph &graph, int startVertex);

  std::vector<unsigned> BreadthFirstSearch(Graph &graph, int startVertex);

  unsigned GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                          int vertex2);

  std::vector<std::vector<unsigned>> GetShortestPathsBetweenAllVertices(
      Graph &graph);

  std::vector<std::vector<unsigned>> GetLeastSpanningTree(Graph &graph);

  TsmResult SolveTravelingSalesmanProblem(Graph &graph);
};
}  // namespace s21

#endif  // SRC_S21_GRAPH_ALGORITHMS_H_
