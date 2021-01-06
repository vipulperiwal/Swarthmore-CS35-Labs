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

#include "maze.h"
#include "mazeUtils.h"

using namespace std;

int main(int argc, char** argv) {
  try {
    if (argc != 3){
      /*
      Checks if there are two arguments entered into the commandline. If not, 
      the program alerts the user that they need to enter two arguments. 
      */
      throw runtime_error("Incorrect number of commandline arguments given! (You must enter two)");
    }

    string search_type = argv[2];
    if(search_type!= "breadth" && search_type!= "depth"){
      /*
      Checks if the search type (the second input) is either "depth" or "breadth". If not,
      the program alerts the user that they have entered an incorrect search type. 
      */
      throw runtime_error("Incorrect search type given! (Correct search types are \"depth\" and \"breadth\")");
    }
    Maze* maze = loadMap(argv[1]);
    if (search_type == "breadth"){
      /*
      Does a breadth first search if the user specifies. 
      */
      List<Position*>* solution = maze -> solveBreadthFirst();
      if(solution == nullptr){
        delete maze;
        throw runtime_error("This maze has no solution!");
      }
      string answer = renderAnswer(maze, solution);
      cout<<answer<<endl;
      delete solution;
      delete maze;
    }
    if (search_type == "depth"){
      /*
      Does a depth first search if the user specifies. 
      */
      List<Position*>* solution = maze -> solveDepthFirst();
      if(solution == nullptr){
        delete maze;
        throw runtime_error("This maze has no solution!");
      }
      string answer = renderAnswer(maze, solution);
      cout<<answer<<endl; 
      delete solution;
      delete maze;
    }
    }
    catch (runtime_error e) {
      /*
      If there is a runtime_error, the user is alerted what type of error it is.
      */
      cout<<e.what()<<endl; 
    }
  return 0;
}

