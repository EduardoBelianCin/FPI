#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)

int inRange(int x,int y, int n,int m) {
    if(x>=0 && x<n && y>=0 && y<m) { return 1; }
    else { return 0; }
}

int main() {
    int n,m; scanf("%d %d", &n,&m);

    // Preenchimento da Matriz
    char Matriz[101][101];
    FORi(n) {
        char Linha[101]; scanf("%s", Linha);
        FORj(m) { Matriz[i][j] = Linha[j]; }
    }

    int dx[8] = {0,1,0,-1, 1,1,-1,-1};
    int dy[8] = {1,0,-1,0, 1,-1,1,-1};

    // Iluminação dos Postes
    FORi(n) {
        FORj(m) {
            if(Matriz[i][j] == 'P') {
                FORk(8) {
                    int ai = i + dx[k], aj = j + dy[k];
                    // Posição Válida
                    if(inRange(ai,aj, n,m)) {
                        if(k < 4) { if(Matriz[ai][aj] != 'P') { Matriz[ai][aj] = '+'; } }
                        else if(Matriz[ai][aj] == '-') { Matriz[ai][aj] = 'x'; }
                    }
                }
            }
        }
    }

    // Print Final
    FORi(n) { printf("%s\n", Matriz[i]); }

    return 0;
}