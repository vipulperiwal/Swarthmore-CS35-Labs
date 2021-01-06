/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <UnitTest++/UnitTest++.h>

#include "adts/BST.h"
#include "adts/list.h"
#include "linkedBST.h"
#include "linkedBSTNode.h"

using namespace std;

/**
 * This helper function will build a small BST on which we can perform
 * experiments.  We can call the methods of the BST
 * in a specific order to make sure it puts the nodes where we want them
 * (assuming, of course, that the insert and get functions work correctly).
 * Our tree will look like this:
 * @verbatim
 *         6
 *        / \
 *       /   \         
 *      2     7
 *     / \     \
 *    1   4     9
 *       /
 *      3               
 * @endverbatim
 * @return An example BST.  The caller is responsible for deleting this BST.
 */

LinkedBST<int, string>* makeExampleBST() {
    LinkedBST<int, string>* bst = new LinkedBST<int, string>();
    bst->insert(6, "6");
    bst->insert(2, "2");
    bst->insert(7, "7");
    bst->insert(1, "1");
    bst->insert(4, "4");
    bst->insert(9, "9");
    bst->insert(3, "3");
    bst->checkInvariants();
    CHECK_THROW(bst->insert(3, "three"), std::runtime_error);
    bst->checkInvariants();
    return bst;
}

/**
 * Generates a larger BST to test with
 * @param size The size of the large BST
 */
LinkedBST<int, int>* makeGiantBST(int size) {//generate a larger BST to test with
    LinkedBST<int, int>* bst = new LinkedBST<int, int>();
    for(int i = 0; i<size; i+=3){
        bst -> insert(i, i);
        bst->checkInvariants();
    }
    
    for(int i = 1; i<size; i+=3){
        bst -> insert(i, i);
        bst->checkInvariants();
    }

    for(int i = 2; i<size; i+=3){
        bst -> insert(i, i);
        bst->checkInvariants();
    }
    return bst;
}

/**
 * Generates the expected level order traversal for a giant tree of size 1000
 */ 
vector<pair<int, int>> expectedLevelTraversalGiant(){
    vector<pair<int, int>> returnVec = {pair<int, int>(0,0), pair<int, int>(3,3), pair<int, int>(1,1), pair<int, int>(6,6)};
    for(int i = 2; i<999; i+= 3){//build up expected traversal in vector
        returnVec.push_back(pair<int, int>(i, i));
        returnVec.push_back(pair<int, int>(i+2, i+2));
        if(i+7<1000){
            returnVec.push_back(pair<int, int>(i+7, i+7));
        }
    }
    return returnVec;
}

/**
 * Test to make sure empty BST works
 */
TEST(emptyBST) {
    LinkedBST<int, string>* bst = new LinkedBST<int, string>();
    CHECK_EQUAL(0, bst->getSize());
    CHECK(bst->isEmpty());
    bst->checkInvariants();
    delete bst;
}

TEST(exampleBST) {
    // Since we have to respect the BST interface -- we can't look directly at
    // the BST nodes -- we have to test the example BST to make sure that it
    // behaves like we'd think.  If this test fails, then either the insert or
    // the get method is broken and it's hard to tell which.
    // The upside is that we test both the insert and get functions with this
    // test.
    LinkedBST<int, string>* bst = makeExampleBST();
    for (int i = 1; i <= 9; i++) {
        if (i != 5 && i != 8) {
            CHECK_EQUAL(to_string(i), bst->get(i));
        }
    }
    CHECK_THROW(bst->get(10), std::runtime_error);
    delete bst;
}

TEST(exampleBSTSize) {
    LinkedBST<int, string>* bst = makeExampleBST();
    CHECK_EQUAL(7, bst->getSize());
    CHECK(!bst->isEmpty());
    delete bst;
}

// NOTE: Be sure to make frequent use of the checkInvariants method
// which verifies that your BST contains the correct number of nodes
// and has properly implemented the BST property.

/** Checks to make sure update method works correctly and throws errors where necessary
 */ 
TEST(update){
    LinkedBST<int, string>* bst = makeExampleBST();
    bst -> update(4, "40000");//update a node
    CHECK_EQUAL("40000", bst->get(4));
    CHECK_THROW(bst->update(10, "10"), std::runtime_error);//try to update a node that doesn't exist
    bst-> checkInvariants();
    delete bst;
}

/** 
 * Tests update method for a giant tree
 */
TEST(updateGiant){
    LinkedBST<int, int>* bst = makeGiantBST(1000);
    bst -> update(bst->getSize()/2, bst->getSize()*2);//update a node
    CHECK_EQUAL(bst->get(bst->getSize()/2), bst->getSize()*2);
    CHECK_THROW(bst->update(bst->getSize()+1, bst->getSize()*2), std::runtime_error);//try to update a node that doesn't exist
    bst-> checkInvariants();
    bst -> update(bst->getSize()/6, bst->getSize()*6);//update a node
    CHECK_EQUAL(bst->get(bst->getSize()/6), bst->getSize()*6);
    CHECK_THROW(bst->update(-1,-1), std::runtime_error);//try to update a node that doesn't exist
    bst-> checkInvariants();
    delete bst;
}

