#include <iostream>
#include "SparseMatrix.h"
#include "Cell.h"
#include <ctime>

int main() {
    /* Test the functionality */
    int row_size = 5;
    int col_size = 6;
    srand(time(0));
    SparseMatrix matrix = SparseMatrix(row_size, col_size);
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++) {
            int value = rand() % 2;
            try {
                std::cout << "Adding value: " << value << "\n";
                matrix.addValue(value, i, j);
            } catch (char const *error) {
                std::cerr << error << std::endl;
            }
        }
    }
    matrix.print();
    return 0;
}