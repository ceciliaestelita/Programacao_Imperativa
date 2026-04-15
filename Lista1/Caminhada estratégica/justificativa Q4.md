Optei por não utilizar IA na construção do código  
O Claude foi usado para gerar test cases

Define em qual quadrante Mário começa, baseado nos valores das coordenadas X e Y

    if (x > 0 && y > 0){
        quadrante_atual = 1;
    } else if (x < 0 && y > 0){
        quadrante_atual = 2;
    } else if (x < 0 && y < 0){
        quadrante_atual = 3;
    } else {
        quadrante_atual = 4;
    }


Define os caminhos de caminhadas inválidas como os casos em que o quadrante C, que deve ser evitado é o mesmo quadrante que o incial ou o destino final

    if (c == quadrante_atual || c == (quadrante_atual + 2) || c == (quadrante_atual - 2)){
        printf("caminhada invalida");


Se o quadrante inicial for 1, os quadrantes adjacentes a serem evitados (C) podem ser o 2 ou 4  
Caso o C seja o 2, Mário deve se mover y passos até o y = 0, 1 passo em y para chegar até o quadrante 4 e depois x passos até x = 0 e mais 1 passo em x para entrar no quadrante destino  
Caso o C seja o 4, Mário deve se mover x passos até o x = 0, 1 passo em x para chegar até o quadrante 2 e depois y passos até y = 0 e mais 1 passo em y para entrar no quadrante destino  


        if (quadrante_atual == 1){
            if (c == 2){
                y += 1;
                x += 1;
                printf("%d passos em y e %d passos em x", y, x);
            } else if (c == 4){
                y += 1;
                x += 1;
                printf("%d passos em x e %d passos em y", x, y);
            }

Se o quadrante inicial for 2, os quadrantes adjacentes a serem evitados (C) podem ser o 1 ou 3  
Caso o C seja o 1, Mário deve se mover y passos até o y = 0, 1 passo em y para chegar até o quadrante 3 e depois -x passos até x = 0 e mais 1 passo em x para entrar no quadrante destino  
Caso o C seja o 3, Mário deve se mover -x passos até o x = 0, 1 passo em x para chegar até o quadrante 1 e depois y passos até y = 0 e mais 1 passo em y para entrar no quadrante destino  

        } else if (quadrante_atual == 2){
            if (c == 1){
                y += 1;
                x = 1 - x;
                printf("%d passos em y e %d passos em x", y, x);
            } else if (c == 3){
                y += 1;
                x = 1 - x;
                printf("%d passos em x e %d passos em y", x, y);
            }

Se o quadrante inicial for 3, os quadrantes adjacentes a serem evitados (C) podem ser o 2 ou 4  
Caso o C seja o 2, Mário deve se mover -x passos até o x = 0, 1 passo em x para chegar até o quadrante 4 e depois -y passos até y = 0 e mais 1 passo em y para entrar no quadrante destino  
Caso o C seja o 4, Mário deve se mover -y passos até o y = 0, 1 passo em y para chegar até o quadrante 2 e depois -x passos até x = 0 e mais 1 passo em x para entrar no quadrante destino  

        }  else if (quadrante_atual == 3){
            if (c == 4){
                y = 1 - y;
                x = 1 - x;
                printf("%d passos em y e %d passos em x", y, x);
            } else if (c == 2){
                y = 1 - y;
                x = 1 - x;
                printf("%d passos em x e %d passos em y", x, y);
            }

Se o quadrante inicial for 4, os quadrantes adjacentes a serem evitados (C) podem ser o 1 ou 3  
Caso o C seja o 1, Mário deve se mover -x passos até o x = 0, 1 passo em x para chegar até o quadrante 3 e depois -y passos até y = 0 e mais 1 passo em y para entrar no quadrante destino  
Caso o C seja o 3, Mário deve se mover -y passos até o y = 0, 1 passo em y para chegar até o quadrante 1 e depois x passos até x = 0 e mais 1 passo em x para entrar no quadrante destino  

        }    else if (quadrante_atual == 4){
            if (c == 3){
                y = 1 - y ;
                x += 1;
                printf("%d passos em y e %d passos em x", y, x);
            } else if (c == 1){
                y = 1 - y;
                x += 1;
                printf("%d passos em x e %d passos em y", x, y);
            }
        }
   
