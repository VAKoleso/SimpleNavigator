#include "path.h"

namespace s21 {
Path::Path(unsigned initial) : distance_(0) { path_.push_back(initial); }

unsigned Path::GetDistance() const { return distance_; }

void Path::AddStep(int vertex, unsigned dist) {
  path_.push_back(vertex);
  distance_ += dist;
}

bool Path::Contains(unsigned location) {
  for (unsigned i{}; i < path_.size() - 1; ++i) {
    if (path_[i] == location) {
      return true;
    }
  }

  return false;
}

unsigned Path::GetNumOfSteps() const { return path_.size(); }

unsigned Path::operator[](unsigned element) const { return path_[element]; }

std::vector<unsigned> Path::GetVector() { return path_; }
}  // namespace s21
