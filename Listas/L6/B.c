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


const int dx[4] = {0,1,0,-1, 1,1,-1,-1};
const int dy[4] = {1,0,-1,0, 1,-1,1,-1};

int inRange(int x,int y, int n,int m) {
    if(x>=0 && x<n && y>=0 && y<m) { return 1; }
    else { return 0; }
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

    printf("Estado inicial do mapa:\n");
    Print_Elementos(Matriz, n,m);


    Free_Mat(Matriz, n,m);

    return 0;
}