#pragma once

#include <stdexcept>

namespace node_based_containers {
template<typename T>
class Deque {
 private:
  template<class U>
  struct Node {
    explicit Node(T value, Node<T> *next = nullptr, Node<T>* previous = nullptr)
        : value_(value), next_(next), previous_(previous) {};
    Node<T> *next_;
    Node<T> *previous_;
    T value_;
  };
 public:
  ~Deque();
  Deque() = default;
  Deque(const Deque<T>&) = delete;
  void Push_back(T value);
  void Push_front(T value);
  T At(int index) const;
  T &operator[](int index) const;
  void Pop_back();
  void Pop_front();
  [[nodiscard]] bool IsEmpty() const;
  T Top() const;
  T Front() const;
  [[nodiscard]] size_t Size() const;
 private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  size_t size_ = 0;
};

template<typename T>
class Stack : Deque<T> {
 public:
  Stack() = default;
  void Pop();
  void Push(T value);
  void operator<<(T expression);
  void operator>>(T &to);
  using Deque<T>::operator[];
  using Deque<T>::Size;
  using Deque<T>::At;
  using Deque<T>::IsEmpty;
  using Deque<T>::Top;
};

template<typename T>
class Queue : Deque<T> {
 public:
  Queue() = default;
  void Pop();
  void Push(T value);
  void operator<<(T expression);
  void operator>>(T &to);
  using Deque<T>::operator[];
  using Deque<T>::Size;
  using Deque<T>::At;
  using Deque<T>::IsEmpty;
  using Deque<T>::Front;
};
}