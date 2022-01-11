//
// Created by Freeman on 2021/6/15.
//

#ifndef DATA_STRUCTURE_REVIEW_LAST_BUT_K_HPP
#define DATA_STRUCTURE_REVIEW_LAST_BUT_K_HPP

#include <iostream>
#include "../LNode.hpp"

namespace Chapter2 {
    /**
     * 问题：输出链表中的倒数第K个结点。
     * 算法思想：用一个p指针遍历链表，用一个q指针指向p指针往前K个元素。这样，当p到达链表末尾时，q指向的就是倒数第K个元素。
     * 步骤阐述：开始时p和q都指向头结点，p先向后遍历，q不动。
     * 使用一个整型变量记录p已经移动了多少次。p移动K次后，q开始跟随p移动。
     * 当p到达链表末尾时，如果q仍然指向头结点，说明链表中的元素不足K个，应返回false。
     * 否则，q指向的元素就是倒数第K个元素。
     * 注：“倒数第K个”用英语表达实际上应该是"the last but K-1"。
     */
    class LastButK {
        static bool solve(LNode *head, int k) {
            LNode *p = head, *q = head;
            int count = 0;
            while (p != nullptr) {
                p = p->next;
                count++;
                if (count > k) q = q->next;
            }
            if (q == head) return false; // 链表中的元素不足k个
            std::cout << q->data << std::endl;
            return true;
        }
    };
}

#endif //DATA_STRUCTURE_REVIEW_LAST_BUT_K_HPP
