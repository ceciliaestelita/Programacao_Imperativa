#include <stdio.h>

int main(){
    int n, a, b;
    scanf("%d", &n);
    scanf("%d%d", &a, &b);

    // princípio da inclusão-exclusão: Soma total - Soma dos múltiplos de A - Soma dos múltiplos de B + Soma dos múltiplos de A e B
    // soma de gauss de todos os números entre 1 e n
    int soma = (n * (n + 1))/2;

    // soma de gauss dos múltiplos de a
    int soma_a = a * ((n/a) * ((n/a) + 1)) / 2;

    // soma de gauss dos múltiplos de b
    int soma_b = b * ((n/b)  * ((n/b)  + 1)) / 2;

    // soma de gauss dos múltiplos de a e b
    int ab = a * b;
    int soma_ab = ab * ((n/ab) * ((n/ab) + 1)) / 2;

    int total = soma - soma_a - soma_b + soma_ab;

    printf("%d\n", total);

    if (total % 2 == 0){
        printf("Lá ele!!!\n");
    } else {
        printf("Opa xupenio AULAS...");
    }

    return 0;
}
