#ifndef ICS2210_AVLTREE_H
#define ICS2210_AVLTREE_H

#include <cstdio>
#include <iostream>
#include "node.h"

using namespace std;

template <typename T>
int height(Node<T>* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

template <typename T>
int max(int a, int b) {
    return (a > b) ? a : b;
}

template <typename T>
Node<T>* newNode(const T& key) {
    return new Node<T>(key);
}

template <typename T>
Node<T>* rightRotate(Node<T>* y) {
    Node<T>* x = y->left;
    Node<T>* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

template <typename T>
Node<T>* leftRotate(Node<T>* x) {
    Node<T>* y = x->right;
    Node<T>* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

template <typename T>
int getBalance(Node<T>* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

template <typename T>
Node<T>* insert(Node<T>* node, const T& key) {
    if (node == nullptr) {
        return new Node<T>(key);
    }

    if (key < node->value) {
        node->left = insert(node->left, key);
    } else if (key > node->value) {
        node->right = insert(node->right, key);
    } else {
        // Key already exists in the tree
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->value) {
        return rightRotate(node);
    }

    if (balance < -1 && key > node->right->value) {
        return leftRotate(node);
    }

    if (balance > 1 && key > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

template <typename T>
void printInOrder(Node<T>* node) {
    if (node == nullptr) {
        return;
    }

    printInOrder(node->left);
    cout << node->value << " ";
    printInOrder(node->right);
}

template <typename T>
class AVLTree {
public:
    Node<T>* root;

    AVLTree() : root(nullptr) {}

    void insert(const T& value) {
        root = insert(root, value);
    }

    void printInOrder() {
        printInOrder(root);
        cout << endl;
    }

private:
    int height(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Node<T>* newNode(const T& value) {
        return new Node<T>(value);
    }

    Node<T>* rightRotate(Node<T>* y) {
        Node<T>* x = y->left;
        Node<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node<T>* leftRotate(Node<T>* x) {
        Node<T>* y = x->right;
        Node<T>* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node<T>* insert(Node<T>* node, const T& value) {
        if (node == nullptr) {
            return newNode(value);
        }

        if (value < node->value) {
            node->left = insert(node->left, value);
        } else if (value > node->value) {
            node->right = insert(node->right, value);
        } else {
            // Value already exists in the tree
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = height(node->left) - height(node->right);

        if (balance > 1 && value < node->left->value) {
            return rightRotate(node);
        }

        if (balance < -1 && value > node->right->value) {
            return leftRotate(node);
        }

        if (balance > 1 && value > node->left->value) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && value < node->right->value) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void printInOrder(Node<T>* node) {
        if (node == nullptr) {
            return;
        }

        printInOrder(node->left);
        cout << node->value << " ";
        printInOrder(node->right);
    }
};

#endif // ICS2210_AVLTREE_H