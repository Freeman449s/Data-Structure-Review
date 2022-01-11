#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

#include <cstdint>
#include "List.hpp"
#include "../Exceptions.hpp"

template<typename T>
class ArrayList : public List<T> {
private:
    int capacity;
    int curSize;
    T* internalArray;

public:
    ArrayList();

    ArrayList(const ArrayList<T> &list);

    /**
     * 移动构造函数
     */
    ArrayList(ArrayList<T> &&list) noexcept;

    T operator[](int index);

    /**
     * 重写List的add方法。
     * 永远返回true。
     * @param elem 待插入元素
     * @return true
     */
    virtual bool add(T elem);

    /**
     * 重写List的clear方法。
     * 清空线性表后，容量恢复到默认值（10）。
     */
    virtual void clear();

    virtual bool contains(T elem);

    virtual T get(int index);

    /**
     * 重写List的indexOf方法，返回线性表中与elem相等的第一个元素的下标。
     * @param elem 待查找元素
     * @return 线性表中与elem相等的第一个元素的下标。如果未找到，返回-1
     */
    virtual int indexOf(T elem);

    virtual void insert(int index, T elem);

    virtual bool isEmpty();

    /**
     * 重写List的lastIndexOf方法，返回线性表中与elem相等的最后一个元素的下标。
     * @param elem 待查找元素
     * @return 线性表中与elem相等的最后一个元素的下标。如果未找到，返回-1
     */
    virtual int lastIndexOf(T elem);

    virtual T remove(int index);

    /**
     * 移除fromIndex至toIndex（不包含）之间的元素。
     * @param fromIndex 起始位置（包含）
     * @param toIndex 终止位置（不包含）
     */
    void removeRange(int fromIndex, int toIndex);

    virtual T set(int index, T elem);

    virtual int size() const;

    /**
     * 将数组中的元素按照升序或者降序排序。
     * 时间所限，目前使用插入排序。
     * @param ascending 是否按照升序排序
     */
    virtual void sort(bool ascending);

    ArrayList<T> subList(int fromIndex, int toIndex);

    ~ArrayList();

private:
    void ensureCapacity(int minCapacity);

    void expand();

    /**
     * 检查传入索引是否越界。
     * @param index 待检查索引
     * @return true，如果传入索引越界
     */
    bool checkIndex(int index);
};

template<typename T>
ArrayList<T>::ArrayList() {
    capacity = 10;
    curSize = 0;
    internalArray = new T[10];
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &list) {
    capacity = list.capacity;
    curSize = list.curSize;
    internalArray = new T[capacity];
    for (int i = 0; i <= curSize - 1; i++) {
        internalArray[i] = T(list.internalArray[i]);
    }
}

template<typename T>
ArrayList<T>::ArrayList(ArrayList<T> &&list) noexcept {
    capacity = list.capacity;
    curSize = list.curSize;
    internalArray = list.internalArray;
    list.internalArray = nullptr;
}

template<typename T>
T ArrayList<T>::operator[](int index) {
    return internalArray[index];
}

template<typename T>
bool ArrayList<T>::add(T elem) {
    if (curSize >= capacity) expand();
    internalArray[curSize] = elem;
    curSize++;
    return true;
}

template<typename T>
void ArrayList<T>::clear() {
    delete[] internalArray;
    internalArray = new T[10];
    capacity = 10;
    curSize = 0;
}

template<typename T>
bool ArrayList<T>::contains(T elem) {
    for (int i = 0; i < curSize; i++) {
        if (internalArray[i] == elem) return true;
    }
    return false;
}

template<typename T>
T ArrayList<T>::get(int index) {
    if (!checkIndex(index)) throw IndexOutOfRangeException();
    return internalArray[index];
}

template<typename T>
int ArrayList<T>::indexOf(T elem) {
    for (int i = 0; i < curSize; i++) {
        if (internalArray[i] == elem) return i;
    }
    return -1;
}

template<typename T>
bool ArrayList<T>::isEmpty() {
    return curSize <= 0;
}

template<typename T>
int ArrayList<T>::lastIndexOf(T elem) {
    for (int i = curSize - 1; i >= 0; i--) {
        if (internalArray[i] == elem) return i;
    }
    return -1;
}

template<typename T>
void ArrayList<T>::insert(int index, T elem) {
    if (index < 0 || index > curSize) return;
    if (curSize >= capacity) {
        expand();
    }
    for (int i = curSize - 1; i >= index; i--) {
        internalArray[i + 1] = internalArray[i];
    }
    internalArray[index] = elem;
    curSize++;
}

template<typename T>
T ArrayList<T>::remove(int index) {
    if (!checkIndex(index)) throw IndexOutOfRangeException();
    T ret = internalArray[index];
    for (int i = index; i <= curSize - 2; i++) {
        internalArray[i] = internalArray[i + 1];
    }
    curSize--;
    return ret;
}

template<typename T>
void ArrayList<T>::removeRange(int fromIndex, int toIndex) {
    if (toIndex <= fromIndex) throw IllegalArgumentException();
    if (fromIndex < 0 || toIndex > curSize) throw IndexOutOfRangeException();
    int removeCount = toIndex - fromIndex;
    for (int count = 1; count <= removeCount; count++) {
        remove(fromIndex);
    }
}

template<typename T>
T ArrayList<T>::set(int index, T elem) {
    if (!checkIndex(index)) throw IndexOutOfRangeException();
    internalArray[index] = elem;
}

template<typename T>
int ArrayList<T>::size() const {
    return curSize;
}

template<typename T>
void ArrayList<T>::sort(bool ascending) {
    for (int i = 1; i <= curSize - 1; i++) {
        T x = internalArray[i];
        int j;
        for (j = i - 1; j >= 0; j--) {
            if (ascending) {
                if (internalArray[j] > x) {
                    internalArray[j + 1] = internalArray[j];
                }
                else break;
            }
            else {
                if (internalArray[j] < x) {
                    internalArray[j + 1] = internalArray[j];
                }
                else break;
            }
        }
        internalArray[j + 1] = x;
    }
}

template<typename T>
ArrayList<T> ArrayList<T>::subList(int fromIndex, int toIndex) {
    if (fromIndex < 0 || toIndex > curSize) throw IndexOutOfRangeException();
    if (toIndex < fromIndex) throw IllegalArgumentException();

    ArrayList<T> ret = ArrayList<T>();
    for (int i = fromIndex; i < toIndex; i++) ret.add(internalArray[i]);
    return ret;
}

template<typename T>
ArrayList<T>::~ArrayList<T>() {
    delete[] internalArray;
}

template<typename T>
void ArrayList<T>::ensureCapacity(int minCapacity) {
    if (minCapacity <= capacity) return;
    if (capacity * 2 < 0 || capacity * 2 < minCapacity) capacity = minCapacity;
    T* originalArray = internalArray;
    internalArray = new T[capacity];
    for (int i = 0; i < curSize; i++) {
        internalArray[i] = originalArray[i];
    }
    delete[] originalArray;
}

template<typename T>
void ArrayList<T>::expand() {
    if (capacity > INT32_MAX / 2) {
        if (capacity < INT32_MAX) capacity = INT32_MAX;
        else throw OutOfMemoryError(); // capacity == INT32_MAX
    }
    else capacity *= 2;
    T* originalArray = internalArray;
    internalArray = new T[capacity];
    for (int i = 0; i < curSize; i++) {
        internalArray[i] = originalArray[i];
    }
    delete[] originalArray;
}

template<typename T>
bool ArrayList<T>::checkIndex(int index) {
    if (index < 0 || index >= curSize) return false;
    else return true;
}

#endif