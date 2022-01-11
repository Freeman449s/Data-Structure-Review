//
// Created by Freeman on 2021/6/16.
//

#ifndef DATA_STRUCTURE_REVIEW_MASTER_ELEM_HPP
#define DATA_STRUCTURE_REVIEW_MASTER_ELEM_HPP

#include <vector>

namespace Chapter2 {
    /**
     * 问题：长度为n的整型数组中，所有元素的取值范围是[0,n-1]。如果一个元素的出现次数大于n/2，则称该元素为数组的主元素。
     * 设计一个尽可能高效的算法，找出数组的主元素。
     */
    class MasterElem {
        /**
         * 思想：新建一个数组count[]，数组各个元素初值为0. 遍历原数组（向量）v，v[i]是什么值，就在count对应下标处加1.
         * 再遍历一遍数组count[]，记录最大元素的下标。判断此元素是否大于n/2，若大于n/2，则返回下标；否则返回-1。
         * @param v 输入向量，每个元素的取值范围是[0,size()-1]
         * @return 主元素。如果不存在主元素，返回-1.
         */
        static int algorithm1(std::vector<int> &v) {
            int n = v.size();
            int *count = new int[n];
            for (int i = 0; i < n; i++) {
                count[i] = 0;
            }
            for (int i = 0; i < n; i++) {
                count[v[i]]++;
            }
            int maxIndex = 0, maxCount = count[0];
            for (int i = 1; i < n; i++) {
                if (count[i] > maxCount) {
                    maxCount = count[i];
                    maxIndex = i;
                }
            }
            if (maxCount > n / 2) return maxIndex;
            else return -1;
        }
    };
}

#endif //DATA_STRUCTURE_REVIEW_MASTER_ELEM_HPP
