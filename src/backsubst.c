#include "../include/backsubst.h"

int backsubst(Matrix *x, Matrix *mat, Matrix *b) {
    if (mat->r != mat->c || mat->r != b->r || mat->r != x->r || b->c != 1 || x->c != 1) {
        return 2;
    }

    int i;
    for (i = mat->r - 1; i >= 0; i--) {
        if (mat->data[i][i] == 0) {
            return 1;
        }

        // POPRAWKA: Inicjalizujemy x wartością z b dla tego wiersza
        x->data[i][0] = b->data[i][0];

        for (int j = i + 1; j < mat->c; j++) {
            x->data[i][0] -= mat->data[i][j] * x->data[j][0];
        }
        
        x->data[i][0] /= mat->data[i][i];
    }
    return 0;
}