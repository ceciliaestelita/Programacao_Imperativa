#include <stdio.h>

int main(){
    long long n, a, b;
    scanf("%lld", &n);
    scanf("%lld%lld", &a, &b);

    // princípio da inclusão-exclusão: Soma total - Soma dos múltiplos de A - Soma dos múltiplos de B + Soma dos múltiplos de A e B
    // soma de gauss de todos os números entre 1 e n
    long long soma = (n * (n + 1))/2;

    // soma de gauss dos múltiplos de a
    long long soma_a = a * ((n/a) * ((n/a) + 1)) / 2;

    // soma de gauss dos múltiplos de b
    long long soma_b = b * ((n/b)  * ((n/b)  + 1)) / 2;

    // soma de gauss dos múltiplos de a e b
    long long ab = a * b;
    long long soma_ab = ab * ((n/ab) * ((n/ab) + 1)) / 2;

    long long total = soma - soma_a - soma_b + soma_ab;

    printf("%lld\n", total);

    if (total % 2 == 0){
        printf("Lá ele!!!\n");
    } else {
        printf("Opa xupenio AULAS...");
    }

    return 0;
}
