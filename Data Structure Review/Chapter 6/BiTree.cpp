//
// Created by Freeman on 2021/9/7.
//

#include <iostream>
#include "BiTree.hpp"

using namespace std;

#define MAX_SIZE 10000

void preOrderNoneRecur(BTNode *root) {
    if (!root) return;

    BTNode *stack[MAX_SIZE];
    int top = -1;

    stack[++top] = root;
    while (top >= 0) {
        BTNode *node = stack[top--];
        visit(node);
        if (node->rChild) stack[++top] = node->rChild; // 右孩子先入栈，后访问
        if (node->lChild) stack[++top] = node->lChild;
    }
}

void inOrderNoneRecur(BTNode *root) {
    BTNode *stack[MAX_SIZE];
    int top = -1;

    BTNode *node = root;
    while (top > -1 || node) { // 遍历过程中栈可能为空，需要双重条件
        while (node) { // 不断将左孩子入栈
            stack[++top] = node;
            node = node->lChild;
        }
        if (top > -1) {
            node = stack[top--];
            visit(node);
            node = node->rChild; // 入栈右孩子；当右孩子为空时，弹出该结点的双亲
        }
    }
}

void postOrderNoneRecur_doubleStack(BTNode *root) {
    if (!root) return;

    /**
     * 第1步：先进行先序遍历。
     * 将非递归先序遍历中左右孩子入栈的顺序调换，即变为左孩子先入栈，可以得到逆序的后序遍历序列。
     */
    BTNode *stack1[MAX_SIZE], *stack2[MAX_SIZE];
    int top1 = -1, top2 = -1;

    BTNode *node = root;
    stack1[++top1] = node;
    while (top1 > -1) {
        node = stack1[top1--];
        stack2[++top2] = node;
        if (node->lChild) {
            stack1[++top1] = node->lChild;
        }
        if (node->rChild) {
            stack1[++top1] = node->rChild;
        }
    }

    /**
     * 第2步：将栈2中的元素全部出栈即可。
     */
    while (top2 > -1) {
        node = stack2[top2--];
        visit(node);
    }
}

void postOrderNoneRecur_singleStack(BTNode *root) {
    if (!root) return;

    BTNode *lastPopped = nullptr;
    BTNode *stack[MAX_SIZE];
    int top = -1;

    BTNode *node = root;
    stack[++top] = node;
    while (top > -1) {
        while (node->lChild) {
            node = node->lChild;
            stack[++top] = node;
        } // 发现没有左孩子的结点
        // 考虑栈顶元素
        while (top > -1) {
            if (node->rChild) { // 有右孩子
                if (lastPopped && node->rChild == lastPopped) { // 右孩子刚刚出栈，则此结点也出栈
                    lastPopped = stack[top--];
                    visit(lastPopped);
                    node = stack[top];
                }
                else { // 有右孩子，右孩子入栈。退出循环，搜索右孩子的左子树。
                    node = node->rChild;
                    stack[++top] = node;
                    break;
                }
            }
            else { // 没有右孩子，此结点出栈
                lastPopped = stack[top--];
                visit(lastPopped);
                node = stack[top];
            }
        }
    }
}

void levelOrder(BTNode *root) {
    if (root == nullptr) return;

    BTNode *queue[MAX_SIZE];
    int front = 0, rear = 0;

    rear = (rear + 1) % MAX_SIZE;
    queue[rear] = root;
    while (front != rear) { // 当队列不为空时循环
        front = (front + 1) % MAX_SIZE;
        BTNode *node = queue[front];
        visit(node);
        if (node->lChild) {
            rear = (rear + 1) % MAX_SIZE;
            queue[rear] = node->lChild;
        }
        if (node->rChild) {
            rear = (rear + 1) % MAX_SIZE;
            queue[rear] = node->rChild;
        }
    }
}

void visit(BTNode *tree) {
    cout << tree->data << " ";
}

BTNode *buildSampleBiTree() {
    auto root = new BTNode(1);
    auto node2 = new BTNode(2);
    auto node3 = new BTNode(3);
    auto node4 = new BTNode(4);
    auto node5 = new BTNode(5);
    root->lChild = node2;
    root->rChild = node3;
    node2->lChild = node4;
    node2->rChild = node5;
    return root;
}