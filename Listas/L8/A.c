#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)

typedef union {
    unsigned char byte_bruto;

    struct {
        unsigned int erro : 1;
        unsigned int modo_op : 3;
        unsigned int leitura : 4;
    } infos;
} Sensor;

int main() {
    unsigned char entrada; scanf("%hhu", &entrada);

    Sensor sensor;
    sensor.byte_bruto = entrada;

    printf("Byte bruto: %d | Erro: %d | Modo: %d | Leitura: %d\n", sensor.byte_bruto, sensor.infos.erro, sensor.infos.modo_op, sensor.infos.leitura);

    return 0;
}