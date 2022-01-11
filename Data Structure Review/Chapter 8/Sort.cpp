//
// Created by Freeman on 2021/9/27.
//

#include "Sort.hpp"

using namespace std;

vector<int> Sort::generateTestCase() {
    vector<int> v;
    for (int i = 10; i >= 1; i--) {
        v.push_back(i);
    }
    return v;
}

vector<unsigned> Sort::generateTestCase2() {
    vector<unsigned> v;
    for (unsigned u = 100; u >= 1; u--) {
        v.push_back(u);
    }
    return v;
}