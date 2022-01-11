//
// Created by Freeman on 2021/9/27.
//

#ifndef DATA_STRUCTURE_REVIEW_SORT_HPP
#define DATA_STRUCTURE_REVIEW_SORT_HPP

#include <cmath>
#include <vector>
#include "MaxHeap.hpp"
#include "../Util.hpp"

class Sort;

/**
 * 基数排序结点类
 */
class RadixNode {
    friend class Sort;

private:
    unsigned data;
    RadixNode *next = nullptr;

public:
    explicit RadixNode(unsigned data) {
        this->data = data;
    }

    RadixNode() : RadixNode(0) {}
};

class Sort {
public:
    template<class T>
    static void insertionSort(std::vector<T> &v) {
        int i, j;
        for (i = 1; i < v.size(); i++) {
            T tmp = v[i];
            for (j = i - 1; j >= 0; j--) {
                if (v[j] > tmp) v[j + 1] = v[j];
                else break;
            }
            v[j + 1] = tmp;
        }
    }

    template<class T>
    static void binaryInsertionSort(std::vector<T> &v) {
        int i, j;
        for (i = 1; i < v.size(); i++) {
            T tmp = v[i];
            int low = 0, high = i - 1;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (v[mid] < tmp)low = mid + 1;
                else high = mid - 1;
            }
            for (j = i - 1; j >= low; j--) v[j + 1] = v[j]; // 大于tmp的元素后移
            v[low] = tmp;
        }
    }

    template<class T>
    static void shellSort(std::vector<T> &v) {
        // 根据帕佩尔诺夫和斯塔舍维奇提出的方法，选定最大的增量
        int time = 0; // 次数
        while (pow(2, time) + 1 < v.size()) time++;
        time -= 1;

        // 希尔排序核心算法
        while (time >= 0) {
            int delta = (int) pow(2, time) + 1;
            int i, j;
            for (i = delta; i < v.size(); i++) { // 将元素分成若干组，然后组内进行插入排序，事实上也需要逐个将向量内元素作为待插入对象
                T tmp = v[i];
                for (j = i - delta; j >= 0; j -= delta) {
                    if (v[j] > tmp) v[j + delta] = v[j];
                    else break;
                }
                v[j + delta] = tmp;
            }
            time--;
        }
        insertionSort(v); // 最后进行一次插入排序
    }

    template<class T>
    static void bubbleSort(std::vector<T> &v) {
        for (int i = v.size() - 2; i >= 0; i--) {
            bool flag = false; // 标记本轮是否发生位置交换
            for (int j = 0; j <= i; j++) {
                if (v[j] > v[j + 1]) {
                    T tmp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = tmp;
                    flag = true;
                }
            }
            if (!flag) return; // 本轮未发生交换，可提前结束
        }
    }

    template<class T>
    static void quickSort(std::vector<T> &v) {
        quickSortRecur(v, 0, v.size());
    }

    template<class T>
    static void selectionSort(std::vector<T> &v) {
        for (int i = 0; i <= v.size() - 2; i++) {
            int min_index = i;
            for (int j = i + 1; j <= v.size() - 1; j++) {
                if (v[j] < v[min_index]) min_index = j;
            }
            T tmp = v[i];
            v[i] = v[min_index];
            v[min_index] = tmp;
        }
    }

    template<class T>
    static void heapSort(std::vector<T> &v) {
        MaxHeap<T>::adjust(v);
        for (int i = 1; i <= v.size() - 1; i++) { // 每次选出最大的元素，重复N-1次
            // 堆顶元素移动到后端，后端元素提前
            T tmp = v[v.size() - i];
            v[v.size() - i] = v[0];
            v[0] = tmp;
            MaxHeap<T>::percolate_down(v, 0, v.size() - i - 1); // 下滤调整
        }
    }

    template<class T>
    static void mergeSort(std::vector<T> &v) {
        mergeSortRecur(v, 0, v.size());
    }

    static void radixSort(std::vector<unsigned> &v) {
        /**
         * 针对不同的关键字，基数排序有不同的写法，此处仅实现无符号整数的排序。
         */

        // 第一步：初始向量转为链
        RadixNode *head = new RadixNode();
        RadixNode *p = head;
        for (unsigned elem:v) {
            p->next = new RadixNode(elem);
            p = p->next;
        }

        // 第二步：从低位向高位开始分配-收集
        int nKeys = getNKeys(v);
        RadixNode *bucketHeads[10];
        RadixNode *bucketTails[10];
        for (int i = 0; i <= 9; i++) {
            bucketHeads[i] = new RadixNode();
            bucketTails[i] = bucketHeads[i];
        }
        for (int round = 1; round <= nKeys; round++) {
            // 恢复桶到初态
            for (int i = 0; i <= 9; i++) {
                bucketHeads[i]->next = nullptr;
                bucketTails[i] = bucketHeads[i];
            }
            // 各元素分配到桶
            p = head->next;
            while (p) {
                int digit = Util::getDigit(p->data, round);
                bucketTails[digit]->next = p;
                bucketTails[digit] = bucketTails[digit]->next;
                p = p->next;
            }
            // 各桶串起
            p = head;
            for (int bucketNO = 0; bucketNO <= 9; bucketNO++) {
                if (bucketHeads[bucketNO]->next) {
                    p->next = bucketHeads[bucketNO]->next;
                    p = bucketTails[bucketNO];
                }
            }
            p->next = nullptr;
        }

        // 第三步：排序后的序列复制回原向量
        RadixNode *tmp;
        p = head->next;
        delete head;
        int i = 0;
        while (p) {
            v[i++] = p->data;
            tmp = p;
            p = p->next;
            delete tmp;
        }
        for (i = 0; i <= 9; i++) delete bucketHeads[i];
    }

    /**
     * 生成1~10逆序排列的向量，作为排序算法的测试用例。
     * @return 1~10逆序排列的向量。
     */
    static std::vector<int> generateTestCase();

    /**
     * 生成1~100逆序排列的向量，作为排序算法的测试用例。这里的1~100为无符号整型。
     * @return 1~100逆序排列的向量。
     */
    static std::vector<unsigned> generateTestCase2();

