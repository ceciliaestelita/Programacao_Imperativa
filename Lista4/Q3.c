#include <stdio.h>

int cidade[4][4];
int lin = 0, col = 0;       // posição inicial

void mover() {          // lê os 20 movimentos e incrementa a posição      
    char mov;
    int i;

    for (i = 0; i < 20; i++) {
        scanf(" %c", &mov);

        // incrementa a posição
        if (mov == 'c' && lin > 0) lin--;        // cima: diminui a linha
        else if (mov == 'b' && lin < 3) lin++;   // baixo: aumenta linha
        else if (mov == 'e' && col > 0) col--;   // esquerda: diminui coluna
        else if (mov == 'd' && col < 3) col++;   // direita: aumenta coluna

        cidade[lin][col]++;  // conta a visita nessa célula
    }
}

int max_linha = 0, max_col = 0;


void busca_max() {       // percorre a matriz inteira e armazena a cidade mais visitada
    int valor_max = 0;   // quantidade de visitas
    int l, c;

    for (l = 0; l < 4; l++) {
        for (c = 0; c < 4; c++) {
            if (cidade[l][c] > valor_max) {     // verifica se a cidade atual tem mais visitas que o valor máximo, se sim, atualiza o valor máximo pra a quantidade de visitas daquela cidade
                valor_max = cidade[l][c];
                max_linha = l;                  // atualiza a linha e a coluna do valor máximo
                max_col = c;
            }
        }
    }
}

int main() {
    cidade[lin][col]++;  // conta a posição (0,0)

    mover();          // lê os movimentos e preenche a matriz
    busca_max();      // encontra a célula mais visitada

    printf("Coordenada X:%d, Y:%d\n", max_col, max_linha);

    return 0;
}