#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define printn(v,n) for(int i=0;i<n;i++) printf("%d", v[i]); (i == n-1 ? "\n" : " ")

void Check_Null(void* p) {
    if(p == NULL) {
        printf("Erro Aloc\n");
        free(p);
        exit(1);
    }
}

void Aloc(int **mat, int n, int m) {
    FORi(n) {
        mat[i] = (int*) malloc(m * sizeof(int));
        if(mat[i] == NULL) {
            printf("Erro Aloc - Coluna %d\n", i);
            FORj(i) { free(mat[j]); }
            free(mat);
            exit(1);
        }
    }
}

void Ler_Elementos(int **mat, int n, int m) {   
    FORi(n) { FORj(m) { scanf ("%d", &mat[i][j]); } }
}

void Print_Elementos(int **mat, int n, int m) {
    FORi(n) {
        FORj(m) {
            printf("%d", mat[i][j]);
            if(j == m-1) { printf("\n"); }
            else { printf(" "); }
        }
    }
}

void Free_Mat(int **mat, int n, int m) {
    FORi(n) { free(mat[i]); }
    free(mat);
}

int dobro(int x) { return x*2; }
int quadrado(int x) { return x*x; }
int absoluto(int x) { return abs(x); }

void Operacoes(int **mat, int n, int m, int op) {
    int (*funcao)(int);

    if(op == 1) { funcao = dobro; }
    else if(op == 2) { funcao = quadrado; }
    else if(op == 3) { funcao = absoluto; }

    // Aplica a Operação desejada em todos os elementos da Matriz
    FORi(n) { FORj(m) { mat[i][j] = funcao(mat[i][j]); } }
}

int main() {
    int n,m; scanf("%d %d", &n, &m);

    int **Matriz;
    Matriz = (int**) malloc(n * sizeof(int*));
    Check_Null(Matriz);
    Aloc(Matriz, n,m);
    Ler_Elementos(Matriz, n,m);

    // Realiza a Operação deseja na Matriz
    int op; scanf("%d", &op);
    Operacoes(Matriz, n,m, op);
    Print_Elementos(Matriz, n,m);

    Free_Mat(Matriz, n,m);

    return 0;
}