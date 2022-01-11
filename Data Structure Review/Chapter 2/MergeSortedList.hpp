//
// Created by Freeman on 2021/6/7.
//

#ifndef DATA_STRUCTURE_REVIEW_MERGE_SORTED_LIST_HPP
#define DATA_STRUCTURE_REVIEW_MERGE_SORTED_LIST_HPP

namespace Chapter2 {
    /// <summary>
    /// 有序链表类。默认升序。
    /// </summary>
    class SortedList {
    public:
        int data = 0;
        SortedList *next = nullptr;

    public:
        explicit SortedList(int data) {
            this->data = data;
        }
    };

    class MergeSortedList {
    public:
        /// <summary>
        /// 将传入的有序链表按升序合并。假设链表有（虚）头节点。
        /// 解决方法是遍历两个链表，每次将较小的一个元素接到新链表的尾部。
        /// 直接对原链表进行操作。调用此函数将破坏原先的链表结构。
        /// </summary>
        /// <param name="listA">有序链表A</param>
        /// <param name="listB">有序链表B</param>
        /// <returns>合并后的链表头</returns>
        static SortedList *ascendingMerge(SortedList *listA, SortedList *listB) {
            SortedList *p = listA->next;
            SortedList *q = listB->next;
            SortedList *head = listA;
            delete listB;
            SortedList *tail = head;
            while (p != nullptr && q != nullptr) {
                if (p->data <= q->data) {
                    tail->next = p;
                    p = p->next;
                    tail = tail->next;
                }
                else {
                    tail->next = q;
                    q = q->next;
                    tail = tail->next;
                }
            }
            if (p != nullptr) tail->next = p;
            else tail->next = q;
            return head;
        }

        /// <summary>
        /// 降序合并有序链表。假设链表有（虚）头节点。
        /// 解决方法是遍历两个链表，每次将较小的元素接到新链表的头部。
        /// 直接对原链表进行操作。调用此函数将破坏原先的链表结构。
        /// </summary>
        /// <param name="listA">有序链表A</param>
        /// <param name="listB">有序链表B</param>
        /// <returns>合并后的链表头</returns>
        static SortedList *descendingMerge(SortedList *listA, SortedList *listB) {
            SortedList *p = listA->next;
            SortedList *q = listB->next;
            SortedList *head = listA;
            delete listB;
            while (p != nullptr && q != nullptr) {
                if (p->data <= q->data) {
                    SortedList *tmp = p->next;
                    p->next = head->next; // “头部插入法”
                    head->next = p;
                    p = tmp;
                }
                else {
                    SortedList *tmp = q->next;
                    q->next = head->next;
                    head->next = q;
                    q = tmp;
                }
            }
            while (p != nullptr) {
                SortedList *tmp = p->next;
                p->next = head->next;
                head->next = p;
                p = tmp;
            }
            while (q != nullptr) {
                SortedList *tmp = q->next;
                q->next = head->next;
                head->next = q;
                q->next = tmp;
            }
            return head;
        }
    };
}

#endif //DATA_STRUCTURE_REVIEW_MERGE_SORTED_LIST_HPP
