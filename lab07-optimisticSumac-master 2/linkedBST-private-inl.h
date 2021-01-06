/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <stdexcept>
#include <utility>

#include "adts/list.h"
#include "adts/stlList.h"

using std::runtime_error;
using namespace std;

template <typename K, typename V>
V LinkedBST<K, V>::findInSubtree(LinkedBSTNode<K, V>* current, K key) {
    if (current == nullptr) {
        throw runtime_error("Key not found");
    }
    else if (current -> getKey() == key) {// we found the key
        return current -> getValue();
    } else if (current -> getKey() > key) {// our key is to the left
        return findInSubtree(current -> getLeft(), key);
    } else {// our key is to the left
        return findInSubtree(current -> getRight(), key);
    }
}

template <typename K, typename V>
bool LinkedBST<K, V>::containsInSubtree(LinkedBSTNode<K, V>* current, K key) {
    if (current == nullptr) {// we found the key
        return false;
    }
    else if (current -> getKey() == key) {
        return true;
    } else if (current -> getKey() > key) {// our key is to the left
        return containsInSubtree(current -> getLeft(), key);
    } else {// our key is to the left
        return containsInSubtree(current -> getRight(), key);
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::updateInSubtree(LinkedBSTNode<K, V>* current, K key, V value) {
    if (current == nullptr) {
        throw runtime_error("Key doesn't exist!");
    }
    if (current -> getKey() == key) {// we found the key
        current -> setValue(value);
    } else if (current -> getKey() > key) {// our key is to the left
        updateInSubtree(current -> getLeft(), key, value);
    } else {// our key is to the right
        updateInSubtree(current -> getRight(), key, value);
    }
}
    
template <typename K, typename V>
int LinkedBST<K, V>::getHeightInSubtree(LinkedBSTNode<K, V>* current) {
    if(current == nullptr){// empty tree height
        return -1;
    }
    else if(current -> getLeft() == nullptr && current -> getRight() == nullptr){// single node tree height
        return 0; 
    }
    else{
        if (getHeightInSubtree(current->getLeft()) <= getHeightInSubtree(current->getRight())){// If right is taller, recursively getHeightInSubtree on right
            return getHeightInSubtree(current-> getRight()) + 1;
        }
        else {// If left is taller, recursively getHeightInSubtree on left
            return getHeightInSubtree(current -> getLeft()) + 1;
        }
    }
}

template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMinInSubtree(LinkedBSTNode<K, V>* current) {
    if(this-> isEmpty()){
        throw runtime_error("The tree is empty! Cannot getMaxKey!");
    }
    while (current -> getLeft() != nullptr){// run down the left side of the tree
        current = current -> getLeft();
    }
    pair<K,V> p(current -> getKey(), current -> getValue());// format return values correctly
    return p;
}

template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMaxInSubtree(LinkedBSTNode<K, V>* current) {
    if(this-> isEmpty()){
        throw runtime_error("The tree is empty! Cannot getMaxKey!");
    }
    while (current -> getRight() != nullptr){// run down the right side of the tree
        current = current-> getRight();
    }
    pair<K,V> p(current -> getKey(), current -> getValue());// format return values correctly
    return p;
}

template <typename K, typename V>
LinkedBSTNode<K, V>*
LinkedBST<K, V>::insertInSubtree(LinkedBSTNode<K, V>* current, K key, V value) {
    if (current == nullptr) {// at a leaf so insert
        current = new LinkedBSTNode<K, V>(key, value);
        return current;
    }
    if (current -> getKey() == key) {
        throw runtime_error("Key already exists");
    } else if (current -> getKey() > key) {// our key is to the left
        current -> setLeft(insertInSubtree(current -> getLeft(), key, value));
        return current;
    } else {// our key is to the right
        current -> setRight(insertInSubtree(current -> getRight(), key, value));
        return current;
    }
}

template <typename K, typename V>
LinkedBSTNode<K, V>*
LinkedBST<K, V>::removeFromSubtree(LinkedBSTNode<K, V>* current, K key) {
    if(current == nullptr){
        throw runtime_error("Error: key not found! Cannot remove!");
    }
    else if(key < current -> getKey()){
        current -> setLeft(removeFromSubtree(current->getLeft(), key));
        return current;
    }
    else if(key > current -> getKey()){
        current -> setRight(removeFromSubtree(current -> getRight(),key));
        return current;
    }
    else{   //We found the node
        if ((current -> getLeft() == nullptr) && (current -> getRight() == nullptr)) {// node is a leaf
            delete current;
            return nullptr;
        } else if ((current -> getLeft() == nullptr) && (current -> getRight() != nullptr)){// node has one right child
            LinkedBSTNode<K, V>* temp = current->getRight();
            delete current;
            return temp;
        } else if ((current -> getLeft() != nullptr) && (current -> getRight() == nullptr)) {// node has one left child
            LinkedBSTNode<K, V>* temp = current->getLeft();
            delete current;
            return temp;
        } else if ((current -> getLeft() != nullptr) && (current -> getRight() != nullptr)) {// node has two children
            K bigKey = getMinInSubtree(current -> getRight()).first;
            V bigVal = get(bigKey);
            current -> setRight(removeFromSubtree(current -> getRight(), bigKey));
            current -> setKey(bigKey);
            current -> setValue(bigVal);
            return current;
        }
        else {
            throw runtime_error("Error: Invalid state");
        }
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::deleteSubtree(LinkedBSTNode<K, V>* current) {
    if (current != nullptr){
        if (current -> getLeft() != nullptr){//delete nodes to the left
            deleteSubtree(current -> getLeft());
        }
        if (current -> getRight() != nullptr) {//delete does to the right
            deleteSubtree(current -> getRight());
        }
        delete current;
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPreOrderTraversal(LinkedBSTNode<K, V>* current, List<pair<K, V>>* list) {
    pair<K,V> nodePair(current->getKey(), current->getValue());
    list -> insertLast(nodePair);
    if(current -> getLeft() != nullptr) {//traverse left subtree by recursively calling;
        buildPreOrderTraversal(current -> getLeft(), list);
    }
    if(current -> getRight() != nullptr) {//traverse right subtree by recursively calling;
        buildPreOrderTraversal(current-> getRight(), list);
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::buildInOrderTraversal(LinkedBSTNode<K, V>* current, List<pair<K, V>>* list) {
   if(current -> getLeft() != nullptr) {//traverse left subtree by recursively calling;
        buildInOrderTraversal(current -> getLeft(), list);
    }
    pair<K,V> nodePair(current->getKey(), current->getValue());
    list -> insertLast(nodePair);
    if(current -> getRight() != nullptr) {//traverse right subtree by recursively calling;
        buildInOrderTraversal(current-> getRight(), list);
    }    
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPostOrderTraversal(LinkedBSTNode<K, V>* current, List<pair<K, V>>* list) {
    if(current -> getLeft() != nullptr) { //traverse left subtree by recursively calling;
        buildPostOrderTraversal(current -> getLeft(), list);
    }
    if(current -> getRight() != nullptr) {//traverse right subtree by recursively calling;
        buildPostOrderTraversal(current-> getRight(), list);
    }
    pair<K,V> nodePair(current->getKey(), current->getValue());
    list -> insertLast(nodePair); 
}

template <typename K, typename V>
int LinkedBST<K, V>::countNodes(LinkedBSTNode<K, V>* current) {
    if (current == nullptr) {
        return 0;
    } else {
        return this->countNodes(current->getLeft()) +
               this->countNodes(current->getRight()) + 1;
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::verifyKeysBoundedBy(LinkedBSTNode<K, V>* current,
                                          bool minApplies, K minBound,
                                          bool maxApplies, K maxBound) {
    if (minApplies && current->getKey() < minBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a "
                            "right descendent with lesser key");
    }
    if (maxApplies && current->getKey() > maxBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a left "
                            "descendent with greater key");
    }
    if (current->getLeft() != nullptr) {
        verifyKeysBoundedBy(current->getLeft(), minApplies, minBound, true,
                            current->getKey());
    }
    if (current->getRight() != nullptr) {
        verifyKeysBoundedBy(current->getRight(), true, current->getKey(),
                            maxApplies, maxBound);
    }
}