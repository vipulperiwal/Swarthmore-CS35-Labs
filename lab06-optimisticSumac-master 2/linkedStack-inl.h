/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include "linkedStack.h"

using namespace std;

// NOTE: Most of the method bodies in this class will only require a single line
// of code!

template <typename T> LinkedStack<T>::LinkedStack() {
    this -> stack = new STLList<T>();
}

template <typename T> LinkedStack<T>::~LinkedStack() {
    delete this -> stack;
}

template <typename T> void LinkedStack<T>::push(T element) {
    this -> stack -> insertFirst(element);
}

template <typename T> T LinkedStack<T>::pop() {
    return this -> stack -> removeFirst();
}

template <typename T> void LinkedStack<T>::insert(T element) {
    this->push(element);
}

template <typename T> T LinkedStack<T>::remove() {
    return this -> pop();
}

template <typename T> int LinkedStack<T>::getSize() {
    return this -> stack -> getSize();
}

template <typename T> bool LinkedStack<T>::isEmpty() {
    return this -> stack -> isEmpty();
}

template <typename T> T LinkedStack<T>::peek() {
    return this -> stack -> getFirst();
}
