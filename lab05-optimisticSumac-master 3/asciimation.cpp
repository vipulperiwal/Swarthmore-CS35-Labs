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

#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"

using namespace std;


/*
This is the main function that allows the user to choose which movie to play and how to play it
**/
int main(int argc, char** argv) {
  string filename;
  bool reverse = false;
  if(argc >3){//Throw various errors, if necessary
    throw runtime_error("Error! Too many arguments!");
  }
  if(argc == 3){//Set up reverse playback, if selected
    string rev = argv[1];
    if(rev != "--reverse"){
      throw runtime_error("Error! Second argument is not --reverse !");
    }
    reverse = true;
    filename = argv[2];
  }
  if(argc == 1){
    throw runtime_error("Error! Too few arguments! No input data specified!");
  }
  if(!reverse){
    filename = argv[1];
  }
  List<pair<int, string>>* data_list = loadMovie(filename);//Load in movie
  if(reverse){  //play movie in reverse
    List<pair<int, string>>* revData_list = new LinkedList<pair<int, string>>;
    int size = data_list->getSize();
    for(int i = 0; i<size; i++){//Build up reverse movie
      revData_list -> insertFirst(data_list->removeFirst());
    }
    delete data_list;
    playMovie(revData_list);
    delete revData_list;
  }
  else{ //play movie forward
    playMovie(data_list);
    delete data_list;
  }
  return 0;
}
