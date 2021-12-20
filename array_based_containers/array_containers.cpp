#include "array_containers.h"

using namespace Containers;

template<class T, class U>
bool operator==(const Deque<T> &a, const Deque<U> &b) {
  return a.Size() == b.Size();
}

template<class T, class U>
bool operator>(const Deque<T> &a, const Deque<U> &b) {
  return a.Size() > b.Size();
}

template<class T, class U>
bool operator<(const Deque<T> &a, const Deque<U> &b) {
  return a.Size() < b.Size();
}

template<class T, class U>
bool operator==(const Stack<T> &a, const Stack<U> &b) {
  return a.Size() == b.Size();
}

template<class T, class U>
bool operator>(const Stack<T> &a, const Stack<U> &b) {
  return a.Size() > b.Size();
}

template<class T, class U>
bool operator<(const Stack<T> &a, const Stack<U> &b) {
  return a.Size() < b.Size();
}

template<class T>
void Stack<T>::Pop() { Deque<T>::Pop_back(); }

template<class T>
void Stack<T>::Push(T expr) {
  Deque<T>::Push_back(expr);
}

template<class T, class U>
bool operator==(const Queue<T> &a, const Queue<U> &b) {
  return a.Size() == b.Size();
}

template<class T, class U>
bool operator>(const Queue<T> &a, const Queue<U> &b) {
  return a.Size() > b.Size();
}

template<class T, class U>
bool operator<(const Queue<T> &a, const Queue<U> &b) {
  return a.Size() < b.Size();
}

template<class T>
void Queue<T>::Pop() { Deque<T>::Pop_front(); }

template<class T>
void Queue<T>::Push(T expr) {
  Deque<T>::Push_back(expr);
}

template<class T>
void Deque<T>::IncreaseSize(ContainerSide side) {
  size_t new_cont_size = container_size_ + CONTAINER_SIDE_INCREASE_SIZE;
  T *new_container = new T[new_cont_size];
  size_t new_first_element_pos = side == kFront ? CONTAINER_SIDE_INCREASE_SIZE : firstElementPos_;
  for (size_t i = 0; i < numOfElements_; ++i)
    new_container[i + new_first_element_pos] = container_[firstElementPos_ + i];
  delete[] container_;
  container_ = new_container;
  container_size_ = new_cont_size;
  firstElementPos_ = new_first_element_pos;
  lastElementPos_ = firstElementPos_ + numOfElements_ - 1;
}

template<class T>
bool Deque<T>::NeedsToBeShrinked() const {
  return (numOfElements_ < container_size_ / 3) && (numOfElements_ > CONTAINER_MIN_SHRINK_SIZE);
}

template<class T>
void Deque<T>::Shrink_to_fit() {
  size_t new_container_size = 2 * numOfElements_;
  size_t new_first_pos = new_container_size / 3;
  T *new_container = new T[new_container_size];
  for (int i = 0; i < numOfElements_; ++i)
    new_container[i + new_first_pos] = container_[i + firstElementPos_];
  delete[] container_;
  container_ = new_container;
  firstElementPos_ = new_first_pos;
  lastElementPos_ = firstElementPos_ + numOfElements_ - 1;
  container_size_ = new_container_size;
}

template<class T>
void Deque<T>::Pop_back() {
  if (NeedsToBeShrinked())
    Shrink_to_fit();
  if (IsEmpty())
    throw std::logic_error("The container is empty!");
  --numOfElements_;
  --lastElementPos_;
}

template<class T>
void Deque<T>::Pop_front() {
  if (NeedsToBeShrinked())
    Shrink_to_fit();
  if (IsEmpty())
    throw std::logic_error("The container is empty!");
  --numOfElements_;
  ++firstElementPos_;
}

template<class T>
void Deque<T>::Push_back(T expression) {
  if (lastElementPos_ >= container_size_ - 2)
    IncreaseSize(kBack);
  container_[++lastElementPos_] = expression;
  ++numOfElements_;
}

template<class T>
void Deque<T>::Push_front(T expression) {
  if (firstElementPos_ == 0)
    IncreaseSize(kFront);
  container_[--firstElementPos_] = expression;
  ++numOfElements_;
}

template<class T>
bool Deque<T>::IsEmpty() const {
  return numOfElements_ == 0;
}

template<class T>
T Deque<T>::Front() const {
  if (IsEmpty())
    throw std::logic_error("The container is empty!");
  return container_[firstElementPos_];
}

template<class T>
T Deque<T>::Top() const {
  if (IsEmpty())
    throw std::logic_error("The container is empty!");
  return container_[lastElementPos_];
}

template<class T>
T Deque<T>::At(int index) const {
  if (index >= numOfElements_)
    throw std::range_error("The index is out of range!");
  return container_[firstElementPos_ + index];
}

template<class T>
T &Deque<T>::operator[](int index) const {
  return &container_[firstElementPos_ + index];
}

template<class T>
void Deque<T>::Reset() {
  delete[] container_;
  firstElementPos_ = CONTAINER_DEFAULT_SIZE / 2;
  lastElementPos_ = CONTAINER_DEFAULT_SIZE / 2 - 1;
  numOfElements_ = 0;
  container_size_ = CONTAINER_DEFAULT_SIZE;
  container_ = new T[CONTAINER_DEFAULT_SIZE];
}

template<class T>
size_t Deque<T>::Size() const {
  return numOfElements_;
}

template<class T>
Deque<T>& Deque<T>::operator=(const Deque<T>& copy) {
  if (this == &copy)
    return *this;
  delete[] container_;
  container_ = new T[copy.container_size_];
  for (int i = copy.firstElementPos_; i <= copy.lastElementPos_; ++i)
    container_[i] = copy.container_[i];
  firstElementPos_ = copy.firstElementPos_;
  lastElementPos_ = copy.lastElementPos_;
  numOfElements_ = copy.numOfElements_;
  return *this;
}

template<typename T>
size_t Deque<T>::npos = std::numeric_limits<size_t>::max();

template<typename T>
Deque<T>::~Deque() {
  delete[] container_;
}