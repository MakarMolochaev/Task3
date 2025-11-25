#pragma once
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <memory>
#include <vector>
#include "Node.h"

class BinarySearchTree {
    private:
        std::unique_ptr<Node> root;
        size_t size;
        size_t opsSinceRebalance;
        const size_t rebalanceRate = 4;
    public:
        BinarySearchTree();
        ~BinarySearchTree();
        void Insert(int value);
        bool Search(int value);
        bool Remove(int value);
        void Print();
        int NodeCount();
        void PrettyPrint();

    private:
        void rebalance();
        void insertForNode(std::unique_ptr<Node>& node, int value);
        bool removeForNode(std::unique_ptr<Node>& node, int value);
        int minForNode(std::unique_ptr<Node>& node);
        int maxForNode(std::unique_ptr<Node>& node);
        void checkRebalance();
        std::unique_ptr<Node> sortedArrayToBST(const std::vector<int>& nums, int start, int end);
        void prettyPrintHelper(const Node* node, std::string prefix, bool isLast);
        int heightHelper(const Node* node);
};

#endif