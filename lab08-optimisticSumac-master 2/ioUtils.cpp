#include "ioUtils.h"

#include <fstream>
#include "adts/stlList.h"
#include "tweet.h"

using namespace std;

List<Tweet>* readTweetFile(string filename) {
    ifstream file(filename);
    List<Tweet>* results = new STLList<Tweet>();
    string line;
    getline(file, line); // priming
    while (file.good() && line.length() > 0) {
        string id = line;
        getline(file, line);
        string date = line;
        getline(file, line);
        string username = line;
        getline(file, line);
        string screenname = line;
        getline(file, line);
        string contents = line;
        getline(file, line);
        int replies = stoi(line);
        getline(file, line);
        int retweets = stoi(line);
        getline(file, line);
        int likes = stoi(line);
        getline(file, line);
        string url = line;;
        results->insertLast(
            Tweet(id, date, username, screenname, contents, replies, retweets,
                  likes, url));
        getline(file, line); // for next loop iteration
    }
    file.close();
    return results;
}