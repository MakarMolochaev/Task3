#pragma once
#ifndef NODE_H
#define NODE_H

#include <memory>

class Node {
    public:
        int data;
        std::unique_ptr<Node> L;
        std::unique_ptr<Node> R;

        Node(int value) : data(value), L(nullptr), R(nullptr) {}
};

#endif