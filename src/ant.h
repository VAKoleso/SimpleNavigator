#ifndef SRC_ANT_H_
#define SRC_ANT_H_

#include <climits>
#include <cmath>
#include <memory>
#include <random>

#include "path.h"
#include "s21_graph.h"

namespace s21 {
class Ant {
 private:
  std::default_random_engine &random_engine_;
  unsigned location_;
  unsigned start_;
  std::unique_ptr<Path> path_;
  bool can_move_;

 public:
  Ant(std::default_random_engine &engine, unsigned loc, bool exact);

  unsigned MakeChoice(Graph &pheromone, Graph &distance, double apha,
                      double beta);
  unsigned GetLocation() const;
  std::unique_ptr<Path> GetPath();
  bool CanContinue() const;
  bool IsOnStart() const;
};
}  // namespace s21

#endif  // SRC_ANT_H_
