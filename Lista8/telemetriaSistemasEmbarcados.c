#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// mapeamento do pacote de 32 bits por union + bitfields             
typedef struct {
    uint32_t id_sensor : 10;  // bits  0-9: ID do sensor (0-1023)       
    uint32_t status    :  3;  // bits 10-12: código de status (0-7)       
    uint32_t bateria   :  1;  // bit  13: bateria baixa (0=ok, 1=crítico) 
    int32_t  temp      : 12;  // bits 14-25: temperatura (complementa 2)  
    uint32_t paridade  :  6;  // bits 26-31: controle/paridade            
} CamposPacote;

typedef union {
    uint32_t raw;        // acesso ao dado bruto de 32 bits 
    CamposPacote campos; // acesso campo a campo via bitfields 
} PacoteTelemetria;

                                         
// imprime o pacote
void imprimir_pacote(int indice, PacoteTelemetria p) {
    printf("Pacote [%d] - Dado Bruto: 0x%08X\n", indice, p.raw);
    printf("ID do Sensor : %u\n",  p.campos.id_sensor);
    printf("Status : %u\n",  p.campos.status);
    printf("Bateria Baixa: %s\n",  p.campos.bateria ? "SIM (ALERTA)" : "Nao");
    printf("Temperatura : %d graus\n", p.campos.temp);
    printf("-------------------------------------------------\n");
}

// leitura, realloc e liberção da memória           
int main(void) {
    int capacidade = 2;          // capacidade inicial do vetor dinâmico 
    int tamanho    = 0;          // quantidade de pacotes lidos           

    PacoteTelemetria *pacotes = malloc(capacidade * sizeof(PacoteTelemetria));
    if (!pacotes) {
        fprintf(stderr, "Erro: falha na alocacao inicial.\n");
        return 1;
    }

    uint32_t entrada;

    // leitura de hexadecimais até receber 0 ou 0x0 
    while (scanf("%x", &entrada) == 1 && entrada != 0) {

        // dobra a capacidade quando o vetor fica cheio 
        if (tamanho == capacidade) {
            capacidade *= 2;
            PacoteTelemetria *tmp = realloc(pacotes, capacidade * sizeof(PacoteTelemetria));
            if (!tmp) {
                fprintf(stderr, "Erro: falha no realloc.\n");
                free(pacotes);
                return 1;
            }
            pacotes = tmp;
        }

        pacotes[tamanho].raw = entrada;
        tamanho++;
    }

    // processamento e impressão do relatório 
    for (int i = 0; i < tamanho; i++) {
        imprimir_pacote(i + 1, pacotes[i]);
    }

    // liberação da memória alocada 
    free(pacotes);
    pacotes = NULL;

    return 0;
}
