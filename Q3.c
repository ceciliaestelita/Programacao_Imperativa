#include <stdio.h>
#include <string.h>

#define max 101

int main() {
    char s[max];
    fgets(s, max, stdin); // CLAUDE: usa fgets no lugar do scanf pra não quebrar a leitura caso tenha um espaço em branco

    char todas_palavras[max * max]; // armazena as palavras no vetor 'todas_palavras' separadas por \0, pra poder verificar a ordem invertida sem usar vetor bidimensional
    int inicio[max];
    int n = 0, todas_palavrasPos = 0; // define o começo da palavra
    int len = strlen(s); // verifica o tamanho de s

    int i = 0;
    while (i < len) { // vai lendo cada letra até terminar a palavra
        while (i < len && !((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))){ // pula o que não é letra usando a tabela ascii
            i++;
        }
        if (i >= len){ // quebra a palavra pra ir pra próxima
            break;
        }
        inicio[n] = todas_palavrasPos; // CLAUDE: define o começo da próxima palavra

        while (i < len && ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))) { // salva a letra original sem converter, pra preservar maiúsculas na hora de imprimir
            todas_palavras[todas_palavrasPos++] = s[i++]; // pega o índice da primeira letra da próxima palavra e salva como veio
        }
        todas_palavras[todas_palavrasPos++] = '\0'; // quebra a palavra antes de ir pra próxima
        n++;
    }

    int pares = 0; // conta os pares de anagramas
    for (int a = 0; a < n; a++) { 
        for (int b = a + 1; b < n; b++) { // CLAUDE: = a + 1 pra não pegar o mesmo par mais de uma vez nem comparar a palavra com ela mesma
            int letras[26] = {0}; // vetor de todas as letras do alfabeto
            for (int k = inicio[a]; todas_palavras[k]; k++){ // percorre todas as letras da palavra a e transforma cada letra em um índice
                char c = todas_palavras[k];
                if (c >= 'A' && c <= 'Z') c = c + 32; // converte pra minúscula só pra comparar, sem alterar o buffer
                letras[c - 'a']++;
            }
            for (int k = inicio[b]; todas_palavras[k]; k++){ // faz a mesma coisa com a palavra b, mas decrementa pra ler invertendo, pq se o resultado final for 0, significa que era a mesma quantidade e as mesmas letras, então são anagramas
                char c = todas_palavras[k];
                if (c >= 'A' && c <= 'Z') c = c + 32; // converte pra minúscula só pra comparar, sem alterar o buffer
                letras[c - 'a']--;
            }
            int anagrama = 1;
            for (int k = 0; k < 26; k++) {
                if (letras[k] != 0){ // se ficou 0, eram anagramas, senão não eram
                    anagrama = 0; 
                    break;
                }
            }
            if (anagrama) pares++; // se eram anagramas, conta +1 na contagem de pares de anagramas
        }
    }

    if (pares == 0) {
        printf("Nao existem anagramas na frase.\n");
    } else {
        printf("Pares de anagramas encontrados:\n");
        for (int a = 0; a < n; a++) {
            for (int b = a + 1; b < n; b++) {
                int letras[26] = {0};
                for (int k = inicio[a]; todas_palavras[k]; k++){
                    char c = todas_palavras[k];
                    if (c >= 'A' && c <= 'Z') c = c + 32; // converte pra minúscula só pra comparar, sem alterar o buffer
                    letras[c - 'a']++;
                }
                for (int k = inicio[b]; todas_palavras[k]; k++){
                    char c = todas_palavras[k];
                    if (c >= 'A' && c <= 'Z') c = c + 32; // converte pra minúscula só pra comparar, sem alterar o buffer
                    letras[c - 'a']--;
                }
                int anagrama = 1;
                for (int k = 0; k < 26; k++) if (letras[k] != 0) { anagrama = 0; break; }
                if (anagrama) printf("%s e %s\n", todas_palavras + inicio[a], todas_palavras + inicio[b]);
            }
        }
        printf("\nTotal de pares: %d\n", pares);
    }

    return 0;
}