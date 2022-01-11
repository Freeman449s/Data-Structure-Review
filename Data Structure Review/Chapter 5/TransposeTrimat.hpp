//
// Created by Freeman on 2021/8/30.
//

#ifndef DATA_STRUCTURE_REVIEW_TRANSPOSE_TRIMAT_HPP
#define DATA_STRUCTURE_REVIEW_TRANSPOSE_TRIMAT_HPP

namespace Chapter5 {
    /**
     * 问题：给定稀疏矩阵A的三元组表示，要求求出其转置B的三元组表示。
     * 注意：构造三元组时，是按行优先构造的，应确保其转置B的构造也遵循行优先顺序。
     * 可以将A的三元组按照列指标排序，然后交换行指标和列指标，复杂度O(P^2)，其中P是三元组数组的规模。
     * 也可以让列指标从0开始增加，每一轮从A的三元组中找出列指标相同的元素，顺序存入B的三元组中，然后交换行指标和列指标，复杂度O(PN)，其中N是列数。
     * 下面实现算法2.
     */
    class TransposeTrimat {
    public:
        static void solve(int A[][3],int B[][3]);
    };
}


#endif //DATA_STRUCTURE_REVIEW_TRANSPOSE_TRIMAT_HPP
