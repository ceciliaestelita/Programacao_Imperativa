#include <stdio.h>

int main() {
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);

    int primeiro = -1; // armazena o primeiro num que satisfaz, começa com -1 pq não está dentro do intervalo [n,k)
    int q = 0;         // contador dos números que vêm depois do primeiro

    // percorre o intervalo [n,k)
    for (int i = n; i < k; i++) {
        // números menores que 2 não têm fatores primos
        // Se p for 0, 0 ou 1 poderia valer, mas primos são a partir de 2
        if (i < 2) {
            if (p == 0) { 
                if (primeiro == -1){
                    primeiro = i;
                }
                else{
                    q++;
                }
            }
            continue;
        }

        int num = i;           // cópia do valor de i para fatorar sem sobrescrever i
        int cont_impares = 0;  
        int valido = 1;        // se tiver fatores primos ímpares que se repetem, não é válido

        // se o número for par, tira todos os 2 pra sobrar só a parte ímpar do número
        while (num > 0 && num % 2 == 0) {
            num /= 2;
        }

        // começa do 3 e vai só pelos ímpares (d += 2)
        // d * d <= num é a fatoração
        for (int d = 3; d * d <= num; d += 2) {
            if (num % d == 0) {
                cont_impares++; 
                num /= d;       // divide uma vez.

                // se depois de dividir uma vez, ele AINDA for divisível por d, tem fatores primos repetidos e não é válido
                if (num % d == 0) {
                    valido = 0; 
                    break;      // para de testar esse número i e pula pro próximo
                }
            }
        }

        if (valido && num > 1) {
            cont_impares++;
        }

        // verificação final
        if (valido && cont_impares == p) {
            if (primeiro == -1) { // não teve dentro do intervalo
                primeiro = i;
            } else {
                q++;
            }
        }
    }

    if (primeiro == -1) {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    } else {
        printf("%d %d\n", primeiro, q);
    }

    return 0;
}