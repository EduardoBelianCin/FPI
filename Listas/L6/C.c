#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)
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

int Min(int a, int b) {
    if(a < b) { return a; }
    else { return b; }
}

int Calibracao(int x) { return x+5; }
int Saturacao(int x) { return Min(x, 80); }
int Amplificador(int x) { return x*2; }

void modificar(int **mat, int n, int m, int op) {
    int (*funcao)(int);

    if(op == 1) { funcao = Calibracao; }
    else if(op == 2) { funcao = Saturacao; }
    else if(op == 3) { funcao = Amplificador; }
    else if(op == 4) {
        int qtd_f; scanf("%d", &qtd_f);
        int (*vec_funcao[qtd_f])(int);
        FORi(qtd_f) {
            int o; scanf("%d", &o);
            if(o == 1) { vec_funcao[i] = Calibracao; }
            else if(o == 2) { vec_funcao[i] = Saturacao; }
            else if(o == 3) { vec_funcao[i] = Amplificador; }
        }

        FORk(qtd_f) {
            FORi(n) { FORj(m) { mat[i][j] = (vec_funcao[k])(mat[i][j]); } }
        }
    }

    if(1 <= op && op <=3) { FORi(n) { FORj(m) { mat[i][j] = funcao(mat[i][j]); } } }
}

int main() {
    int n,m; scanf("%d %d", &n, &m);

    int **Matriz;
    Matriz = (int**) malloc(n * sizeof(int*));
    Check_Null(Matriz);
    Aloc(Matriz, n,m);
    Ler_Elementos(Matriz, n,m);

    int cmd;
    while(scanf("%d", &cmd)) {
        if(cmd == 0) { break; }

        modificar(Matriz, n,m, cmd);
    }

    printf("Matriz processada:\n");
    Print_Elementos(Matriz, n,m);

    int max_valor = 0, x_max, y_max;
    FORi(n) { FORj(m) {
        if(Matriz[i][j] > max_valor) {
            max_valor = Matriz[i][j];
            x_max = i; y_max = j;
        }
    } }
    printf("\nSensor critico: %d\nPosicao: (%d,%d)\n", max_valor, x_max, y_max);

    Free_Mat(Matriz, n,m);

    return 0;
}