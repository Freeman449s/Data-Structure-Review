//
// Created by Freeman on 2021/6/17.
//

#ifndef DATA_STRUCTURE_REVIEW_LINKED_STACK_HPP
#define DATA_STRUCTURE_REVIEW_LINKED_STACK_HPP

#include "../Exceptions.hpp"

template<typename T>
class LinkedStack;

template<typename T>
class LStackNode {
    friend class LinkedStack<T>;

private:
    T data;
    LStackNode *next = nullptr;
};

template<typename T>
class LinkedStack {
private:
    LStackNode<T> *top;

public:
    LinkedStack() {
        top = new LStackNode<T>();
    }

    bool empty() {
        return top->next == nullptr;
    }

    T peek() {
        if (empty()) throw EmptyStackException();
        return top->data;
    }

    T pop() {
        if (empty()) throw EmptyStackException();
        T ret = top->data;
        LStackNode<T> *tmp = top;
        top = top->next;
        delete tmp;
        return ret;
    }

    void push(T data) {
        auto *newNode = new LStackNode<T>();
        newNode->data = data;
        newNode->next = top;
        top = newNode;
    }
};

#endif //DATA_STRUCTURE_REVIEW_LINKED_STACK_HPP
