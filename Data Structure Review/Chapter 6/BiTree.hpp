//
// Created by Freeman on 2021/9/7.
//

#ifndef DATA_STRUCTURE_REVIEW_BI_TREE_HPP
#define DATA_STRUCTURE_REVIEW_BI_TREE_HPP

/**
 * 二叉树结点
 */
class BTNode {
public:
    int data;
    BTNode *lChild = nullptr;
    BTNode *rChild = nullptr;

public:
    explicit BTNode(int data) {
        this->data = data;
    }
};

/**
 * 非递归先序遍历
 * @param root 二叉树根
 */
void preOrderNoneRecur(BTNode *root);

/**
 * 非递归中序遍历
 * @param root 二叉树根
 */
void inOrderNoneRecur(BTNode *root);

/**
 * 非递归后序遍历（使用双栈）
 * @param root 二叉树根
 */
void postOrderNoneRecur_doubleStack(BTNode *root);

/**
 * 非递归后序遍历（使用单栈）
 * @param root 二叉树根
 */
void postOrderNoneRecur_singleStack(BTNode *root);

/**
 * 层序遍历
 * @param root 二叉树根
 */
void levelOrder(BTNode *root);

void visit(BTNode *node);

/**
 * 建立一棵用作测试样例的二叉树
 * @return 二叉树根
 */
BTNode* buildSampleBiTree();

#endif //DATA_STRUCTURE_REVIEW_BI_TREE_HPP
