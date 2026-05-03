#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)

typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;     // Atk: Dano Base   | Def: Blindagem Fixa | Utl: Recup. Base
    int atrib2;     // Atk: Custo Ener. | Def: Bônus de Slot   | Utl: Multiplicador
    
    // Função Modular: deve ser atribuída conforme o tipo do sistema.
    // m: ponteiro para o mecha dono do sistema.
    // slot: o índice da posição de entrada deste sistema no array sistemas[]
    // input: o dano base enviado pelo Wintermute para o combate.
    // output: onde deve ser gravado o resultado final da operação.
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;                // Identificador único (0 até N-1)
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;       // Contexto de dano enviado pelo Comando
    SubSistema sistemas[]; // O Flexible Array Member (FAM)
};


void sub_defesa(Mecha *mecha, int slot, int input, int *output) {
    int a1 = mecha->sistemas[slot].atrib1, a2 = mecha->sistemas[slot].atrib2;
    *output = input - a1 - (slot*a2);
    if(*output < 0) { *output = 0; }
}
void sub_utilidade(Mecha *mecha, int slot, int input, int *output) {
    int a1 = mecha->sistemas[slot].atrib1, a2 = mecha->sistemas[slot].atrib2;
    *output = a1 + (slot*a2);
    mecha->energia_atual += *output;
}
void sub_ataque(Mecha *mecha, int slot, int input, int *output) {
    int a1 = mecha->sistemas[slot].atrib1, a2 = mecha->sistemas[slot].atrib2;
    if(mecha->energia_atual >= a2) {
        *output = a1 + mecha->energia_atual + slot - input;
        mecha->energia_atual -= a2;
    }
    else { *output = -1; }
}



int main() {
    int n; scanf("%d", &n);

    Mecha *Mechas[n];
    FORi(n) {
        int id, energia_inicial, q, valor_wintermute; char modelo[50];
        scanf("%d %s %d %d", &id, modelo, &energia_inicial, &q);

        Mechas[i] = malloc(sizeof(Mecha) + q * sizeof(SubSistema));
        
        Mechas[i]->id = id;
        Mechas[i]->energia_atual = energia_inicial;
        Mechas[i]->num_sistemas = q;
        strcpy(Mechas[i]->modelo, modelo);

        FORj(q) {
            char tipo;
            scanf(" %c %s %d %d", &tipo, Mechas[i]->sistemas[j].nome, &Mechas[i]->sistemas[j].atrib1, &Mechas[i]->sistemas[j].atrib2);

            if(tipo == 'D') { Mechas[i]->sistemas[j].subrotina = sub_defesa; }
            else if(tipo == 'U') { Mechas[i]->sistemas[j].subrotina = sub_utilidade; }
            else if(tipo == 'A') { Mechas[i]->sistemas[j].subrotina = sub_ataque; }
        }

        scanf("%d", &valor_wintermute);
        Mechas[i]->valor_wintermute = valor_wintermute;
    }

    // Ordenação dos ID
    FORi(n) {
        FORj(n-i-1) {
            if(Mechas[j]->id > Mechas[j+1]->id) {
                Mecha *temp = Mechas[j];
                Mechas[j] = Mechas[j+1];
                Mechas[j+1] = temp;
            }
        }
    }

    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");
    FORi(n) {
        Mecha *mecha = Mechas[i];
        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", mecha->id, mecha->modelo, mecha->energia_atual);

        // D
        FORj(mecha->num_sistemas) {
            if(mecha->sistemas[j].subrotina == sub_defesa) {
                int dano_final;
                mecha->sistemas[j].subrotina(mecha, j, mecha->valor_wintermute, &dano_final);
                printf("-> [DEFESA] %s | Dano final sofrido: %d\n", mecha->sistemas[j].nome, dano_final);
            }
        }
        // U
        FORj(mecha->num_sistemas) {
            if(mecha->sistemas[j].subrotina == sub_utilidade) {
                int energia_rec;
                mecha->sistemas[j].subrotina(mecha, j, mecha->valor_wintermute, &energia_rec);
                printf("-> [UTILIDADE] %s | Energia atual: %d\n", mecha->sistemas[j].nome, mecha->energia_atual);
            }
        }
        // A
        FORj(mecha->num_sistemas) {
            if(mecha->sistemas[j].subrotina == sub_ataque) {
                int dano_causado;
                mecha->sistemas[j].subrotina(mecha, j, mecha->valor_wintermute, &dano_causado);
                if(dano_causado == -1) { printf("-> [ATAQUE] %s | Energia insuficiente!\n", mecha->sistemas[j].nome); }
                else { printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", mecha->sistemas[j].nome, dano_causado, mecha->energia_atual); }
            }
        }
        printf("ENERGIA FINAL: %d\n", mecha->energia_atual);
        printf("-----------------------------------------\n");
    }
    printf("Esquadrao pronto para o combate.\n");

    FORi(n) { free(Mechas[i]); }

    return 0;
}