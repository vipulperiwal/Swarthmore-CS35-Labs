#include "tweet.h"

using namespace std;

Tweet::Tweet(std::string id, std::string date, std::string username,
             std::string screenname, std::string contents, int replies,
             int retweets, int likes, std::string url) {
    this->id = id;
    this->date = date;
    this->username = username;
    this->screenname = screenname;
    this->contents = contents;
    this->replies = replies;
    this->retweets = retweets;
    this->likes = likes;
    this->url = url;
}