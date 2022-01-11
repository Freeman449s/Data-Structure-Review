//
// Created by Freeman on 2021/9/8.
//

#ifndef DATA_STRUCTURE_REVIEW_TB_TREE_HPP
#define DATA_STRUCTURE_REVIEW_TB_TREE_HPP

namespace Chapter6 {
    enum PointerType {
        pointer, thread
    };
}

/**
 * 线索二叉树
 */
class TBTree {
public:
    int data;
    TBTree *lChild, *rChild;
    Chapter6::PointerType lTag, rTag;
};

/**
 * 为二叉树建立中序线索
 * @param root 二叉树根
 */
void buildInThread(TBTree *root);

/**
 * 建立中序线索时递归调用的函数
 * @param node 当前结点
 * @param pre 前驱结点
 */
void buildInThreadRecur(TBTree *node, TBTree *&pre);

/**
 * 求中序遍历下的第一个结点。二叉树必须已建立中序线索。
 * @param root 线索二叉树根
 * @return 中序遍历下的第一个结点
 */
TBTree *inOrderFirst(TBTree *root);

/**
 * 求中序遍历下的最后一个结点。二叉树必须已建立中序线索。
 * @param root 线索二叉树根
 * @return 中序遍历下的最后一个结点
 */
TBTree *inOrderLast(TBTree *root);

/**
 * 求中序遍历的下一个结点。二叉树必须已建立中序线索。
 * @param node 当前结点
 * @return 中序遍历的下一个结点
 */
TBTree *inOrderNext(TBTree *node);

/**
 * 求中序遍历的前一个结点。二叉树必须已建立中序线索。
 * @param node 当前结点
 * @return 中序遍历的前一个结点
 */
TBTree *inOrderPrior(TBTree *node);

/**
 * 中序遍历线索二叉树。二叉树必须已建立中序线索。
 * @param root 线索二叉树根
 */
void inOrder(TBTree *root);

/**
 * 建立前序线索时递归调用的函数
 * @param node 当前结点
 * @param pre 前驱结点
 */
void buildPreThreadRecur(TBTree *node, TBTree *&pre);

/**
 * 前序遍历线索二叉树。二叉树必须已建立前序线索。
 * @param root 线索二叉树根
 */
void preOrder(TBTree *root);

/**
 * 建立后序线索时递归调用的函数
 * @param node 当前结点
 * @param pre 前驱结点
 */
void buildPostThreadRecur(TBTree *node, TBTree *&pre);

void visit(TBTree *root);

#endif //DATA_STRUCTURE_REVIEW_TB_TREE_HPP
