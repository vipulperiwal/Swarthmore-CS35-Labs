/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "hashTable.h"
#include "ioUtils.h"
#include "tweet.h"
#include "adts/stlList.h"
#include "adts/stlMaxPriorityQueue.h"


using namespace std;

void cleanUpHash(HashTable<string, STLList<Tweet>*>* hash){
    /**
     * Cleans up the hash table
     * @param hash The hash table to clean.
     * @return None
     */
    vector<string> keysList = hash -> getKeys();
    for(int i=0; i<hash -> getSize(); i++){//deletes tweets at every key
        STLList<Tweet>* toDelete = hash -> get(keysList[i]);
        delete toDelete;
    }
    delete hash;
}

void displayTop5(bool byRetweet, string search, HashTable<string, STLList<Tweet>*>* tweetDict){
    /**
     * Displays the top 5 tweets by either like or retweet
     * @param byRetweet Determines if we display by retweet or likes
     * @param search the key to be looked up
     * @param tweetDict the hashtable containing tweets
     * @return None
     */
    STLList<Tweet>* searchList;
    searchList = tweetDict -> get(search);  //Get list of relavant tweets
    vector<Tweet> tweetVec = searchList -> toVector();
    vector<pair<int, Tweet>> prioVec;
    if(byRetweet){  //create vector with priorities
        for(int i=0; i<tweetVec.size(); i++){
            prioVec.push_back(pair<int,Tweet>(tweetVec[i].retweets, tweetVec[i]));
        } 
    }
    else{
        for(int i=0; i<tweetVec.size(); i++){
            prioVec.push_back(pair<int,Tweet>(tweetVec[i].likes, tweetVec[i]));
        }
    }
    STLMaxPriorityQueue<int, Tweet> tweetQueue(prioVec);    //create max priority queue to heapify results
    for(int i = 0; i<5; i++){
        if(tweetQueue.getSize() > 0){
            Tweet displayTweet = tweetQueue.remove();
                                
                                //BUILD UP LAYOUT:   
                                
                                //username      date 
                                //contents
                                //replies       retweets        likes       url
    
            cout << "@" << displayTweet.username<< "    "<<"("<<displayTweet.date<< ")" << endl;
            cout << displayTweet.contents << endl;
            cout << "Rpl: " << displayTweet.replies << "    " <<"Rtw: "<< displayTweet.retweets << "    " << 
            "Lik: " <<displayTweet.likes << "    " <<"URL: "<< displayTweet.url << "    " << endl<<endl;
        }
    }
}

HashTable<string, STLList<Tweet>*>* buildUpDictOfTweetsUser(string filename){
    /**
     * Builds up dictionary of tweets with user name as the key
     * @param filename the file containing tweets
     * @return Hash Table of tweets
     */
    List<Tweet>* listOfTweets = readTweetFile(filename);    //read tweets in
        HashTable<string, STLList<Tweet>*>* tweetsByUserName = new HashTable<string, STLList<Tweet>*>;
        int tweetsNum = listOfTweets->getSize();
        for(int i = 0; i<tweetsNum; i++){// build up hash table
            Tweet tweet = listOfTweets -> removeFirst();
            if(!tweetsByUserName -> contains(tweet.username)){// add new key if it does not exist in the dictionary already
                STLList<Tweet>* tweetList = new STLList<Tweet>;
                tweetList -> insertLast(tweet);
                tweetsByUserName -> insert(tweet.username, tweetList);
            }
            else{// add tweet to a list if the key is already in the dictionary
                STLList<Tweet>* listPtr = tweetsByUserName -> get(tweet.username);
                listPtr -> insertLast(tweet);
            }
        }
    delete listOfTweets;
    return tweetsByUserName;
}

HashTable<string, STLList<Tweet>*>* buildUpDictOfTweetsDate(string filename){
    /**
     * Builds up dictionary of tweets with date as the key
     * @param filename the file containing tweets
     * @return Hash Table of tweets
     */
    cout<<"Loading Tweets..."<<endl;
    List<Tweet>* listOfTweets = readTweetFile(filename);    //read tweets in
    cout<<"Processing Tweets..."<<endl;
    HashTable<string, STLList<Tweet>*>* tweetsByDate = new HashTable<string, STLList<Tweet>*>;
    int tweetsNum = listOfTweets->getSize();
    for(int i = 0; i<tweetsNum; i++){   // build up hash table
        Tweet tweet = listOfTweets -> removeFirst();
        if(!tweetsByDate -> contains(tweet.date)){// add new key if it does not exist in the dictionary already
            STLList<Tweet>* tweetList = new STLList<Tweet>;
            tweetList -> insertLast(tweet);
            tweetsByDate -> insert(tweet.date, tweetList);
        }
        else{// add tweet to a list if the key is already in the dictionary
            STLList<Tweet>* listPtr = tweetsByDate -> get(tweet.date);
            listPtr -> insertLast(tweet);
        }
    }
    delete listOfTweets;
    return tweetsByDate;
}


