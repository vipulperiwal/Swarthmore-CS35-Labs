#pragma once

/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include "adts/dictionary.h"

/**
 * An implementation of a dictionary using a list.
 */
template <typename K, typename V>
class LinearDictionary : public Dictionary<K, V> {
  public:
    /**
     * Creates a new, empty LinearDictionary.
     */
    LinearDictionary();

    /**
     * Cleans up this LinearDictionary.
     */
    ~LinearDictionary();

    /* Dictionary ADT Methods.  You must implement these acording to ADT
       specification.  All of these methods are expected to run in O(n) time.
     */
    int getSize();
    bool isEmpty();
    void insert(K key, V value);
    void update(K key, V value);
    V get(K key);
    bool contains(K key);
    void remove(K key);
    vector<K> getKeys();
    vector<pair<K, V>> getItems();

  private:
    /**
     * Stores the size of the linear dictionary
     */    
    int size;
    /**
     * Vector of Key-Value pairs with the data in the Linear Dictionary.
     */
    vector<pair<K,V>> data;
};

/**
 * removes an element from an arbitrary index in the vector
 * @param list vector to remove element from
 * @param index offset into vector where element to be removed resides
 * @return none, but list is modified
 * @throw runtime_error if index is out of range
 */
template <typename T> void removeFromVector(vector<T> &list, int index);
#include "linearDictionary-inl.h"
