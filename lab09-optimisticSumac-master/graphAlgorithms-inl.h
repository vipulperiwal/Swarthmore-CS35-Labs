/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <iostream>
#include <stdexcept>
#include "adts/stlHashTable.h"
#include "adts/stlStack.h"
#include "adts/stlQueue.h"
#include "adts/stlMinPriorityQueue.h"

template <typename V, typename W>
bool reachableDFS(Graph<V, W>* g, V src, V dest) {
    STLStack<V> frontier;
    STLHashTable<V,V> visited;    
    frontier.push(src);
    visited.insert(src, src);
    V current;
    while(!frontier.isEmpty()){ // runs if the stack frontier is not empty
        current = frontier.pop();
        if(current == dest){ // checks to see if current is the destination we are looking for
            return true;
        }
        // adds all neighbors of current to frontier and marks them as visited if they are not already visited
        vector<V> neighbors = g -> getNeighbors(current);
        for (int i = 0; i < neighbors.size(); i++){
            if (!visited.contains(neighbors[i])){
                frontier.push(neighbors[i]);
                visited.insert(neighbors[i], neighbors[i]);
            }
        }
    }
    // returns false if the destination is unreachable
    return false;
}

template <typename V, typename W>
vector<V> shortestLengthPathBFS(Graph<V, W>* g, V src, V dest) {
    vector<V> backReturnVec;
    vector<V> returnVec;
    STLQueue<V> frontier;
    STLHashTable<V,V> previous;    
    frontier.enqueue(src);
    previous.insert(src, src);
    V current;
    while(!frontier.isEmpty()){ // runs if the queue frontier is not empty
        current = frontier.dequeue();
        if(current == dest){ // runs if current matches the destination
            backReturnVec.push_back(current);
            V previousVertex = previous.get(current);
            while(previousVertex != src){ /* keeps getting the previous vertex and adds it to 
            backReturnVec until we reach the starting point */
                backReturnVec.push_back(previousVertex);
                previousVertex = previous.get(previousVertex);
            }
            if(dest != src){ /* if the destination does not equal the starting point, 
            ensures starting point is added to backReturnVec */
                backReturnVec.push_back(src);
            }
            for (int i = backReturnVec.size() - 1; i > -1; i--){ // reverses backReturnVec and stores it in returnVec
                returnVec.push_back(backReturnVec[i]);
            }
            return returnVec;
        }
        vector<V> neighbors = g -> getNeighbors(current);
        for (int i = 0; i < neighbors.size(); i++){ //runs for all neighbors of current
            if (!previous.contains(neighbors[i])){ /* if neighbor is not in previous, enqueues neihbor to 
            frontier and inserts into previous */
                frontier.enqueue(neighbors[i]);
                previous.insert(neighbors[i], current);
            }
        }
    }
    throw std::runtime_error("No path!");
}

template <typename V, typename W>
Dictionary<V, W>* singleSourceShortestPath(Graph<V, W>* g, V src) {
    STLMinPriorityQueue<W, V> frontier;
    STLHashTable<V,W>* costs = new STLHashTable<V,W>;    
    frontier.insert(0, src);
    costs -> insert(src, 0);
    V current;
    while(!frontier.isEmpty()){ // runs if the priority queue frontier is not empty
        current = frontier.remove();
        vector<Edge<V, W>> outgoingEdges = g -> getOutgoingEdges(current);
        for (int i = 0; i < outgoingEdges.size(); i++){ // runs for every ougoing edge
            V neighbor = outgoingEdges[i].getDestination();
            W stepCost = outgoingEdges[i].getWeight();
            W newCost = costs -> get(current) + stepCost;
            if (!costs -> contains(neighbor)){ // runs if the costs Hash Table does not contain the neighbor
                frontier.insert(newCost, neighbor);
                costs -> insert(neighbor, newCost);
            }
            else if(costs -> get(neighbor) > newCost){ // runs if the costs of neighbor are greater than the newCost
                frontier.insert(newCost, neighbor);
                costs -> update(neighbor, newCost);
            }
        }
    }
    return costs;
}
