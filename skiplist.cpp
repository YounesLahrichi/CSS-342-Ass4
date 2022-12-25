// This code is written by Younes Lahrichi
// This is my implementation of a skiplist
// This coode is a 4 way linked list that searches, adds, and removes values from a linked list with low time complexity.
// 11/20/2021

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

// this is the operator overload method for printing our my linked lists
ostream &operator<<(ostream &Out, const SkipList &SkipL) {
  for (int Index = SkipL.maxLevel - 1; Index >= 0; Index--) {
    Out << "Level: " + to_string(Index) + " -- ";
    SNode* Curr = SkipL.frontGuards[Index];
    while(Curr != nullptr) {
      Out<< to_string(Curr->value) + ", ";
      Curr = Curr->forward;
    }
    Out << "\n";
  }
  return Out;
}

// this is my SNode class constructor 
SNode::SNode(int value) : value{value}{}

// this is my SkipList constructor
SkipList::SkipList(int maxLevel, int probability) : maxLevel{maxLevel}, probability{probability} {
  //this checks if max level is greater than 0 and the probability is less than 100 but greater than 0
  assert(maxLevel > 0 && probability >= 0 && probability < 100);
  //this creates new array of nodes for the front and rear guards for the linked lists
  frontGuards = new SNode* [maxLevel];
  rearGuards = new SNode* [maxLevel];
  
  // this for loop sets all the front guards to point to the rear guards and the rear guards to the front guards
  // then it sets all the front guards backward pointers to nullptr and all the rear guards front pointers to nullptr
  for (int i = 0; i < maxLevel; i++) {
    frontGuards[i] = new SNode(INT_MIN);
    rearGuards[i] = new SNode(INT_MAX);
    frontGuards[i]->forward = rearGuards[i];
    rearGuards[i]->backward = frontGuards[i];
    frontGuards[i]->backward = nullptr;
    rearGuards[i]->forward = nullptr;
  }

  // this forloop links all of the front and rear guards to each other
  for (int i = 0; i < maxLevel; i++){
    // this if checks if the its the base level, if so it makes the down pointers of the rear and front guards nullptr
    if(i == 0){
      frontGuards[i]->up = frontGuards[i+1];
      rearGuards[i]->up = rearGuards[i+1];
      frontGuards[i]->down = nullptr;
      rearGuards[i]->down = nullptr;
    }
    //this if checks that if its the top level then it sets both the front and rear guard up pointers to nullptr
    else if(i == maxLevel - 1){
      frontGuards[i]->up = nullptr;
      rearGuards[i]->up = nullptr;
      frontGuards[i]->down = frontGuards[i-1];
      rearGuards[i]->down = rearGuards[i-1];
    }
    // this else links the guards up and down if it isnt the first or last level
    else {
      frontGuards[i]->up = frontGuards[i+1];
      rearGuards[i]->up = rearGuards[i+1];
      frontGuards[i]->down = frontGuards[i-1];
      rearGuards[i]->down = rearGuards[i-1];
    }
  }
}

// this is the skip list destructor
SkipList::~SkipList() {
  // this forloop deletes each node individual 
  // it starts from the top most level then it saves the next pointer and deletes all the pointers and nodes
  // of the first node then moves to the next one
  for (int i = maxLevel - 1; i >= 0; i--){
  
    SNode* dlt = frontGuards[i];
    
    SNode* dltNext;
    while(dlt != nullptr){
      dltNext = dlt->forward;
      dlt->forward = nullptr;
      dlt->backward = nullptr;
      dlt->up = nullptr;
      dlt->down = nullptr;
      delete dlt;
      dlt = dltNext;
    }
  }
  // this deletes the dynamically allocated arrays of the front a rear guards.
  delete[] frontGuards;
  delete[] rearGuards;
}

// this is the roll whether the random number generated is larger than the probabilty that is passed in
bool SkipList::shouldInsertAtHigher() const {
  return rand() % 100 < probability;
}

// this is the method given a value and the next node it will add that value in a node to the next node
void SkipList::addBefore(int value, SNode *NextNode) {
  SNode* store = NextNode->backward;
  NextNode->backward = new SNode(value);
  NextNode->backward->backward = store;
  store->forward = NextNode->backward;
  NextNode->backward->forward = NextNode;
}

//this method adds a value the linked list
bool SkipList::add(int value) {
  bool goneUp = true;
  SNode* curr = frontGuards[maxLevel-1];
  // this for loop starts at the top level of the linked list
  // and checks if the next node is bigger than the passed in value if it isnt it moves forward
  // then it checks if the next value is a duplicate
  // if both of these checks dont happen at a each level then it moves down
  for(int i = maxLevel-1; i >= 0; i--){
    while(curr->forward != nullptr && curr->forward->value < value){
      curr = curr->forward;
    } 
      
    if (curr->forward != nullptr && curr->forward->value == value){
      return false;
    }
    if (i != 0){
      curr = curr->down;
    }
  }
  // then it runs the addBefore method to add the node
  addBefore(value,curr->forward);

  
  curr->forward->down = nullptr;
  curr = curr->forward->forward;
  // then this runs to check if the node should be added to the next level of the linked list
  // if it should be inserted at the next level, this method adds it to the next level and rolls again 
  // to check if it should be added at the next level until it gets to the top level  
  for (int i = 1; i < maxLevel && goneUp; i++){
    if(shouldInsertAtHigher()){
      SNode* store = curr->backward;
      while (curr->forward != nullptr && curr->up == nullptr){
        curr = curr->forward;
      }
      curr = curr->up;
      
      addBefore(value, curr);
      store->up = curr->backward;
      curr->backward->down = store;
      curr->backward->up = nullptr;
    }
    else {goneUp = false;}
  }
  return true;
}

// this method removes a value from all levels of the linked list
bool SkipList::remove(int value) {
  SNode* store;
  // this for loops iterates from the max level and checks if the next value is greater than the current value
  for (int i = maxLevel - 1; i >=0; i--){
    SNode* curr = frontGuards[i];
    while(value > curr->forward->value){
      curr = curr->forward;
    }
    // if the current value is equal to the value you want to remove then it links
    // the forward and backward pointers to each other and stores the one below it
    // then it sets all the pointers to nullptr and deletes the node
    // then you go to the node below it and repeat til you get to the first level and then it just deletes it  
    if (curr->forward->value == value){
      curr = curr->forward;
      store = curr->down;
      curr->backward->forward = curr->forward;
      curr->forward->backward = curr->backward;
      curr->forward = nullptr;
      curr->backward = nullptr;
      curr->down = nullptr;
      curr->up = nullptr;
      delete curr;
      curr = store;
    }
    else if (i != 0) {
      curr = curr->down;
    }
    else{return false;}
  }
  return true; 
}

// this method checks if the passed in value is in the list
bool SkipList::contains(int value) const {
  // this forloop starts at the max level checks if the next value is greater than the value its looking for
  // then if it isn't then it moves to that node
  for (int i = maxLevel - 1; i >=0; i--){
    SNode* curr = frontGuards[i];
    while(value > curr->forward->value){
      curr = curr->forward;
    }
    // if the next value is equal to the value you are looking for then it will return true
    if (curr->forward->value == value){
      return true;
    }
    // if it doesnt find that value in that level it will go down a level
    else if(i != 0){
      curr = curr->down;
    }
  }
  return false; 
}
