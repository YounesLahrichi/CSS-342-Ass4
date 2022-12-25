#include <cassert>
#include <iostream>
#include <time.h>
#include "skiplist.h"

using namespace std;

void test1() {
  srand(time(NULL));
  SkipList skp(1, 0);
  cout << boolalpha;
  skp.add(30);
  skp.add(13);
  skp.add(82);
  skp.add(1991);
  skp.add(1453);
  skp.add(903);
  skp.add(334);
  skp.add(76);
  skp.add(50);
  skp.add(35);
  skp.add(1);
  skp.add(18);
  skp.add(99);
  skp.add(105);


  skp.remove(30);
  skp.remove(13);
  skp.remove(82);
  skp.remove(1991);
  skp.remove(1453);
  skp.remove(903);
  skp.remove(334);
  skp.remove(76);
  skp.remove(50);
  skp.remove(35);
  skp.remove(1);
  skp.contains(9);
  cout << skp << endl;
}

void test2() {
  srand(time(NULL));
  SkipList skp1(5, 99);
  cout << boolalpha;
  skp1.add(30);
  skp1.add(13);
  skp1.add(82);
  skp1.add(1991);
  skp1.add(1453);
  skp1.add(903);
  skp1.add(334);
  skp1.add(76);
  skp1.add(50);
  skp1.add(35);
  skp1.add(1);
  skp1.add(18);
  skp1.add(99);
  skp1.add(105);


  skp1.remove(30);
  skp1.remove(13);
  skp1.remove(82);
  skp1.remove(1991);
  skp1.remove(1453);
  skp1.remove(903);
  skp1.remove(334);
  skp1.remove(76);
  skp1.remove(50);
  skp1.remove(35);
  skp1.remove(1);
  skp1.contains(9);
  cout << skp1 << endl;
}

void test3() {
  srand(time(NULL));
  SkipList skp2(20, 80);
  cout << boolalpha;
  skp2.add(30);
  skp2.add(13);
  skp2.add(82);
  skp2.add(1991);
  skp2.add(1453);
  skp2.add(903);
  skp2.add(334);
  skp2.add(76);
  skp2.add(50);
  skp2.add(35);
  skp2.add(1);
  skp2.add(18);
  skp2.add(99);
  skp2.add(105);


  skp2.remove(30);
  skp2.remove(13);
  skp2.remove(82);
  skp2.remove(1991);
  skp2.remove(1453);
  skp2.remove(903);
  skp2.remove(334);
  skp2.remove(76);
  skp2.remove(50);
  skp2.remove(35);
  skp2.remove(1);
  skp2.contains(9);
  skp2.contains(13);
  skp2.contains(30);
  skp2.contains(50);
  skp2.contains(35);
  cout << skp2 << endl;
}


int main() {

  test1();
  test2();
  test3();

  cout << "Done." << endl;
  return 0;
}