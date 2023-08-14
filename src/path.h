#ifndef SRC_PATH_H_
#define SRC_PATH_H_

#include <iostream>
#include <vector>

namespace s21 {
class Path {
 private:
  std::vector<unsigned> path_;
  unsigned distance_;

 public:
  unsigned operator[](unsigned element) const;

  Path(unsigned initial);
  std::vector<unsigned> GetVector();
  unsigned GetDistance() const;
  unsigned GetNumOfSteps() const;
  void AddStep(int vertex, unsigned dist);
  bool Contains(unsigned location);
};
}  // namespace s21

#endif  // SRC_PATH_H_
