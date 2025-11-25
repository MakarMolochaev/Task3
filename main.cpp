#include <iostream>
#include "BinarySearchTree.h"

int main() {
    BinarySearchTree tree;
    tree.Insert(1);
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(4);
    tree.PrettyPrint();
    std::cout << std::endl;
    tree.Insert(5);
    tree.Insert(6);
    tree.Insert(7);
    tree.Insert(8);
    tree.PrettyPrint();
    std::cout << std::endl;

    std::cout << tree.Search(5) << " " << tree.Search(10) << std::endl;
    tree.Remove(5);
    tree.PrettyPrint();
    std::cout << std::endl;
    tree.Insert(-1000);
    tree.PrettyPrint();
    std::cout << std::endl;
    return 0;
}