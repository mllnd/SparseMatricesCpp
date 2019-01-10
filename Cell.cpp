#include "Cell.h"
#include <iostream>

Cell::Cell() {
    next_cell_col = nullptr;
    next_cell_row = nullptr;
    row_id = NULL;
    col_id = NULL;
    value = NULL;
}

void Cell::setRowId(const int row) {
    row_id = row;
}

void Cell::setColId(const int col) {
    col_id = col;
}

void Cell::setValue(const double &val) {
    value = val;
}