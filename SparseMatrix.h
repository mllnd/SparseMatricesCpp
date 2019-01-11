#pragma once
#include "Cell.h"
#include <iostream>

using namespace std;

class SparseMatrix {
    public:
        SparseMatrix(const int row_size, const int col_size);
        SparseMatrix(const SparseMatrix &base);
        ~SparseMatrix();
        void print();
        void printByRows();
        void printByGet();
        void addValue(const int value, const int row, const int col);
        double getElement(const int row, const int col) const;
        int getSizeRows();
        int getSizeCols();
        void setElement(int value,int row, int col);
        SparseMatrix& operator =(const SparseMatrix &sparse_matrix);
        SparseMatrix& operator +=(const SparseMatrix &sparse_matrix);
        SparseMatrix& operator -=(const SparseMatrix &sparse_matrix);
        SparseMatrix& operator *=(const SparseMatrix &sparse_matrix);
        void operator ^(const int number);
        SparseMatrix operator !();
        friend bool operator ==(SparseMatrix &matrix_1, SparseMatrix &matrix_2);
        friend SparseMatrix operator +(SparseMatrix &matrix_1, SparseMatrix &matrix_2);
        friend SparseMatrix operator -(SparseMatrix &matrix_1, SparseMatrix &matrix_2);
        friend SparseMatrix operator *(SparseMatrix &matrix_1, SparseMatrix &matrix_2);
        friend ostream& operator <<(ostream &os, const SparseMatrix &matrix_1);
        friend istream& operator >>(istream &is, SparseMatrix &matrix_1);
    private:
        int row_size;
        int col_size;
        Cell* cell_pointer;
        void wrapper(int row_size, int col_size);
        Cell* getPrevCol(int row, int col);
        Cell* getPrevRow(int row, int col);
        void removeElement(int row, int col);
};