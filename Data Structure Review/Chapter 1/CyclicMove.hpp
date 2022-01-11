#ifndef __CYCLIC_MOVE_HPP__
#define __CYCLIC_MOVE_HPP__

#include <iostream>
#include <vector>
#include "../Exceptions.hpp"

namespace Chapter1 {
    class CyclicMove {
        /// <summary>
        /// 循环移动向量中的元素
        /// </summary>
    public:
        /// <summary>
        /// 将向量中的一部分元素逆置
        /// </summary>
        /// <param name="v">待操作向量</param>
        /// <param name="left">左边界（包含）</param>
        /// <param name="right">右边界（不包含）</param>
        static void reverse(std::vector<int> &v, int left, int right) {
            if (left < 0 || right > v.size() || right <= left) throw IllegalArgumentException();
            for (int i = left, j = right - 1; i <= j; i++, j--) {
                int tmp = v[i];
                v[i] = v[j];
                v[j] = tmp;
            }
        }

        /// <summary>
        /// 解函数
        /// </summary>
        /// <param name="v">待操作向量</param>
        /// <param name="p">移动多少位</param>
        /// <param name="moveLeft">是否循环左移</param>
        /// <returns>元素循环移动后的向量</returns>
        static std::vector<int> execute(std::vector<int> v, int p, bool moveLeft) {
            if (v.empty() || p == 0) return v;
            if (p < 0) throw IllegalArgumentException();
            if (p >= v.size()) p = p % v.size();
            if (moveLeft) {
                // 先将整个向量逆置，然后逆置右侧p个元素和左侧n-p个元素
                reverse(v, 0, v.size());
                reverse(v, v.size() - p, v.size());
                reverse(v, 0, v.size() - p);
            }
            else {
                // 循环右移，上述操作的对称操作
                reverse(v, 0, v.size());
                reverse(v, 0, p);
                reverse(v, p, v.size());
            }
            return v;
        }
    };
}

#endif // !__CYCLIC_MOVE_HPP__