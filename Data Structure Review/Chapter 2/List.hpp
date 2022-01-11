#ifndef __LIST_HPP__
#define __LIST_HPP__

template<typename T>
class List {
public:
    virtual bool add(T elem) = 0;

    virtual void clear() = 0;

    virtual bool contains(T elem) = 0;

    virtual T get(int index) = 0;

    virtual int indexOf(T elem) = 0;

    virtual void insert(int index, T elem) = 0;

    virtual bool isEmpty() = 0;

    virtual int lastIndexOf(T elem) = 0;

    virtual T remove(int index) = 0;

    virtual T set(int index, T elem) = 0;

    virtual int size() const = 0;

    virtual void sort(bool ascending) = 0;
};

#endif // !__LIST_HPP_