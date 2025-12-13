#include "../include/gauss.h"
#include "../include/mat_io.h"

#include <stdbool.h>
#include <math.h>

#define MIN(A,B) (A < B ? A : B)

int find_biggest_in_col(Matrix *mat, const int c, const int start_row) {
    if (mat->r <= start_row) return -1;

    int biggest_index = start_row;
    for (int r = start_row + 1; r < mat->r; r++) {
        if (fabs(mat->data[r][c]) > fabs(mat->data[biggest_index][c])) {
            biggest_index = r;
        }
    } 
    return biggest_index;
}

void swap_rows(Matrix *mat, const int r1, const int r2) {
    if (r1 == r2 || r1 < 0 || r2 < 0) return; 

    double *temp = mat->data[r1];
    mat->data[r1] = mat->data[r2];
    mat->data[r2] = temp;
}

void apply_operation(Matrix *mat, Matrix *b, const int from, const int to, const double k) {
    for (int c = 0; c < mat->c; c++) {
        mat->data[to][c] -= mat->data[from][c] * k;
    }
    b->data[to][0] -= b->data[from][0] * k;
}

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
        for (int c = 0; c < mat->c - 1; c++) {
            // start_row is the same as c bcs rows above are already handled
            swap_rows(mat, c, find_biggest_in_col(mat, c, c));

            for (int r = c + 1; r < mat->r; r++) {
                const double pivot = mat->data[c][c];
                // can't divide by 0
                if (pivot == 0.0) {
                    return 1;
                }
                // mnożnik
                const double k = mat->data[r][c] / pivot;
                apply_operation(mat, b, c, r, k);
            }

        }
        if (mat->data[mat->r - 1][mat->c - 1] == 0) {
            return 1;
        }

		return 0;
}
