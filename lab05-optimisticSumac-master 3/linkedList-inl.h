/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <stdexcept>

//#include "linkedList.h"

using std::runtime_error;

// This file defines the methods for two classes: LinkedListNode and LinkedList.
// The LinkedListNode methods have been defined for you.  You are responsible
// for defining the LinkedList methods.

// //////// LinkedListNode /////////////////////////////////////////////////////

template <typename T>
LinkedListNode<T>::LinkedListNode(T val, LinkedListNode<T>* next) {
    this->value = val;
    this->next = next;
}

// //////// LinkedList /////////////////////////////////////////////////////////


template <typename T> LinkedList<T>::LinkedList() {
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

template <typename T> LinkedList<T>::~LinkedList(){
    LinkedListNode<T>* current_ptr = this->head;
    if(this->size>0){ //Delete nodes if there are nodes
        while(current_ptr->next!=nullptr){
            LinkedListNode<T>* temp = current_ptr->next; //walk through the list deleting the nodes
            delete current_ptr;
            current_ptr = temp;
        }
        delete this->tail;
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }
}

template <typename T> void LinkedList<T>::checkInvariants() {
    int counter = 0;
    LinkedListNode<T>* current_ptr = this->head;
        while(current_ptr != nullptr){  //Walk through the list, manually counting the number of nodes
            counter++;
            current_ptr = current_ptr->next;
        }
    if(counter != this -> size){
        throw runtime_error("Error! Size does not match number of nodes!");
    }
}

template <typename T> int LinkedList<T>::getSize() {
    return this->size;
}

template <typename T> bool LinkedList<T>::isEmpty() {
    if (this->size == 0){
        return true;
    }
    return false;
}

template <typename T> T LinkedList<T>::getFirst() {
    if(this->size == 0){
        throw runtime_error("Nothing in the list!");
    }
    else{
        return this->head->value;
    }    
}

template <typename T> T LinkedList<T>::getLast() {
    if(this->size == 0){
        throw runtime_error("Nothing in the list!");
    }
    else{
        return this->tail->value;
    }
    
}

template <typename T> T LinkedList<T>::get(int index) {
    if(this->size == 0){    //Throw various errors if necessary
        throw runtime_error("Invalid! The list is empty!");
    }
    if(index<0){
        throw runtime_error("Invalid index! Cannot get element at negative index!");
    }
    if(index>=size){
        throw runtime_error("Invalid index! Index too large!");
    }
    LinkedListNode<T>* current_ptr = this->head;
    for (int i = 0; i < index; i++){
        current_ptr = current_ptr->next;    //Walk through the list, retreiving the desired element
    }
    return current_ptr->value;
}

template <typename T> void LinkedList<T>::insertFirst(T value) {
    LinkedListNode<T>* new_node = new LinkedListNode<T>(value, this->head);
    this->head = new_node;  //set head to new node
    if(this->size==0){
        this->tail = new_node;  //set up tail if not set up already
    }
    this->size++;
}

template <typename T> void LinkedList<T>::insertLast(T value) {
    LinkedListNode<T>* new_node = new LinkedListNode<T>(value, nullptr);
    if(this->size==0){  //set up head and tail if list is empty
        this->head = new_node;
        this->tail = new_node;
        this->size++;
    } else{
        this->tail->next = new_node;    //links old tail to new tail
        this->tail = new_node;  //reset correct tail pointer
        this->size++;
    }
}

template <typename T> T LinkedList<T>::removeFirst() {
    if(this->size==0){
        throw runtime_error("The list is empty! Can't remove first!");
    }
    LinkedListNode<T>* temp = this->head; //temporarily save first element so it can be returned
    this->head = this->head->next;  //reset correct head pointer
    this->size--;
    if(this-> size == 0){
        this->head = nullptr; //reset fields essentially back to the state after construction
        this->tail = nullptr;
    }
    T returnVal = temp->value;
    delete temp;
    return returnVal;
}

template <typename T> T LinkedList<T>::removeLast() {
    if(this->size==0){
        throw runtime_error("The list is empty! Can't remove last!");
    }
    LinkedListNode<T>* current_ptr = this->head;
    if (this->size == 1) {
        LinkedListNode<T>* temp = this->head;   //temporarily save node so value can be returned
        this->head = nullptr;   //reset fields essentially back to the state after construction
        this->tail = nullptr;
        this->size = 0;
        T returnVal = temp->value; //temporarily save element so it can be returned
        delete temp;
        return returnVal; 
    }
    else{
        while(current_ptr->next->next != nullptr) {//Walk through the list until we reach the second-to-last element
            current_ptr = current_ptr -> next;
        }
        T tempVal = this->tail->value;  //temporarily save element so it can be returned
        delete current_ptr->next;
        current_ptr->next = nullptr;    //new tail->next set to nullptr
        this->tail = current_ptr;   //reset tail
        this->size--;
        return tempVal;
    }
}
