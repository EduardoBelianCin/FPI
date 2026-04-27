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

int** Copiar_Matriz(int **mat, int n, int m) {
    int **copia = (int**) malloc(n * sizeof(int*));
    Check_Null(copia);

    FORi(n) {
        copia[i] = (int*) malloc(m * sizeof(int));
        Check_Null(copia[i]);
    }

    FORi(n) { FORj(m) { copia[i][j] = mat[i][j]; } }
    return copia;
}

// 0-4 Camada_1 e 5-20 Camada_2
const int dx[21] = {0, 0,1,0,-1, 1,1,-1,-1, -2,-2,-2, -1,0,1, 2,2,2, -1,0,1};
const int dy[21] = {0, 1,0,-1,0, 1,-1,1,-1, -1,0,1, 2,2,2, -1,0,1, -2,-2,-2};

int inRange(int x,int y, int n,int m) {
    if(x>=0 && x<n && y>=0 && y<m) { return 1; }
    else { return 0; }
}

int Max(int a, int b) {
    if(a > b) { return a; }
    else { return b; }
}

int exp_1(int x, int vazio) { return Max(0, x-50); }
int exp_2(int x, int vazio) { return Max(0, x-25); }
int nuvem(int x, int vizinhos) { return Max(0, x-(5 + 8*vizinhos)); }

void Causar_Dano(int **mat, int n,int m, int op, int camada) {
    int (*funcao)(int,int);

    if(op == 1 && camada == 1) { funcao = exp_1; }
    else if(op == 1 && camada == 2) { funcao = exp_2; }
    else if(op == 2 && camada != 0) { funcao = nuvem; }
}

void Operacoes(int **mat, int **mat_res, int n,int m, int x,int y, int op) {
    int (*funcao)(int,int);

    if(op == 1) { funcao = exp_1; }
    else if(op == 2) { funcao = exp_2; }
    else if(op == 3) { funcao = nuvem; }

    if(op < 3) { mat_res[x][y] = funcao(mat_res[x][y], 0); }
    else {
        int viz = 0;
        for(int k=1;k<9;k++) {
            int ax = x + dx[k], ay = y + dy[k];
            if(inRange(ax,ay, n,m) && mat[ax][ay] > 0) { viz++; }
        }
        mat_res[x][y] = funcao(mat_res[x][y], viz);
    }
}

int main() {
    int n,m; scanf("%d %d", &n, &m);

    int **Matriz;
    Matriz = (int**) malloc(n * sizeof(int*));
    Check_Null(Matriz);
    Aloc(Matriz, n,m);
    Ler_Elementos(Matriz, n,m);

    int x,y; scanf("%d %d", &x, &y);
    char ataque[16]; scanf("%s", ataque);
    int **Matriz_Final = Copiar_Matriz(Matriz, n,m);

    printf("Estado inicial do mapa:\n");
    Print_Elementos(Matriz, n,m);


    int idx_atk = 0;
    if(!strcmp(ataque, "EXPLOSAO_ARCANA")) { idx_atk = 1; }
    else if(!strcmp(ataque, "NUVEM_VENENOSA")) { idx_atk = 2; }

    if(idx_atk == 1) {
        printf("\nEstado do mapa após usar a Explosão Arcana:\n");
        for(int k=0;k<5;k++) {
            int ax = x + dx[k], ay = y + dy[k];
            if(inRange(ax,ay, n,m)) { Operacoes(Matriz, Matriz_Final, n,m, ax,ay, 1); }
        }
        for(int k=5;k<21;k++) {
            int ax = x + dx[k], ay = y + dy[k];
            if(inRange(ax,ay, n,m)) { Operacoes(Matriz, Matriz_Final, n,m, ax,ay, 2); }
        }
        Print_Elementos(Matriz_Final, n,m);
    }
    else if(idx_atk == 2) {
        printf("\nEstado do mapa, por turno, após usar a Nuvem Venenosa:");
        
        int continuar = 3;
        while(continuar > 0) {
            printf("\n");
            int **Matriz_Estado = Copiar_Matriz(Matriz_Final, n,m);

            int qtd = 0, qtd_0 = 0;
            for(int k=0;k<21;k++) {
                int ax = x + dx[k], ay = y + dy[k];
                if(inRange(ax,ay, n,m)) {
                    Operacoes(Matriz_Estado, Matriz_Final, n,m, ax,ay, 3);
                    if(Matriz_Final[ax][ay] == 0) { qtd_0++; }
                    qtd++;
                }
            }
            if(qtd == qtd_0) { continuar = 0; }
            Print_Elementos(Matriz_Final, n,m);
            Free_Mat(Matriz_Estado, n,m);
            continuar--;
        }
    }

    Free_Mat(Matriz, n,m);
    Free_Mat(Matriz_Final, n,m);

    return 0;
}