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
#include <vector>

#include "adts/list.h"
#include "adts/queue.h"
#include "adts/stlList.h"
#include "adts/stlQueue.h"
#include "helpers.h"

#include "linkedBSTNode.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> LinkedBST<K, V>::LinkedBST() {
    this -> size = 0;
    this -> root = nullptr;
}

template <typename K, typename V> LinkedBST<K, V>::~LinkedBST() {
    deleteSubtree(this -> root);
}

template <typename K, typename V> int LinkedBST<K, V>::getSize() {
    return this-> size;
}

template <typename K, typename V> bool LinkedBST<K, V>::isEmpty() {
    if (this -> size == 0) {
        return true;
    }
    return false;
}

template <typename K, typename V> void LinkedBST<K, V>::insert(K key, V value) {
    this -> root = insertInSubtree(this -> root, key, value);
    this -> size ++;
}

template <typename K, typename V> void LinkedBST<K, V>::update(K key, V value) {
    updateInSubtree(this -> root, key, value);
}

template <typename K, typename V> V LinkedBST<K, V>::get(K key) {
    return findInSubtree(this -> root, key);
}

template <typename K, typename V> bool LinkedBST<K, V>::contains(K key) {
    return containsInSubtree(this -> root, key);
}

template <typename K, typename V> void LinkedBST<K, V>::remove(K key) {
    this->root = removeFromSubtree(this -> root, key);
    this -> size --;
}

template <typename K, typename V> vector<K> LinkedBST<K, V>::getKeys() {
    vector<pair<K,V>> keyValPairs = traversePreOrder();
    vector<K> keysOnly;
    for(int i = 0; i<keyValPairs.size(); i++){
        keysOnly.push_back(keyValPairs[i].first);
    }
    return keysOnly;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::getItems() {
    return this -> traversePreOrder();
}

template <typename K, typename V> int LinkedBST<K, V>::getHeight() {
   return getHeightInSubtree(this-> root);
}

template <typename K, typename V> K LinkedBST<K, V>::getMaxKey() {
    return getMaxInSubtree(this->root).first;
}

template <typename K, typename V> K LinkedBST<K, V>::getMinKey() {
    return getMinInSubtree(this->root).first;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePreOrder() {
    List<pair<K, V>>* blankList = new STLList<pair<K, V>>;
    buildPreOrderTraversal(this-> root, blankList);// create traversal list
    vector<pair<K, V>> finalVec = dynamicListToStaticVector(blankList);// convert list to vector
    delete blankList;
    return finalVec;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseInOrder() {
    List<pair<K, V>>* blankList = new STLList<pair<K, V>>;
    buildInOrderTraversal(this-> root, blankList);// create traversal list
    vector<pair<K, V>> finalVec = dynamicListToStaticVector(blankList);// convert list to vector
    delete blankList;
    return finalVec;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePostOrder() {
    List<pair<K, V>>* blankList = new STLList<pair<K, V>>;
    buildPostOrderTraversal(this-> root, blankList);// create traversal list
    vector<pair<K, V>> finalVec = dynamicListToStaticVector(blankList);// convert list to vector
    delete blankList;
    return finalVec;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseLevelOrder() {
    vector<pair<K, V>> returnVec;
    STLQueue<LinkedBSTNode<K,V>*> traversal;// create traveral by using a queue
    traversal.insert(this->root);
    while(!traversal.isEmpty()){// while there are items in the queue
        LinkedBSTNode<K,V>* bstNode = traversal.remove();
        returnVec.push_back(pair<K,V>(bstNode->getKey(), bstNode -> getValue()));// visit node
        if(bstNode -> getLeft() != nullptr){// enqueue left node
            traversal.insert(bstNode -> getLeft());
        }
        if(bstNode -> getRight() != nullptr){// dequeue left node
            traversal.insert(bstNode -> getRight());
        }
    }
    return returnVec;
}

template <typename K, typename V> void LinkedBST<K, V>::checkInvariants() {
    if (this->countNodes(this->root) != this->size) {
        throw runtime_error(
            "Problem in BST: Node count doesn't match tree size");
    }
    if (this->root != nullptr) {
        // The bounds provided here are arbitrary because the false arguments
        // indicate that they do not apply.  But we need a value of type K to
        // fill this parameter since we don't have globally min/max K values
        // generically.
        this->verifyKeysBoundedBy(this->root, false, this->root->getKey(),
                                  false, this->root->getKey());
    }
}
