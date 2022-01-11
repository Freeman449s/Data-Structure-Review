//
// Created by Freeman on 2021/6/15.
//

#ifndef DATA_STRUCTURE_REVIEW_BENCHMARK_DIVIDE_HPP
#define DATA_STRUCTURE_REVIEW_BENCHMARK_DIVIDE_HPP

#include <vector>

namespace Chapter2 {
    /**
     * 问题：设顺序表中的表头元素为e，将小于e的元素移至头部，大于e的元素移至尾部。
     */
    class BenchmarkDivide {
    public:
        /**
         * 算法1：使用两个指针i和j指向第二个元素和最后一个元素，同时相向运动，如果i发现大于e的元素，i停止移动；j发现小于e的元素，j停止移动。
         * 当i和j各自发现大于/小于e的元素时，交换两个元素。
         * i > j时循环停止。
         * 假定线性表中元素不重复。
         * 注意：不保证算法始终正确。
         */
        static void algorithm1(std::vector<int> &v) {
            int benchmark = v[0];
            int i = 1, j = v.size() - 1;
            while (i <= j) {
                if (v[i] > benchmark && v[j] < benchmark) {
                    swap(v, i, j);
                    i++;
                    j--;
                }
                if (v[i] < benchmark) i++;
                if (v[j] > benchmark) j--;
            }
            swap(v, 0, j);
        }

        /**
         * 算法2（标准算法）：保存benchmark，i和j指向线性表两端。j先向左移动直至遇到小于e的元素，覆盖i指向的位置，然后i开始向右移动。
         * i和j重复上述操作，直至i和j指向同一个位置，该位置是无效的。用benchmark覆盖此位置。
         */
        static void algorithm2(std::vector<int> &v) {
            int benchmark = v[0];
            int i = 0, j = v.size() - 1;
            while (i < j) {
                while (i < j && v[j] > benchmark) j--;
                if (i < j) {
                    v[i] = v[j];
                    i++;
                }
                while (i < j && v[i] < benchmark) i++;
                if (i < j) {
                    v[j] = v[i];
                    j--;
                }
            }
            v[i] = benchmark;
        }

    private:
        static void swap(std::vector<int> &v, int i, int j) {
            int tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
        }
    };
}

#endif //DATA_STRUCTURE_REVIEW_BENCHMARK_DIVIDE_HPP
