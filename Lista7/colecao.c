#include <stdio.h>   
#include <string.h>  
#include <stdlib.h>  
#include <ctype.h>   

#define MAX_JOGOS 100 

// struct do jogo
typedef struct {
    char nome[100];   
    char genero[50];  
    char dev[50];     // desenvolvedor
    char plat[50];    // plataforma
    int nota;                
    int ano;          
} Jogo;

// recebe linha de texto e ponteiro pra um jogo e preenche o struct
void parse_jogo(char *linha, Jogo *j) {
    sscanf(linha, "%s %s %s %s %d %d",
           j->nome, j->genero, j->dev, j->plat, &j->nota, &j->ano);
}

// main
int main() {
    Jogo jogos[MAX_JOGOS]; // qrray de todos os jogos 
    int num_jogos = 0;     // contador de jogos lidos
    int N = 0;             // qtd que o usuário quer cadastrar
    char linha[256];       // buffer pra guardar cada linha lida do stdin

    // leitura do N (atoi converte str pra int)
    if (fgets(linha, sizeof(linha), stdin)) {
        N = atoi(linha);
    }

    for (int i = 0; i < N; i++) {

        // leitura de linha, se der errado, para o loop
        if (!fgets(linha, sizeof(linha), stdin)) break;

        // tira a quebra de linha 
        linha[strcspn(linha, "\r\n")] = 0;

        if (strlen(linha) == 0) { i--; continue; }

        // chama a função pra preencher o struct com os dados da linha
        parse_jogo(linha, &jogos[num_jogos]);

        if (jogos[num_jogos].nota > 7) {
            printf("AWESOME! Mais um GOTY pra minha coleção!\n");
        } else if (jogos[num_jogos].nota < 4) {
            printf("Era melhor jogar mais um jogo de Mahjong.\n");
        }

        num_jogos++; // só incrementa depois de cadastrar e imprimir, para não pular os índices
    }

    // loop até o EOF
    while (fgets(linha, sizeof(linha), stdin)) {

        // tira '\r' e '\n' do final da linha 
        linha[strcspn(linha, "\r\n")] = 0;

        // ignora linhas em branco
        if (strlen(linha) == 0) continue;

        // param começa com zeros pra não ter lixo caso não exista parâmetro
        char cmd[50] = {0}, param[50] = {0};

        // sscanf separa a linha em dois tokens:
        //   cmd   -> primeira palavra  
        //   param -> segunda palavra   
        sscanf(linha, "%s %s", cmd, param);

        // não tem parâmetro, printa nome e nota de todos os jogos 
        if (strcmp(cmd, "printColecao") == 0) {
            for (int i = 0; i < num_jogos; i++) {
                printf("%s %d\n", jogos[i].nome, jogos[i].nota);
            }
        }

        // converte o param pra int e printa o ano 
        else if (strcmp(cmd, "printAno") == 0) {
            int ano_busca = atoi(param); // Converte "1991" → 1991
            int count = 0;

            for (int i = 0; i < num_jogos; i++) {
                if (jogos[i].ano == ano_busca) {
                    printf("%s\n", jogos[i].nome);
                    count++;
                }
            }

            // se encontrou pelo menos 1 jogo, printa o resumo; senão, avisa Wilson
            if (count > 0) {
                printf("Tenho %d jogos || %d.\n", count, ano_busca);
            } else {
                printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
            }
        }

        // pega o primeiro caractere da string, padroniza o formato maiúscula e minúscula e printa 
        else if (strcmp(cmd, "printLetra") == 0) {
            char letra = param[0];
            int count = 0;

            for (int i = 0; i < num_jogos; i++) {
                if (tolower(jogos[i].nome[0]) == tolower(letra)) {
                    printf("%s\n", jogos[i].nome);
                    count++;
                }
            }

            if (count > 0) {
                printf("Tenho %d jogos || %c.\n", count, letra);
            } else {
                printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
            }
        }

        // compara as strings pra ver se é o mesmo estúdio do param
        else if (strcmp(cmd, "printStudio") == 0) {
            int count = 0;

            for (int i = 0; i < num_jogos; i++) {
                if (strcmp(jogos[i].dev, param) == 0) {
                    printf("%s\n", jogos[i].nome);
                    count++;
                }
            }

            if (count > 0) {
                printf("Tenho %d jogos || %s.\n", count, param);
            } else {
                printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
            }
        }

        // compara a plataforma
        else if (strcmp(cmd, "printConsole") == 0) {
            int count = 0;

            for (int i = 0; i < num_jogos; i++) {
                if (strcmp(jogos[i].plat, param) == 0) {
                    printf("%s\n", jogos[i].nome);
                    count++;
                }
            }

            if (count > 0) {
                printf("Tenho %d jogos || %s.\n", count, param);
            } else {
                printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
            }
        }

    } 
    printf("Enjoei de jogar, agora vou ver TV.\n");

    return 0; 
}
