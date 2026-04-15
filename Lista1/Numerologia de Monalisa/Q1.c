#include <stdio.h>
#include <math.h>

int main(){
    int dia_aniv, mes_aniv, ano_aniv, dia_atual, mes_atual, ano_atual;
    scanf("%d/%d/%d %d/%d/%d", &dia_aniv, &mes_aniv, &ano_aniv, &dia_atual, &mes_atual, &ano_atual);

    int soma_amor = (7 * (dia_aniv + mes_aniv + ano_aniv + dia_atual + mes_atual + ano_atual));
    int soma_sorte = (9 * (dia_aniv + mes_aniv + dia_atual + mes_atual)) + (ano_atual - ano_aniv);
    int soma_trabalho = (ano_aniv + ano_atual) - (8 * (dia_aniv + dia_atual + mes_aniv + mes_atual));

    // pra calcular o amor
    int amor = soma_amor % 101;

    if (amor < 20) {
        printf("Amor: %d%% Pessimo dia para se apaixonar.\n", amor);
    } else if (amor >= 20 && amor <= 40){
        printf("Amor: %d%% Melhor manter o coracao <3 longe de perigo.\n", amor);
    } else if (amor >= 41 && amor <= 69){
        printf("Amor: %d%% Se o papo e as ideias baterem, esta liberado pensar em algo.\n", amor);
    } else if (amor >= 70 && amor <= 80){
        printf("Amor: %d%% Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.\n", amor);
    } else if (amor > 80){
        printf("Amor: %d%% Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.\n", amor);
    }

    // pra calcular a sorte
    int sorte = soma_sorte % 101;
 
    if (sorte < 30) {
        printf("Sorte: %d%% Nem jogue moedas pra cima hoje. Sem tigrinho nem jogos de azar, por favor!\n", sorte);
    } else if (sorte >= 30 && sorte <= 50){
        printf("Sorte: %d%% Melhor nao arriscar. Sem tigrinho nem jogos de azar, por favor!\n", sorte);
    } else if (sorte >= 51 && sorte <= 79){
        printf("Sorte: %d%% Por sua conta em risco. Sem tigrinho nem jogos de azar, por favor!\n", sorte);
    } else if (sorte >= 80 && sorte <= 90){
        printf("Sorte: %d%% Hoje vale a pena arriscar. Sem tigrinho nem jogos de azar, por favor!\n", sorte);
    } else if (sorte > 90){
        printf("Sorte: %d%% Nao tenha medo de virar cartas hoje. Sem tigrinho nem jogos de azar, por favor!\n", sorte);
    }

    // pra calcular o trabalho 
    int trabalho = soma_trabalho % 101;
 
    if (trabalho < 40) {
        printf("Trabalho: %d%% Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.\n", trabalho);
    } else if (trabalho >= 40 && trabalho <= 50){
        printf("Trabalho: %d%% Segura a emocao, nao xinga ninguem, nao esquece de beber agua.\n", trabalho);
    } else if (trabalho >= 51 && trabalho <= 69){
        printf("Trabalho: %d%% Um dia proveitoso com certeza, leve sua simpatia consigo.\n", trabalho);
    } else if (trabalho >= 70 && trabalho <= 84){
        printf("Trabalho: %d%% Boas vibracoes hoje, chances podem estar ao seu redor.\n", trabalho);
    } else if (trabalho > 85){
        printf("Trabalho: %d%% Use do maximo de networking possível hoje, dia bom para negocios.\n", trabalho);
    }
    
    // pra calcular a cor
    int quadrado_dia_aniv  = dia_aniv  * dia_aniv;
    int quadrado_mes_aniv  = mes_aniv  * mes_aniv;
    int quadrado_ano_aniv  = ano_aniv  * ano_aniv;
    int quadrado_dia_atual = dia_atual * dia_atual;
    int quadrado_mes_atual = mes_atual * mes_atual;
    int quadrado_ano_atual = ano_atual * ano_atual;
    
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



