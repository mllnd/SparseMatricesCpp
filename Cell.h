#pragma once
//#include "SparseMatrix.h"
class Cell {
    public:
        Cell();
    private:
        Cell* next_cell_row;
        Cell* next_cell_col;
        int value;
        int row_id;
        int col_id;
        void setRowId(const int row);
        void setColId(const int col);
        void setValue(const double &val);
        friend class SparseMatrix;
};