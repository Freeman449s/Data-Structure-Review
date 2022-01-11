//
// Created by Freeman on 2021/9/23.
//

#include "../Util.hpp"
#include "../Chapter 6/UnionFindSet.hpp"
#include "UndirectedGraph.hpp"

using namespace std;

#ifndef DBL_MAX
#define DBL_MAX 1E308
#endif

bool UndirectedGraph::addEdge(int tail, int head) {
    if (tail < 0 || tail >= nVex || head < 0 || head >= nVex) throw IllegalArgumentException();

    if (!vertices[tail].addEdge(head)) return false;
    else {
        nEdges += 1;
        vertices[head].addEdge(tail);
        return true;
    }
}

bool UndirectedGraph::addEdge(int tail, int head, double weight) {
    if (!weighted) throw IllegalOperationException();
    if (tail < 0 || tail >= nVex || head < 0 || head >= nVex) throw IllegalArgumentException();

    if (!vertices[tail].addEdge(head, weight)) return false;
    else {
        nEdges += 1;
        vertices[head].addEdge(tail, weight);
        return true;
    }
}

void UndirectedGraph::DFS(int startVex) {
    bool *visited = new bool[nVex];
    for (int i = 0; i < nVex; i++) visited[i] = false;
    DFSRecur(startVex, visited);
    delete[] visited;
}

void UndirectedGraph::DFSRecur(int startVex, bool visited[]) {
    visit(startVex);
    visited[startVex] = true;
    EdgeNode *edge = vertices[startVex].firstEdge;
    while (edge) {
        if (!visited[edge->vexNO]) DFSRecur(edge->vexNO, visited);
        edge = edge->next;
    }
}

void UndirectedGraph::BFS(int startVex) {
    bool *visited = new bool[nVex];
    for (int i = 0; i < nVex; i++) visited[i] = false;

    int queueSize = nVex;
    int *queue = new int[queueSize];
    int front = 0, rear = 0;

    rear = (rear + 1) % queueSize;
    queue[rear] = startVex;
    while (front != rear) {
        front = (front + 1) % queueSize;
        int vexNO = queue[front];
        visit(vexNO);
        visited[vexNO] = true;
        EdgeNode *edge = vertices[vexNO].firstEdge;
        while (edge) {
            if (!visited[edge->vexNO]) {
                rear = (rear + 1) % queueSize;
                queue[rear] = edge->vexNO;
            }
            edge = edge->next;
        }
    }

    delete[] queue;
    delete[] visited;
}

set<pair<int, int>> UndirectedGraph::Prim() {
    set<pair<int, int>> tree; // 记录了生成树含有的边
    bool *inTree = new bool[nVex]; // 指示顶点是否已在树中
    double *dist = new double[nVex]; // 树外顶点到树的距离，定义为与树中各邻接顶点的边的最小权值
    int *closetVex = new int[nVex]; // 距离最近的顶点
    for (int i = 0; i < nVex; i++) {
        inTree[i] = false;
        dist[i] = DBL_MAX;
    }

    inTree[0] = true;
    EdgeNode *edge = vertices[0].firstEdge;
    while (edge) {
        dist[edge->vexNO] = edge->weight;
        closetVex[edge->vexNO] = 0;
        edge = edge->next;
    }
    while (true) {
        // 寻找距离最近的顶点
        double min = DBL_MAX;
        int min_index = -1;
        for (int i = 0; i < nVex; i++) {
            if (!inTree[i]) {
                if (dist[i] < min) {
                    min = dist[i];
                    min_index = i;
                }
            }
        }
        if (min_index == -1) break; // 已经找不到与树直接相连的顶点

        // 将顶点和边加入树
        tree.insert(pair<int, int>(min_index, closetVex[min_index]));
        inTree[min_index] = true;
        edge = vertices[min_index].firstEdge;
        while (edge) {
            if (!inTree[edge->vexNO]) {
                if (dist[edge->vexNO] > edge->weight) {
                    dist[edge->vexNO] = edge->weight;
                    closetVex[edge->vexNO] = min_index;
                }
            }
            edge = edge->next;
        }
    }
    return tree;
}

set<pair<int, int>> UndirectedGraph::Kruskal() {
    vector<Edge> edges;
    set<pair<int, int>> tree;
    // 构建所有边的集合，排序由set容器完成。
    for (int i = 0; i < nVex; i++) {
        EdgeNode *edgeNode = vertices[i].firstEdge;
        while (edgeNode) {
            Edge edge = Edge(i, edgeNode->vexNO, false, edgeNode->weight);
            edges.push_back(edge);
            edgeNode = edgeNode->next;
        }
    }
    Util::insertionSort<Edge>(edges);

    UnionFindSet UFSet = UnionFindSet(nVex);
    while (!edges.empty() && tree.size() < nVex - 1) { // 寻找连接树内和树外结点的最小边，将之加入树中。
        Edge edge = *edges.begin();
        edges.erase(edges.begin());
        if (UFSet.Find(edge.head) != UFSet.Find(edge.tail)) {
            UFSet.Union(edge.head, edge.tail);
            tree.insert(pair<int, int>(edge.head, edge.tail));
        }
    }
    return tree;
}
