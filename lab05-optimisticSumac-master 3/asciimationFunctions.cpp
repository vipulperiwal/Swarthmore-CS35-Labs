/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <utility>

#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"

using namespace std;

List<pair<int, string>>* loadMovie(string filename) {
  ifstream myFile;
  string data;
  int fr;
  string final; //final string (frame) to build up
  List<pair<int, string>>* frame_data = new LinkedList<pair<int, string>>;  //linked list to store frames
  myFile.open(filename);
  if(!myFile.is_open()) {
    delete frame_data;
    throw runtime_error("file " + filename + "failed to open. (Possibly no file name was given.)");
  } 
  else {
    getline(myFile, data);
    while (!myFile.eof()) {//read in all lines
      final = "";
      for (int i = 0; i < 14; i++){//Build up a frame data pair
        if(i == 0){
          fr = stoi(data);
        }
        else{
          getline(myFile, data);
          final = final + data + "\n";
        }
      }
      pair<int, string> data_pair(fr, final); //Put frame data into a pair
      frame_data -> insertLast(data_pair);
      getline(myFile, data);
    }
  }
  return frame_data;
}

void playMovie(List<pair<int, string>>* list) {
  system("clear");
  pair<int, string> framePair;
  int size = list->getSize();
  for (int i = 0; i<size; i++){ //display each pair
    framePair = list->removeFirst();
    int frameNum = framePair.first;
    string frameStr = framePair.second;
    cout<< frameStr;  //display the frame
    double fifteenth_of_sec = 1000000/15;
    double sleepTime = fifteenth_of_sec*frameNum; //display the frame for the right amount of time
    usleep(sleepTime);
    system("clear");  //clear the screen after each frame
  }
}
