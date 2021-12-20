#pragma once

#include <stdexcept>
#include <numeric>

#define CONTAINER_DEFAULT_SIZE 200
#define CONTAINER_SIDE_INCREASE_SIZE container_size_/2
#define CONTAINER_MIN_SHRINK_SIZE 200

namespace Containers {
enum ContainerSide {
  kFront,
  kBack
};

template<typename T>
class Deque {
 public:
  static size_t npos;
  ~Deque();
  Deque() = default;
  void Push_back(T expression);
  void Push_front(T expression);
  void Pop_back();
  void Pop_front();
  T Top() const;
  T Front() const;
  T At(int index) const;
  T &operator[](int index) const;
  [[nodiscard]] bool IsEmpty() const;
  void Shrink_to_fit();
  void Reset();
  [[nodiscard]] size_t Size() const;
  Deque &operator=(const Deque &copy);
 private:
  [[nodiscard]] bool NeedsToBeShrinked() const;
  void IncreaseSize(ContainerSide side);
  size_t firstElementPos_ = CONTAINER_DEFAULT_SIZE / 2;
  size_t lastElementPos_ = CONTAINER_DEFAULT_SIZE / 2 - 1;
  size_t numOfElements_ = 0;
  size_t container_size_ = CONTAINER_DEFAULT_SIZE;
  T *container_ = new T[CONTAINER_DEFAULT_SIZE];
};
template<class T, class U>
bool operator==(const Deque<T> &a, const Deque<U> &b);
template<class T, class U>
bool operator>(const Deque<T> &a, const Deque<U> &b);
template<class T, class U>
bool operator<(const Deque<T> &a, const Deque<U> &b);

template<typename T>
class Stack : Deque<T> {
 public:
  Stack() = default;
  void Pop();
  void Push(T expr);
  void operator<<(const T expression) { push(expression); }
  void operator>>(T &to) {
    to = Top();
    Pop();
  }
  using Deque<T>::operator[];
  using Deque<T>::operator=;
  using Deque<T>::Size;
  using Deque<T>::Shrink_to_fit;
  using Deque<T>::At;
  using Deque<T>::IsEmpty;
  using Deque<T>::Top;
  using Deque<T>::Reset;
};
template<class T, class U>
bool operator==(const Stack<T> &a, const Stack<U> &b);
template<class T, class U>
bool operator>(const Stack<T> &a, const Stack<U> &b);
template<class T, class U>
bool operator<(const Stack<T> &a, const Stack<U> &b);

template<typename T>
class Queue : Deque<T> {
 public:
  Queue() = default;
  void Pop();
  void Push(T expr);
  void operator<<(const T expression) { push(expression); }
  void operator>>(T &to) {
    to = Front();
    Pop();
  };
  using Deque<T>::operator[];
  using Deque<T>::operator=;
  using Deque<T>::Size;
  using Deque<T>::Shrink_to_fit;
  using Deque<T>::At;
  using Deque<T>::IsEmpty;
  using Deque<T>::Front;
  using Deque<T>::Reset;
};
template<class T, class U>
bool operator==(const Queue<T> &a, const Queue<U> &b);
template<class T, class U>
bool operator>(const Queue<T> &a, const Queue<U> &b);
template<class T, class U>
bool operator<(const Queue<T> &a, const Queue<U> &b);
}