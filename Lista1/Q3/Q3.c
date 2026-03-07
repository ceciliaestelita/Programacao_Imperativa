#include <stdio.h>

int main(){
    int total, x, y, z;
    scanf("%d %d %d %d", &total, &x, &y, &z);

    int porcentagem_x, porcentagem_y, porcentagem_z, troco, investiu, dinheiro;

    // tenta dividir o total original
    if (((total * x) % 100) == 0 && ((total * y) % 100) == 0 && ((total * z) % 100) == 0) {
        porcentagem_x = (total * x) / 100;
        porcentagem_y = (total * y) / 100;
        porcentagem_z = (total * z) / 100;
        troco = total - porcentagem_x - porcentagem_y - porcentagem_z;
        investiu = 0;

        printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", porcentagem_x, porcentagem_y, porcentagem_z);
        dinheiro = 3 + troco;

    // tenta total + 1
    } else if ((((total+1) * x) % 100) == 0 && (((total+1) * y) % 100) == 0 && (((total+1) * z) % 100) == 0) {
        porcentagem_x = ((total+1) * x) / 100;
        porcentagem_y = ((total+1) * y) / 100;
        porcentagem_z = ((total+1) * z) / 100;
        troco = (total+1) - porcentagem_x - porcentagem_y - porcentagem_z;
        investiu = 1;

        if (troco > 1) {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", porcentagem_x, porcentagem_y, porcentagem_z);
            dinheiro = 2 + troco; // 3 - 1 investido + troco
        } else {
            printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
            dinheiro = 3;
        }

    // tenta total + 2
    } else if ((((total+2) * x) % 100) == 0 && (((total+2) * y) % 100) == 0 && (((total+2) * z) % 100) == 0) {
        porcentagem_x = ((total+2) * x) / 100;
        porcentagem_y = ((total+2) * y) / 100;
        porcentagem_z = ((total+2) * z) / 100;
        troco = (total+2) - porcentagem_x - porcentagem_y - porcentagem_z;
        investiu = 2;

        if (troco > 2) {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", porcentagem_x, porcentagem_y, porcentagem_z);

            char c1, c2, c3;
            scanf(" %c %c %c", &c1, &c2, &c3);
            printf("%d\n", (c1-'a'+1) + (c2-'a'+1) + (c3-'a'+1));

            dinheiro = 1 + troco; // 3 - 2 investido + troco
        } else {
            printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
            dinheiro = 3;
        }

    // tenta total + 3
    } else if ((((total+3) * x) % 100) == 0 && (((total+3) * y) % 100) == 0 && (((total+3) * z) % 100) == 0) {
        porcentagem_x = ((total+3) * x) / 100;
        porcentagem_y = ((total+3) * y) / 100;
        porcentagem_z = ((total+3) * z) / 100;
        troco = (total+3) - porcentagem_x - porcentagem_y - porcentagem_z;
        investiu = 3;

        if (troco > 3) {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", porcentagem_x, porcentagem_y, porcentagem_z);

            int i1, i2, i3;
            scanf("%d %d %d", &i1, &i2, &i3);

            int parcelas = 0;
            if (i1 % 3 == 0) { parcelas += (i1 % 9 == 0) ? (i1 % 27 == 0) ? (i1 % 81 == 0) ? 4 : 3 : 2 : 1; }
            if (i2 % 3 == 0) { parcelas += (i2 % 9 == 0) ? (i2 % 27 == 0) ? (i2 % 81 == 0) ? 4 : 3 : 2 : 1; }
            if (i3 % 3 == 0) { parcelas += (i3 % 9 == 0) ? (i3 % 27 == 0) ? (i3 % 81 == 0) ? 4 : 3 : 2 : 1; }

            printf("%d\n", parcelas);

            dinheiro = 0 + troco; // 3 - 3 investido + troco
        } else {
            printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
            dinheiro = 3;
        }

    // nenhuma divisão funcionou
    } else {
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
        dinheiro = 3;
    }

    if (dinheiro >= 7) {
        printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
    } else {
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }

    return 0;
}