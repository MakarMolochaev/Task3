#include "BinarySearchTree.h"
#include <iostream>
#include <queue>
#include <math.h>
#include <algorithm>

BinarySearchTree::BinarySearchTree() : size(0), opsSinceRebalance(0) {}

BinarySearchTree::~BinarySearchTree() = default;

void BinarySearchTree::Insert(int value) {
    this->insertForNode(this->root, value);
    this->size++;
    this->opsSinceRebalance++;
    checkRebalance();
}

void BinarySearchTree::insertForNode(std::unique_ptr<Node>& node, int value){
    if (!node) {
        node = std::make_unique<Node>(value);
        return;
    }
    
    if (value < node->data) {
        this->insertForNode(node->L, value);
    } else if (value > node->data) {
        this->insertForNode(node->R, value);
    }
}

bool BinarySearchTree::Search(int value) {
    Node* current = root.get();

    while (current) {
        if (value == current->data) {
            return true;
        }
        if (value < current->data) {
            current = current->L.get();
        } else {
            current = current->R.get();
        }
    }
    return false;
}

int BinarySearchTree::minForNode(std::unique_ptr<Node>& node) {
    if(!node->L) {
        return node->data;
    }
    return minForNode(node->L);
}

int BinarySearchTree::maxForNode(std::unique_ptr<Node>& node) {
    if(!node->R) {
        return node->data;
    }
    return maxForNode(node->R);
}

void BinarySearchTree::Print() {
    if (!root) {
        std::cout << "Tree is empty" << std::endl;
        return;
    }
    
    std::queue<Node*> q;
    q.push(root.get());
    
    while (!q.empty()) {
        int levelSize = q.size();
        
        for (int i = 0; i < levelSize; ++i) {
            const Node* current = q.front();
            q.pop();
            
            std::cout << current->data << " ";
            
            if (current->L) q.push(current->L.get());
            if (current->R) q.push(current->R.get());
        }
        std::cout << std::endl;
    }
}

int BinarySearchTree::NodeCount() {
    return this->size;
}

void BinarySearchTree::rebalance() {
    if (!root) {
        return;
    }

    std::vector<int> allElements;
    
    std::queue<Node*> q;
    q.push(root.get());
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            const Node* current = q.front();
            q.pop();
            
            allElements.push_back(current->data);
            
            if (current->L) q.push(current->L.get());
            if (current->R) q.push(current->R.get());
        }
    }

    //for(int i=0;i<allElements.size();i++) {
    //    std::cout << allElements[i] << " ";
    //}

    std::sort(allElements.begin(), allElements.end());

    root = sortedArrayToBST(allElements, 0, this->size-1);
}

std::unique_ptr<Node> BinarySearchTree::sortedArrayToBST(const std::vector<int>& nums, int start, int end) {
    if (start > end) return nullptr;
    
    int mid = start + (end - start) / 2;
    std::unique_ptr<Node> node = std::make_unique<Node>(nums[mid]);
    
    node->L = this->sortedArrayToBST(nums, start, mid - 1);
    node->R = this->sortedArrayToBST(nums, mid + 1, end);
    
    return node;
}

bool BinarySearchTree::Remove(int value) {
    bool removed = removeForNode(this->root, value);
    if (removed) {
        this->size--;
        this->opsSinceRebalance++;
    }
    checkRebalance();
    return removed;
}

bool BinarySearchTree::removeForNode(std::unique_ptr<Node>& node, int value) {
    if (!node) {
        return false;
    }

    if (value < node->data) {
        return removeForNode(node->L, value);
    } else if (value > node->data) {
        return removeForNode(node->R, value);
    } else {
        if (!node->L && !node->R) {
            node = nullptr;
        } else if (!node->L) {
            node = std::move(node->R);
        } else if (!node->R) {
            node = std::move(node->L);
        } else {
            int min_val = minForNode(node->R);
            node->data = min_val;
            removeForNode(node->R, min_val);
        }
        return true;
    }
}

void BinarySearchTree::checkRebalance() {
    if(this->opsSinceRebalance >= this->rebalanceRate) {
        double idealHeight = log2(this->size + 1);
        int actualHeight = this->heightHelper(root.get());

        if(actualHeight > 2.0 * idealHeight + 1) {
            this->rebalance();
            this->opsSinceRebalance = 0;
        }
    }
}

int BinarySearchTree::heightHelper(const Node* node) {
    if (!node) return 0;
    int leftH  = this->heightHelper(node->L.get());
    int rightH = this->heightHelper(node->R.get());
    return 1 + std::max(leftH, rightH);
}

void BinarySearchTree::PrettyPrint() {
    if (!this->root) {
        std::cout << "Дерево пустое\n";
        return;
    }
    this->prettyPrintHelper(root.get(), "", true);
}

void BinarySearchTree::prettyPrintHelper(const Node* node, std::string prefix, bool isLast) {
    if (!node) return;

    std::cout << prefix;

    std::cout << (isLast ? "\\-- " : "|-- ");

    std::cout << node->data << "\n";

    if (node->L || node->R) {
        std::string newPrefix = prefix + (isLast ? "    " : "|   ");

        if (node->L) {
            bool lastChild = !node->R;
            prettyPrintHelper(node->L.get(), newPrefix, lastChild);
        } else {
            std::cout << newPrefix << "|-- (null)\n";
        }

        if (node->R) {
            prettyPrintHelper(node->R.get(), newPrefix, true);
        }
    }
}