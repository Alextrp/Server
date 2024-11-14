#include "Matrix.h"
#include <iostream>
#include <thread>
#include <chrono>

Matrix::Matrix(int size) : size(size), matrix(size, std::vector<int>(size, 0)) {}


bool Matrix::canApplyConfiguration(const Configurationn& config, int startX, int startY) const {
    for (const auto& pos : config.relative_positions) {
        int x = startX + pos.first;
        int y = startY + pos.second;
        if (x < 0 || x >= size || y < 0 || y >= size || matrix[x][y] > 0) {
            return false;
        }
    }
    return true;
}

int Matrix::matrixSize()
    const {
    return matrix.size();
}

void Matrix::applyConfiguration(const Configurationn& config, int startX, int startY) {
    for (const auto& pos : config.relative_positions) {
        int x = startX + pos.first;
        int y = startY + pos.second;
        if (x >= 0 && x < size && y >= 0 && y < size) {
            matrix[x][y] = 1024 / 128; // ������������� ����� ��������� � ������
        }
    }
}

void Matrix::updateCooldowns() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] > 0) {
                --matrix[i][j];
            }
        }
    }
}

void Matrix::display() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] == 8) {
                std::cout << "* ";
            }
            else if (matrix[i][j] > 0) {
                std::cout << "# ";
            }
            else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }
}
