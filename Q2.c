#include <stdio.h>

int main() {
    int N, X, Y;
    scanf("%d %d %d", &N, &X, &Y);

    // vetores pra guardar os horários (min) e as latas já registradas como vendidas
    int horario[Y + 1], latas_sistema[Y + 1];

    for (int i = 1; i <= Y; i++) { // percorre de 1 até a quantidade de clientes, pedindo os horários e a quantidade de latas de cada cliente
        int hh, mm, z;

        scanf("%d:%d %d", &hh, &mm, &z);

        horario[i] = hh * 60 + mm; // converte pra min
        latas_sistema[i] = z;
    }

    // vetor que guarda a quantidade de latas de cada cliente
    int latas[N + 1];

    for (int i = 1; i <= N; i++){
        int minuto_cliente = 420 + i * 3; // 420 = 07:00 horário do primeiro cliente, i clientes que são atendidos em 3 min cada

        // verifica se esse cliente tá na lista do sistema
        int ta_no_sistema = 0;
        for (int j = 1; j <= Y; j++) {
            if (minuto_cliente == horario[j]) {
                // cliente encontrado no sistema: usa a quantidade de latas do sistema
                latas[i] = latas_sistema[j];
                ta_no_sistema = 1;
                break; // não precisa continuar procurando
            }
        }

        // se não estava no sistema, verifica a regra do múltiplo de X
        if (!ta_no_sistema) {
            if (X != 0 && i % X == 0){
                latas[i] = 1;  // é múltiplo de X: comprou 1 lata
            } else {
                latas[i] = 0;  // não comprou nada
            }
        }
    }

    int acumulado = 0; // total de latas vendidas até agora
    int vencedor = -1; // guarda o índice do cliente vencedor (-1 = não teve ainda)

    for (int i = 1; i <= N; i++) {
        if (latas[i] > 0) { // só processa quem comprou pelo menos 1 lata
            int antes = acumulado; // salva o total antes de somar
            acumulado += latas[i]; // soma as latas do cliente atual

            // verifica se foi esse cliente que comprou a lata 50
            if (antes < 50 && acumulado >= 50) {
                vencedor = i;
                break; // se achou o vencedor, para o loop
            }
        }
    }

    if (vencedor == -1) {
        // nenhum cliente chegou na lata 50 
        int faltam = 50 - acumulado;
        if (faltam == 1){
            printf("Ainda nao foram vendidas latas suficientes. Falta %d lata.\n", faltam);
        } else if (faltam > 1){
            printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.\n", faltam);
        }
        } else {
        // calcula a hora de atendimento do vencedor em HH:MM
        int horario_vencedor = 420 + vencedor * 3;
        int hh = horario_vencedor / 60; // parte inteira = hh
        int mm = horario_vencedor % 60; // resto = mm
        int m = latas[vencedor]; // quantidade de latas que ele comprou

        // %02d pra as horas e minutos terem só 2 dígitos
        if (m == 1)
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou 1 lata.\n", vencedor, hh, mm);
        else
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.\n", vencedor, hh, mm, m);
    }

    return 0;
}