#ifndef ICS2210_SKIPLIST_H
#define ICS2210_SKIPLIST_H

#include "node.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

template <typename T>
class SkipList {
private:
    Node<T>* header;
    int maxHeight;
    float prob;

    int randomHeight() {
        int height = 1;
        while (std::rand() < RAND_MAX * prob)
            height++;
        return height;
    }

    Node<T>* find(T data) {
        Node<T>* x = header;
        for (int i = maxHeight - 1; i >= 0; i--) {
            while (x->next[i] && x->next[i]->value < data)
                x = x->next[i];
        }
        return x->next[0];
    }

public:
    explicit SkipList(float prob = 0.5) : header(new Node<T>(-1)), maxHeight(1), prob(prob) {
        header->next.resize(maxHeight, nullptr);
    }

    ~SkipList() {
        Node<T>* x = header;
        Node<T>* y = nullptr;
        while (x != nullptr) {
            y = x;
            x = x->next[0];
            delete y;
        }
    }

    void insert(T data) {

        int height = randomHeight();
        if (height > maxHeight) {
            maxHeight = height;
            header->next.resize(maxHeight, nullptr);
        }

        Node<T>* update[maxHeight];
        Node<T>* x = header;
        for (int i = maxHeight - 1; i >= 0; i--) {
            while (x->next[i] && x->next[i]->value < data)
                x = x->next[i];
            update[i] = x;
        }

        if (x->next[0] && x->next[0]->value == data)
            return;

        auto* newNode = new Node<T>(data);
        newNode->next.resize(height, nullptr);
        for (int i = 0; i < height; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }

        std::cout << "Inserted " << data << " at height " << height << std::endl;
        for (int i = 0; i < height; i++) {
            std::cout << "Node " << update[i]->value << " points to " << update[i]->next[i]->value << std::endl;
        }
    }

    void print() {
        Node<T>* x = header->next[0];
        while (x!= nullptr) {
            std::cout << x->value << " ";
            x = x->next[0];
        }
        std::cout << std::endl;
    }
};

#endif //ICS2210_SKIPLIST_H
