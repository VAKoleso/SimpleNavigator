#ifndef SRC_CONTAINERS_NODE_H_
#define SRC_CONTAINERS_NODE_H_
#include <stdexcept>

namespace s21 {
template <typename T>
class Node {
 public:
  T data_;
  Node *p_next_;
  Node() : data_(), p_next_(nullptr) {}
  explicit Node(T const &data = T(), Node *p_next = nullptr)
      : data_(data), p_next_(p_next) {}
  ~Node() { FreeMemory(); }
  inline void FreeMemory() { p_next_ = nullptr; }
};
}  // namespace s21

#endif  // SRC_CONTAINERS_NODE_H_
