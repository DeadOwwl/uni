
//
// Created by aowl on 21.03.2021.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>
#pragma warning(disable:4996)

void algebraicComplement(int** mat, int** temp, int r, int c, int n){
    int i = 0, j = 0;
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            if (row != r && col != c){
                temp[i][j++] = mat[row][col];
                if (j == n - 1){
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinantOfMatrix(int** mat, int n){
    int D = 0;
    if (n == 1)
        return mat[0][0];
    int** temp = new int*[n];
    for (int i = 0; i < n; i++)
        temp[i] = new int[n];
    int sign = 1;
    for (int f = 0; f < n; f++) {
        algebraicComplement(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
        sign *= -1;
    }
    return D;
}

void threadF(std::string i, std::string o){
    std::fstream in(i);
    std::ofstream out(o);
    int** matrix;
    int m(0);
    in >> m;
    if (m >= 1) {
        matrix = new int *[m];
        for (int i = 0; i < m; i++)
            matrix[i] = new int[m];
        for (int i = 0; i < m; i++) {
            matrix[i] = new int[m];
            for (int j = 0; j < m; j++)
                in >> matrix[i][j];
        }
        int d = determinantOfMatrix(matrix, m);
        out << d;
    } else
        out << "Error: matrix size < 1.";
    in.close();
    out.close();
}

int main() {
    unsigned int start_time = clock();
    std::thread th(&threadF, "in.txt", "out.txt");
    th.join();
    unsigned int t = clock() - start_time;
    std::cout << "Time execution: " << t << " ms";
    return 0;
}

