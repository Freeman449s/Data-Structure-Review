//
// Created by Freeman on 2021/9/22.
//

#ifndef DATA_STRUCTURE_REVIEW_UNION_FIND_SET_HPP
#define DATA_STRUCTURE_REVIEW_UNION_FIND_SET_HPP

#include "../Exceptions.hpp"

class UnionFindSet {
private:
    int *array = nullptr;
    int nElem = 0;

public:
    explicit UnionFindSet(int nElem) {
        if (nElem <= 0) throw IllegalArgumentException();
        this->nElem = nElem;
        array = new int[nElem];
        for (int i = 0; i < nElem; i++) array[i] = -1;
    }

    /**
     * 查找x元素所属的集合的根。
     * @param x
     * @return x元素所属的集合的根。
     */
    int Find(int x);

    /**
     * 合并a和b元素所属的集合。
     * @param a
     * @param b
     * @return 合并后集合的根。
     */
    int Union(int a, int b);

    ~UnionFindSet() {
        delete[] array;
    }
};


#endif //DATA_STRUCTURE_REVIEW_UNION_FIND_SET_HPP
