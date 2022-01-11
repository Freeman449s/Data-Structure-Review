//
// Created by Freeman on 2021/9/29.
//

#ifndef DATA_STRUCTURE_REVIEW_MAX_HEAP_HPP
#define DATA_STRUCTURE_REVIEW_MAX_HEAP_HPP

#include <vector>

template<class T>
class MaxHeap {
private:
    std::vector<T> tree;

public:
    void add(T elem) {
        tree.push_back(elem);
        percolate_up(tree, tree.size() - 1);
    }

    T remove(int index) {
        T ret = tree[index];
        tree[index] = tree[tree.size() - 1];
        tree.pop_back();
        percolate_down(tree, index);
        return ret;
    }

    T get(int index) {
        return tree[index];
    }

    /**
     * 将任意向量调整为最大二叉堆。
     * @param v 待调整向量。
     */
    static void adjust(std::vector<T> &v) {
        for (int i = v.size() / 2; i >= 0; i--) { // v.size()/2指向最后一个分支节点
            percolate_down(v, i);
        }
    }

    /**
     * 上滤操作。
     * @param tree 待调整二叉堆。
     * @param index 需要执行上滤操作的元素的下标。
     */
    template<class K>
    static void percolate_up(std::vector<K> &tree, int index) {
        K tmp = tree[index];
        int holeIndex = index, parentIndex = (holeIndex + 1) / 2;
        while (holeIndex > 0) {
            if (tree[parentIndex] < tmp) {
                tree[holeIndex] = tree[parentIndex];
                holeIndex = parentIndex;
                parentIndex = (holeIndex + 1) / 2;
            }
            else break;
        }
        tree[holeIndex] = tmp;
    }

    /**
     * 下滤操作。
     * @param tree 待调整二叉堆。
     * @param index 需要执行下滤操作的元素的下标。
     * @param bound 执行下滤操作的边界。超出边界的元素不会被下滤操作影响。
     */
    template<class K>
    static void percolate_down(std::vector<K> &tree, int index, int bound = -1) {
        K tmp = tree[index];
        int holeIndex = index, childIndex = holeIndex * 2 + 1;
        if (bound == -1) bound = tree.size() - 1;
        while (childIndex <= bound) {
            if (childIndex + 1 <= bound && tree[childIndex + 1] > tree[childIndex]) { // 选出较大的孩子
                childIndex += 1;
            }
            if (tree[childIndex] > tmp) {
                tree[holeIndex] = tree[childIndex];
                holeIndex = childIndex;
                childIndex = holeIndex * 2 + 1;
            }
            else break;
        }
        tree[holeIndex] = tmp;
    }
};


#endif //DATA_STRUCTURE_REVIEW_MAX_HEAP_HPP
