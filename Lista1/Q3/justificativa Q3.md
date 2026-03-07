Nessa questão, foi utilizada a IA Claude nos blocos marcados por:❗Obs: Solução da IA Claude

Verifica se a porcentagem é inteira, calculando o resto da divisão por 100 e calcula o que sobrou pra Rebeka (e se ela precisou juntar os próprios 3 reais ao montante)
    
    if (((total * x) % 100) == 0 && ((total * y) % 100) == 0 && ((total * z) % 100) == 0) {
        porcentagem_x = (total * x) / 100;
        porcentagem_y = (total * y) / 100;
        porcentagem_z = (total * z) / 100;
        troco = total - porcentagem_x - porcentagem_y - porcentagem_z;
        investiu = 0;

Dinheiro que sobra pra Rebeka: o troco + os próprios 3 reais

        dinheiro = 3 + troco;

Caso não tenha sido uma divisão exata, adiciona 1 real de Rebeka e verifica se agora as porcentagens são inteiras

    } else if ((((total+1) * x) % 100) == 0 && (((total+1) * y) % 100) == 0 && (((total+1) * z) % 100) == 0) {
        porcentagem_x = ((total+1) * x) / 100;
        porcentagem_y = ((total+1) * y) / 100;
        porcentagem_z = ((total+1) * z) / 100;
        troco = (total+1) - porcentagem_x - porcentagem_y - porcentagem_z;
        investiu = 1;

Se o troco for maior que 1, então Rebeka fica com mais dinheiro do que os 3 reais iniciais, senão, ela não ajuda

        if (troco > 1) {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", porcentagem_x, porcentagem_y, porcentagem_z);
            dinheiro = 2 + troco;
        } else {
            printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
            dinheiro = 3;
        }
        
Caso não tenha sido uma divisão exata novamente, adiciona 2 reais de Rebeka e verifica se agora as porcentagens são inteiras

    } else if ((((total+2) * x) % 100) == 0 && (((total+2) * y) % 100) == 0 && (((total+2) * z) % 100) == 0) {
        porcentagem_x = ((total+2) * x) / 100;
        porcentagem_y = ((total+2) * y) / 100;
        porcentagem_z = ((total+2) * z) / 100;
        troco = (total+2) - porcentagem_x - porcentagem_y - porcentagem_z;
        investiu = 2;

Se o troco for maior que 2, então Rebeka recebe três letras (c1, c2, c3) e soma o valor delas no alfabeto, senão, ela não ajuda

        if (troco > 2) {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", porcentagem_x, porcentagem_y, porcentagem_z);

            char c1, c2, c3;
            scanf(" %c %c %c", &c1, &c2, &c3);
            ❗printf("%d\n", (c1-'a'+1) + (c2-'a'+1) + (c3-'a'+1));

            dinheiro = 1 + troco; 
        } else {
            printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
            dinheiro = 3;
        }
        
❗Todas as letras dos inputs são minúsculas, então subtraindo 'a', temos a posição (valor) de c1, c2 e c3. (+1 só pra definir 'a' como 1 e não como 0)

❗Obs: Solução da IA Claude

Caso não tenha sido uma divisão exata novamente, adiciona 3 reais de Rebeka e verifica se agora as porcentagens são inteiras

    } else if ((((total+3) * x) % 100) == 0 && (((total+3) * y) % 100) == 0 && (((total+3) * z) % 100) == 0) {
        porcentagem_x = ((total+3) * x) / 100;
        porcentagem_y = ((total+3) * y) / 100;
        porcentagem_z = ((total+3) * z) / 100;
        troco = (total+3) - porcentagem_x - porcentagem_y - porcentagem_z;
        investiu = 3;
        
        if (troco > 3) {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", porcentagem_x, porcentagem_y, porcentagem_z);

Cada homem diz a própria idade pra Rebeka verificar se pelo menos alguma é divisível por 3

            int i1, i2, i3;
            scanf("%d %d %d", &i1, &i2, &i3);

❗Uso dos ternários pra verificar se a idade 'i' é divisível por 3, se sim, verifica quantas vezes aparece 3 quando fatora 'i'. 
Se o if for satisfeito, soma 4 a parcelas, se (i % 9 == 0) for satisfeito, soma 3 ao novo resultado; se (i % 27 == 0) for satisfeito, soma 2 ao novo resultado; se (i % 81 == 0) for satisfeito, soma 1 ao novo resultado 

❗Obs: Solução da IA Claude


            int parcelas = 0;
           ❗ if (i1 % 3 == 0) { parcelas += (i1 % 9 == 0) ? (i1 % 27 == 0) ? (i1 % 81 == 0) ? 4 : 3 : 2 : 1; }
           ❗ if (i2 % 3 == 0) { parcelas += (i2 % 9 == 0) ? (i2 % 27 == 0) ? (i2 % 81 == 0) ? 4 : 3 : 2 : 1; }
           ❗ if (i3 % 3 == 0) { parcelas += (i3 % 9 == 0) ? (i3 % 27 == 0) ? (i3 % 81 == 0) ? 4 : 3 : 2 : 1; }

Quantidade de parcelas de 3 na idade dos homens

            printf("%d\n", parcelas);

            dinheiro = 0 + troco; 
        } else {
            printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
            dinheiro = 3;
        }

Caso não tenha sido divisível

    } else {
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
        dinheiro = 3;
    }
    
Se o dinheiro de Rebeka for pelo menos 7 reais, ela consegue ir pra casa

    if (dinheiro >= 7) {
        printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
    } else {
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }

