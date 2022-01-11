//
// Created by Freeman on 2021/9/19.
//

#include <iostream>
#include <set>
#include "Graph.hpp"
#include "../Exceptions.hpp"
#include "../Util.hpp"
#include "../Chapter 6/UnionFindSet.hpp"

using namespace std;

#ifndef DBL_MAX
#define DBL_MAX 1E308
#endif

bool VexNode::hasAdjNode(int vexNO) {
    EdgeNode *edge = firstEdge;
    while (edge) {
        if (edge->vexNO == vexNO) return true;
        edge = edge->next;
    }
    return false;
}

bool VexNode::addEdge(int vexNO) {
    if (hasAdjNode(vexNO)) return false;
    EdgeNode *edge = firstEdge;
    if (!edge) {
        firstEdge = new EdgeNode(vexNO);
        return true;
    }
    else {
        while (edge->next) {
            edge = edge->next;
        }
        edge->next = new EdgeNode(vexNO);
        return true;
    }
}

bool VexNode::addEdge(int vexNO, double weight) {
    if (hasAdjNode(vexNO)) return false;
    EdgeNode *edge = firstEdge;
    if (!edge) {
        firstEdge = new EdgeNode(vexNO, weight);
        return true;
    }
    else {
        while (edge->next) {
            edge = edge->next;
        }
        edge->next = new EdgeNode(vexNO, weight);
        return true;
    }
}

void Graph::addNode() {
    this->nVex += 1;
    vertices.push_back(VexNode());
}

bool operator==(const Edge &edge1, const Edge &edge2) {
    if (edge1.directed != edge2.directed) return false;
    if (edge1.directed) {
        return edge1.head == edge2.head && edge1.tail == edge2.tail && abs(edge1.weight - edge2.weight) < 1E-6;
    }
    else {
        return ((edge1.head == edge2.head && edge1.tail == edge2.tail) ||
                (edge1.head == edge2.tail && edge1.tail == edge2.head))
               && abs(edge1.weight - edge2.weight) < 1E-6;
    }
}

ostream &operator<<(ostream &out, const Edge &edge) {
    if (edge.directed) {
        return out << "<" << edge.tail << ", " << edge.head << ">  " << edge.weight;
    }
    else return out << "(" << edge.tail << ", " << edge.head << ")  " << edge.weight;
}

bool Edge::operator<(const Edge &other) const {
    return weight < other.weight;
}

bool Edge::operator>=(const Edge &other) const {
    return !operator<(other);
}

bool Edge::operator>(const Edge &other) const {
    return weight > other.weight;
}

bool Edge::operator<=(const Edge &other) const {
    return !operator>(other);
}

void visit(int vex) {
    cout << vex << " ";
}