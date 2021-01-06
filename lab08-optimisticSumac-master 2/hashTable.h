#pragma once

/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include "linearDictionary.h"
#include "adts/dictionary.h"

template <typename K, typename V> class HashTable : public Dictionary<K, V> {
  public:
    /**
     * Creates a new HashTable with a maximum load factor of 0.75.
     */
    HashTable();

    /**
     * Creates a new HashTable.
     * @param maxLoadFactor The maximum load factor which will be permitted
     *                      before this hash table changes its capacity.
     */
    HashTable(float maxLoadFactor);
    /**
     * Cleans up this HashTable.
     */
    ~HashTable();

    /* Dictionary ADT Methods.
       You must implement these acording to ADT specification
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
     * Doubles the capacity of the table in order to reduce the load factor.
     *  All items should be rehashed into the new table
     */
    void expandCapacity();

    /**
     * Stores the size of a HashTable
     */
    int size;
    /**
     * Stores the load factor of a HashTable (num pairs/ num buckets)
     */  
    float loadFactor;
    /**
     * Stores the current capacity of a HashTable
     */
    int capacity;
    /**
     * Linear Dictionary of key-value pairs in the HashTable
     */
    LinearDictionary<K,V>* data;
    /**
     * Stores the array size of the HashTable
     */
    int arraySize;
};

#include "hashTable-inl.h"
