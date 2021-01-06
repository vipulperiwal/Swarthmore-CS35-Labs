/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <string>
#include <iostream>
#include "hashTable.h"
#include "adts/stlList.h"

using namespace std;

// int main(int argc, char** argv) {
//   LinearDictionary<int, STLList<int>*>* testHash = new LinearDictionary<int, STLList<int>*>;
//   for(int i=0; i<100; i++){
//     STLList<int>* testList = new STLList<int>;
//     for(int j = 0; j<100; j++){
//       testList -> insertLast(i);
//     }
//     testHash -> insert(i,testList);
//   }
//   delete testHash;
// }

int main(int argc, char** argv) {//tests that the hash-table doesn't contain memory errors
  LinearDictionary<int, int*>* testHash = new LinearDictionary<int, int*>;
  for(int i=0; i<100; i++){
    int* j = new int(i);
    testHash -> insert(i,j);
  }
  delete testHash;
}

