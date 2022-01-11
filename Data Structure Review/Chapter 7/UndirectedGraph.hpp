//
// Created by Freeman on 2021/9/23.
//

#ifndef DATA_STRUCTURE_REVIEW_UNDIRECTED_GRAPH_HPP
#define DATA_STRUCTURE_REVIEW_UNDIRECTED_GRAPH_HPP

#include "Graph.hpp"

/**
 * 无向图类
 */
class UndirectedGraph : public Graph {
public:
    UndirectedGraph(bool weighted, int nVex) : Graph(weighted, nVex) {}

    explicit UndirectedGraph(bool weighted) : Graph(weighted) {}

    bool addEdge(int tail, int head) override;

    bool addEdge(int tail, int head, double weight) override;

    /**
     * 从指定顶点开始，进行深度优先搜索。
     * 注意：不在同一个连通分量中的顶点无法到达。
     * @param startVex 搜索开始的顶点。
     */
    void DFS(int startVex);

    /**
     * 从指定顶点开始，进行宽度优先搜索。
     * 注意：不在同一个连通分量中的顶点无法到达。
     * @param startVex 搜索开始的顶点。
     */
    void BFS(int startVex);

    /**
     * Prim算法求最小生成树。
     * 当图不连通时，返回结点0所在连通分量的最小生成树。
     * @return 最小生成树的边形成的集合。
     */
    std::set<std::pair<int, int>> Prim();

    /**
     * Kruskal算法求最小生成树。
     * 当图不连通时，返回生成森林中各树含有的边。
     * @return 最小生成树的边形成的集合。
     */
    std::set<std::pair<int, int>> Kruskal();

private:
    void DFSRecur(int startVex, bool visited[]);
};

#endif //DATA_STRUCTURE_REVIEW_UNDIRECTED_GRAPH_HPP
