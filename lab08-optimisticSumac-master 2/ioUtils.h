#pragma once

/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <string>

#include "adts/list.h"
#include "tweet.h"

/**
 * Reads a data file containing a series of tweets.
 * @param filename The name of the file.
 * @return A list containing all of the tweets obtained from the file.  It is
 *         the caller's responsibility to delete this list.
 * @throw runtime_error If an I/O error occurs.
 */
List<Tweet>* readTweetFile(std::string filename);
