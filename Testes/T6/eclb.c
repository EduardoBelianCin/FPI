#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)

// FUNCOES PRA MANIPULAÇOES COM A MATRIZ USANDO PONTEIROS
void Check_Null(void* p) {
    if(p == NULL) {
        printf("Erro Na Aloc\n");
        free(p);
        exit(1);
    }
}
void Aloc(int **Mat, int n, int m) {
    FORi(n) {
        Mat[i] = (int*) malloc(m * sizeof(int));
        if(Mat[i] == NULL) {
            printf("Erro Na Aloc");
            FORj(i) { free(Mat[j]); }
            free(Mat);
            exit(1);
        }
    }
}
void Ler_Elementos(int **Mat, int n, int m) {   
    FORi(n) { FORj(m) { scanf ("%d", &Mat[i][j]); } }
}
void Print_Elementos(int **Mat, int n, int m) {
    FORi(n) {
        FORj(m) {
            printf("%d", Mat[i][j]);
            if(j == m-1) { printf("\n"); }
            else { printf(" "); }
        }
    }
}
void Free_Mat(int **Mat, int n, int m) {
    FORi(n) { free(Mat[i]); }
    free(Mat);
}
int** Copy_Matriz(int **Mat, int n, int m) {
    int **copia = (int**) malloc(n * sizeof(int*));
    Check_Null(copia);
    FORi(n) {
        copia[i] = (int*) malloc(m * sizeof(int));
        Check_Null(copia[i]);
    }
    FORi(n) { FORj(m) { copia[i][j] = Mat[i][j]; } }
    return copia;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// FUNCOES PRA RESOLUÇÃO

// 0 = centro, 1-4 = adjacentes, 5-9 = diagonais, 10-20 = em volta
const int dx[21] = {0, 0,0,1,-1, 1,1,-1,-1, 2,2,2, -1,0,1, -2,-2,-2, -1,0,1};
const int dy[21] = {0, 1,-1,0,0, 1,-1,1,-1, -1,0,1, 2,2,2, -1,0,1, -2,-2,-2};

int inRange(int x,int y, int n,int m) {
    if(x>=0 && x<n && y>=0 && y<m) { return 1; }
    return 0;
}
int MAX(int a, int b) {
    if(a > b) { return a; }
    else { return b; }
}

int Atk1_1(int x, int nada) { return MAX(x-50, 0); }
int Atk1_2(int x, int nada) { return MAX(x-25, 0); }
int Atk2(int x, int vizinhos) { return MAX(x-(6*vizinhos + 3), 0); }

void Ataques(int **Mat,int **New_Mat, int n,int m,int x,int y,int op) {
    int (*func)(int, int);

    if(op == 1) { func = Atk1_1; }
    else if(op == 2) { func = Atk1_2; }
    else if(op == 3) { func = Atk2; }

    if(op != 3) { New_Mat[x][y] = func(Mat[x][y], 0); }
    else {
        int vizinhos = 0;
        for(int k=1;k<9;k++) {
            int ax = x + dx[k], ay = y + dy[k];
            if(inRange(ax,ay, n,m) && Mat[ax][ay] > 0) { vizinhos++; }
        }
        New_Mat[x][y] = func(Mat[x][y], vizinhos);
    }
}


int main() {
    int n,m; scanf("%d %d", &n,&m);

    int **Matriz; Matriz = (int**) malloc(n*sizeof(int*));
    Check_Null(Matriz);
    Aloc(Matriz,n,m);
    Ler_Elementos(Matriz,n,m);

    int x,y; scanf("%d %d", &x,&y);
    char atk[20]; scanf("%s", atk);
    int **Matriz_Final = Copy_Matriz(Matriz,n,m);

    printf("Estado inicial do mapa:\n");
    Print_Elementos(Matriz, n,m);

    if(!strcmp(atk,"RETARDANTE_QUIMICO")) {
        printf("\nEstado do mapa após usar o Retardante Químico:\n");
        for(int k=0;k<5;k++) {
            int ax = x + dx[k], ay = y + dy[k];
            if(inRange(ax,ay, n,m)) { Ataques(Matriz,Matriz_Final, n,m, ax,ay,1); }
        }
        for(int k=5;k<21;k++) {
            int ax = x + dx[k], ay = y + dy[k];
            if(inRange(ax,ay, n,m)) { Ataques(Matriz,Matriz_Final, n,m, ax,ay,2); }
        }
        Print_Elementos(Matriz_Final, n,m);
    }
    else if(!strcmp(atk,"CHUVA_ARTIFICIAL")) {
        printf("\nEstado do mapa, por turno, após usar a Chuva Artificial:");

        int rodadas = 3;
        while(rodadas > 0) {
            printf("\n");
            int **Matriz_atual = Copy_Matriz(Matriz_Final,n,m);

            int qtd_tot = 0, qtd_zerados = 0;
            for(int k=0;k<21;k++) {
                int ax = x + dx[k], ay = y + dy[k];
                if(inRange(ax,ay, n,m)) {
                    Ataques(Matriz_atual,Matriz_Final, n,m, ax,ay,3);
                    if(Matriz_Final[ax][ay] == 0) { qtd_zerados++; }
                    qtd_tot++;
                }
            }
            if(qtd_tot == qtd_zerados) { rodadas = 0; }

            Print_Elementos(Matriz_Final,n,m);
            Free_Mat(Matriz_atual,n,m);
            rodadas--;
        }
    }

// NAO ESQUECER Os FREE
    Free_Mat(Matriz,n,m);
    Free_Mat(Matriz_Final,n,m);

    return 0;
}