int main(int argc, char** argv) {
    /**
     * This is our main function with our user interface!
     */
    string filename;
    if(argc != 2){// make sure correct number of arguments are given
        try{
            throw runtime_error("Error! Invalid number of command-line arguments!");
        }
        catch (runtime_error e){
            cout<<e.what()<<endl;
            return 0;
        }
    }
    else{
        filename = argv[1];
    }
    HashTable<string, STLList<Tweet>*>* dictByDate = buildUpDictOfTweetsDate(filename); //build up dictionary of tweets
    HashTable<string, STLList<Tweet>*>* dictByUsername = buildUpDictOfTweetsUser(filename);
    if(dictByDate->isEmpty() && dictByUsername -> isEmpty()){   //make sure file/tweets exists
        cout<<"Error! File does not exist or, if it does exist, no tweets are in the file."<<endl;
        cleanUpHash(dictByUsername);
        cleanUpHash(dictByDate);
        return 0;
    }
    cout<<"File "<<filename<<" successfully loaded!"<<endl<<endl;
    cout<<"~~~ Welcome to the tweet database query tool! ~~~"<<endl;
    string selection = "0";

    while(selection != "3"){    //user descision loop
        cout<<endl<<"Please choose from the following options:"<< endl;
        cout<< "1) Search by username" << endl;
        cout<< "2) Search by date"<< endl;
        cout<< "3) Quit"<< endl;
        cout<<"? ";
        cin >> selection;   //take in selection
        cout<<endl;
        if(selection == "3"){
            cout<<"Goodbye!"<<endl;
            cleanUpHash(dictByUsername);    //memory management
            cleanUpHash(dictByDate);
            return 0;
        } else if(selection != "1" && selection !="2"){
            cout<<"Invalid choice. Please select option 1 or option 2 or option 3."<<endl;
        }
        else if(selection == "1"){//Want to search by username
            string username;
            cout<<"Please enter your search username: ";
            cin >> username;
            if(!dictByUsername-> contains(username)){
                cout<<"Error! Tweets with that username do not exist in the specified file!"<<endl;
            }
            else{
                cout<<"Would you like to search by (r)etweet count or (l)ike count? ";
                string searchBy;
                cin >> searchBy;
                cout<<endl;
                while(searchBy != "r"&&searchBy != "l"){
                    cout<<"Invalid choice. Please select option r or option l.";
                    cin >> searchBy;
                }
                if(searchBy == "r"){//display info as necessary
                    try{
                        displayTop5(true, username, dictByUsername);
                    }
                    catch (runtime_error e) {
                        cout<<"Error! That username does not exist in the specified file!"<<endl;
                    }
                }
                else{
                    try{
                        displayTop5(false, username, dictByUsername);
                    }
                    catch (runtime_error e) {// just in case ;)
                        cout<<"Error! That username does not exist in the specified file!"<<endl;
                    }
                }
            }
        }
        else{//want to search by date
            string date;
            cout<< "Please enter your search date: ";
            cin >> date;
            if(!dictByDate -> contains(date)){
                cout<<"Error! Tweets with that date do not exist in the specified file!"<<endl;
            }
            else{
                cout<<"Would you like to search by (r)etweet count or (l)ike count? ";
                string searchBy;
                cin >> searchBy;
                cout<<endl;
                while(searchBy != "r"&&searchBy != "l"){
                    cout<<"Invalid choice. Please select option r or option l: ";
                    cin >> searchBy;
                }
                if(searchBy == "r"){//display info as necessary
                    try{
                        displayTop5(true, date, dictByDate);
                    }
                    catch (runtime_error e) {//just in case ;)
                        cout<<"Error! Tweets with that date does not exist in the specified file!"<<endl;
                    }

                }
                else{
                    try{
                        displayTop5(false, date, dictByDate);
                    }
                    catch (runtime_error e) {
                        cout<<"Error! Tweets with that date does not exist in the specified file!"<<endl;
                    }
                }
            }
        }   
    }
    return 0;
}
