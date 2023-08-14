#include "ant.h"

namespace s21 {
Ant::Ant(std::default_random_engine &engine, unsigned loc, bool exact)
    : random_engine_(engine), can_move_(true) {
  if (exact) {
    location_ = loc;
  } else {
    std::uniform_int_distribution<unsigned> dis(0, loc - 1);
    location_ = dis(random_engine_);
  }

  start_ = location_;
  path_ = std::unique_ptr<Path>(new Path(location_));
}

unsigned Ant::MakeChoice(Graph &pheromone, Graph &distance, double alpha,
                         double beta) {
  unsigned from = location_;

  if (path_->GetNumOfSteps() == distance.GetSize()) {
    can_move_ = false;
    location_ = start_;
    path_->AddStep(start_, distance(from, start_));
    return start_;
  }

  std::vector<unsigned> neighbour_probability_markers;
  double max_probability = 0.0;
  double current_probability;

  for (unsigned i{}, size = distance.GetSize(); i < size; ++i) {
    if (i == from) {
      neighbour_probability_markers.push_back(0);
    } else if (path_->Contains(i)) {
      neighbour_probability_markers.push_back(0);
    } else {
      current_probability = std::pow(pheromone(from, i), alpha) *
                            std::pow(distance(from, i), beta);
      max_probability += current_probability;
      neighbour_probability_markers.push_back(max_probability);
    }
  }

  if (max_probability == 0) {
    can_move_ = false;
    return UINT_MAX;
  }

  std::uniform_real_distribution<double> dis(0.0, max_probability);
  double choice = dis(random_engine_);

  for (unsigned i{}; i < neighbour_probability_markers.size(); ++i) {
    if (choice < neighbour_probability_markers[i]) {
      location_ = i;
      path_->AddStep(i, distance(from, i));
      return i;
    }
  }

  throw "Error: Ant::MakeChoice";
}

unsigned Ant::GetLocation() const { return location_; }

bool Ant::CanContinue() const { return can_move_; }

std::unique_ptr<Path> Ant::GetPath() { return std::move(path_); }
}  // namespace s21
