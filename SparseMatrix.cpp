#include "SparseMatrix.h"
#include <iostream>
#include <stdlib.h>


/**
 * Class constructor
 * @param row_size
 * @param col_size
 */
SparseMatrix::SparseMatrix(const int row_size, const int col_size) {
    wrapper(row_size, col_size);
}

/**
 * Constructor for copying
 * @param SparseMatrix
 */
SparseMatrix::SparseMatrix(const SparseMatrix &base) {
    row_size = base.row_size;
    col_size = base.col_size;
    wrapper(row_size, col_size);
    for (int i = 0; i < col_size; i++) {
        for (int j = 0; j < row_size; j++) {
            this->addValue(base.getElement(i, j), i, j);
        }
    }
}

/**
 * Class destructor
 */
SparseMatrix::~SparseMatrix() {
    Cell* temp = cell_pointer->next_cell_row;
    for (int i = 0; i < row_size; i++) {
        Cell* printer = temp->next_cell_col;
        while (printer != temp) {
            Cell* temp2 = printer->next_cell_col;
            delete(printer);
            printer = temp2;
        }
        Cell* remove_counter = temp->next_cell_row;
        delete(temp);
        temp = remove_counter;
    }
    temp = temp->next_cell_col;
    while (temp != cell_pointer) {
        Cell* temp2 = temp->next_cell_col;
        delete(temp);
        temp = temp2;
    }
    delete(cell_pointer);
}

/**
 * Get the size of columns
 * @return integer
 */
int SparseMatrix::getSizeCols() {
    return col_size;
}

/**
 * Get the size of rows
 * @return integer
 */
int SparseMatrix::getSizeRows() {
    return row_size;
}

/**
 * Add value to matrix
 * @param integer
 * @param integer
 * @param integer
 */
void SparseMatrix::addValue(const int value, const int row, const int col) {
    if (row > col_size || col > row_size || row < 0 || col < 0) {
        throw "Error - matrix index out of bounds!";
    } else {
        // Skip zero values
        if (value != 0) {
            Cell* cell_to_add = new Cell();
            cell_to_add->col_id = col;
            cell_to_add->row_id = row;
            cell_to_add->value = value;
            Cell* previous_col = getPrevCol(row, col);
            cell_to_add->next_cell_col = previous_col->next_cell_col;
            previous_col->next_cell_col = cell_to_add;
            Cell* previous_row = getPrevRow(row, col);
            cell_to_add->next_cell_row = previous_row->next_cell_row;
            previous_row->next_cell_row = cell_to_add;
        }
    }
}

/**
 * Return the previous element in row
 * @param integer
 * @param integer
 * @return
 */
Cell* SparseMatrix::getPrevRow(int row, int col) {
    Cell* tracker = cell_pointer;
    Cell* temp = cell_pointer->next_cell_col;
    for (int i = 0; i < row; i++) {
        if (temp->next_cell_col != tracker) {
            temp = temp->next_cell_col;
        } else {
            break;
        }
    }
    tracker = temp;
    while (temp->next_cell_row != tracker) {
        if (temp->next_cell_row->row_id == row && temp->next_cell_row->col_id == col) {
            return temp;
        } else {
            temp = temp->next_cell_row;
        }
    }
}

/**
 * Return the previous element in column
 * @param integer
 * @param integer
 * @return
 */
Cell* SparseMatrix::getPrevCol(int row, int col) {
    Cell* tracker = cell_pointer;
    Cell* temp = cell_pointer->next_cell_row;
    for (int i = 0; i < col; i++) {
        if (temp->next_cell_row != tracker) {
            temp = temp->next_cell_row;
        }
    }
    tracker = temp;
    while (temp->next_cell_col != tracker) {
        if (temp->next_cell_col->row_id == row && temp->next_cell_col->col_id == col) {
            return temp;
        } else {
            temp = temp->next_cell_col;
        }
    }
}

/**
 * Standard print - print all values in the matrix
 */
void SparseMatrix::print() {
    Cell* temp = cell_pointer->next_cell_row;
    for (int i = 0; i < row_size; i++) {
        Cell* printer = temp->next_cell_col;
        std::cout << temp->value << " is pointing to " << temp->next_cell_col->value << "\n";
        while (printer != temp) {
            std::cout << printer->value << " is pointing to " << printer->next_cell_col->value << "\n";
            printer = printer->next_cell_col;
        }
        temp = temp->next_cell_row;
    }
}

/**
 * Print all non-empty (not zero) rows
 */
void SparseMatrix::printByRows() {
    Cell* temp = cell_pointer->next_cell_col;
    for (int i = 0; i < col_size; i++) {
        Cell* printer = temp->next_cell_row;
        while (printer != temp) {
            std::cout << "Location " << printer->row_id << ";" << printer->col_id << " -> " << printer->value << "\n";
            printer = printer->next_cell_row;
        }
        temp = temp->next_cell_col;
    }
}

/**
 * Print the whole matrix by utilizing the getElement method
 */
