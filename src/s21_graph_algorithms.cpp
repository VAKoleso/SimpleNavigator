#include "s21_graph_algorithms.h"

namespace s21 {
std::vector<std::vector<unsigned>> GraphAlgorithms::GetLeastSpanningTree(
    Graph &graph) {
  if (!graph.GetSize()) throw std::invalid_argument("invalid_argument");
  std::vector<std::vector<unsigned>> vec = graph.GetAdjacencyMatrix();
  std::vector<std::vector<unsigned>> result;

  for (unsigned i{}; i < vec.size(); ++i) {
    std::vector<unsigned> tmp(vec.size());
    result.push_back(tmp);
  }

  std::set<unsigned> set1, set2;
  for (unsigned i{}; i < vec.size() - 1; ++i) set2.insert(i);

  set1.insert(0);
  set2.erase(0);
  while (!set2.empty()) {
    unsigned min = UINT32_MAX;
    std::pair<unsigned, unsigned> pos;
    auto it = set1.begin();
    while (it != set1.end()) {
      for (unsigned i{}; i < vec.size(); ++i) {
        if (!set1.count(i) && vec[*it][i] > 0 && vec[*it][i] < min) {
          min = vec[*it][i];
          pos = {*it, i};
        }
      }
      ++it;
    }
    set1.insert(pos.second);
    set2.erase(pos.second);
    result[pos.first][pos.second] = min;
  }
  return result;
}

std::vector<unsigned> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                          int startVertex) {
  if (startVertex < 1 || (unsigned)startVertex > graph.GetSize()) {
    throw std::invalid_argument("Incorrect starting vertex");
  }

  std::vector<unsigned> result;
  std::vector<bool> visited(graph.GetSize());
  s21::Queue<int> vertexQueue;

  visited[startVertex - 1] = true;
  vertexQueue.push(startVertex - 1);

  while (!vertexQueue.empty()) {
    result.push_back(vertexQueue.front() + 1);
    int current = vertexQueue.pop();

    for (unsigned i = 0; i < graph.GetSize(); i++) {
      if (graph(current, i) && !visited[i]) {
        vertexQueue.push(i);
        visited[i] = true;
      }
    }
  }

  return result;
}

std::vector<unsigned> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                        int startVertex) {
  if (startVertex < 1 || (unsigned)startVertex > graph.GetSize()) {
    throw std::invalid_argument("incorrect starting vertex");
  }

  std::vector<unsigned> result;
  std::vector<bool> visited(graph.GetSize());
  s21::Stack<int> vertexStack;
  visited[startVertex - 1] = true;
  vertexStack.push(startVertex - 1);

  while (!vertexStack.empty()) {
    result.push_back(vertexStack.top() + 1);
    int current = vertexStack.pop();

    for (int i = graph.GetSize() - 1; i >= 0; i--) {
      if (graph(current, i) && !visited[i]) {
        vertexStack.push(i);
        visited[i] = true;
      }
    }
  }

  return result;
}

unsigned GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph,
                                                         int vertex1,
                                                         int vertex2) {
  if ((unsigned)vertex1 > graph.GetSize() ||
      (unsigned)vertex2 > graph.GetSize() || vertex1 < 1 || vertex2 < 1) {
    throw std::invalid_argument("incorrect input vertexes");
  }

  std::set<int> visited;
  std::vector<unsigned> path(graph.GetSize());
  std::vector<std::vector<unsigned>> deykstra = graph.GetAdjacencyMatrix();

  for (unsigned i = 0; i < graph.GetSize(); i++) {
    if (i == (unsigned)vertex1 - 1) {
      deykstra[i][0] = 0;
      visited.insert(i);
      path[i] = 0;
    } else {
      deykstra[i][0] = std::numeric_limits<int>::max();
    }
  }

  int lastVisitedVertex = vertex1 - 1;

  for (unsigned i = 1; i < graph.GetSize(); i++) {
    if (lastVisitedVertex == vertex2 - 1) {
      return path[vertex2 - 1];
    }

    std::pair<int, int> min = {std::numeric_limits<int>::max(),
                               std::numeric_limits<int>::max()};

    for (unsigned i = 0; i < graph.GetSize(); i++) {
      if (!visited.count(i)) {
        if (graph(lastVisitedVertex, i) != 0) {
          deykstra[i][i] = std::min(
              (int)deykstra[i][i - 1],
              (int)(path[lastVisitedVertex] + graph(lastVisitedVertex, i)));
          if ((unsigned)min.second > deykstra[i][i]) min = {i, deykstra[i][i]};
        } else {
          deykstra[i][i] = deykstra[i][i - 1];
          if ((unsigned)min.second > deykstra[i][i]) min = {i, deykstra[i][i]};
        }
      }
    }

    path[min.first] = min.second;
    visited.insert(min.first);
    lastVisitedVertex = min.first;
  }

  return path[vertex2 - 1];
}

std::vector<std::vector<unsigned>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  if (!graph.GetSize()) throw std::invalid_argument("invalid_argument");
  
  unsigned size = graph.GetSize();
  std::vector<std::vector<unsigned>> tmp_matrix = graph.GetAdjacencyMatrix();

  for (unsigned k = 0; k < size; k++) {
    for (unsigned i = 0; i < size; i++) {
      for (unsigned j = 0; j < size; j++) {
        if (tmp_matrix[i][j] > tmp_matrix[i][k] + tmp_matrix[k][j])
          tmp_matrix[i][j] = tmp_matrix[i][k] + tmp_matrix[k][j];
      }
    }
  }

  return tmp_matrix;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  if (!graph.GetSize()) throw std::invalid_argument("invalid_argument");

  std::vector<unsigned> tmp_vec;
  double distance;

  Swarm swarm(graph);
  swarm.FindBestTravel(tmp_vec, distance);

  TsmResult answer;
  answer.distance = distance;
  answer.vertices = tmp_vec;

  return answer;
}
}  // namespace s21
