#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <cmath>
#include <vector>
#include "Exceptions.hpp"

class Util {
public:
    static void swap(int *a, int *b) {
        int tmp = *b;
        *b = *a;
        *a = tmp;
    }

    /**
     * 找出数组中最小元素对应的下标。
     * @param array
     * @param len
     * @return
     */
    static int min_index(const double array[], int len) {
        if (len <= 0) throw IllegalArgumentException();
        if (len == 1) return 0;

        double min = array[0];
        int min_index = 0;
        for (int i = 1; i < len; i++) {
            if (array[i] < min) {
                min = array[i];
                min_index = i;
            }
        }
        return min_index;
    }

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

    /**
     * 检查向量内的元素是否已经有序。
     */
    template<class T>
    static bool isInOrder(const std::vector<T> &v, bool ascending = true) {
        if (ascending) {
            for (int i = 0; i <= v.size() - 2; i++) {
                if (v[i] > v[i + 1]) return false;
            }
            return true;
        }
        else {
            for (int i = 0; i <= v.size() - 2; i++) {
                if (v[i] < v[i + 1]) return false;
            }
            return true;
        }
    }

    /**
     * 将一个向量中的两段合并为递增有序的一段。
     * @param v 待操作向量。
     * @param left 第一段的左端点（包含）。
     * @param mid 两端的分隔点，第一段范围为[left,mid-1]，第二段范围为[mid,right-1]。
     * @param right 第二段的右端点（不包含）。
     */
    template<class T>
    static void merge(std::vector<T> &v, int left, int mid, int right) {
        int lIndex = left, rIndex = mid, tmpIndex = 0;
        std::vector<T> tmpVec(right - left);
        while (lIndex <= mid - 1 && rIndex <= right - 1) {
            if (v[lIndex] < v[rIndex]) { tmpVec[tmpIndex++] = v[lIndex++]; }
            else { tmpVec[tmpIndex++] = v[rIndex++]; }
        }
        while (lIndex <= mid - 1) {
            tmpVec[tmpIndex++] = v[lIndex++];
        }
        while (rIndex <= right - 1) {
            tmpVec[tmpIndex++] = v[rIndex++];
        }
        for (int i = 0; i <= right - left - 1; i++) {
            v[i + left] = tmpVec[i];
        }
    }

    /**
     * 获取无符号整型u第i位上的数字。
     */
    static int getDigit(unsigned u, int i) {
        if (i < 1 || i > 10) throw IllegalArgumentException();
        int divisor = (int) pow(10, i - 1);
        if (i == 10) return u / divisor;
        else return u / divisor - u / divisor / 10 * 10;
    }
};

#endif // !__UTIL_HPP__