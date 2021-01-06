/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <stdexcept>
using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> LinearDictionary<K, V>::LinearDictionary() {
    this -> size = 0;
    
}

template <typename K, typename V> LinearDictionary<K, V>::~LinearDictionary() {
    //everything is statically allocated, so no need to delete anything
}

template <typename K, typename V> int LinearDictionary<K, V>::getSize() {
    return this -> size;
}

template <typename K, typename V> bool LinearDictionary<K, V>::isEmpty() {
    if(this -> size == 0){
        return true;
    }
    else{
        return false;
    }
}

template <typename K, typename V>
void LinearDictionary<K, V>::insert(K key, V value) {
    for(int i = 0; i<this-> size; i++){ //Checks if key already exists
        if((this -> data)[i].first == key){
            throw runtime_error("Error: Cannot insert! Key already present!");
        }
    }
    //adds key to data vector
    (this -> data).push_back(pair<K,V>(key, value));
    this->size++;
}

template <typename K, typename V>
void LinearDictionary<K, V>::update(K key, V value) {
    bool updated = false;
    int i = 0;
    while (i < this -> size){//checks every element and updates the one with the given key
        if((this -> data)[i].first == key){
            (this -> data)[i].second = value;
            updated = true;
            i = this -> size;
        }
        i++;
    }
    if(!updated){
        throw runtime_error("Error: Cannot update! Key not present!");
    }
}

template <typename K, typename V> V LinearDictionary<K, V>::get(K key) {
    int i = 0;
    while (i < this -> size){ //runs through linear dictionary until key is found
        if ((this-> data)[i].first == key){ 
            return (this-> data)[i].second;
        }
        i++;    
    }
    
    throw runtime_error("Error: Cannot get! Key not present!");  
    }

template <typename K, typename V> bool LinearDictionary<K, V>::contains(K key) {
    for(int i = 0; i<this-> size; i++){ //runs through linear dictionary until key is found
        if((this -> data)[i].first == key){
           return true;
        }
    }
    return false;
}

template <typename K, typename V> void LinearDictionary<K, V>::remove(K key) {
    int i = 0;
    bool removed = false;
    while (i < this -> size){//find the key somewhere in the vector of data
        if ((this-> data)[i].first == key){ 
            removeFromVector(this->data,i);
            this -> size--;
            removed = true;
            i = this -> size;
        }
        i++;
    }
    if(!removed){
        throw runtime_error("Error: Cannot remove! Key not present!");
    }
    
}

template <typename K, typename V> vector<K> LinearDictionary<K, V>::getKeys() {
    vector<K> returnVec;
    for(int i = 0; i<this->size; i++){ //runs through every element in data and pushes key to the return vector
        returnVec.push_back((this->data)[i].first);
    }
    return returnVec;
}

template <typename K, typename V>
vector<pair<K, V>> LinearDictionary<K, V>::getItems() {
    return this->data;
}

template <typename T> void removeFromVector(vector<T> &list, int index){
  if(index < 0 || index >= list.size()){
    throw runtime_error("index out of range in removeFromVector");
  }
  list.erase(list.begin()+index, list.begin()+index+1);
}

// TODO: put any other definitions here
