//
// Created by Freeman on 2021/8/7.
//

#ifndef DATA_STRUCTURE_REVIEW_CYCLIC_QUEUE_HPP
#define DATA_STRUCTURE_REVIEW_CYCLIC_QUEUE_HPP

#include "../Exceptions.hpp"

template<typename T>
class CyclicQueue {
private:
    int maxSize;
    T *internalArray;
    int front = 0, rear = 0;

public:
    explicit CyclicQueue(int maxSize) {
        this->maxSize = maxSize;
        internalArray = new T[maxSize];
    }

    bool add(T e) {
        if (isFull()) throw IllegalStateException();
        rear = (rear + 1) % maxSize;
        internalArray[rear] = e;
    }

    T poll() {
        if (isEmpty()) throw EmptyQueueException();
        front = (front + 1) % maxSize;
        return internalArray[front];
    }

    bool isEmpty() {
        return front == rear;
    }

private:
    bool isFull() {
        return (rear + 1) % maxSize == front;
    }
};


#endif //DATA_STRUCTURE_REVIEW_CYCLIC_QUEUE_HPP
