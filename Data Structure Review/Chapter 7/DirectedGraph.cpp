//
// Created by Freeman on 2021/9/23.
//

#include <map>
#include "DirectedGraph.hpp"

using namespace std;

#ifndef DBL_MAX
#define DBL_MAX 1E308
#endif

bool DirectedGraph::addEdge(int tail, int head) {
    if (tail < 0 || tail >= nVex || head < 0 || head >= nVex) throw IllegalArgumentException();

    if (vertices[tail].addEdge(head)) {
        nEdges += 1;
        return true;
    }
    else return false;
}

bool DirectedGraph::addEdge(int tail, int head, double weight) {
    if (!weighted) throw IllegalOperationException();
    if (tail < 0 || tail >= nVex || head < 0 || head >= nVex) throw IllegalArgumentException();

    if (vertices[tail].addEdge(head, weight)) {
        nEdges += 1;
        return true;
    }
    else return false;
}

void DirectedGraph::Dijkstra(int v, vector<double> &dist, vector<int> &path) {
    if (v < 0 || v >= nVex) throw IllegalArgumentException();

    // 初始化
    bool *found = new bool[nVex]; // 是否已找到v到该顶点的最短路径
    dist.clear();
    path.clear();
    for (int i = 0; i < nVex; i++) {
        dist.push_back(DBL_MAX);
        path.push_back(-1);
        found[i] = false;
    }
    EdgeNode *edge = vertices[v].firstEdge;
    while (edge) {
        dist[edge->vexNO] = edge->weight;
        path[edge->vexNO] = v;
        edge = edge->next;
    }
    found[v] = true;

    for (int count = 1; count <= nVex - 1; count++) {
        double minDist = DBL_MAX;
        int closetVex = -1;
        for (int i = 0; i < nVex; i++) {
            if (!found[i]) {
                if (dist[i] < minDist) {
                    minDist = dist[i];
                    closetVex = i;
                }
            }
        }
        found[closetVex] = true;
        edge = vertices[closetVex].firstEdge;
        while (edge) {
            int w = edge->vexNO;
            if (dist[w] > dist[closetVex] + edge->weight) {
                dist[w] = dist[closetVex] + edge->weight;
                path[w] = closetVex;
            }
            edge = edge->next;
        }
    }

    delete[] found;
}

void DirectedGraph::Floyd(vector<vector<double>> &dist, vector<vector<int>> &path) {
    // 初始化距离和路径矩阵
    dist.clear();
    path.clear();
    for (int i = 0; i < nVex; i++) {
        dist.push_back(vector<double>(nVex, DBL_MAX));
        path.push_back(vector<int>(nVex, -1));
    }
    for (int i = 0; i < nVex; i++) {
        EdgeNode *edge = vertices[i].firstEdge;
        while (edge) {
            dist[i][edge->vexNO] = edge->weight;
            edge = edge->next;
        }
    }

    // Floyd核心算法
    for (int v = 0; v < nVex; v++) { // 逐个扩展最短路径可能包含的顶点
        for (int i = 0; i < nVex; i++) {
            for (int j = 0; j < nVex; j++) {
                if (i == j) continue; // dist[i][i]初始为DBL_MAX，可能被错误更改
                if (dist[i][v] >= DBL_MAX || dist[v][j] >= DBL_MAX) continue; // 直接进入下次循环，避免相加导致上溢
                if (dist[i][j] > dist[i][v] + dist[v][j]) { // 经过v，i到j的路径是否能缩短
                    dist[i][j] = dist[i][v] + dist[v][j];
                    path[i][j] = v; // v现在是i到j最短路径上的一个中间点
                }
            }
        }
    }
}

vector<int> DirectedGraph::getPath(int u, int v,
                                   const vector<vector<double>> &distMat, const vector<vector<int>> &pathMat) {
    vector<int> path;
    if (distMat[u][v] >= DBL_MAX) return path; // 不存在路径
    if (pathMat[u][v] == -1) { // 邻接
        path.push_back(u);
        path.push_back(v);
        return path;
    }
    // 存在路径，且有中间结点
    int mid = pathMat[u][v];
    path.push_back(u); // 为避免顶点重复，getPathRecur只将位于弧头的顶点加入path向量，因此此处要补全路径上的第一个顶点u
    getPathRecur(u, mid, path, distMat, pathMat);
    getPathRecur(mid, v, path, distMat, pathMat);
    return path;
}

vector<int> DirectedGraph::topologicalSort() {
    vector<int> sequence;
    // 初始化
    int *inDegree = new int[nVex];
    for (int i = 0; i < nVex; i++) {
        inDegree[i] = 0;
    }
    for (int i = 0; i < nVex; i++) {
        EdgeNode *edge = vertices[i].firstEdge;
        while (edge) {
            inDegree[edge->vexNO] += 1;
            edge = edge->next;
        }
    }
    int *stack = new int[nVex];
    int top = -1;

    for (int i = 0; i < nVex; i++) {
        if (inDegree[i] == 0) {
            stack[++top] = i;
            break;
        }
    }
    while (top > -1) {
        int vex = stack[top--];
        sequence.push_back(vex);
        EdgeNode *edge = vertices[vex].firstEdge;
        while (edge) {
            inDegree[edge->vexNO] -= 1;
            if (inDegree[edge->vexNO] == 0) {
                stack[++top] = edge->vexNO;
            }
            edge = edge->next;
        }
    }

    delete[] stack;
    delete[] inDegree;

    if (sequence.size() < nVex) sequence.clear(); // 无法找到拓扑序列
    return sequence;
}

