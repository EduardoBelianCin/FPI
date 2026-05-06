#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int Max(int a, int b) {
    if(a > b) { return a; }
    return b;
}

typedef struct Nodo Nodo;

typedef struct {
    char rotulo[30];
    int coef1; // Escudo: Absorção Fixa | Regulador: Captação Base | Conversor: Custo Base | Pulso: Emissão Base
    int coef2; // Escudo: Fator de Slot | Regulador: Mult. de Slot | Conversor: Ganho | Pulso: Custo

    // Protocolo Modular: atribuído conforme o tipo durante a montagem.
    // n: ponteiro para o nodo dono do módulo.
    // slot: índice original deste módulo no array modulos[] da struct Nodo — ou seja, a posição (0-based) em que ele foi alocado dentro do nodo dono; deve ser passado exatamente como armazenado, sem reordenação.
    // sinal: intensidade do pulso de corrupção enviado pela Rede Carmesim.
    // resultado: onde o valor calculado deve ser gravado.
    void (*protocolo)(Nodo *n, int slot, int sinal, int *resultado);
} Modulo;

struct Nodo {
    int uid; // Identificador único (0 até N-1)
    char arquitetura[50];
    int carga_atual;
    int num_modulos;
    int sinal_micelio; // Intensidade do pulso de corrupção recebido
    Modulo modulos[]; // Flexible Array Member (FAM)
};


void Func_E(Nodo *n, int slot, int sinal, int *resultado) {
    Modulo mod = n->modulos[slot];
    int c1 = mod.coef1, c2 = mod.coef2;
    *resultado = sinal - c1 - (slot * c2);
    if(*resultado < 0) { *resultado = 0; }
}
void Func_R(Nodo *n, int slot, int sinal, int *resultado) {
    Modulo mod = n->modulos[slot];
    int c1 = mod.coef1, c2 = mod.coef2;
    int captado = c1 + (slot * c2);
    n->carga_atual += captado;
    *resultado = n->carga_atual;
}
void Func_C(Nodo *n, int slot, int sinal, int *resultado) {
    Modulo mod = n->modulos[slot];
    int c1 = mod.coef1, c2 = mod.coef2;
    int custo = c1 + slot, ganho = c2;
    if(n->carga_atual < custo) { *resultado = 0; }
    else { n->carga_atual += (ganho - custo); *resultado = ganho; }
}
void Func_P(Nodo *n, int slot, int sinal, int *resultado) {
    Modulo mod = n->modulos[slot];
    int c1 = mod.coef1, c2 = mod.coef2;
    int custo = c2;
    if(n->carga_atual < custo) { *resultado = 0; }
    else {
        *resultado = c1 + n->carga_atual + slot - sinal;
        n->carga_atual -= custo;
    }
}


// N (inteiro: quantidade de nós na rede)
// Para cada Nodo (UIDs podem vir fora de ordem):
//     UID (int)  arquitetura (string)  carga_inicial (int)  Q (int: quantidade de módulos)
//     Para cada um dos Q módulos:
//         tipo (char: E, R, C ou P)  rotulo (string)  coef1 (int)  coef2 (int)
//     sinal_micelio (inteiro: intensidade do pulso de corrupção)`

int main() {
    int n; scanf("%d", &n);

    Nodo *Nodos[n];
    FORi(n) {
        int UID, carga_inicial, q; char arquitetura[50];
        scanf("%d %s %d %d", &UID, arquitetura, &carga_inicial, &q);

        Nodos[i] = malloc(sizeof(Nodo) + q * sizeof(Modulo));
        if(Nodos[i] == NULL) {
            printf("Erro Aloc\n");
            FORj(i) { free(Nodos[j]); }
            exit(1);
        }

        Nodos[i]->uid = UID;
        strcpy(Nodos[i]->arquitetura, arquitetura);
        Nodos[i]->carga_atual = carga_inicial;
        Nodos[i]->num_modulos = q;

        FORj(q) {
            char tipo;
            scanf(" %c %s %d %d", &tipo, Nodos[i]->modulos[j].rotulo, &Nodos[i]->modulos[j].coef1, &Nodos[i]->modulos[j].coef2);

            if(tipo == 'E') { Nodos[i]->modulos[j].protocolo = Func_E; }
            else if(tipo == 'R') { Nodos[i]->modulos[j].protocolo = Func_R; }
            else if(tipo == 'C') { Nodos[i]->modulos[j].protocolo = Func_C; }
            else if(tipo == 'P') { Nodos[i]->modulos[j].protocolo = Func_P; }
        }

        int sinal_micelio; scanf("%d", &sinal_micelio);
        Nodos[i]->sinal_micelio = sinal_micelio;
    }


    FORi(n) {
        FORj(n-i-1) {
            if(Nodos[j]->uid > Nodos[j+1]->uid) {
                Nodo *temp = Nodos[j];
                Nodos[j] = Nodos[j+1];
                Nodos[j+1] = temp;
            }
        }
    }

    printf("[RELATORIO DE REDE: PROTOCOLO RAIZ CARMESIM]\n");
    FORi(n) {
        // Mecha *mecha = Mechas[i];
        Nodo *no = Nodos[i];
        printf("UID: %d | NÓ: %s | CARGA: %d\n", no->uid, no->arquitetura, no->carga_atual);

        // E
        FORj(no->num_modulos) {
            if(no->modulos[j].protocolo == Func_E) {
                int absorcao;
                no->modulos[j].protocolo(no, j, no->sinal_micelio, &absorcao);

                printf("-> [ESCUDO] %s | Absorção registrada: %d\n", no->modulos[j].rotulo, absorcao);
            }
        }
        // R
        FORj(no->num_modulos) {
            if(no->modulos[j].protocolo == Func_R) {
                int sincronizada;
                no->modulos[j].protocolo(no, j, no->sinal_micelio, &sincronizada);

                printf("-> [REGULADOR] %s | Carga sincronizada: %d\n", no->modulos[j].rotulo, sincronizada);
            }
        }
        // C
        FORj(no->num_modulos) {
            if(no->modulos[j].protocolo == Func_C) {
                int convertida;
                no->modulos[j].protocolo(no, j, no->sinal_micelio, &convertida);

                if(convertida != 0) { printf("-> [CONVERSOR] %s | Energia convertida: %d\n", no->modulos[j].rotulo, convertida); }
                else { printf("-> [CONVERSOR] %s | Conversão inviável!\n", no->modulos[j].rotulo); }
            }
        }
        // P
        FORj(no->num_modulos) {
            if(no->modulos[j].protocolo == Func_P) {
                int emissao;
                no->modulos[j].protocolo(no, j, no->sinal_micelio, &emissao);

                if(emissao != 0) { printf("-> [PULSO] %s | Emissão calculada: %d | Carga restante: %d\n", no->modulos[j].rotulo, Max(0, emissao), no->carga_atual); }
                else { printf("-> [PULSO] %s | Carga crítica!\n", no->modulos[j].rotulo); }
            }
        }

        printf("CARGA FINAL: %d\n=========================================\n", no->carga_atual);
    }
    printf("Rede estabilizada. Micélio contido.\n");

    // NAO ESQUECER OS FREE
    FORi(n) { free(Nodos[i]); }

    return 0;
}