#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)

int inRange(int x,int y, int min_x,int min_y, int max_x,int max_y) {
    if(x>=min_x && x<=max_x && y>=min_y && y<=max_y) { return 1; }
    else { return 0; }
}

int main() {
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    
    char Matriz[20][20][4];
    int Vis[20][20];
    FORi(20) {
        FORj(20) {
            Vis[i][j] = 0;
            FORk(4) { Matriz[i][j][k] = '\0'; }
        }
    }

    // Preenchimento da Matriz
    int n; scanf("%d", &n);
    FORi(n) { FORj(n) { int x; scanf("%s", Matriz[i][j]); } }

    // Gerar a Espiral
    int idx_dir = 0, x = 0, y = 0;
    int Espiral[400][2];
    int idx_espiral = 0;
    int topo = 0, dir = n-1, baixo = n-1, esq = 0;
    while(x>=0 && x<n && y>=0 && y<n && !Vis[x][y]) {
        Espiral[idx_espiral][0] = x;
        Espiral[idx_espiral][1] = y;
        Vis[x][y] = 1;

        if(!inRange(x+dx[idx_dir],y+dy[idx_dir], topo,esq, baixo,dir)) {
            if(idx_dir == 0) { topo++; }
            else if(idx_dir == 1) { dir--; }
            else if(idx_dir == 2) { baixo--; }
            else if(idx_dir == 3) { esq++; }

            idx_dir = (idx_dir+1) % 4;
        }

        x += dx[idx_dir];
        y += dy[idx_dir];
        idx_espiral++;
    }

    // Achar a Maior Sequência
    int max_seq_size = 0, max_seq_start_idx = 0;
    int seq_size = 0, seq_start_idx = 0;
    int prev_soma = -1, prev_value = -1;
    FORi(n*n) {
        int ax = Espiral[i][0], ay = Espiral[i][1];
        int soma = 0, value = 0;
        FORj(4) {
            if(Matriz[ax][ay][j] != '\0') {
                soma += Matriz[ax][ay][j] - '0';
                value *= 10;
                value += Matriz[ax][ay][j] - '0';
            }
        }

        if(soma == prev_soma && (value < prev_value || prev_value == -1)) { seq_size++; }
        else {
            seq_start_idx = i;
            prev_soma = soma;
            seq_size = 1;
        }

        if(seq_size > max_seq_size) {
            max_seq_size = seq_size;
            max_seq_start_idx = seq_start_idx;
        }

        prev_value = value;
    }

    if(max_seq_size <= 1) { printf("0\n"); }
    else {
        // Print da Maior Sequência
        printf("%d\n", max_seq_size);
        for(int i=max_seq_start_idx;i<max_seq_start_idx+max_seq_size;i++) {
            printf("(%d,%d)\n", Espiral[i][0], Espiral[i][1]);
        }
    }

    return 0;
}