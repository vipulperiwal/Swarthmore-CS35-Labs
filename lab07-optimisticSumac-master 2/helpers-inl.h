/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include "helpers.h"

template <typename T> vector<T> dynamicListToStaticVector(List<T>* list) {
    vector<T> returnVec;
    for(int i = 0; i < list -> getSize(); i++){//for each element of the list, build up the static vector
        returnVec.push_back(list -> get(i));
    }
    return returnVec;
}
