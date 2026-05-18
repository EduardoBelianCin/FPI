#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    uint64_t valor_bruto;

    struct {
        uint64_t tipo : 2;
        uint64_t id_subsistema : 6;

        uint64_t eixo : 2;
        uint64_t temperatura : 10;
        uint64_t velocidade_angular : 18;
        uint64_t paridade : 26;
    } navegacao;

    struct {
        uint64_t tipo : 2;
        uint64_t id_subsistema : 6;

        uint64_t tensao_painel : 12;
        uint64_t corrente_consumo : 12;
        uint64_t status_baterias : 4;
        uint64_t checksum : 28;
    } energia;

    struct {
        uint64_t tipo : 2;
        uint64_t id_subsistema : 6;

        uint64_t codigo_erro : 8;
        uint64_t criticidade : 3;
        uint64_t timestamp : 20;
        uint64_t padding : 25;
    } alerta;
} Pacote;

const char* Tipos[] = {"Navegação", "Energia", "Alerta do Sistema"};
const char* C[] = {"X", "Y", "Z", "Calibração"};
const char* Criticidade[] = {"Info", "Warning", "Severe", "Fatal"};

int main() {
    printf("RELATÓRIO DE TELEMETRIA - CUBESAT\n");

    int tamanho = 0, capacidade = 4;
    Pacote *Pacotes = malloc(capacidade * sizeof(Pacote));
    Check_Null(Pacotes);

    float soma_temp0 = 0.0, soma_corrente1 = 0.0; int qtd0 = 0, qtd1 = 0, alertas_criticos = 0;

    uint64_t entrada; scanf("%llX", &entrada);
    while(entrada != 0) {
        Pacote pac; pac.valor_bruto = entrada;
        int tipo = pac.navegacao.tipo;

        // se pacote invalido, vai pra proxima
        if(tipo == 3 || (tipo == 2 && pac.alerta.criticidade >= 4)) { scanf("%llX", &entrada); continue; }

        if(tamanho == capacidade) {
            capacidade += 4;
            Pacote *temp_Pacotes = realloc(Pacotes, capacidade * sizeof(Pacote));
            Check_Null(temp_Pacotes);

            Pacotes = temp_Pacotes;
        }

        printf("[Registro %d] RAW: 0x%016llX\n", tamanho+1, pac.valor_bruto);
        printf("-> Tipo: %s\n-> ID do Subsistema Origem: %d\n", Tipos[pac.navegacao.tipo], pac.navegacao.id_subsistema);

        // Navegação
        if(tipo == 0) {
            qtd0++;
            soma_temp0 += pac.navegacao.temperatura;
            printf("-> Temperatura: %d°C\n", pac.navegacao.temperatura);
            printf("-> Velocidade Angular: %d rad/s\n", pac.navegacao.velocidade_angular);
            printf("-> Eixo: %s\n", C[pac.navegacao.eixo]);
        }
        // Energia
        else if(tipo == 1) {
            qtd1++;
            soma_corrente1 += pac.energia.corrente_consumo;
            printf("-> Tensão do Painel: %d mV\n", pac.energia.tensao_painel);
            printf("-> Corrente de Consumo: %d mA\n", pac.energia.corrente_consumo);
            // se todas estao ok, o valor é 0
            if(pac.energia.status_baterias == 0) { printf("-> Status da Baterias: OK\n"); }
            else {
                printf("-> Status da Baterias: Falha no(s) quadrante(s)");
                FORi(4) {
                    // testa se o bit i está ligado
                    if(pac.energia.status_baterias & (1 << i)) { printf(" %d", i); }
                }
                printf("\n");
            }
        }
        // Alerta do Sistema
        else if(tipo == 2) {
            if(pac.alerta.criticidade == 2 || pac.alerta.criticidade == 3) { alertas_criticos++; }

            printf("-> Código do Erro: %d\n", pac.alerta.codigo_erro);
            printf("-> Nível de Criticidade: %s\n", Criticidade[pac.alerta.criticidade]);
            printf("-> Timestamp Relativo: %d ms\n", pac.alerta.timestamp);
        }

        Pacotes[tamanho].valor_bruto = entrada;
        tamanho++;
        scanf("%llX", &entrada);
    }

    printf("\nESTATÍSTICAS CONSOLIDADAS\n");
    printf("- Total de pacotes válidos processados: %d\n", tamanho);
    printf("- Média de Temperatura Externa (Tipo 0): %.2f°C\n", soma_temp0/(qtd0>0 ? qtd0 : 1));
    printf("- Média de Corrente de Consumo (Tipo 1): %.2f mA\n", soma_corrente1/(qtd1>0 ? qtd1 : 1));
    printf("- Alertas Críticos Detectados (Severe/Fatal): %d\n", alertas_criticos);

    // NAO ESQUECER OS FREE
    free(Pacotes);

    return 0;
}