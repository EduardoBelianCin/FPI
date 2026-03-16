#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)

int main() {
    int q; scanf("%d", &q);

    int next_col=0, next_linha=0;
    int valid = 1;
    int x1=0, x2=0, x3=0, x4=0, x5=0, x6=0;
    char c1='#', c2='#', c3='#', c4='#', c5='#', c6='#';
    FORi(q) {
        int x; char c; scanf("%d %c", &x,&c);

        if(c == 'D') { next_col += x; }
        else if(c == 'E') { next_col -= x; }
        else if(c == 'B') { next_linha += x; }

        if(i==0) { x1 = x; c1 = c; }
        else if(i==1) { x2 = x; c2 = c; }
        else if(i==2) { x3 = x; c3 = c; }
        else if(i==3) { x4 = x; c4 = c; }
        else if(i==4) { x5 = x; c5 = c; }
        else if(i==5) { x6 = x; c6 = c; }

        if(next_col < 0) { valid = 0; }
    }

    if(valid == 0) { printf("Informacao invalida\n"); }
    else {
        int col = 0, linha = 0;
        next_col = 0; next_linha = 0;
        char prev_comando = '#';

        int x; char c;
        FORi(q) {
            col = next_col; linha = next_linha;

            if(i==0) { x = x1; c = c1; }
            else if(i==1) { x = x2; c = c2; }
            else if(i==2) { x = x3; c = c3; }
            else if(i==3) { x = x4; c = c4; }
            else if(i==4) { x = x5; c = c5; }
            else if(i==5) { x = x6; c = c6; }

            if(c == 'D') { next_col += x; }
            else if(c == 'E') { next_col -= x; }
            else if(c == 'B') { next_linha += x; }

            if(i == 0) {
                FORj(x+1) { printf("."); }
                printf("\n");
            }
            else {
                if(prev_comando == 'D' && c == 'E') {}
                else if(c == 'B') {
                    FORj(x) {
                        FORk(col) { printf(" "); }
                        printf(".\n");
                    }
                }
                else if(prev_comando == 'B' && c == 'D') {
                    FORj(col) { printf(" "); }
                    FORj(x+1) {
                        if(j==0) { printf("X"); }
                        else { printf("."); }
                    }
                    printf("\n");
                }
                else if(prev_comando == 'B' && c == 'E') {
                    FORj(next_col) { printf(" "); }
                    FORj(x) { printf("."); }
                    printf("X");
                    printf("\n");
                }
            }

            prev_comando = c;
        }

        if(prev_comando == 'B') {
            FORk(col) { printf(" "); }
            printf(".\n");
        }
    }

    return 0;
}