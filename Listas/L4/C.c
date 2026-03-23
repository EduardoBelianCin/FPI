#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)

int main() {
    char Movimentos[20];
    FORi(20) { Movimentos[i] = ' '; }

    // Preenchimento do Array de Movimentos
    char S[40]; scanf("%[^\n]", S);
    FORi(20) { Movimentos[i] = S[i*2]; }

    // Inicialização da Matriz de Freq
    int Matriz[4][4];
    FORi(4) { FORj(4) { Matriz[i][j] = 0; } }

    // Execução dos Movimentos na Matriz
    int x = 0, y = 0;
    int max_x, max_y, max_freq = 0;
    FORi(20) {
        char c = Movimentos[i];

        if(c == 'c' ) { x--; }
        else if(c == 'b') { x++; }
        else if(c == 'e') { y--; }
        else if(c == 'd') { y++; }

        // Analisa se passou a maior freq
        Matriz[x][y]++;
        if(Matriz[x][y] > max_freq) {
            max_freq = Matriz[x][y];
            max_x = x; max_y = y;
        }
    }
    printf("Coordenada X:%d, Y:%d", max_y, max_x);

    return 0;
}