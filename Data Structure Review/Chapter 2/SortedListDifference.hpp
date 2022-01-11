//
// Created by Freeman on 2021/6/8.
//

#ifndef DATA_STRUCTURE_REVIEW_SORTED_LIST_DIFFERENCE_HPP
#define DATA_STRUCTURE_REVIEW_SORTED_LIST_DIFFERENCE_HPP

#include "MergeSortedList.hpp"

namespace Chapter2 {
    /**
     * 问题：已知递增单链表A和B。求出集合A和B的差集A-B，将结果保存在单链表A中，并保持元素的有序性。
     * 解决方法：用两个指针p和q遍历listA和listB，何者指向的元素较小，何者后移。发现相同的元素，则删除p指向的结点。
     * p和q任何一者完成遍历后返回。
     */
    class Difference {
    public:
        /**
         * 移除listA中在listB里面出现过的元素。
         * @param listA 有序链表A
         * @param listB 有序链表B
         * @return 移除目标元素后的有序链表。实际上是将修改过的listA直接返回。
         */
        static SortedList *execute(SortedList *listA, SortedList *listB) {
            SortedList *p = listA;
            SortedList *q = listB;
            SortedList *prior = listA; // 追踪p节点的前一个节点
            while (p != nullptr && q != nullptr) {
                if (p->data < q->data) {
                    p = p->next;
                    prior = prior->next;
                }
                else if (q->data < p->data) q = q->next;
                else { // p->data == q->data
                    SortedList *tmp = p;
                    prior->next = p->next;
                    p = p->next;
                    delete tmp;
                }
            }
            return listA;
        }
    };
}

#endif //DATA_STRUCTURE_REVIEW_SORTED_LIST_DIFFERENCE_HPP
