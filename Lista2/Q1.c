#include <stdio.h>

int main(){
    char letra;
    scanf("%c", &letra);
    int h = letra; //altura do triângulo
    h -= 64; // A = 65 na tabela ascii, então, defini A = 1, B = 2...
    
    // loop em que a quantidade de pontos = altura do triângulo - 1 (da base do triângulo, que não tem pontos) - i (a cada linha, diminui em 1 a quantidade de pontos de cada lado das letras)
    for (int i = 0; i < h; i++) {

        for (int j = 0; j < (h - 1 - i); j++) {
            printf(".");
        }
        
        // printa o primeiro A e vai printando as próximas letras até a letra chegar na letra que definiu a altura da pirâmide
        for (char j = 'A'; j < 'A' + i; j++) {
            printf("%c", j);
        }
        
        // printa a letra que vem antes da letra que definiu a altura e vai printando de trás pra frente até chegar em A
        for (char j = 'A' + i; j >= 'A'; j--) {
            printf("%c", j);
        }

        for (int j = 0; j < (h - 1 - i); j++) {
            printf(".");
        }

        printf("\n");
    }

    return 0;
}

