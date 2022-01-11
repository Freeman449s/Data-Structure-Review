//
// Created by Freeman on 2021/8/29.
//

#ifndef DATA_STRUCTURE_REVIEW_ORTHO_LIST_HPP
#define DATA_STRUCTURE_REVIEW_ORTHO_LIST_HPP

#ifndef OLIST_MAX_SIZE
#define OLIST_MAX_SIZE 10
#endif

namespace Chapter5 {
    template<typename T>
    class OLNode {
        template<typename E> friend
        class OrthoList;

    private:
        int row = 0, col = 0;
        T val;
        OLNode *right = nullptr, *down = nullptr;

    public:
        OLNode() {
            this->val = T();
        }

        explicit OLNode(T val) {
            this->val = val;
        }

        OLNode(int row, int col) : OLNode() {
            this->row = row;
            this->col = col;
        }

        OLNode(int row, int col, T val) : OLNode(val) {
            this->row = row;
            this->col = col;
        }
    };

    /**
     * 从给定稀疏矩阵建立十字链表，实现压缩存储
     * 代码正确性已经经过验证
     */
    template<typename T>
    class OrthoList {
    private:
        OLNode<T> *cHeadArr, *rHeadArr; // 各列头结点和各行头结点组成的数组
        int nCol, nRow;
        int nNoneConst = 0; // 不为常量c的元素的个数

    public:
        OrthoList(T mat[][OLIST_MAX_SIZE], int nRow, int nCol, T c) {
            // 初始化十字链表
            this->nCol = nCol;
            this->nRow = nRow;
            cHeadArr = new OLNode<T>[nCol];
            rHeadArr = new OLNode<T>[nRow];
            for (int i = 0; i <= nCol - 1; i++) {
                cHeadArr[i].row = -1;
                cHeadArr[i].col = i;
            }
            for (int i = 0; i <= nRow - 1; i++) {
                rHeadArr[i].row = i;
                rHeadArr[i].col = -1;
            }

            // 填入元素
            for (int i = 0; i <= nRow - 1; i++) {
                OLNode<T> *RLHead = &rHeadArr[i];
                OLNode<T> *RLTail = RLHead;
                for (int j = 0; j <= nCol - 1; j++) {
                    if (mat[i][j] != c) {
                        nNoneConst += 1;
                        OLNode<T> *CLHead = &cHeadArr[j];
                        OLNode<T> *CLTail = findCLTail(CLHead);
                        auto *node = new OLNode<T>(i, j, mat[i][j]);
                        CLTail->down = node;
                        RLTail->right = node;
                        RLTail = RLTail->right;
                    }
                }
            }
        }

        void print() {
            for (int i = 0; i <= nRow - 1; i++) {
                OLNode<T> *p = rHeadArr[i].right;
                if (p == nullptr) std::cout << "Row Empty";
                while (p != nullptr) {
                    std::cout << p->val << '\t';
                    p = p->right;
                }
                std::cout << std::endl;
            }
        }

    private:
        /**
         * 找到列链表的尾结点
         */
        OLNode<T> *findCLTail(OLNode<T> *head) {
            OLNode<T> *p = head;
            while (p->down != nullptr) p = p->down;
            return p;
        }

        /**
         * 找到行链表的尾结点
         */
        OLNode<T> *findRLTail(OLNode<T> *head) {
            OLNode<T> *p = head;
            while (p->right != nullptr) p = p->down;
            return p;
        }
    };
}

#endif //DATA_STRUCTURE_REVIEW_ORTHO_LIST_HPP
