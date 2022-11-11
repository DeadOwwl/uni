
//
// Created by aowl2 on 21.03.2021.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <thread>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <queue>
#include <windows.h>
#pragma warning(disable:4996)

struct stMatrix {
    int n = 0;
    int** matrix = nullptr;
};

struct result {
    stMatrix stm;
    long long determinant = 0;
    bool mistake = false;
    double timeExecution = 0;
};

struct resultThread {
    unsigned int numCompletedTask = 0;
    double executionTimeSolution = 0;
};

std::queue<stMatrix>arrayParams;
std::vector<result> arrayResult;
std::vector<resultThread> threadResults;

CRITICAL_SECTION csParam;
CRITICAL_SECTION csResult;
CRITICAL_SECTION csResultThread;

unsigned int taskCount = 0, threadCount = 0;
unsigned int allCompletedTask = 0;
unsigned int notCompletedTaskCalculationError = 0;
unsigned int hasNoSolutions = 0;
double writingTime = 0;

void algebraicComplement(int** mat, int** temp, int q, int n) {
    int i = 0, j = 0, p = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinantOfMatrix(int** mat, int n) {
    int D = 0;
    if (n == 1)
        return mat[0][0];
    int** temp = new int* [n];
    for (int i = 0; i < n; i++)
        temp[i] = new int[n];
    int sign = 1;
    for (int f = 0; f < n; f++) {
        algebraicComplement(mat, temp, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
        sign *= -1;
    }
    for (int i = 0; i < n; i++) {
        delete[] temp[i];
    }
    delete[] temp;
    return D;
}

void threadMain() {
    resultThread rt;
    while (true) {
        bool empty = true;
        stMatrix p;
        EnterCriticalSection(&csParam);
        if (!arrayParams.empty()) {
            p = arrayParams.front();
            arrayParams.pop();
            empty = false;
        }
        LeaveCriticalSection(&csParam);
        if (empty) {
            break;
        }
        result res;
        res.stm = p;
        clock_t startTime = clock();

        allCompletedTask++;
        res.determinant = determinantOfMatrix(p.matrix, p.n);
        res.mistake = false;
        res.timeExecution = clock() - startTime;
        rt.executionTimeSolution += res.timeExecution;
        rt.numCompletedTask += 1;
        EnterCriticalSection(&csResult);
        arrayResult.push_back(res);
        LeaveCriticalSection(&csResult);
    }
    EnterCriticalSection(&csResultThread);
    threadResults.push_back(rt);
    LeaveCriticalSection(&csResultThread);
}

int main() {
    //1
    InitializeCriticalSection(&csParam);
    InitializeCriticalSection(&csResult);
    InitializeCriticalSection(&csResultThread);
    std::srand(time(nullptr));
    std::cout << "Number of parameter's set: ";
    std::cin >> taskCount;
    std::cout << "Number of threads: ";
    std::cin >> threadCount;

    //2
    for (unsigned i(0); i < taskCount; i++) {
        stMatrix p;
        p.n = rand() % 11 + 1;
        p.matrix = new int* [p.n];
        for (int k = 0; k < p.n; k++) {
            p.matrix[k] = new int[p.n];
            for (int j = 0; j < p.n; j++)
                p.matrix[k][j] = rand() % 10 + 1;
        }
        arrayParams.push(p);
    }

    //3
    auto* threads = new std::thread[threadCount];
    for (unsigned i = 0; i < threadCount; i++) {
        threads[i] = std::thread(threadMain);
    }
    for (unsigned i = 0; i < threadCount; i++) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }

    //4
    clock_t start = clock();
    std::ofstream final("final result out.txt");
    for (unsigned k = 0; k < taskCount; k++) {
        final << k + 1 << ". Size: " << arrayResult[k].stm.n << "\nMatrix: \n";
        for (unsigned i = 0; i < arrayResult[k].stm.n; i++) {
            for (unsigned j = 0; j < arrayResult[k].stm.n; j++)
                final << arrayResult[k].stm.matrix[i][j] << " ";
            final << "\n";
        }
        final << "Determinant: ";
        if (arrayResult[k].mistake)
            final << "-";
        else
            final << arrayResult[k].determinant << "\n";
        final<<std::endl;
    }
    final.close();
    writingTime = (clock() - start);

    //5
    std::sort(threadResults.begin(), threadResults.end(), [](resultThread a, resultThread b)->bool {
        return a.executionTimeSolution > b.executionTimeSolution;
    });
    std::cout << "\nTasks were completed: " << allCompletedTask
              << "\nTasks weren't completed because of calculation error: " << notCompletedTaskCalculationError
              << "\nTasks didn't have solutions: " << hasNoSolutions << "\n\n";
    for (unsigned i = 0; i < threadCount; i++) {
        std::cout << i + 1<< " thread completed " << threadResults[i].numCompletedTask
                  << " tasks, it's execution time: " << threadResults[i].executionTimeSolution << " ms\n";
    }
    std::cout << "\nMaximum execution time: " << threadResults[0].executionTimeSolution
              << " ms\nMaximum execution time: " << threadResults[threadResults.size() - 1].executionTimeSolution
              << " ms\nTime for writing in file: " << writingTime << " ms\n";
    return 0;
}