void SparseMatrix::printByGet() {
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++) {
            std::cout << "Location " << j << ";" << i << " -> " << getElement(j, i) << "\n";
        }
    }
}

/**
 * Retrieve a specific element from matrix
 * @param integer
 * @param integer
 * @return double
 */
double SparseMatrix::getElement(const int row, const int col) const {
    if (row > col_size || row < 0 || col > row_size || col < 0) {
        throw "Error while getting an element - index out of bounds!";
    } else {
        Cell* temp = cell_pointer->next_cell_row;
        for (int i = 0; i < col; i++) {
            temp = temp->next_cell_row;
        }
        Cell* iterator = temp->next_cell_col;
        while (iterator != temp) {
            if (iterator->row_id == row && iterator->col_id == col) {
                return iterator->value;
            }
            iterator = iterator->next_cell_col;
        }
        return 0;
    }
}
/**
 * Set a specific element in matrix
 * @param integer
 * @param integer
 * @param integer
 */
void SparseMatrix::setElement(int value, int row, int col) {
    if (row > col_size || col > row_size || row < 0 || col < 0) {
        throw "Error - Matrix index out of bounds!";
    } else {
        Cell* previous_col = getPrevCol(row, col);
        previous_col->next_cell_col->value = value;

    }
}

SparseMatrix& SparseMatrix::operator =(const SparseMatrix &sparse_matrix) {
    SparseMatrix *destruct = this;
    wrapper(sparse_matrix.row_size, sparse_matrix.col_size);
    for (int i = 0; i < col_size; i++) {
        for (int j = 0; j < row_size; j++) {
            this->addValue(sparse_matrix.getElement(i, j), i, j);
        }
    }
    return *this;
}

SparseMatrix& SparseMatrix::operator +=(const SparseMatrix &sparse_matrix) {
    if (row_size != sparse_matrix.row_size || col_size != sparse_matrix.col_size) {
        throw "Error during addition - matrices have different dimensions!";
    } else {
        for (int i = 0; i < col_size; i++) {
            for (int j = 0; j < row_size; j++) {
                int value_in_this = this->getElement(i, j);
                int value_in_right_operand = sparse_matrix.getElement(i, j);
                if (value_in_this == 0) {
                    this->addValue(value_in_right_operand, i, j);
                } else {
                    int value_to_add = value_in_this + value_in_right_operand;
                    if (value_to_add == 0) {
                        this->removeElement(i, j);
                    } else {
                        this->setElement(value_to_add, i, j);
                    }
                }
            }
        }
    }
    return *this;
}

SparseMatrix& SparseMatrix::operator -=(const SparseMatrix& sparse_matrix) {
    if (row_size != sparse_matrix.row_size || col_size != sparse_matrix.col_size) {
        throw "Error during addition, matrices have different dimensions!";
    } else {
        for (int i = 0; i < col_size; i++) {
            for (int j = 0; j < row_size; j++) {
                if (this->getElement(i, j) == 0) {
                    this->addValue(-sparse_matrix.getElement(i, j), i, j);
                } else {
                    int value_to_add = this->getElement(i, j) - sparse_matrix.getElement(i, j);
                    if (value_to_add == 0) {
                        this->removeElement(i, j);
                    } else {
                        this->setElement(value_to_add, i, j);
                    }
                }
            }
        }
    }
    return *this;
}

SparseMatrix& SparseMatrix::operator *=(const SparseMatrix& sparse_matrix) {
    if (row_size != sparse_matrix.col_size) {
        throw "Error, Matrices can not be multiplied!";
    } else {
        int counter = 0;
        SparseMatrix new_matrix(col_size, sparse_matrix.row_size);
        for (int i = 0; i < col_size; i++) {
            for (int j = 0; j < sparse_matrix.row_size; j++) {
                for (int k = 0; k < row_size; k++) {
                    counter += getElement(i, k) * sparse_matrix.getElement(k, j);
                }
                new_matrix.addValue(counter, j, i);
                counter = 0;
            }
        }
        *this = new_matrix;
        return *this;
    }
}

void SparseMatrix::operator ^(const int number) {
    for (int i = 0; i < col_size; i++) {
        for (int j = 0; j < row_size; j++) {
            this->setElement(this->getElement(i, j)*number, i, j);
        }
    }
}

SparseMatrix SparseMatrix::operator !() {
    SparseMatrix new_matrix(col_size, row_size);
    for (int i = 0; i < col_size; i++) {
        for (int j = 0; j < row_size; j++) {
            new_matrix.addValue(this->getElement(i, j), j, i);
        }
    }
    return new_matrix;
}

/**
 * Remove a specific element from matrix
 * @param integer
 * @param integer
 */