private:
    /**
     * 递归进行快速排序。
     * @tparam T 待排序的关键字的类型。
     * @param v 待排序向量。
     * @param left 排序范围的左边界（包含）。
     * @param right 排序范围的右边界（不包含）。
     */
    template<class T>
    static void quickSortRecur(std::vector<T> &v, int left, int right) {
        if (left < right) {
            int i = left, j = right - 1;
            T pivot = v[left];
            while (i < j) {
                while (i < j && v[j] > pivot) j--;
                if (i < j) v[i] = v[j];
                while (i < j && v[i] <= pivot) i++;
                if (i < j) v[j] = v[i];
            }
            v[i] = pivot;
            quickSortRecur(v, left, i);
            quickSortRecur(v, i + 1, right);
        }
    }

    /**
     * 递归进行归并排序。
     * @param v 待排序向量。
     * @param left 排序范围的左边界（包含）。
     * @param right 排序范围的右边界（不包含）。
     */
    template<class T>
    static void mergeSortRecur(std::vector<T> &v, int left, int right) {
        if (left + 1 < right) { // 至少含有两个元素
            int mid = (left + right) / 2;
            mergeSortRecur(v, left, mid);
            mergeSortRecur(v, mid, right);
            Util::merge(v, left, mid, right);
        }
    }

    /**
     * 统计基数排序涉及的关键字个数（即向量v所含无符号整数的最大位数）。
     * @param v 待处理向量。
     * @return 基数排序涉及的关键字个数。
     */
    static int getNKeys(const std::vector<unsigned> &v) {
        unsigned max = 0;
        for (unsigned elem:v) {
            if (elem > max) max = elem;
        }
        return getNDigits(max);
    }

    /**
     * 统计一个无符号整数有几位数。
     */
    static int getNDigits(unsigned u) {
        if (u == 0) return 1;
        int divisor = 1;
        for (int nDigits = 1; nDigits <= 9; nDigits++, divisor *= 10) { // unsigned最大为10位数
            if (u / divisor != 0 && u / divisor / 10 == 0) return nDigits;
        }
        return 10;
    }
};

#endif //DATA_STRUCTURE_REVIEW_SORT_HPP
