#include <stdio.h>

// struct de bitfield pra decodificar o byte do status 
typedef struct {
    unsigned char erro   : 1;  // bit 0: falha do sensor 
    unsigned char modo   : 3;  // bits 1-3: modo de operacao (0-7) 
    unsigned char leitura: 4;  // bits 4-7: leitura do sensor (0-15) 
} CamposSensor;

// union: compartilha o mesmo espaco de memoria 
typedef union {
    unsigned char rawByte;    // acesso ao byte bruto 
    CamposSensor  campos;     // acesso aos campos individuais 
} StatusSensor;

// função que printa os dados do sensor
void decodificar(unsigned char byte) {
    StatusSensor sensor;
    sensor.rawByte = byte;

    printf("Byte bruto: %3u | Erro: %u | Modo: %u | Leitura: %u\n",
           sensor.rawByte,
           sensor.campos.erro,
           sensor.campos.modo,
           sensor.campos.leitura);
}

int main(void) {
    int entrada;

    scanf("%d", &entrada);
    decodificar((unsigned char) entrada);

    return 0;
}