/**
 * Tests contains method
 */
TEST(contains){
    LinkedBST<int, string>* bst = makeExampleBST();
    bool t1 = bst -> contains(4);
    CHECK_EQUAL(true, t1);  //check contains == true
    bool t2 = bst -> contains(30);
    CHECK_EQUAL(false, t2); //checks continas == false
    bst-> checkInvariants();
    delete bst;
}

/**
 * Tests contiains method for a giant tree
 */
TEST(containsGiant){
    LinkedBST<int, int>* bst = makeGiantBST(1000);
    for(int i = 0; i<1000; i++){//check contains == true
        CHECK_EQUAL(true, bst->contains(i));
        bst->checkInvariants();
    }
    for(int i = 1001; i<2000; i++){//checks continas == false
        CHECK_EQUAL(false, bst-> contains(i));
        bst->checkInvariants();
    }
    for(int i = -1; i>-20; i--){//checks continas == false
        CHECK_EQUAL(false, bst-> contains(i));
        bst->checkInvariants();
    }
    delete bst;
}

/**
 * Tests remove method to make sure it works correctly and throws errors where necessary
 */
TEST(remove){
    LinkedBST<int, string>* bst = makeExampleBST(); //various checks below: remove and checkInvariants
    bst->remove(2);
    bst -> checkInvariants();
    bst -> remove(4);
    bst -> checkInvariants();
    bst->remove(6);
    bst -> checkInvariants();
    bst->remove(7);
    bst -> checkInvariants();
    CHECK_EQUAL(false, bst -> isEmpty());
    bst -> remove(1);
    bst -> checkInvariants();
    bst->remove(3);
    bst -> checkInvariants();
    bst -> remove(9);
    CHECK_THROW(bst->remove(10), std::runtime_error);
    bst -> checkInvariants();
    CHECK_EQUAL(0, bst-> getSize());
    CHECK_EQUAL(true, bst -> isEmpty());
    delete bst;
}

/**
 * Tests remove on a giant tree
 */
TEST(removeGiant){
    LinkedBST<int, int>* bst = makeGiantBST(1000);  //various checks below: remove and checkInvariants
    for(int i = 0; i<1000; i+= 5){
        bst -> remove(i);
        bst -> checkInvariants();
    }
    CHECK_EQUAL(800,bst->getSize());
    for(int i = 1001; i <2000; i++){
        CHECK_THROW(bst->remove(i), std::runtime_error);
    }
    CHECK_EQUAL(true, bst->contains(999));
    for(int i = 1000; i>-1; i--){
        if(i%5 !=0){
            bst -> remove(i);
            bst -> checkInvariants();
        }
    }
    delete bst;
}

/**
 * Tests getKeys method
 */
TEST(getKeys){
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<int> expected = {6,2,1,4,3,7,9};
    for(int i = 0; i<7; i++){//compare expected and actual getKeys values
        CHECK_EQUAL(expected[i], bst->getKeys()[i]);
    }
    bst-> checkInvariants();
    delete bst;
}

/**
 * Tests getItems method
 */
TEST(getItems) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> items = bst->traversePreOrder();//get actual vector
    vector<pair<int, string>> expected;
    expected.push_back(pair<int, string>(6, "6"));//build up expected vector
    expected.push_back(pair<int, string>(2, "2"));
    expected.push_back(pair<int, string>(1, "1"));
    expected.push_back(pair<int, string>(4, "4"));
    expected.push_back(pair<int, string>(3, "3"));
    expected.push_back(pair<int, string>(7, "7"));
    expected.push_back(pair<int, string>(9, "9"));
    REQUIRE CHECK_EQUAL(expected.size(), items.size());
    for (int i = 0; i < expected.size(); i++) {
        CHECK_EQUAL(expected[i].first, items[i].first);//check expected and actual equal
        CHECK_EQUAL(expected[i].second, items[i].second);
    }
    bst-> checkInvariants();
    delete bst;
}

/**
 * Tests getHeight method
 */
TEST(getHeight){
    LinkedBST<int, string>* bst = makeExampleBST();
    CHECK_EQUAL(3, bst -> getHeight());
    delete bst;
}

/**
 * Tests getMax method
 */
TEST(getMax){
    LinkedBST<int, string>* bst = makeExampleBST();
    CHECK_EQUAL(9, bst -> getMaxKey());
    delete bst;
    bst = new LinkedBST<int, string>;
    CHECK_THROW(bst -> getMaxKey(), std::runtime_error);//try to getMaxkey for empty tree
    delete bst;
}

