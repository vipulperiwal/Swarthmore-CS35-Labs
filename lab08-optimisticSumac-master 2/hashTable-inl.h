/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <stdexcept>


#include "hashFunctions.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> HashTable<K, V>::HashTable() {
    size = 0;
    loadFactor = 0.75;
    capacity = loadFactor;
    arraySize = 1;
    data = new LinearDictionary<K,V>[this->arraySize];
}

template <typename K, typename V>
HashTable<K, V>::HashTable(float maxLoadFactor) {
    size = 0;
    loadFactor = maxLoadFactor;
    capacity = loadFactor;
    arraySize = 1;
    data = new LinearDictionary<K,V>[this->arraySize];
}

template <typename K, typename V> HashTable<K, V>::~HashTable() {
    delete[] this->data;
    
}

template <typename K, typename V> int HashTable<K, V>::getSize() {
    return this -> size;
}

template <typename K, typename V> bool HashTable<K, V>::isEmpty() {
    if(this-> size == 0){ //size = 0 is the only case where the Hash Table is empty
        return true;
    }
    else{
        return false;
    }
}

template <typename K, typename V> void HashTable<K, V>::insert(K key, V value) {
    int hashOfKey = hash(key, this->arraySize);
    if(data[hashOfKey].contains(key)){
        throw runtime_error("Error! Key already exists");
    }
    else if(this->size + 1<capacity){// if capacity has not been exceeded
        data[hashOfKey].insert(key, value);
        this->size++;
    }
    else{//if capacity has been exceeded, we first expand the capacity, then we insert the K-V pair
        expandCapacity();
        int hashOfKey = hash(key, this->arraySize);
        data[hashOfKey].insert(key, value);
        this->size++;
    }
}

template <typename K, typename V> void HashTable<K, V>::update(K key, V value) {
    int hashOfKey = hash(key, this->arraySize);
    if(!data[hashOfKey].contains(key)){
        throw runtime_error("Error! Key does not exist");
    }
    //K-V Pair gets updated
    data[hashOfKey].update(key, value);
    
}

template <typename K, typename V> V HashTable<K, V>::get(K key) {
    int hashOfKey = hash(key, this->arraySize);
    if(!data[hashOfKey].contains(key)){
        throw runtime_error("Error! Key does not exist");
    }
    //Value from a given key is returned
    return data[hashOfKey].get(key);
}

template <typename K, typename V> bool HashTable<K, V>::contains(K key) {
    int hashOfKey = hash(key, this->arraySize);
    bool contains = data[hashOfKey].contains(key);
    //Returns whether or not Hash Table contains the given key
    return contains;
}

template <typename K, typename V> void HashTable<K, V>::remove(K key) {
    int hashOfKey = hash(key, this->arraySize);
    if(!data[hashOfKey].contains(key)){
        throw runtime_error("Error! Key does not exist");
    }
    //removes K-V pair at given key
    data[hashOfKey].remove(key);
    this->size--;
}

template <typename K, typename V> vector<K> HashTable<K, V>::getKeys() {
    vector<K> returnVec;
    for (int i = 0; i < this->arraySize; i++) { //runs through every element within data
        // gets keys from a linear dictionary in data and stores in a tmp vector
        vector<K> tmpVec = data[i].getKeys();
        int sizeLD = data[i].getSize();
        // adds every element within the tmp vector to the return vector
        for (int j = 0; j < sizeLD; j++){
            returnVec.push_back(tmpVec[j]);
        }
    }
    return returnVec;
}

template <typename K, typename V>
vector<pair<K, V>> HashTable<K, V>::getItems() {
    vector<pair<K,V>> returnVec;
    for (int i = 0; i < this->arraySize; i++) { //runs through every element within data
        // gets values from a linear dictionary in data and stores in a tmp vector
        vector<pair<K,V>> tmpVec = data[i].getItems();
        int sizeLD = data[i].getSize();
        // adds every element within the tmp vector to the return vector
        for (int j = 0; j < sizeLD; j++){
            returnVec.push_back(tmpVec[j]);
        }
    }
    return returnVec;
}

template <typename K, typename V> void HashTable<K, V>::expandCapacity() {
    //The linear dictionary array pointer points to data
    LinearDictionary<K,V>* oldData = this->data;
    //Points to a linear dictionary array that will be data after the capacity is increased
    LinearDictionary<K,V>* newData;
    vector<pair<K,V>> items = this->getItems();
    //Creates expanded array of linear dictionaries, and updates array size + capacity. 
    newData = new LinearDictionary<K,V>[this->arraySize*2];
    this->arraySize *=2;
    this->capacity = this->loadFactor*arraySize;
    for(int i=0; i<items.size(); i++){ // each item will be re-hashed to newData
        K key = items[i].first;
        V value = items[i].second;
        int hashOfKey = hash(key, this->arraySize);
        newData[hashOfKey].insert(key, value);
    }
    //data now points to our new data
    this -> data = newData;

    //the oldData pointer is deleted
    delete[] oldData;
}

// TODO: put any other definitions here
