#include <stdio.h>

int cidade[4][4];
int lin = 0, col = 0;

void mover() {
    char mov;
    int i;
    int moveu;

    for (i = 0; i < 20; i++) {
        scanf(" %c", &mov);

        moveu = 1;  // assume que o movimento é válido

        if      (mov == 'c' && lin > 0) lin--;
        else if (mov == 'b' && lin < 3) lin++;
        else if (mov == 'e' && col > 0) col--;
        else if (mov == 'd' && col < 3) col++;
        else moveu = 0;  // movimento inválido, não conta

        if (moveu) cidade[lin][col]++;  // só incrementa se moveu
    }
}

int max_linha = 0, max_col = 0;

void busca_max() {
    int valor_max = -1;
    int l, c;

    for (l = 0; l < 4; l++) {
        for (c = 0; c < 4; c++) {
            if (cidade[l][c] > valor_max) {
                valor_max = cidade[l][c];
                max_linha = l;
                max_col   = c;
            }
        }
    }
}

int main() {
    mover();
    busca_max();

    printf("Coordenada X:%d, Y:%d\n", max_col, max_linha);

    return 0;
}
