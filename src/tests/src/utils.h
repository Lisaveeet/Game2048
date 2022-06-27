#ifndef UTILS_H
#define UTILS_H

#include <stdexcept>
#include <random>
#include <vector>
#include <time.h>

struct Utils {

    static int randInt(int min, int max) {
        std::mt19937 gen(time(NULL));

        return std::uniform_int_distribution<int>(min, max)(gen);
    }

    static void rotateMatrix(std::vector<std::vector<int>>& mat, int count) {
        int w = mat[0].size();
        for (int i = 1; i < mat.size(); ++i)
        {
            if (w != mat[i].size())
                throw std::runtime_error("Invalid matrix given! Matrix need to be square (NxN)");
        }

        if (w != mat.size())
            throw std::runtime_error("Invalid matrix given! Matrix need to be square (NxN)");

        int N = mat.size();
        count = abs(count) % 4;

        for (int i = 0; i < count; i++) {

            for (int x = 0; x < N / 2; x++) {
                for (int y = x; y < N - x - 1; y++) {
                    int temp = mat[x][y];
                    mat[x][y] = mat[y][N - 1 - x];
                    mat[y][N - 1 - x] = mat[N - 1 - x][N - 1 - y];
                    mat[N - 1 - x][N - 1 - y] = mat[N - 1 - y][x];
                    mat[N - 1 - y][x] = temp;
                }
            }

        }
    }

};
#endif // UTILS_H
