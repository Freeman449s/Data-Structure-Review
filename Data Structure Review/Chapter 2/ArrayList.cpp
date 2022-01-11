#include "ArrayList.hpp"

template<typename T>
bool operator==(const ArrayList<T> &listA, const ArrayList<T> &listB) {
    if (listA.size() != listB.size()) return false;
    for (int i = 0; i < listA.size(); i++) {
        if (listA[i] != listB[i]) return false;
    }
    return true;
}