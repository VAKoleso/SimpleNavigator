#ifndef SRC_SWARM_H_
#define SRC_SWARM_H_

#include <climits>
#include <iostream>
#include <memory>
#include <random>

#include "ant.h"

namespace s21 {
constexpr double kAlpha = 1;
constexpr double kBeta = 1;
constexpr double kPheromoneTau = 1;
constexpr double kPheromoneEvaporation = 0.7;
constexpr double kPheromonePerAnt = 2;
constexpr int kIterations = 10000;

class Swarm {
 private:
  Graph distance_;
  Graph pheromone_;

  std::random_device rand_dev_;
  std::default_random_engine random_engine_;

  std::vector<std::unique_ptr<Ant>> ants_;

  void CreateAnts();

  void Lay(Graph &pheromone, const Path &path, double pheromone_per_ant);

 public:
  Swarm(Graph graph);
  void FindBestTravel(std::vector<unsigned> &desired_path, double &distance);
};
}  // namespace s21

#endif  // SRC_SWARM_H_
