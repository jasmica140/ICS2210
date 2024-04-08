#include <cstdio>

class Node {
public:
    int key;
    int height;
    Node* left;
    Node* right;

    explicit Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

int height(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(int key) {
    return new Node(key);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node* insert(Node* node, int key) {
    if (node == nullptr) {
        return newNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void printInOrder(Node* node) {
    if (node == nullptr) {
        return;
    }

    printInOrder(node->left);
    printf("%d ", node->key);
    printInOrder(node->right);
}

void insertInAvlTree(int* arr, int n) {
    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    printInOrder(root);
    printf("\n");
}