#include <iostream>
#include "BinarySearchTree.h"

int main() {
    BinarySearchTree tree;
    tree.Insert(1);
    tree.Insert(5);
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(4);

    //std::cout << tree.NodeCount() << std::endl;
    tree.Print();
    std::cout << std::endl;
    tree.rebalance();
    std::cout << std::endl;
    tree.Print();
    tree.Insert(0);
    tree.Print();
    tree.Insert(-100);
    tree.Insert(-200);
    tree.Insert(-300);
    tree.Insert(-400);
    tree.Print();
    tree.rebalance();
    std::cout << std::endl;
    tree.Print();
    return 0;
}