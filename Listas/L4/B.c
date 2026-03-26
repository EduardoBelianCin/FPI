#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)

int inRange(int x,int y, int n,int m) {
    if(x>=0 && x<n && y>=0 && y<m) { return 1; }
    else { return 0; }
}

int main() {
    int n,m; scanf("%d %d", &n,&m);

    // Queue de Coordenadas dos O
    int Matriz_O[500][2];

    // Preenchimento da Matriz
    int idx_O = 0;
    char Matriz[50][50];
    FORi(n) {
        char Linha[50]; scanf("%s", Linha);
        FORj(m) {
            Matriz[i][j] = Linha[j];
            if(Matriz[i][j] == 'o') {
                Matriz_O[idx_O][0] = i;
                Matriz_O[idx_O][1] = j;
                idx_O++;
            }
        }
    }
    int Qtd_O = idx_O;
    int idx = 0;

    while(idx < Qtd_O) {
        int x = Matriz_O[idx][0], y = Matriz_O[idx][1];

        // Queda da Agua
        if(inRange(x+1,y, n,m) && Matriz[x+1][y] == '.') {
            Matriz[x+1][y] = 'o';
            // Adiciona o novo O na Queue
            Matriz_O[idx_O][0] = x+1;
            Matriz_O[idx_O][1] = y;
            idx_O++; Qtd_O++;
        }
        else {
            // Escorrimento Pra Esquerda
            if(inRange(x+1,y, n,m) && Matriz[x+1][y] == '#' && inRange(x,y-1, n,m) && Matriz[x][y-1] == '.') {
                Matriz[x][y-1] = 'o';
                // Adiciona o novo O na Queue
                Matriz_O[idx_O][0] = x;
                Matriz_O[idx_O][1] = y-1;
                idx_O++; Qtd_O++;
            }
            // Escorrimento Pra Direita
            if(inRange(x+1,y, n,m) && Matriz[x+1][y] == '#' && inRange(x,y+1, n,m) && Matriz[x][y+1] == '.') {
                Matriz[x][y+1] = 'o';
                // Adiciona o novo O na Queue
                Matriz_O[idx_O][0] = x;
                Matriz_O[idx_O][1] = y+1;
                idx_O++; Qtd_O++;
            }
        }
        idx++;
    }

    // Print Final
    FORi(n) { printf("%s\n", Matriz[i]); }

    return 0;
}
