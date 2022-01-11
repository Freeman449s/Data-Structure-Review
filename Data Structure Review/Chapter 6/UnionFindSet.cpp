//
// Created by Freeman on 2021/9/22.
//

#include "UnionFindSet.hpp"

int UnionFindSet::Find(int x) {
    if (x >= nElem || x < 0) return -1;

    if (array[x] < 0) return x;
    else {
        array[x] = Find(array[x]); // 路径压缩：令x直接指向根结点
        return array[x];
    }
}

int UnionFindSet::Union(int a, int b) {
    if (a < 0 || a >= nElem || b < 0 || b >= nElem) return -1;

    int aRoot = Find(a), bRoot = Find(b);
    if (aRoot == bRoot) return aRoot;
    int newRoot;
    if (array[aRoot] > array[bRoot]) { // 将较小的树合并到较大的树中
        array[bRoot] += array[aRoot];
        array[aRoot] = bRoot;
        newRoot = bRoot;
    }
    else {
        array[aRoot] += array[bRoot];
        array[bRoot] = aRoot;
        newRoot = aRoot;
    }
    return newRoot;
}