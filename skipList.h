#ifndef ICS2210_SKIPLIST_H
#define ICS2210_SKIPLIST_H

#include <vector>
#include <cstdlib>
#include <algorithm>
#include "node.h"

template <typename T>
class SkipList {
public:
    Node<T>* _header;

    SkipList() : _height(1), _header(new Node<int>(INT_MIN)) {
        _header->next.resize(_height, nullptr);
    }

    ~SkipList() {
        while (!isEmpty()) {
            remove(findMin());
        }

        delete _header;
    }

    void insert(const T& key) {
        Node<T>** update = _header->next.data();
        Node<T>* node = nullptr;

        for (int i = _height - 1; i >= 0; i--) {
            while (update[i] != nullptr && update[i]->value > key) {
                update[i] = update[i]->next[i];
            }

            if (update[i] != nullptr && update[i]->value == key) {
                node = update[i];
                break;
            }
        }

        if (node == nullptr) {
            node = new Node<T>(key);

            for (int i = 0; i < _height; i++) {
                node->next[i] = update[i]->next[i];
                update[i]->next[i] = node;
            }

            while (_height < randomHeight()) {
                _height++;
                auto* newNode = new Node<T>(INT_MIN);
                newNode->next.resize(_height, nullptr);
                _header->next.push_back(newNode);
            }
        }
    }


    void print() const {
        Node<int>* node = _header->next[0];

        while (node != nullptr) {
            cout << node->value << " ";
            node = node->next[0];
        }

        cout << endl;
    }

private:
    int _height;

    bool isEmpty() const {
        return _header->next[0] == nullptr;
    }

    const T& findMin() const {
        if (isEmpty()) {
            throw std::runtime_error("List is empty");
        }
        Node<T>* node = _header->next[0];
        while (node->next[0] != nullptr) {
            node = node->next[0];
        }
        return node->value;
    }

    void remove(const T& key) {
        if (isEmpty()) {
            throw std::runtime_error("List is empty");
        }
        Node<T>** update = _header->next.data();
        Node<T>* nodeToRemove = nullptr;
        for (int i = _height - 1; i >= 0; --i) {
            while (update[i] != nullptr && update[i]->value > key) {
                update[i] = update[i]->next[i];
            }
            if (update[i] != nullptr && update[i]->value == key) {
                nodeToRemove = update[i];
                break;
            }
        }
        if (nodeToRemove == nullptr) {
            return;
        }
        for (int i = 0; i < _height; ++i) {
            if (update[i]->next[i] != nullptr && update[i]->next[i] != nodeToRemove) {
                update[i] = update[i]->next[i];
            }
        }
        delete nodeToRemove;
        while (_height > 1 && _header->next[_height - 1] == nullptr) {
            --_height;
        }
    }



    int randomHeight() {
        int height = 1;
        while (height < MAX_HEIGHT && (rand() & 0xFFFF) < (1 << 15)) {
            height++;
        }

        return height;
    }

    const int& findMax() const {
        Node<int>* node = _header->next[_height - 1];

        if (node == nullptr) {
            throw std::runtime_error("List is empty");
        }

        while (node->next[_height - 1] != nullptr) {
            node = node->next[_height - 1];
        }

        return node->value;
    }
};


template<> SkipList<int>::SkipList() : _height(1), _header(new Node<int>(INT_MIN)) {
    _header->next.resize(_height, nullptr);
}
//
//template <typename T>
//bool SkipList<T>::isEmpty() const {
//    return _header->next[0] == nullptr;
//}
//
//template <typename T>
//const T& SkipList<T>::findMin() const {
//    if (isEmpty()) {
//        throw std::runtime_error("List is empty");
//    }
//    Node<T>* node = _header->next[0];
//    while (node->next[0] != nullptr) {
//        node = node->next[0];
//    }
//    return node->value;
//}
//
//template <typename T>
//void SkipList<T>::remove(const T& key) {
//    if (isEmpty()) {
//        throw std::runtime_error("List is empty");
//    }
//    Node<T>** update = _header->next.data();
//    Node<T>* nodeToRemove = nullptr;
//    for (int i = _height - 1; i >= 0; --i) {
//        while (update[i] != nullptr && update[i]->value > key) {
//            update[i] = update[i]->next[i];
//        }
//        if (update[i] != nullptr && update[i]->value == key) {
//            nodeToRemove = update[i];
//            break;
//        }
//    }
//    if (nodeToRemove == nullptr) {
//        return;
//    }
//    for (int i = 0; i < _height; ++i) {
//        if (update[i]->next[i] != nullptr && update[i]->next[i] != nodeToRemove) {
//            update[i] = update[i]->next[i];
//        }
//    }
//    delete nodeToRemove;
//    while (_height > 1 && _header->next[_height - 1] == nullptr) {
//        --_height;
//    }
//}

template<> SkipList<int>::~SkipList() {
    while (!isEmpty()) {
        remove(findMin());
    }

    delete _header;
}

template<> int SkipList<int>::randomHeight() {
    int height = 1;
    while (height < MAX_HEIGHT && (rand() & 0xFFFF) < (1 << 15)) {
        height++;
    }

    return height;
}
//
//template <typename T>
//void SkipList<T>::insert(const T& key) {
//    Node<T>** update = _header->next.data();
//    Node<T>* node = nullptr;
//
//    for (int i = _height - 1; i >= 0; i--) {
//        while (update[i] != nullptr && update[i]->value > key) {
//            update[i] = update[i]->next[i];
//        }
//
//        if (update[i] != nullptr && update[i]->value == key) {
//            node = update[i];
//            break;
//        }
//    }
//
//    if (node == nullptr) {
//        node = new Node<T>(key);
//
//        for (int i = 0; i < _height; i++) {
//            node->next[i] = update[i]->next[i];
//            update[i]->next[i] = node;
//        }
//
//        while (_height < randomHeight()) {
//            _height++;
//            auto* newNode = new Node<T>(INT_MIN);
//            newNode->next.resize(_height, nullptr);
//            _header->next.push_back(newNode);
//        }
//    }
//}
//
//template<> const int& SkipList<int>::findMax() const {
//    Node<int>* node = _header->next[_height - 1];
//
//    if (node == nullptr) {
//        throw std::runtime_error("List is empty");
//    }
//
//    while (node->next[_height - 1] != nullptr) {
//        node = node->next[_height - 1];
//    }
//
//    return node->value;
//}

template<> void SkipList<int>::print() const {
    Node<int>* node = _header->next[0];

    while (node != nullptr) {
        cout << node->value << " ";
        node = node->next[0];
    }

    cout << endl;
}

#endif //ICS2210_SKIPLIST_H
