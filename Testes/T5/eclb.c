#include <stdio.h>
#include <stdlib.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)

void Check_Null(void* p) {
    if(p == NULL) {
        printf("Erro Aloc\n");
        free(p);
        exit(1);
    }
}


int main() {
    int* Valores = NULL;
    int* Valores_Harm = NULL;
    int n = 0, x;

    while(scanf("%d", &x) != EOF) {
        n++;
        int* temp_Valores = realloc(Valores, n * sizeof(int));
        int* temp_ValoresHarm = realloc(Valores_Harm, n * sizeof(int));
        Check_Null(temp_Valores);
        Check_Null(temp_ValoresHarm);

        Valores = temp_Valores;
        Valores_Harm = temp_ValoresHarm;
        Valores[n-1] = x;
        Valores_Harm[n-1] = x;
    }

    int qtd_trocas = -1;
    int m = n, qtd_atual;
    while(qtd_trocas != 0) {
        qtd_trocas = 0;
        qtd_atual = 0;

        int* New_Harm = NULL;

        FORi(m) {
            if(qtd_trocas == 0) {
                if(i > 0) {
                    if(Valores_Harm[i-1] == Valores_Harm[i]) {
                        New_Harm[qtd_atual-1] = Valores_Harm[i]+1;
                        if(New_Harm[qtd_atual-1] == 8) { New_Harm[qtd_atual-1] = 1; }
                        qtd_trocas++;
                    }
                    else {
                        qtd_atual++;
                        int* temp_NewHarm = realloc(New_Harm, qtd_atual * sizeof(int));
                        Check_Null(temp_NewHarm);

                        New_Harm = temp_NewHarm;
                        New_Harm[qtd_atual-1] = Valores_Harm[i];
                    }
                }
                else {
                    qtd_atual++;
                    int* temp_NewHarm = realloc(New_Harm, qtd_atual * sizeof(int));
                    Check_Null(temp_NewHarm);

                    New_Harm = temp_NewHarm;
                    New_Harm[qtd_atual-1] = Valores_Harm[i];
                }
            }
            else {
                qtd_atual++;
                int* temp_NewHarm = realloc(New_Harm, qtd_atual * sizeof(int));
                Check_Null(temp_NewHarm);

                New_Harm = temp_NewHarm;
                New_Harm[qtd_atual-1] = Valores_Harm[i];
            }
        }
        if(qtd_trocas > 0) {
            Valores_Harm = New_Harm;
            m--;
        }
    }

    printf("Sequencia original:");
    FORi(n) { printf(" %d", Valores[i]); }
    printf("\n");
    printf("Comprimento original: %d\n", n);

    int soma = 0;
    printf("Sequencia harmonizada:");
    FORi(m) { printf(" %d", Valores_Harm[i]); soma += Valores_Harm[i]; }
    printf("\n");
    printf("Comprimento final: %d\n", m);

    printf("Soma harmonizada: %d\n", soma);

    return 0;
}