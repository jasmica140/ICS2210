#include <vector>
#include <ctime>
#include <iostream>

#include "knuthShuffe.h"
#include "AVLTree.h"
#include "skipList.h"

using namespace std;

int main() {
    int integers[5000];

    for (int i = 0; i < 5000; i++) {
        integers[i] = i;
    }

    srand(time(0));

    knuthShuffle(integers, 5000);

    AVLTree<int> avlTree;

    for (int integer : integers) {
        avlTree.insert(integer);
    }

    // Print the AVL tree in order
    avlTree.printInOrder();

    // Create a skip list object
    SkipList<int> skipList;

    // Insert all the integers from the array into the skip list
    for (int integer : integers) {
        skipList.insert(integer);
    }

    // Print the skip list
    //skipList.print();

    return 0;
}


