//
// Created by Freeman on 2021/9/19.
//

#ifndef DATA_STRUCTURE_REVIEW_GRAPH_HPP
#define DATA_STRUCTURE_REVIEW_GRAPH_HPP

#include <iostream>
#include <set>
#include <vector>
#include "../Exceptions.hpp"

class EdgeNode;

class VexNode;

class Graph;

class UndirectedGraph;

class DirectedGraph;

class Edge;

/**
 * 用于邻接表的边结点类
 */
class EdgeNode {
    friend class VexNode;

    friend class Graph;

    friend class UndirectedGraph;

    friend class DirectedGraph;

private:
    int vexNO;
    EdgeNode *next = nullptr;
    double weight = 0; // 权值

public:
    explicit EdgeNode(int vexNO) : vexNO(vexNO) {}

    EdgeNode(int vexNO, double weight) : EdgeNode(vexNO) {
        this->weight = weight;
    }
};

/**
 * 用于邻接表的顶点结点类
 */
class VexNode {
    friend class Graph;

    friend class UndirectedGraph;

    friend class DirectedGraph;

private:
    EdgeNode *firstEdge;

public:
    /**
     * 检查编号为vexNO的顶点是否邻接于此顶点。
     * @param vexNO 待寻找顶点的编号。
     * @return true，如果编号为vexNO的顶点邻接于此顶点。
     */
    bool hasAdjNode(int vexNO);

    /**
     * 添加新边。
     * @param vexNO 邻接于此顶点的顶点的编号。
     * @return true，若边添加成功。当边已存在时，返回false。
     */
    bool addEdge(int vexNO);

    /**
     * 添加新边，并设置此边的权值。
     * @param vexNO 邻接于此顶点的顶点的编号。
     * @param weight 边权值。默认为1。
     * @return true，若边添加成功。当边已存在时，返回false。
     */
    bool addEdge(int vexNO, double weight);
};

/**
 * 图的基类
 */
class Graph {
protected:
    bool weighted; // 是否带权
    std::vector<VexNode> vertices; // 邻接表的顶点表
    int nVex = 0, nEdges = 0; // 顶点数和边数

public:
    explicit Graph(bool weighted) : weighted(weighted) {}

    Graph(bool weighted, int nVex) : Graph(weighted) {
        this->nVex = nVex;
        for (int i = 0; i < nVex; i++) {
            vertices.push_back(VexNode());
        }
    }

    /**
     * 添加新顶点。顶点序号从0开始依次增加。
     */
    void addNode();

    /**
     * 添加新边。
     * @param tail 弧尾。
     * @param head 弧头。
     * @return true，若边添加成功。当边已存在时，返回false。
     */
    virtual bool addEdge(int tail, int head) = 0;

    /**
     * 添加新边。
     * @param tail 弧尾。
     * @param head 弧头。
     * @param weight 边权。
     * @return true，若边添加成功。当边已存在时，返回false。
     */
    virtual bool addEdge(int tail, int head, double weight) = 0;

    ~Graph() {
        // 释放边结点
        for (int i = 0; i < nVex; i++) {
            EdgeNode *edge = vertices[i].firstEdge;
            while (edge) {
                EdgeNode *tmp = edge;
                edge = edge->next;
                delete tmp;
            }
        }
    }
};

class Edge {
    friend class UndirectedGraph;

    friend class DirectedGraph;

    friend bool operator==(const Edge &edge1, const Edge &edge2);

    friend std::ostream &operator<<(std::ostream &out, const Edge &edge);

private:
    int head = -1, tail = -1;
    double weight = 1;
    bool directed = false;

public:
    Edge(int tail, int head, bool directed, double weight = 1) {
        if (head == tail) throw IllegalArgumentException();
        this->tail = tail;
        this->head = head;
        this->directed = directed;
        this->weight = weight;
    }

    bool operator<(const Edge &other) const;

    bool operator>=(const Edge &other) const;

    bool operator>(const Edge &other) const;

    bool operator<=(const Edge &other) const;
};

void visit(int vex);

#endif //DATA_STRUCTURE_REVIEW_GRAPH_HPP
