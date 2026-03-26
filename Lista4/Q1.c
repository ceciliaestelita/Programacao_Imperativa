#include <stdio.h>

int m, n;
char parede[100][100];

void escorrer(int linha, int col, int direcao);         // declara uma função que vai ser definida 

void cair(int linha, int col) {                         // função de printar 'o' na mesma coluna nas linhas abaixo 
    int i = linha;                                      // linha inicial
    while (i + 1 < m && parede[i + 1][col] != '#') {    // enquanto a próxima linha não for a última linha e a próxima posição na coluna for diferente de #, incrementa o valor da linha
        i++;
    }
    for (int k = linha; k <= i; k++) {                  // percorre as linhas e vai preenchendo com 'o' 
        parede[k][col] = 'o';                            
    }
    if (i + 1 < m && parede[i + 1][col] == '#') {       // se a próxima linha for antes da última e a posição da coluna for #, então chama a função de escorrer
        escorrer(i + 1, col, -1);                       // 
        escorrer(i + 1, col, +1);
    }
}

void escorrer(int linha, int col, int direcao) {        // função que faz os 'o' ficarem espalhados na linha acima dos #
    int c = col;                                        

    while (c >= 0 && c < n && parede[linha][c] == '#') {   // enquanto não for a primeira coluna nem a última e tiver # , volta pra linha anterior e coloca 'o'
        parede[linha - 1][c] = 'o'; 
        c += direcao;
    }

    if (c > -1 && c < n) {                              // cai pras bordas
        parede[linha - 1][c] = 'o';
        cair(linha - 1, c);
    }
}

int main() {
    scanf("%d %d", &m, &n);         // pede o tamanho da matriz
    for (int i = 0; i < m; i++)     // vai preenchendo a primeira linha
        scanf("%s", parede[i]);

    int col_inicial = -1;
    for (int j = 0; j < n; j++) {   //vai preenchendo o resto da matriz
        if (parede[0][j] == 'o') {  // define qual é a coluna que tem o primeiro 'o'
            col_inicial = j;
            break;
        }
    }

    cair(0, col_inicial);           // chama a função de cair pra a primeira linha e a coluna que tem o 'o'

    for (int i = 0; i < m; i++)     // vai printando cada linha
        printf("%s\n", parede[i]);

    return 0;
}
