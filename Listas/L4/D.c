#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)

int inRange(int x,int y, int n,int m) {
    if(x>=0 && x<n && y>=0 && y<m) { return 1; }
    else { return 0; }
}

int main() {
    int n,m; scanf("%dx%d", &n,&m);

    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};

    // Queue de Coordenadas
    int Queue[10000][2];

    // Preenchimento da Matriz
    int idx_q = 0, alvo_x, alvo_y;
    char Matriz[101][101];
    int Matriz_Dist[101][101];

    FORi(n) {
        char Linha[101]; scanf("%s", Linha);
        FORj(m) {
            Matriz[i][j] = Linha[j];
            Matriz_Dist[i][j] = 0;

            if(Matriz[i][j] == 'd') {
                Queue[idx_q][0] = i;
                Queue[idx_q][1] = j;
                idx_q++;
            }
            else if(Matriz[i][j] == '#') {
                Matriz_Dist[i][j] = -1;
            }
            else if(Matriz[i][j] == 'o') {
                alvo_x = i;
                alvo_y = j;
            }
        }
    }
    int Qtd_D = idx_q;
    int idx = 0;

    int Find = 0;
    while(idx < Qtd_D && !Find) {
        int x = Queue[idx][0], y = Queue[idx][1];

        FORi(4) {
            int prev_dist = Matriz_Dist[x][y];
            int ax = x + dx[i], ay = y + dy[i];

            // Se a Posição Existe e Não foi preenchida ainda
            if(inRange(ax,ay, n,m) && Matriz_Dist[ax][ay] == 0) {
                Matriz_Dist[ax][ay] = prev_dist + 1;
                Queue[idx_q][0] = ax; Queue[idx_q][1] = ay;
                idx_q++;
                Qtd_D++;
            }

            if(ax == alvo_x && ay == alvo_y) { Find = 1; }
        }
        idx++;
    }

    // Print Final
    if(!Find) { printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n"); }
    else { printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", Matriz_Dist[alvo_x][alvo_y]); }

    return 0;
}