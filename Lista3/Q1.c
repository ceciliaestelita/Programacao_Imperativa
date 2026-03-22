#include <stdio.h>

int main(){
    int t, n;

    scanf("%d", &t); 

    for (int i = 0; i < t; i++){ // pra cada test case, pede a quantidade de itens no vetor
        scanf("%d", &n);

        int v[n]; // define o vetor com a quantidade n de itens
        for (int j = 0; j < n; j++){
            scanf("%d", &v[j]); // preenche o vetor com os itens que vão entrando 
        }

        int inicio_atual = 0, tam_atual = 1; // sequência que está sendo observada no momento, onde começa e quantos itens tem
        int melhor_inicio = 0, melhor_tam = 1; // a melhor (maior) sequência que já foi observada, onde começa e quantos itens tem

        for (int a = 1; a < n; a++){
            if (v[a] < v[a-1]){ // verifica se é uma sequência decrescente e add à quantidade de itens
                tam_atual++;
            } else { // se não for, a sequência acabou
                if (tam_atual > melhor_tam){ // compara se a sequência que acabou de quebrar é maior que a maior sequência que já tinha sido observada
                    melhor_tam = tam_atual; // se for maior, atualiza os melhores tamanhos e inícios
                    melhor_inicio = inicio_atual; 
                }
                // reinicia sequência atual
                inicio_atual = a;
                tam_atual = 1;
            }
        }

        // verifica a última sequência (pq ela nunca quebra dentro do loop)
        if (tam_atual > melhor_tam){
            melhor_tam = tam_atual;
            melhor_inicio = inicio_atual;
        }

        // printa o resultado
        if (melhor_tam >= 2){
            printf("%d\n", melhor_tam);
            for (int a = melhor_inicio; a < melhor_inicio + melhor_tam; a++){
                printf("%d ", v[a]);
            }
            printf("\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
} 