void DirectedGraph::getPathRecur(int u, int v, vector<int> &path,
                                 const vector<vector<double>> &distMat, const vector<vector<int>> &pathMat) {
    if (pathMat[u][v] == -1) { // 邻接。路径的存在性由主调函数保证。
        path.push_back(v);
    }
    else { // 仍有中间结点
        int mid = pathMat[u][v];
        getPathRecur(u, mid, path, distMat, pathMat);
        getPathRecur(mid, v, path, distMat, pathMat);
    }
}

// TODO: 等待测试
vector<Edge> DirectedGraph::criticalPath() {
    vector<Edge> criticalPath;

    // 生成拓扑序列
    vector<int> topoSeq = topologicalSort(); // 拓扑序列
    if (topoSeq.empty()) return criticalPath; // 无法找到拓扑序列，返回空向量
    vector<int> reverseTopoSeq(nVex); // 逆向拓扑序列
    for (int i = 0; i < nVex; i++) reverseTopoSeq[i] = topoSeq[nVex - 1 - i];

    // 初始化邻接矩阵，同时为每条边赋予编号
    map<int, Edge> idEdgeMap;
    int edgeCount = 0;
    vector<vector<double>> adjMat; // 邻接矩阵
    for (int i = 0; i < nVex; i++) {
        adjMat.push_back(vector<double>(nVex));
        for (int j = 0; j < nVex; j++) {
            adjMat[i][j] = DBL_MAX;
        }
    }
    for (int i = 0; i < nVex; i++) {
        EdgeNode *edgeNode = vertices[i].firstEdge;
        while (edgeNode) {
            adjMat[i][edgeNode->vexNO] = edgeNode->weight;
            idEdgeMap.insert(pair<int, Edge>(edgeCount++, Edge(i, edgeNode->vexNO, true, edgeNode->weight)));
            edgeNode = edgeNode->next;
        }
    }

    vector<double> vexEarly(nVex);
    vector<double> vexLate(nVex);
    // 计算事件最早开始时间
    vexEarly[topoSeq[0]] = 0;
    for (int i = 1; i < nVex; i++) {
        int vex = topoSeq[i];
        double earliestTime = -1;
        for (int j = 0; j < i; j++) {
            int prior = topoSeq[j];
            if (adjMat[prior][vex] < DBL_MAX) { // 存在prior到vex的弧
                if (vexEarly[prior] + adjMat[prior][vex] > earliestTime)
                    earliestTime = vexEarly[prior] + adjMat[prior][vex];
            }
        }
        vexEarly[vex] = earliestTime;
    }
    // 计算事件最晚开始时间
    vexLate[reverseTopoSeq[0]] = vexEarly[reverseTopoSeq[0]];
    for (int i = 1; i < nVex; i++) {
        int vex = reverseTopoSeq[i];
        double latestTime = DBL_MAX;
        for (int j = 0; j < i; j++) {
            int posterior = reverseTopoSeq[j];
            if (adjMat[vex][posterior] < DBL_MAX) { // 存在vex到posterior的弧
                if (vexLate[posterior] - adjMat[vex][posterior] < latestTime)
                    latestTime = vexLate[posterior] - adjMat[vex][posterior];
            }
        }
        vexLate[vex] = latestTime;
    }
    // 计算活动的松弛度
    map<int, Edge>::iterator it = idEdgeMap.begin();
    for (; it != idEdgeMap.end(); it++) { // it->first为边的ID，it->second为边
        double actEarly = vexEarly[it->second.tail];
        double actLate = vexLate[it->second.head] - it->second.weight;
        double slackTime = actLate - actEarly;
        if (abs(slackTime) < 1E-6) { // 关键活动
            criticalPath.push_back(idEdgeMap.at(it->first));
        }
    }
    return criticalPath;
}

DirectedGraph buildSampleDirectedGraph() {
    DirectedGraph graph(true, 7);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 6);
    graph.addEdge(1, 2, 1);
    graph.addEdge(3, 2, 2);
    graph.addEdge(1, 4, 7);
    graph.addEdge(3, 5, 5);
    graph.addEdge(2, 5, 4);
    graph.addEdge(2, 4, 6);
    graph.addEdge(5, 4, 1);
    graph.addEdge(4, 6, 6);
    graph.addEdge(5, 6, 8);
    return graph;
}

DirectedGraph buildSampleDirectedGraph2() {
    DirectedGraph graph(true, 11);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 1);
    graph.addEdge(2, 4, 3);
    graph.addEdge(2, 5, 5);
    graph.addEdge(3, 6, 6);
    graph.addEdge(4, 6, 8);
    graph.addEdge(4, 7, 4);
    graph.addEdge(5, 8, 2);
    graph.addEdge(6, 10, 7);
    graph.addEdge(7, 8, 10);
    graph.addEdge(7, 9, 4);
    graph.addEdge(8, 9, 1);
    graph.addEdge(9, 10, 6);
    return graph;
}