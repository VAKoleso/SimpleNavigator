#ifndef SRC_CONTAINERS_S21_STACK_H_
#define SRC_CONTAINERS_S21_STACK_H_

#include "node.h"

namespace s21 {
template <typename T>
class Stack {
 public:
  Stack() : head_(nullptr), size_(0) {}
  explicit Stack(unsigned size) : head_(nullptr), size_(0) {
    while (size != size_) {
      push(T());
    }
  }
  ~Stack() { clear(); }

  void stack() {
    if (size_) clear();
    head_ = nullptr;
    size_ = 0;
  }

  void push(const T &value) {
    Node<T> *tmp = new Node(value, head_);
    head_ = tmp;
    ++size_;
  }

  T pop() {
    if (empty()) throw std::out_of_range("stack is empty");
    Node<T> *del_node = head_;
    head_ = head_->p_next_;
    T value = del_node->data_;
    delete del_node;
    --size_;
    return value;
  }

  const T &top() {
    if (empty()) throw std::out_of_range("stack is empty");
    return head_->data_;
  }

  void clear() {
    while (size_) {
      pop();
    }
  }
  bool empty() const { return !size_; }

 private:
  Node<T> *head_;
  unsigned size_;
};
}  // namespace s21

#endif  // SRC_CONTAINERS_S21_STACK_H_
