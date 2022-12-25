
// This code is written by Younes Lahrichi
// 11/20/2021

#ifndef ASS4_SKIPLIST_H
#define ASS4_SKIPLIST_H

#include <iostream>
#include <vector>

using namespace std;

// only SkipList class can create SNode objects

class SkipList;
// intialization of the SNode class
class SNode {
  friend class SkipList;
  // operator overload initialization
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  // SNode constructor
  explicit SNode(int value);

  // data contained in the object
  int value{0};

  // link to the Next SNode 
  SNode *forward;

  // link to the Prev SNode
  SNode *backward;
   
  //link to the up node 
  SNode *up;

  // link to the down SNode
  SNode *down;
};

class SkipList {
  // operator overload method to display the list with level
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  // maximum number of levels
  int maxLevel = 1;

  // probability of inserting at a higher level
  // as an integer between 0% and 100% (exclusive)
  int probability = 0;

 // array of Depth SNode* objects as FrontGuards linking levels
  SNode **frontGuards;

  // array of Depth SNode* objects as RearGuards linking levels
  SNode **rearGuards;

  // given a SNode, place it before the given nextNode
  void addBefore(int value, SNode *NextNode);

  // return true p% of time,
  // for p = 50, each node has a 50% chance of being at higher level
  bool shouldInsertAtHigher() const;

public:
  // default SkipList has only 1 level, just one doubly-linked list
  explicit SkipList(int maxLevel = 1, int probability = 0);

  // Skip list destructor
  virtual ~SkipList();

  // return true if successfully added, no duplicates allowed
  bool add(int value);

  // return true if successfully removed
  bool remove(int value);

  // return true if found in SkipList
  bool contains(int value) const;
};

#endif // ASS4_SKIPLIST_H
