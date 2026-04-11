#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double calcMedia(double *notas, int n) {    // pega os valores das notas e a quantidade de alunos
    double soma = 0;
    for (int i = 0; i < n; i++){    // percorre todos os alunos e vai somando as notas de cada
        soma += notas[i];
    }
    return soma / n;     // retorna a média
}

void calcMaior(double *notas, int n, double *maior, int *idx) {     // pega os valores das notas, a quantidade de alunos, o valor da maior nota e o indice
    *maior = notas[0];      // define a maior nota como a primeira (única) nota do vetor e a quantidade indices = 1
    *idx = 1;    
    for (int i = 1; i < n; i++){    // percorre as notas e vai verificando se é maior que a maior nota do vetor, se for, atualiza a maior nota e muda o indice pra o indice da nova maior nota
        if (notas[i] > *maior){
            *maior = notas[i];
            *idx = i + 1; 
        }
    }
}

void calcMenor(double *notas, int n, double *menor, int *idx) {     // faz a mesma coisa do calcMaior, mas verifica se a nota é menor que a menor nota já registrada
    *menor = notas[0];
    *idx = 1;
    for (int i = 1; i < n; i++){
        if (notas[i] < *menor){
            *menor = notas[i];
            *idx = i + 1;
        }
    }
}

int calcAcima(double *notas, int n, double media) {     // pega o valor das notas, a quantidade de alunos e a média das notas
    int count = 0;
    for (int i = 0; i < n; i++){
        if (notas[i] > media){          // se a nota for acima da média, conta mais uma na quantidade de notas acima da média
            count++;
        }
    }
    return count;
}

void bubbleSort(double *arr, int n) {   // ordena o vetor em ordem crescente
    for (int i = 0; i < n - 1; i++){           // a cada passagem, o maior elemento vai pro final
        for (int j = 0; j < n - 1 - i; j++){  // a cada iteração, o trecho não ordenado diminui em 1
            if (arr[j] > arr[j + 1]){          // se o elemento atual for maior que o próximo, troca os dois
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

double calcMediana(double *notas, int n) {      
    double *copia = malloc(n * sizeof(double));
    memcpy(copia, notas, n * sizeof(double));   // copia o vetor original pra não alterar a ordem dos alunos
    bubbleSort(copia, n);                       // ordena só a cópia
    double med = (n % 2 == 1) ? copia[n/2] : (copia[n/2-1] + copia[n/2]) / 2.0;
    free(copia);
    return med;
}

void calcModa(double *notas, int n) {
    double *copia = malloc(n * sizeof(double));
    memcpy(copia, notas, n * sizeof(double));   // copia o vetor original pra não alterar a ordem dos alunos
    bubbleSort(copia, n);                       // ordena só a cópia

    int maxFreq = 1, freq = 1, modaCount = 0;
    double moda = copia[0];

    for (int i = 1; i < n; i++) {
        if (copia[i] == copia[i-1]) freq++;
        else freq = 1;
        if (freq > maxFreq) { maxFreq = freq; moda = copia[i]; modaCount = 0; }
        else if (freq == maxFreq && copia[i] != moda) modaCount++;
    }

    if (maxFreq == 1 || modaCount > 0){
        printf("Moda: Nao ha moda unica\n");
    } else {
        printf("Moda: %.2f\n", moda);
    }
    free(copia);
}

void relatorio(double *notas, int n) {
    double media = calcMedia(notas, n);
    double maior, menor;
    int idxMaior, idxMenor;
    calcMaior(notas, n, &maior, &idxMaior);
    calcMenor(notas, n, &menor, &idxMenor);
    int acima = calcAcima(notas, n, media);
    double mediana = calcMediana(notas, n);

    printf("Media: %.2f\n", media);
    printf("Maior nota: %.2f (aluno %d)\n", maior, idxMaior);
    printf("Menor nota: %.2f (aluno %d)\n", menor, idxMenor);
    printf("Acima da media: %d\n", acima);
    printf("Mediana: %.2f\n", mediana);
    calcModa(notas, n);
}

int main() {
    int n;
    scanf("%d", &n);
    double *notas = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) scanf("%lf", &notas[i]);

    printf("Relatorio inicial\n");
    relatorio(notas, n);

    int k;
    scanf("%d", &k);
    notas = realloc(notas, (n + k) * sizeof(double));
    for (int i = 0; i < k; i++) scanf("%lf", &notas[n + i]);
    n += k;

    printf("\nRelatorio atualizado\n");
    relatorio(notas, n);

    free(notas);
    return 0;
}