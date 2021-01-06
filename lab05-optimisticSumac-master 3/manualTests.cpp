/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"
using namespace std;

LinkedList<int>* createListBackward(int size) {
    LinkedList<int>* list = new LinkedList<int>();
    for (int i = size - 1; i >= 0; i--) {
        list->insertFirst(i * 2);
    }
    list->checkInvariants();
    return list;
}

int main(){
    LinkedList<int>* list = new LinkedList<int>;
    list->insertFirst(0);
    list->insertLast(1);
    list->insertLast(2);
    list->insertLast(3);
    list->insertLast(4);
    cout<<list->getLast()<<endl;
    cout<<list->getSize();
    list->checkInvariants();
    list->insertLast(4);
    list->insertLast(5);
    cout<<"getLast"<<list->getLast()<<endl;
    cout<<"getFirst"<<list->getFirst()<<endl;
    list->checkInvariants();
    LinkedList<int>* listt = createListBackward(1000);
    for(int i = 0; i<500; i++){
        listt->removeFirst();
    }
    delete list;
    delete listt;
    LinkedList<int> listtt;
    listtt.insertFirst(1);
    listtt.removeFirst();
    //cout<"***"<<listtt
    return 0;
}