#include "../include/gauss.h"
#include "../include/mat_io.h"
#include <math.h>

int get_pivot_row_index(Matrix *m, int col_idx) {
    int max_idx = col_idx;
    double max_val = fabs(m->data[col_idx][col_idx]);

    for (int i = col_idx + 1; i < m->r; i++) {
        double current_val = fabs(m->data[i][col_idx]);
        if (current_val > max_val) {
            max_val = current_val;
            max_idx = i;
        }
    }
    return max_idx;
}

void swap_matrix_rows(Matrix *mA, Matrix *mB, int r1, int r2) {
    if (r1 == r2) return;

    for (int k = 0; k < mA->c; k++) {
        double tmp = mA->data[r1][k];
        mA->data[r1][k] = mA->data[r2][k];
        mA->data[r2][k] = tmp;
    }

    double tmp_b = mB->data[r1][0];
    mB->data[r1][0] = mB->data[r2][0];
    mB->data[r2][0] = tmp_b;
}

void subtract_scaled_row(Matrix *mA, Matrix *mB, int dest_row, int src_row, double factor) {
    for (int k = 0; k < mA->c; k++) {
        mA->data[dest_row][k] -= factor * mA->data[src_row][k];
    }
    mB->data[dest_row][0] -= factor * mB->data[src_row][0];
}

int eliminate(Matrix *mat, Matrix *b) {
    for (int i = 0; i < mat->c - 1; i++) {
        int pivot_row = get_pivot_row_index(mat, i);

        if (fabs(mat->data[pivot_row][i]) < 1e-12) {
            return 1;
        }

        swap_matrix_rows(mat, b, i, pivot_row);

        double pivot_val = mat->data[i][i];

        for (int k = i + 1; k < mat->r; k++) {
            if (mat->data[k][i] != 0.0) {
                double factor = mat->data[k][i] / pivot_val;
                subtract_scaled_row(mat, b, k, i, factor);
            }
        }
    }

    if (fabs(mat->data[mat->r - 1][mat->c - 1]) < 1e-12) {
        return 1;
    }

    return 0;
}