#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "Configuration.h"

class Matrix {
public:
    Matrix(int size);
    bool canApplyConfiguration(const Configurationn& config, int startX, int startY) const;
    void applyConfiguration(const Configurationn& config, int startX, int startY);
    void updateCooldowns();
    int matrixSize() const;
    void display() const;
    std::vector<std::vector<int>> matrix;

private:
    int size;
        // ������� �����������

};

#endif // MATRIX_H
