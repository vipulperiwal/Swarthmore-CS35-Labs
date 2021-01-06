/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <stdexcept>
using namespace std;
/* ADTs */
#include "adts/list.h"
#include "adts/orderedCollection.h"
#include "adts/queue.h"
#include "adts/stack.h"


/* Implementations of above ADTs */
#include "adts/stlList.h"
#include "linkedQueue.h"
#include "linkedStack.h"

#include "maze.h"

using namespace std;

Maze::Maze(int width, int height) {
    /*
    Constructs a maze, taking in a width and height determining the size of the maze. The constructor
    creates an array pointer of columns, and within each column, an array pointer of rows. The inner for loop adds a Position to each index of the array.
    with the corresponding coordinates. 
    */
    this -> width = width;
    this -> height = height;
    this -> positions = new Position**[width];
    for(int w = 0; w < width; w++){
        this -> positions[w] = new Position*[height];
        for(int h = 0; h < height; h++){
            Position* a_pos = new Position(w, h); 
            this -> positions[w][h] = a_pos;
        }
    }
}


Maze::~Maze() {
    /*
    This is the maze destructor, cleaning up memory after we are done with the maze. We use the two for loops to 
    delete every Position within our Maze, each column, and the array of columns.
    */
    for (int i = 0; i < this -> width; i++) {
        for(int j = 0; j < this-> height; j++){
            delete this -> positions[i][j];
        }
        delete[] this -> positions[i];
    }
    delete[] this -> positions;
}

int Maze::getWidth() {
    return this -> width;
}

int Maze::getHeight() {
    return this -> height;
}

bool Maze::isWall(int x, int y) {
    return this -> positions[x][y] -> isWall();
}

void Maze::setWall(int x, int y) {
    return this -> positions[x][y] -> setWall();
}

List<Position*>* Maze::solveBreadthFirst() {
    OrderedCollection<Position*>* emptyQueue = new LinkedQueue<Position*>();
    return solve(emptyQueue);
}

List<Position*>* Maze::solveDepthFirst() {
    OrderedCollection<Position*>* emptyStack = new LinkedStack<Position*>();
    return solve(emptyStack);
}

List<Position*>* Maze::solve(OrderedCollection<Position*>* exploration) {
//Note: most comments below come directly from the pseudocode on the lab writeup website.//
    Position*** pos_array; //for convenience
    pos_array = this -> positions;
    List<Position*>* final = new STLList<Position*>();
    // Add the start position to your data structure
    exploration -> insert(pos_array[0][0]);
    // Mark the start position as visited
    pos_array[0][0]->setVisited();
    // While there are positions left in the data structure:
    while(!(exploration -> isEmpty())){
        Position* current;
        // Take a position from the data structure; call it the current position.
        current = exploration -> remove();
        if((current -> getX() == this -> width - 1) && (current -> getY() == this -> height - 1)){// If the current position is the exit, then our search is complete; we can break the loop!
            //Break the loop
            bool done = false;
            while(current -> getX() != 0 || current -> getY() != 0){
                final -> insertFirst(current);
                Position* current_tmp = current -> getPrevious();
                current = current_tmp;
            }
            final -> insertFirst(pos_array[0][0]);
            delete exploration; //memory management
            return final;
        }
        else{
            List<Position*>* nbs = getNeighbors(current);
            for(int n=0; n<nbs->getSize(); n++){//for each neighbor of the current position:
                Position* a_neihb = nbs->get(n);
                if(!(a_neihb->isVisited())){// If that neighbor has not been visited: 
                    // Mark the neighbor as visited
                    a_neihb -> setVisited();
                    // Record the current position as previous to the neighbor
                    a_neihb -> setPrevious(current);
                    // Add the neighbor to the data structure
                    exploration -> insert(a_neihb);
                }
            }
            delete nbs; 
        }
    }
    delete final;   //memory management
    delete exploration;
    return nullptr;
}

List<Position*>* Maze::getNeighbors(Position* position) {
    int x = position -> getX(); //initialize some position and dimension data
    int y = position -> getY();
    int width = this -> getWidth();
    int height = this -> getHeight();
    List<Position*>* neighbors = new STLList<Position*>();
    if(y > 0 && !(this -> positions[x][y-1] -> isWall())){//check up
        neighbors -> insertLast(this -> positions[x][y-1]);
    } 
    if(x > 0 && !(this -> positions[x-1][y] -> isWall())){//check left
        neighbors -> insertLast(this -> positions[x-1][y]);
    }
    if(x < width - 1 && !(this -> positions[x+1][y] -> isWall())){//check right
        neighbors -> insertLast(this -> positions[x+1][y]);
    }
    if (y < height - 1 && !(this -> positions[x][y+1] -> isWall())){//check down
        neighbors -> insertLast(this -> positions[x][y+1]);
    }
    return neighbors;
}