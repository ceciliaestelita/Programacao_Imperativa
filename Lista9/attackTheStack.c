#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 100000

char stack[MAX_STACK];
int top = -1; // índice do elemento de cima (-1 = vazio)  

void print_stack() {
    if (top < 0) {
        printf("Pilha vazia!\n");
    } else {
        // printa linha a linha de cima pra baixo 
        for (int i = top; i >= 0; i--) {
            printf("%c\n", stack[i]);
        }
    }
    printf("\n");
}

// funde os dois elementos de cima, retorna 1 se der certo  
int try_fuse() {
    if (top < 1) return 0;
    char a = stack[top - 1]; // segundo de cima pra baixo
    char b = stack[top];     // primeiro de cima pra baixo  
    char result = 0;

    if ((a == 'g' && b == 'b') || (a == 'b' && b == 'g')) result = 'c';
    else if ((a == 'r' && b == 'b') || (a == 'b' && b == 'r')) result = 'm';
    else if ((a == 'r' && b == 'g') || (a == 'g' && b == 'r')) result = 'y';

    if (result) {
        stack[top - 1] = result;
        top--;
        return 1;
    }
    return 0;
}

// verifica se os 3 de cima são iguais e tira, retorna 1 se der certo  
int try_triple() {
    if (top >= 2 &&
        stack[top] == stack[top - 1] &&
        stack[top - 1] == stack[top - 2]) {
        top -= 3;
        return 1;
    }
    return 0;
}

void push(char c) {
    stack[++top] = c;

    // continua as regras no loop   
    int changed = 1;
    while (changed) {
        changed = 0;
        if (try_triple()) { changed = 1; continue; }
        if (try_fuse())   { changed = 1; continue; }
    }
}

int main() {
    char c;
    while (scanf(" %c", &c) == 1) {
        push(c);
        print_stack();
    }
    printf("Thank You So Much For Playing My Game!\n");
    return 0;
}
