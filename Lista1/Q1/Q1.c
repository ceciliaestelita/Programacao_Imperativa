#include <stdio.h>
#include <math.h>

int main(){
    int dia_aniv, mes_aniv, ano_aniv, dia_atual, mes_atual, ano_atual;
    scanf("%d/%d/%d %d/%d/%d", &dia_aniv, &mes_aniv, &ano_aniv, &dia_atual, &mes_atual, &ano_atual);

    int soma_amor = dia_aniv + mes_aniv + ano_aniv + dia_atual + mes_atual + ano_atual;
    int soma_sorte = dia_aniv + mes_aniv + dia_atual + mes_atual;
    int soma_trabalho = - dia_aniv - mes_aniv + ano_aniv - dia_atual - mes_atual + ano_atual;

    // pra calcular o amor
    int mult7 = soma_amor * 7;
    int amor = mult7 % 101;

    if (amor < 20) {
        printf("Amor: %d%% Pessimo dia para se apaixonar.", amor);
    } else if (amor >= 20 && amor <= 40){
        printf("Amor: %d%% Melhor manter o coracao <3 longe de perigo.", amor);
    } else if (amor >= 41 && amor <= 69){
        printf("Amor: %d%% Se o papo e as ideias baterem, esta liberado pensar em algo.", amor);
    } else if (amor >= 70 && amor <= 80){
        printf("Amor: %d%% Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.", amor);
    } else if (amor > 80){
        printf("Amor: %d%% Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.", amor);
    }

    // pra calcular a sorte
    int mult9 = soma_sorte * 9;
    int sorte = mult9 % 101;
 
    if (sorte < 30) {
        printf("Sorte: %d%% Nem jogue moedas pra cima hoje. Sem tigrinho nem jogos de azar, por favor!", sorte);
    } else if (sorte >= 30 && sorte <= 50){
        printf("Sorte: %d%% Melhor nao arriscar. Sem tigrinho nem jogos de azar, por favor!", sorte);
    } else if (sorte >= 51 && sorte <= 79){
        printf("Sorte: %d%% Por sua conta em risco. Sem tigrinho nem jogos de azar, por favor!", sorte);
    } else if (sorte >= 80 && sorte <= 90){
        printf("Sorte: %d%% Hoje vale a pena arriscar. Sem tigrinho nem jogos de azar, por favor!", sorte);
    } else if (sorte > 90){
        printf("Sorte: %d%% Nao tenha medo de virar cartas hoje. Sem tigrinho nem jogos de azar, por favor!", sorte);
    }

    // pra calcular o trabalho 
    int mult8 = soma_trabalho * 8;
    int trabalho = mult8 % 101;
 
    if (trabalho < 40) {
        printf("Sorte: %d%% Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.", trabalho);
    } else if (trabalho >= 40 && trabalho <= 50){
        printf("Sorte: %d%% Segura a emocao, nao xinga ninguem, nao esquece de beber agua.", trabalho);
    } else if (trabalho >= 51 && trabalho <= 69){
        printf("Sorte: %d%% Um dia proveitoso com certeza, leve sua simpatia consigo.", trabalho);
    } else if (trabalho >= 70 && trabalho <= 84){
        printf("Sorte: %d%% Boas vibracoes hoje, chances podem estar ao seu redor.", trabalho);
    } else if (trabalho > 85){
        printf("Sorte: %d%% Use do maximo de networking possível hoje, dia bom para negocios.", trabalho);
    }
    
    // pra calcular a cor
    int quadrado_dia_aniv = pow(dia_aniv, 2);
    int quadrado_mes_aniv = pow(mes_aniv, 2);
    int quadrado_ano_aniv = pow(ano_aniv, 2);
    int quadrado_dia_atual = pow(dia_atual, 2);
    int quadrado_mes_atual = pow(mes_atual, 2);
    int quadrado_ano_atual = pow(ano_atual, 2);
    
    int soma_quadrados = quadrado_dia_aniv + quadrado_mes_aniv + quadrado_ano_aniv + quadrado_dia_atual + quadrado_mes_atual + quadrado_ano_atual;
    int divide11 = soma_quadrados % 11;
    

    switch (divide11) {
        case 0:
            printf("Cor: Cinza.");
            break;
        case 1:
            printf("Cor: Vermelho.");
            break;
        case 2:
            printf("Cor: Laranja.");
            break;
        case 3:
            printf("Cor: Amarelo.");
            break;
        case 4:
            printf("Cor: Verde.");
            break;
        case 5:
            printf("Cor: Azul.");
            break;
        case 6:
            printf("Cor: Roxo.");
            break;
        case 7:
            printf("Cor: Marrom.");
            break;
        case 8:
            printf("Cor: Rosa.");
            break;
        case 9:
            printf("Cor: Preto.");
            break;;
        case 10:
            printf("Cor: Branco.");
            break;
        default:
            break;
}

    return 0;
}



