#include "node_based_containers.h"

using namespace node_based_containers;

template<typename T>
bool Deque<T>::IsEmpty() const {
  return size_ == 0;
}

template<typename T>
void Deque<T>::Push_back(T value) {

  if (IsEmpty()) {
    head_ = new Node<T>(value);
    tail_ = head_;
    ++size_;
    return;
  }
  tail_->next_ = new Node<T>(value);
  tail_ = tail_->next_;
  ++size_;
}

template<typename T>
void Deque<T>::Push_front(T value) {
  if (IsEmpty()) {
    head_ = new Node<T>(value);
    tail_ = head_;
  } else {
    head_->previous_ = new Node<T>(value);
    head_ = head_->previous_;
  }
  ++size_;
}

template<typename T>
void Deque<T>::Pop_back() {
  if (IsEmpty())
    throw std::logic_error("The container is empty!");
  --size_;
  Node<T> *temp = tail_;
  tail_ = tail_->previous_;
  delete temp;
}

template<typename T>
void Deque<T>::Pop_front() {
  if (IsEmpty())
    throw std::logic_error("The container is empty!");
  --size_;
  Node<T> *temp = head_;
  head_ = head_->next_;
  delete temp;
}

template<typename T>
T Deque<T>::At(int index) const {
  if (index >= size_)
    throw std::overflow_error("The index is out of range!");
  if (index < 0)
    throw std::underflow_error("The index is below the range!");
  Node<T> *finder = head_;
  if (index < size_ / 2) {
    for (int i = 0; i < index; ++i)
      finder = finder->next_;
  } else {
    for (int i = size_ - 1; i > index - 1; ++i)
      finder = finder->previous_;
  }
  return finder->value_;
}

template<typename T>
T &Deque<T>::operator[](int index) const {
  Node<T> *finder = head_;
  if (index < size_ / 2) {
    for (int i = 0; i < index; ++i)
      finder = finder->next_;
  } else {
    for (int i = size_ - 1; i > index - 1; ++i)
      finder = finder->previous_;
  }
  return finder->value_;
}

template<typename T>
T Deque<T>::Top() const {
  if (IsEmpty())
    throw std::logic_error("The container is empty!");
  return tail_->value_;
}

template<typename T>
T Deque<T>::Front() const {
  if (IsEmpty())
    throw std::logic_error("The container is empty!");
  return head_->value_;
}

template<typename T>
size_t Deque<T>::Size() const {
  return size_;
}

template<typename T>
Deque<T>::~Deque() {
  Node<T> *traveller = head_;
  Node<T> *temp;
  while (traveller != nullptr) {
    temp = traveller;
    traveller = traveller->next_;
    delete temp;
  }
}

template<typename T>
void Stack<T>::Pop() {
  Deque<T>::Pop_back();
}

template<typename T>
void Stack<T>::Push(T value) {
  Deque<T>::Push_back(value);
}

template<typename T>
void Queue<T>::Push(T value) {
  Deque<T>::Push_back(value);
}

template<typename T>
void Queue<T>::Pop() {
  Deque<T>::Pop_front();
}

template<typename T>
void Queue<T>::operator>>(T &to) {
  to = Front();
  Pop();
}

template<typename T>
void Queue<T>::operator<<(T expression) { push(expression); }

template<typename T>
void Stack<T>::operator>>(T &to) {
  to = Top();
  Pop();
}

template<typename T>
void Stack<T>::operator<<(T expression) { push(expression); }