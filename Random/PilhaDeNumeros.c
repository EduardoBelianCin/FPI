#include <stdio.h>
#include <string.h>
#define FORi(n) for(int i=0;i<n;i++)

int main() {
    char Entrada[10];
    int Pilha[50];
    int *P_idx = &Pilha[0];
    int qtd_pilha = 0, soma = 0;

    while(strcmp(Entrada, "exit")) {
        scanf("%s", Entrada);

        if(!strcmp(Entrada, "push")) {
            int x; scanf("%d", &x);
            *P_idx = x;
            soma += *P_idx;
            P_idx++;
            qtd_pilha++;
        }
        else if(!strcmp(Entrada, "pop")) {
            if(qtd_pilha > 0) {
                P_idx--;
                soma -= *P_idx;
                qtd_pilha--;
            }
        }
        else if(!strcmp(Entrada, "sum")) {
            printf("%d\n", soma);
        }
        else if(!strcmp(Entrada, "pow")) {
            FORi(qtd_pilha) {
                printf("%d ", Pilha[i]*Pilha[i]);
            }
            printf("\n");
        }
        else if(!strcmp(Entrada, "average")) {
            float media = soma;
            if(qtd_pilha > 0) {
                media /= qtd_pilha;
            }
            printf("%.2f\n", media);
        }
        else if(!strcmp(Entrada, "print")) {
            FORi(qtd_pilha) {
                printf("%d ", Pilha[i]);
            }
            printf("\n");
        }
    }
    return 0;
}