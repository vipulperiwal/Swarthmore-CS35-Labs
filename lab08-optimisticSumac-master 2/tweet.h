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

/**
 * This class represents Twitter data.  A single object of this class contains
 * information about one tweet.  Note that this class is written in a way which
 * allows it to be copied, so you can write
 *
 * \code{.cpp}
 * Tweet t1 = ...;
 * Tweet t2 = t1;
 * \endcode
 *
 * just as you can with C++ pair objects.
 */
class Tweet {
  public:
    /** The ID of this tweet. */
    std::string id;
    /** The date of the tweet as an ISO-formatted date (YYYY-MM-DD). */
    std::string date;
    /** The username of the user who created this tweet. */
    std::string username;
    /** The user's screenname at the time this tweet was created. */
    std::string screenname;
    /** The contents of the tweet. */
    std::string contents;
    /** The number of replies to this tweet. */
    int replies;
    /** The number of times this tweet has been retweeted. */
    int retweets;
    /** The number of times this tweet has been liked. */
    int likes;
    /** The URL of this tweet. */
    std::string url;

    /**
     * A constructor to create a Request object.
     */
    Tweet(std::string id, std::string date, std::string username,
          std::string screenname, std::string contents, int replies,
          int retweets, int likes, std::string url);
};
