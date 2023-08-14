#ifndef SRC_CONTAINERS_QUEUE_H_
#define SRC_CONTAINERS_QUEUE_H_

#include "node.h"

namespace s21 {
template <typename T>
class Queue {
 public:
  Queue() : head_(nullptr), size_(0) {}
  explicit Queue(unsigned size) : head_(nullptr), size_(0) {
    while (size != size_) {
      push(T());
    }
  }
  ~Queue() { clear(); }

  void queue() {
    if (size_) clear();
    head_ = nullptr;
    size_ = 0;
  }

  void push(const T &value) {
    Node<T> *tmp = new Node(value);
    if (!size_) {
      head_ = tmp;
    } else {
      Node<T> *last = head_;
      while (last->p_next_ != nullptr) last = last->p_next_;
      last->p_next_ = tmp;
    }
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

  const T &front() {
    if (empty()) throw std::out_of_range("stack is empty");
    return head_->data_;
  }

  const T &back() {
    if (empty()) throw std::out_of_range("stack is empty");

    Node<T> *tmp_node = head_;

    while (tmp_node->p_next_ != nullptr) {
      tmp_node = tmp_node->p_next_;
    }

    return tmp_node->data_;
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

#endif  // SRC_CONTAINERS_QUEUE_H_
