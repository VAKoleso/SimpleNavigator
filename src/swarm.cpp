#include "swarm.h"

namespace s21 {
Swarm::Swarm(Graph graph)
    : distance_(graph),
      pheromone_(graph.GetSize(),
                 [](unsigned from, unsigned to) -> unsigned {
                   return from != to ? kPheromoneTau : 0;
                 }),
      rand_dev_(),
      random_engine_(rand_dev_()) {}

void Swarm::CreateAnts() {
  unsigned size = distance_.GetSize();

  ants_.resize(size);

  for (unsigned i{}; i < size; ++i) {
    ants_[i] = std::unique_ptr<Ant>(new Ant(random_engine_, size, false));
  }
}

void Swarm::FindBestTravel(std::vector<unsigned> &desired_path,
                           double &distance) {
  unsigned best_lenght = UINT_MAX;
  std::vector<unsigned> best_path;

  int looping_counter = kIterations;

  while (looping_counter > 0) {
    CreateAnts();

    for (std::unique_ptr<Ant> &ant : ants_) {
      while (ant->CanContinue()) {
        ant->MakeChoice(pheromone_, distance_, kAlpha, kBeta);
      }

      std::unique_ptr<Path> current_path = ant->GetPath();

      if (best_lenght > current_path->GetDistance()) {
        best_lenght = current_path->GetDistance();
        looping_counter = kIterations;
        best_path = current_path.get()->GetVector();
      }

      Lay(pheromone_, *current_path, kPheromonePerAnt);
    }
    --looping_counter;
  }

  distance = best_lenght;
  desired_path = best_path;
}

void Swarm::Lay(Graph &pheromone, const Path &path, double pheromone_per_ant) {
  double pheromone_to_lay = pheromone_per_ant / path.GetNumOfSteps();

  for (size_t i = 1, n = path.GetNumOfSteps(); i < n; ++i) {
    pheromone.Alter(path[i - 1], path[i], [pheromone_to_lay](unsigned &val) {
      val += pheromone_to_lay;
    });
  }
}
}  // namespace s21
