//
// Created by Freeman on 2021/9/23.
//

#ifndef DATA_STRUCTURE_REVIEW_DIRECTED_GRAPH_HPP
#define DATA_STRUCTURE_REVIEW_DIRECTED_GRAPH_HPP

#include <vector>
#include "Graph.hpp"

/**
 * 有向图类
 */
class DirectedGraph : public Graph {
public:
    DirectedGraph(bool weighted, int nVex) : Graph(weighted, nVex) {}

    explicit DirectedGraph(bool weighted) : Graph(weighted) {}

    bool addEdge(int tail, int head) override;

    bool addEdge(int tail, int head, double weight) override;

    /**
     * 使用Dijkstra算法求v到各顶点的最短路径。
     * 注意：函数默认v可以到达任何顶点。
     * @param v
     * @param dist 需要外部传入的距离向量。调用函数后，dist存储v到各顶点的最短距离。
     * @param path 需要外部传入的路径向量。调用函数后，dist存储v到任意顶点w的最短路径上，位于w之前的顶点。
     */
    void Dijkstra(int v, std::vector<double> &dist, std::vector<int> &path);

    /**
     * 使用Floyd算法求各顶点之间的最短路径。
     * @param dist 需要外部传入的最短距离矩阵。调用函数后，dist[i][j]存储顶点i到j的最短距离。
     * @param path 需要外部传入的路径矩阵。调用函数后，path[i][j]存储i到j的最短路径上需要经过的一个中间顶点，可以用递归方法求出i到j的最短路径。当path[i][j]==-1时，i与j邻接，或不存在i到j的路径。
     */
    void Floyd(std::vector<std::vector<double>> &dist, std::vector<std::vector<int>> &path);

    /**
     * 从Floyd算法产生的路径矩阵中，找到u到v的最短路径。
     * @param u 起点。
     * @param v 终点。
     * @param distMat Floyd算法产生的距离矩阵。
     * @param pathMat Floyd算法产生的路径矩阵。
     * @return u到v的最短路径包含的顶点。若不存在最短路径，返回空向量。
     */
    std::vector<int> getPath(int u, int v,
                             const std::vector<std::vector<double>> &distMat,
                             const std::vector<std::vector<int>> &pathMat);

    /**
     * 获得当前图的一个拓扑排序序列。
     * @return 拓扑排序序列。如果不存在拓扑排序，将返回空向量。
     */
    std::vector<int> topologicalSort();

    /**
     * 求关键路径。
     * @return 储存了关键路径上的边的向量。
     */
    std::vector<Edge> criticalPath();

private:
    void getPathRecur(int u, int v, std::vector<int> &path,
                      const std::vector<std::vector<double>> &distMat, const std::vector<std::vector<int>> &pathMat);
};

DirectedGraph buildSampleDirectedGraph();

DirectedGraph buildSampleDirectedGraph2();

#endif //DATA_STRUCTURE_REVIEW_DIRECTED_GRAPH_HPP
