#include <stdio.h>
#include <stdlib.h>

int main() {
    long long X, N;
    scanf("%lld", &X);
    scanf("%lld", &N);

    // todos começam em -1 pq não existe nenhum valor ainda entre 1 e n
    long long melhor_dist = -1;
    long long melhor_canal = -1;
    long long melhor_minuto = -1;
    long long melhor_termo = -1;

    // percorre todos os canais entre 1 e n
    for (int canal = 1; canal <= N; canal++) {
        long long a, b; // os valores iniciais que vão fazer f(1) e f(2)
        scanf("%lld %lld", &a, &b);

        long long dist_local = -1;
        long long minuto_local = -1;
        long long termo_local = -1;

        // f(1) = a
        long long anterior = a;   // f(i-2)
        long long atual = b;      // f(i-1)
        int minuto = 1;

        // avalia f(1) = a, se a distância for negativa, transforma em positiva
        long long dist = anterior - X;
        if (dist < 0){
            dist = -dist;
        }
        dist_local = dist;
        minuto_local = 1;
        termo_local = anterior;

        // avalia f(2) = b, se a distância for negativa, transforma em positiva
        dist = atual - X;
        if (dist < 0){
            dist = -dist;
        } 
        // verifica se a distância é menor que a menor distância já encontrada pra poder trocar, ou se as distâcias forem iguais, verifica se o termo de agora é maior que o termo já encontrado
        if (dist < dist_local || (dist == dist_local && atual < termo_local)) {
            dist_local = dist;
            minuto_local = 2;
            termo_local = atual;
        }

        // gera e avalia f(3), f(4), f(5)... até passar de X
        minuto = 3;
        while (1) {
            long long proximo = anterior + atual; // f(i) = f(i-2) + f(i-1)

            dist = proximo - X;
            if (dist < 0) dist = -dist;

            if (dist < dist_local || (dist == dist_local && proximo < termo_local)) {
                dist_local = dist;
                minuto_local = minuto;
                termo_local = proximo;
            }

            // o atual vira anterior, o proximo vira atual
            anterior = atual;
            atual = proximo;
            minuto++;

            // pra quando passar bem além de X
            if (proximo > X * 3 && minuto > 10){
                break;
            }
        }

        // compara com o melhor global
        if (melhor_dist == -1 || dist_local < melhor_dist ||
           (dist_local == melhor_dist)) {
            melhor_dist = dist_local;
            melhor_canal = canal;
            melhor_minuto = minuto_local;
            melhor_termo = termo_local;
        }
    }

    // verifica se é vip (soma dos dígitos do termo vencedor > 10)
    long long soma = 0;
    long long temp = melhor_termo;
    while (temp > 0) {
        soma += temp % 10;
        temp /= 10;
    }

    if (soma > 10) {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %lld e sera chamado mais ou menos no minuto %lld e com o VIP garantido!!!\n", melhor_canal, melhor_minuto);
    } else {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %lld e sera chamado mais ou menos no minuto %lld, mas o ingresso VIP não vai rolar :(\n", melhor_canal, melhor_minuto);
    }

    return 0;
}


