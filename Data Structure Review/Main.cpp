#include <iostream>
#include <stack>
#include <vector>
#include "Util.hpp"
#include "Chapter 2/BenchmarkDivide.hpp"
#include "Chapter 3/Calculator.hpp"
#include "Chapter 3/CyclicQueue.hpp"
#include "Chapter 3/Permutation.hpp"
#include "Chapter 4/KMP.hpp"
#include "Chapter 4/DelChar.hpp"
#include "Chapter 5/OrthoList.hpp"
#include "Chapter 6/BiTree.hpp"
#include "Chapter 7/Graph.hpp"
#include "Chapter 7/UndirectedGraph.hpp"
#include "Chapter 7/DirectedGraph.hpp"
#include "Chapter 8/Sort.hpp"

using namespace std;
using namespace Chapter3;
using namespace Chapter4;
using namespace Chapter5;

int main() {
    vector<unsigned> v = Sort::generateTestCase2();
    Sort::radixSort(v);
    cout << Util::isInOrder(v) << endl;
}