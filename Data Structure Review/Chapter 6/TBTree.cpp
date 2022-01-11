//
// Created by Freeman on 2021/9/8.
//

#include "TBTree.hpp"

using namespace Chapter6;

void buildInThread(TBTree *root) {
    if (!root) return;

    TBTree *pre = nullptr;
    buildInThreadRecur(root, pre);
    pre->rChild = nullptr; // 调用buildInThreadRecur后，pre指向中序遍历的最后一个结点
    pre->rTag = PointerType::thread;
}

void buildInThreadRecur(TBTree *node, TBTree *&pre) {
    if (!node) return;

    buildInThreadRecur(node->lChild, pre);
    // 处理完左子树后，pre指向node的前驱。现在处理建立node和pre之间的线索。
    if (!node->lChild) {
        node->lChild = pre;
        node->lTag = PointerType::thread;
    }
    if (pre && !pre->rChild) {
        pre->rChild = node;
        pre->rTag = PointerType::thread;
    }
    pre = node; // 处理右子树前，将pre更新为当前结点
    buildInThreadRecur(node->rChild, node);
}

TBTree *inOrderFirst(TBTree *root) {
    if (!root) return nullptr;

    TBTree *node = root;
    while (node->lTag == PointerType::pointer) node = node->lChild; // 只有在指针为线索类型时，指针才有可能为空
    return node;
}

TBTree *inOrderLast(TBTree *root) {
    if (!root) return nullptr;

    TBTree *node = root;
    while (node->rTag == PointerType::pointer) node = node->rChild;
    return node;
}

TBTree *inOrderNext(TBTree *node) {
    if (node->rTag == PointerType::pointer) return inOrderFirst(node->rChild);
    else return node->rChild;
}

TBTree *inOrderPrior(TBTree *node) {
    if (node->lTag == PointerType::pointer) return inOrderLast(node->lChild);
    else return node->lChild;
}

void inOrder(TBTree *root) {
    TBTree *node = inOrderFirst(root);
    while (node) {
        visit(node);
        node = inOrderNext(node);
    }
}

void buildPreThreadRecur(TBTree *node, TBTree *&pre) {
    /**
     * 前序线索的建立与中序线索十分相似，只不过把处理node和pre的过程提前。
     * 注意在递归之前增加了条件。
     */
    if (!node) return;

    if (!node->lChild) {
        node->lChild = pre;
        node->lTag = PointerType::thread;
    }
    if (pre && !pre->rChild) {
        pre->rChild = node;
        pre->rTag = PointerType::thread;
    }

    pre = node; // 处理完node和pre后，始终需要让pre指向当前结点
    if (node->lTag == PointerType::pointer) { // 与建立中序线索时不同，在递归的入口处增加了条件
        buildPreThreadRecur(node->lChild, pre);
    }
    if (node->rTag == PointerType::pointer) {
        buildPreThreadRecur(node->rChild, pre);
    }
}

void preOrder(TBTree *root) {
    if (!root) return;

    TBTree *node = root;
    while (node) {
        while (node->lTag == PointerType::pointer) { // 沿左路一直向下
            visit(node);
            node = node->lChild;
        }
        visit(node); // 循环退出。此时node已经没有左孩子，先访问node.
        node = node->rChild; // 无论右指针是否为线索，都是下一个需要访问的对象。
    }
}

void buildPostThreadRecur(TBTree *node, TBTree *&pre) {
    /**
     * 后续线索的建立与中序线索十分相似，只不过把处理node和pre的过程置后。
     */
    if (!node) return;

    buildPostThreadRecur(node->lChild, pre);
    buildPostThreadRecur(node->rChild, pre);
    if (!node->lChild) {
        node->lChild = pre;
        node->lTag = PointerType::thread;
    }
    if (pre && !pre->rChild) {
        pre->rChild = node;
        pre->rTag = PointerType::thread;
    }
    pre = node; // 处理完node和pre后，始终需要让pre指向当前结点
}

void visit(TBTree *node) {}