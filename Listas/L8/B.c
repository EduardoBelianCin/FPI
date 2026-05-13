#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)

void Check_Null(void* p) {
    if(p == NULL) {
        printf("Erro Aloc\n");
        free(p);
        exit(1);
    }
}

typedef union {
    uint32_t dado_bruto;

    struct {
        unsigned int id_sensor : 10;
        unsigned int code_st : 3;
        unsigned int bateria : 1;
        int temperatura : 12;
        unsigned int cont_parid : 6;
    } infos;
} Sensor;

int main() {
    int n = 0, capacidade = 1;

    Sensor *Pacotes = malloc(capacidade * sizeof(Sensor));
    Check_Null(Pacotes);

    uint32_t entrada; scanf("%x", &entrada);
    while(entrada != 0) {
        if(n == capacidade) {
            capacidade *= 2;
            Sensor *temp_Pacotes = realloc(Pacotes, capacidade * sizeof(Sensor));
            Check_Null(temp_Pacotes);

            Pacotes = temp_Pacotes;
        }

        Pacotes[n].dado_bruto = entrada;
        n++;
        scanf("%x", &entrada);
    }

    FORi(n) {
        printf("Pacote [%d] - Dado Bruto: 0x%08X\n", i+1, Pacotes[i].dado_bruto);
        printf("ID do Sensor : %d\n", Pacotes[i].infos.id_sensor);
        printf("Status : %d\n", Pacotes[i].infos.code_st);
        if(Pacotes[i].infos.bateria == 1) { printf("Bateria Baixa: SIM (ALERTA)\n"); }
        else { printf("Bateria Baixa: Nao\n"); }
        printf("Temperatura : %d graus\n", Pacotes[i].infos.temperatura);
        printf("-------------------------------------------------\n");
    }

    // NAO ESQUECER O FREE
    free(Pacotes);

    return 0;
}