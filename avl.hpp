#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <stdexcept>
#include <stack>
struct AVLNode {
    time_t timestamp;
    std::string post;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(std::string post) : timestamp(std::time(nullptr)), post(post), left(nullptr), right(nullptr), height(0) {}
};
struct AVL
{
    AVLNode* root;

    AVL() : root(nullptr) {}

    int height(AVLNode* N) {
        return N ? N->height : -1;
    }

    int balance(AVLNode* N) {
        if(!N) throw std::invalid_argument("Invalid AVLNode");
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

    void insert(std::string post) {
        std::stack<AVLNode*> st;
        if(!root){
            root = new AVLNode(post);
            return;
        }
        AVLNode* curr=root;
        while(curr->right){
            st.push(curr);
            curr=curr->right;
        }
        curr->right = new AVLNode(post);
        curr->height=1 + std::max(height(curr->left), height(curr->right));
        while(!st.empty()){
            AVLNode* node=st.top();
            st.pop();
            node->height = 1 + std::max(height(node->left), height(node->right));
            if (balance(node) < -1) node = leftRotate(node);
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

