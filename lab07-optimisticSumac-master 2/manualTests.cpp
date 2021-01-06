/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <iostream>
#include <string>
#include <utility>

#include "linkedBST.h"

using namespace std;

int main() {
  LinkedBST<int, string>* bst = new LinkedBST<int, string>();
  bst->insert(6, "6");
  bst->insert(2, "2");
  bst->insert(7, "7");
  bst->insert(1, "1");
  bst->insert(4, "4");
  bst->insert(9, "9");
  bst->insert(3, "3");
  bst->remove(1);
  cout<<bst->getSize();
  bst->remove(7);
  cout<<bst->getSize();
  bst -> remove(10);

  return 0;
}

// while(this-> root != nullptr){
//   remove(this-> root);
// }