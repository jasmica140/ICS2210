
#ifndef ICS2210_NODE_H
#define ICS2210_NODE_H

#include <vector>

using namespace std;

#define MAX_HEIGHT 1000

template <typename T>
class Node {
public:
    T value;
    int height;
    Node* left;
    Node* right;
    vector<Node*> next;

    explicit Node(const T& value) : value(value), height(1), left(nullptr), right(nullptr) {}
};

#endif //ICS2210_NODE_H
