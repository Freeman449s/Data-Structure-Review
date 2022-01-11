//
// Created by Freeman on 2021/8/30.
//

#include "TransposeTrimat.hpp"

using namespace Chapter5;

void TransposeTrimat::solve(int A[][3], int B[][3]) {
    B[0][0] = A[0][0];
    B[0][1] = A[0][2];
    B[0][2] = A[0][1];
    int nCol = A[0][2], p = A[0][0], k = 1;
    for (int col = 0; col <= nCol - 1; col++) {
        for (int i = 1; i <= p; i++) {
            if (A[i][2] == col) {
                B[k][0] = A[i][0];
                B[k][1] = A[i][2];
                B[k][2] = A[i][1];
                k++;
            }
        }
    }
}