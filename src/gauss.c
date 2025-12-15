#include "../include/gauss.h"
#include "../include/mat_io.h"

#include <stdbool.h>

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