void SparseMatrix::removeElement(int row, int col) {
    Cell* previous_col = getPrevCol(row , col);
    Cell* previous_row = getPrevRow(row, col);
    Cell* cell_to_remove = previous_col->next_cell_col;
    previous_col->next_cell_col = cell_to_remove->next_cell_col;
    previous_row->next_cell_row = cell_to_remove->next_cell_row;
    cell_to_remove->next_cell_col = nullptr;
    cell_to_remove->next_cell_row = nullptr;
    delete(cell_to_remove);
}


/**
 * Initialize the matrix
 * @param integer
 * @param integer
 */
void SparseMatrix::wrapper(int row_size, int col_size) {
    this->row_size = row_size;
    this->col_size = col_size;
    cell_pointer = new Cell;
    cell_pointer->row_id = -1;
    cell_pointer->col_id = -1;
    int row_tracker = -1;
    int col_tracker = -1;
    Cell* temp;
    temp = cell_pointer;
    for (int i = 0; i < row_size; i++) {
        col_tracker++;
        temp->next_cell_row = new Cell;
        temp->next_cell_row->row_id = row_tracker;
        temp->next_cell_row->col_id = col_tracker;
        temp->next_cell_row->next_cell_col = temp->next_cell_row;
        temp = temp->next_cell_row;
    }
    temp->next_cell_row = cell_pointer;
    temp = cell_pointer;
    col_tracker = -1;
    for (int i = 0; i < col_size; i++) {
        row_tracker++;
        temp->next_cell_col = new Cell;
        temp->next_cell_col->row_id = row_tracker;
        temp->next_cell_col->col_id = col_tracker;
        temp->next_cell_col->next_cell_row = temp->next_cell_col;
        temp = temp->next_cell_col;
    }
    temp->next_cell_col = cell_pointer;
}

bool operator ==(SparseMatrix &matrix_1, SparseMatrix &matrix_2){
    if (matrix_1.getSizeCols() != matrix_2.getSizeCols() || matrix_1.getSizeRows() != matrix_2.getSizeRows()) {
        return false;
    } else {
        for (int i = 0; i < matrix_1.col_size; i++) {
            for (int j = 0; j < matrix_1.row_size; j++) {
                if (matrix_1.getElement(i, j) != matrix_2.getElement(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }
}

SparseMatrix operator +(SparseMatrix &matrix_1, SparseMatrix &matrix_2) {
    if (matrix_1.col_size != matrix_2.col_size || matrix_1.row_size != matrix_2.row_size) {
        throw "Error while adding matrices, incompatible dimensions";
    } else {
        SparseMatrix toReturn(matrix_1.row_size, matrix_1.col_size);
        for (int i = 0; i < matrix_1.col_size; i++) {
            for (int j = 0; j < matrix_1.row_size; j++) {
                int value_to_add = matrix_1.getElement(i, j) + matrix_2.getElement(i, j);
                toReturn.addValue(value_to_add, i, j);
            }
        }
        return toReturn;
    }
}

SparseMatrix operator -(SparseMatrix &matrix_1, SparseMatrix &matrix_2) {
    if (matrix_1.col_size != matrix_2.col_size || matrix_1.row_size != matrix_2.row_size) {
        throw "Error while adding matrices, incompatible dimensions";
    } else {
        SparseMatrix toReturn(matrix_1.row_size, matrix_1.col_size);
        for (int i = 0; i < matrix_1.col_size; i++) {
            for (int j = 0; j < matrix_1.row_size; j++) {
                int value_to_add = matrix_1.getElement(i, j) - matrix_2.getElement(i, j);
                toReturn.addValue(value_to_add, i, j);
            }
        }
        return toReturn;
    }
}

SparseMatrix operator *(SparseMatrix &matrix_1, SparseMatrix &matrix_2) {
    if (matrix_1.row_size != matrix_2.col_size) {
        throw "Error, Matrices can not be multiplied";
    } else {
        int counter = 0;
        SparseMatrix toReturn(matrix_1.col_size, matrix_2.row_size);
        for (int i = 0; i < matrix_1.col_size; i++) {
            for (int j = 0; j < matrix_2.row_size; j++) {
                for (int k = 0; k < matrix_1.row_size; k++) {
                    counter += matrix_1.getElement(i, k)*matrix_2.getElement(k, j);
                }
                toReturn.addValue(counter, j, i);
                counter = 0;
            }
        }
        return toReturn;
    }
}

ostream& operator <<(ostream &os, const SparseMatrix &matrix_1) {
    for (int i = 0; i < matrix_1.col_size; i++) {
        for (int j = 0; j < matrix_1.row_size; j++) {
            os << matrix_1.getElement(i, j) << " is the value on position " << i << ";" << j << "\n\n";
        }
    }
    return os;
}

istream& operator >>(istream &is, SparseMatrix &matrix_1) {
    for (int i = 0; i < matrix_1.getSizeCols(); i++) {
        for (int j = 0; j < matrix_1.getSizeRows(); j++) {
            std::cout << "Enter integer value for position (" << i << ";" << j << ")";
            int value;
            is >> value;
            matrix_1.addValue(value, i, j);
        }
    }
    return is;
}