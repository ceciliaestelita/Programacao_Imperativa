#include <stdio.h>
int main(){
    int q, x;
    char c;
    int coluna = 0; // posi??o horizontal atual do cursor
    char mov = ' ';
    char mov_anterior;

    scanf("%d", &q);

    // percorre de 0 at? a quantidade q de instru??es, pedindo os valores de x e c
    for (int i = 0; i < q; i++){
        scanf("%d %c", &x, &c);
        // se a instru??o for pra direita, come?a do zero e enquanto n?o tiver andado a quantidade de passos, continua dando passos
        if (c == 'D'){
            int flag = 0;
            for (int j = 0; j < coluna; j++){
                printf(" ");
                flag = 1;
            }
            if (mov == 'B' && q == 2){
                flag = 1;
            }
            for (int j = 0; j < x + flag; j++){
                printf(".");
                coluna++; // vai aumentando o n?mero da coluna atual a medida que vai dando os passos
            } 
            mov = 'D';
        }
        // se a instru??o for pra esquerda, come?a do zero e enquanto n?o tiver andado a quantidade de passos, continua dando passos
        else if (c == 'E'){
            if (x > coluna){ // pra n?o dar erro caso o n?mero de passos seja maior que o de colunas
                printf("Informacao invalida");
                return 0;
            }
            else{
                //printf("%d %d\n", x, coluna);
                int flag = 0;
                for (int j = 0; j < coluna - x - 1; j++){
                    printf(" ");        // imprime os espa?os antes dos pontos
                    flag = 1;
                }
                for (int j = 0; j < x + flag; j++){
                    printf(".");
                    coluna--; // vai diminuindo o valor da coluna a medida que vai dando os passos
                }
            }
            mov = 'E';
        }
        // se a instru??o for pra baixo, come?a do zero e enquanto n?o tiver andado a quantidade de passos, continua dando passos
        else if (c == 'B'){
            if (mov == ' ' && q != 2){
                printf(".");
            } 
            if (mov != 'E'){
                for (int j = 0; j < x - 1; j++){
                    printf("\n"); // desce de linha
                    for (int k = 0; k < coluna - 1; k++){ // come?a do zero e enquanto n?o tiver atingido o n?mero da coluna que vai ser printado o ponto, vai dando espa?o
                        printf(" "); 
                    }
                    printf(".");              
                } 
            } else {
                    for (int j = 0; j < x - 1; j++){
                    printf("\n"); // desce de linha
                    for (int k = 0; k < coluna ; k++){ // come?a do zero e enquanto n?o tiver atingido o n?mero da coluna que vai ser printado o ponto, vai dando espa?o
                        printf(" "); 
                    }
                    printf(".");              
                } 
            }
            if (mov == 'D'){ // define o movimento que foi feito antes do movimento ser o B
                mov_anterior = 'D';
            }
            printf("\n");
            mov = 'B';
        } 
    }
    if (q > 1){
        if (mov == 'B' && mov_anterior == 'D'){
            for (int a = 0; a < coluna - 1; a++){
                printf(" ");
            } printf(".");
        }
    }

    printf("\n");
    return 0;
}
