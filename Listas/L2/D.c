#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)

int main() {
    int q; scanf("%d", &q);

    int col = 0, linha = 0;
    int next_col = 0, next_linha = 0;
    char prev_comando = '#';

    int x; char c;
    FORi(q) {
        scanf("%d %c", &x,&c);
        col = next_col; linha = next_linha;

        if(i==0) {
            if(c == 'D') {
                next_col += x-1;
                FORi(col) { printf(" "); }
                FORi(x) { printf("."); }
                printf("\n");
            }
            else if(c == 'B') {
                next_linha += x;
                FORi(x-1) {
                    FORj(col) { printf(" "); }
                    printf(".\n");
                }
            }
            else if(c == 'E') {
                printf("Informacao invalida\n");
                return 0;
            }
        }
        else {
            if(c == 'D') {
                next_col += x;
                FORi(col) { printf(" "); }
                FORi(x+1) { printf("."); }
                printf("\n");
            }
            else if(c == 'E') {
                next_col -= x;
                FORi(next_col) { printf(" "); }
                FORi(x+1) { printf("."); }
                printf("\n");
            }
            else if(c == 'B') {
                next_linha += x;
                FORi(x-1) {
                    FORj(col) { printf(" "); }
                    printf(".\n");
                }
            }
        }

        col = next_col;
        linha = next_linha;

        prev_comando = c;
    }
    if(prev_comando == 'B') {
        FORk(col) { printf(" "); }
        printf(".\n");
    }

    return 0;
}