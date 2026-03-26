#include <stdio.h>
#include <string.h>

int main() {
    int R;
    scanf("%d", &R);

    /* Vetor linear: R strings de tamanho m�ximo 61, lado a lado */
    char resultados[1000 * 61];
    int num_resultados = 0;

    for (int i = 0; i < R; i++) {
        char S[61];
        int F;
        scanf("%s %d", S, &F);

        int n = strlen(S);

        for (int c = 0; c < F; c++) {
            if (S[0] == 'X') S[0] = 'O';
            else S[0] = 'X';

            for (int j = 0; j < n - 1; j++) {
                if (S[j] == 'X') {
                    if (S[j+1] == 'X') S[j+1] = 'O';
                    else S[j+1] = 'X';
                } else {
                    break;
                }
            }
        }

        printf("%s\n", S);

        /* Copia S no vetor na posi��o i*61 */
        int base = i * 61;
        int k;
        for (k = 0; k < n; k++)
            resultados[base + k] = S[k];
        resultados[base + k] = '\0';

        num_resultados++;
    }

    /* Monta a luz gigante */
    char gigante[100000];
    int tam_gigante = 0;
    gigante[0] = '\0';

    for (int i = 0; i < num_resultados; i++) {
        int base = i * 61;

        if (i == 0) {
            int k;
            for (k = 0; resultados[base + k] != '\0'; k++)
                gigante[k] = resultados[base + k];
            gigante[k] = '\0';
            tam_gigante = k;
        } else {
            char ornamento;
            char ultimo  = gigante[tam_gigante - 1];
            char primeiro = resultados[base];

            if (tam_gigante % 2 == 0)
                ornamento = (ultimo == primeiro) ? '@' : '$';
            else
                ornamento = (ultimo == primeiro) ? '#' : '%';

            gigante[tam_gigante++] = ornamento;
            gigante[tam_gigante] = '\0';

            int k;
            for (k = 0; resultados[base + k] != '\0'; k++)
                gigante[tam_gigante + k] = resultados[base + k];
            gigante[tam_gigante + k] = '\0';
            tam_gigante += k;
        }
    }

    printf("%s\n", gigante);

    return 0;
}
