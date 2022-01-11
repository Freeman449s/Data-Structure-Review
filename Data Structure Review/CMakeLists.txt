cmake_minimum_required(VERSION 3.19)
project(Data_Structure_Review)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories("Chapter 1")
include_directories("Chapter 2")

add_executable(Data_Structure_Review
        "Chapter 1/CyclicMove.hpp"
        "Chapter 2/ArrayList.cpp"
        "Chapter 2/ArrayList.hpp"
        "Chapter 2/List.hpp"
        "Chapter 2/MergeSortedList.hpp"
        Main.cpp
        Exceptions.hpp
        Util.hpp "Chapter 2/SortedListDifference.hpp" "Chapter 2/BenchmarkDivide.hpp" "Exams/LastButK_Exam2009.hpp" "Chapter 2/LNode.hpp" "Exams/MasterElem_Exam2013.hpp" "Chapter 3/Calculator.hpp" "Chapter 3/LinkedStack.hpp" "Chapter 3/CyclicQueue.hpp" "Chapter 3/Permutation.hpp" "Chapter 4/KMP.hpp" "Chapter 4/DelChar.hpp" "Chapter 5/OrthoList.hpp" "Chapter 5/TransposeTrimat.cpp" "Chapter 5/TransposeTrimat.hpp" "Chapter 6/BiTree.cpp" "Chapter 6/BiTree.hpp" "Chapter 6/TBTree.cpp" "Chapter 6/TBTree.hpp" "Chapter 7/Graph.cpp" "Chapter 7/Graph.hpp" "Chapter 6/UnionFindSet.cpp" "Chapter 6/UnionFindSet.hpp" Util.cpp "Chapter 7/DirectedGraph.cpp" "Chapter 7/DirectedGraph.hpp" "Chapter 7/UndirectedGraph.cpp" "Chapter 7/UndirectedGraph.hpp" "Chapter 8/Sort.hpp" "Chapter 8/Sort.cpp" "Chapter 8/MaxHeap.cpp" "Chapter 8/MaxHeap.hpp")
