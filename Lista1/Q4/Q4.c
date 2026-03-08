#include <stdio.h>

int main() {
    int x, y, c, quadrante_atual;
    scanf("%d %d %d", &x, &y, &c);

    if (x > 0 && y > 0){
        quadrante_atual = 1;
    } else if (x < 0 && y > 0){
        quadrante_atual = 2;
    } else if (x < 0 && y < 0){
        quadrante_atual = 3;
    } else {
        quadrante_atual = 4;
    }

    // se o quadrante que é pra evitar for o mesmo em que mário começa ou o quadrante final (na diagonal do inicial), caminhada inválida
    if (c == quadrante_atual || c == (quadrante_atual + 2) || c == (quadrante_atual - 2)){
        printf("caminhada invalida");
    } else {
        // caso o quadrante atual seja 1, existem duas possibilidades: evitar o quadrante 2 ou 4
        if (quadrante_atual == 1){
            if (c == 2){
                y += 1;
                x += 1;
                printf("%d passos em y e %d passos em x", y, x);
            } else if (c == 4){
                y += 1;
                x += 1;
                printf("%d passos em x e %d passos em y", x, y);
            }
        } else if (quadrante_atual == 2){
            if (c == 1){
                y += 1;
                x = 1 - x;
                printf("%d passos em y e %d passos em x", y, x);
            } else if (c == 3){
                y += 1;
                x = 1 - x;
                printf("%d passos em x e %d passos em y", x, y);
            }
        }  else if (quadrante_atual == 3){
            if (c == 4){
                y = 1 - y;
                x = 1 - x;
                printf("%d passos em y e %d passos em x", y, x);
            } else if (c == 2){
                y = 1 - y;
                x = 1 - x;
                printf("%d passos em x e %d passos em y", x, y);
            }
        }    else if (quadrante_atual == 4){
            if (c == 3){
                y = 1 - y ;
                x += 1;
                printf("%d passos em y e %d passos em x", y, x);
            } else if (c == 1){
                y = 1 - y;
                x += 1;
                printf("%d passos em x e %d passos em y", x, y);
            }
        }
    }

    return 0;
}