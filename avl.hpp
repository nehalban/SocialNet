#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <stack>
struct AVLNode {
    time_t timestamp;
    std::string post;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(std::string post) : timestamp(std::time(nullptr)), post(post), left(nullptr), right(nullptr), height(0) {}
};
struct AVL{
    AVLNode* root;

    AVL() : root(nullptr) {}

    int height(AVLNode* N) {
        return N ? N->height : -1;
    }

    int balance(AVLNode* N) {
        if(!N){
            std::cout<<"Error: Trying to get balance of a null node"<<std::endl;
            return 0;
        }
        return height(N->left) - height(N->right);
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;

        y->left = x->right;
        x->right = y;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLNode* leftRotate(AVLNode* y) {
        AVLNode* x = y->right;

        y->right = x->left;
        x->left = y;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    void insert(const std::string& post) {
        if (!root) {
            root = new AVLNode(post);
            return;
        }
        std::stack<AVLNode*> st;
        AVLNode* curr = root;
        while (curr->right) {
            st.push(curr);
            curr = curr->right;
        }
        curr->right = new AVLNode(post);
        curr->height = 1 + std::max(height(curr->left), height(curr->right));
        while (!st.empty()) {
            AVLNode* node = st.top();
            st.pop();
            node->height = 1 + std::max(height(node->left), height(node->right));
            int bf = balance(node);

            if (bf < -1) {
                AVLNode* rotated = leftRotate(node);
                if (st.empty()) {
                    root = rotated;
                } else {
                    AVLNode* parent = st.top();
                    if (parent->right == node) parent->right = rotated; else parent->left = rotated;
                }
            }
        }
    }

    void reverseInOrder(AVLNode* node, int& n) {
        if(n <= 0 || !node) return;
        reverseInOrder(node->right, n);
        if (n > 0) {
            std::cout << "Timestamp: " << std::asctime(std::localtime(&node->timestamp)) << "   Post: " << node->post << std::endl;
            n--;
            reverseInOrder(node->left, n);
        }
    }

    void deleteTree(AVLNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    ~AVL(){
        deleteTree(root);
    }
};