/**
 * Tests getMin method
 */
TEST(getMin){
    LinkedBST<int, string>* bst = makeExampleBST();
    CHECK_EQUAL(1, bst -> getMinKey());
    delete bst;
    bst = new LinkedBST<int, string>;
    CHECK_THROW(bst -> getMinKey(), std::runtime_error);//try to getMinkey for empty tree
    delete bst;
}

/**
 *  Tests generating a pre-order tree traversal
 */
TEST(examplePreOrderTraversal) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> traversal = bst->traversePreOrder();

    // build vector containing what we the ordering should be
    vector<pair<int, string>> expected;
    expected.push_back(pair<int, string>(6, "6"));
    expected.push_back(pair<int, string>(2, "2"));
    expected.push_back(pair<int, string>(1, "1"));
    expected.push_back(pair<int, string>(4, "4"));
    expected.push_back(pair<int, string>(3, "3"));
    expected.push_back(pair<int, string>(7, "7"));
    expected.push_back(pair<int, string>(9, "9"));
    REQUIRE CHECK_EQUAL(expected.size(), traversal.size());
    for (int i = 0; i < expected.size(); i++) {//check expected and actual equal
        CHECK_EQUAL(expected[i].first, traversal[i].first);
        CHECK_EQUAL(expected[i].second, traversal[i].second);
    }
    delete bst;
}

/**
 *  Tests generating an in-order tree traversal
 */
TEST(inOrderTraversal) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> traversal = bst->traverseInOrder();

    // build vector containing what we the ordering should be
    vector<pair<int, string>> expected;
    expected.push_back(pair<int, string>(1, "1"));
    expected.push_back(pair<int, string>(2, "2"));
    expected.push_back(pair<int, string>(3, "3"));
    expected.push_back(pair<int, string>(4, "4"));
    expected.push_back(pair<int, string>(6, "6"));
    expected.push_back(pair<int, string>(7, "7"));
    expected.push_back(pair<int, string>(9, "9"));
    REQUIRE CHECK_EQUAL(expected.size(), traversal.size());
    for (int i = 0; i < expected.size(); i++) {//check expected and actual equal
        CHECK_EQUAL(expected[i].first, traversal[i].first);
        CHECK_EQUAL(expected[i].second, traversal[i].second);
    }
    delete bst;
}

/**
 *  Tests generating a post-order tree traversal
 */
TEST(postOrderTraversal) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> traversal = bst->traversePostOrder();

    // build vector containing what we the ordering should be 1, 3, 4, 2, 9, 7, 6
    vector<pair<int, string>> expected;
    expected.push_back(pair<int, string>(1, "1"));
    expected.push_back(pair<int, string>(3, "3"));
    expected.push_back(pair<int, string>(4, "4"));
    expected.push_back(pair<int, string>(2, "2"));
    expected.push_back(pair<int, string>(9, "9"));
    expected.push_back(pair<int, string>(7, "7"));
    expected.push_back(pair<int, string>(6, "6"));
    REQUIRE CHECK_EQUAL(expected.size(), traversal.size());
    for (int i = 0; i < expected.size(); i++) {//check expected and actual equal
        CHECK_EQUAL(expected[i].first, traversal[i].first);
        CHECK_EQUAL(expected[i].second, traversal[i].second);
    }
    delete bst;
}

/**
 *  Tests generating a level-order tree traversal
 */
TEST(levelOrderTraversal) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> traversal = bst->traverseLevelOrder();

    // build vector containing what we the ordering should be 6271493
    vector<pair<int, string>> expected;
    expected.push_back(pair<int, string>(6, "6"));
    expected.push_back(pair<int, string>(2, "2"));
    expected.push_back(pair<int, string>(7, "7"));
    expected.push_back(pair<int, string>(1, "1"));
    expected.push_back(pair<int, string>(4, "4"));
    expected.push_back(pair<int, string>(9, "9"));
    expected.push_back(pair<int, string>(3, "3"));
    REQUIRE CHECK_EQUAL(expected.size(), traversal.size());
    for (int i = 0; i < expected.size(); i++) {//check expected and actual equal
        CHECK_EQUAL(expected[i].first, traversal[i].first);
        CHECK_EQUAL(expected[i].second, traversal[i].second);
    }
    delete bst;
}

/**
 *  Tests generating a level-order tree traversal for a giant tree
 */
TEST(levelOrderGiant){
    LinkedBST<int, int>* bst = makeGiantBST(1000);
    vector<pair<int, int>> traversal = bst->traverseLevelOrder();
    vector<pair<int, int>> expected = expectedLevelTraversalGiant();
    for(int i = 0; i<1000; i++){//check expected and actual equal
        CHECK_EQUAL(expected[i].first,traversal[i].first);
    }
    delete bst;
}

int main() {
    return UnitTest::RunAllTests();
}
