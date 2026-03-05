#include <stdio.h>
#include <stdlib.h>

int main() {
    int x,y,c; scanf("%d %d %d", &x, &y, &c);

    int passos_y = abs(y)+1, passos_x = abs(x)+1;

    if(y > 0) {
        // Quad 1 (+ +)
        if(x > 0) {
            if(c == 1 || c == 3) { printf("caminhada invalida\n"); }
            else {
                if(c==2) { printf("%d passos em y e %d passos em x\n", passos_y, passos_x); }
                else if(c==4) { printf("%d passos em x e %d passos em y\n", passos_x, passos_y); }
            }
        }
        // Quad 2 (- +)
        else {
            if(c == 2 || c == 4) { printf("caminhada invalida\n"); }
            else {
                if(c==1) { printf("%d passos em y e %d passos em x\n", passos_y, passos_x); }
                else if(c==3) { printf("%d passos em x e %d passos em y\n", passos_x, passos_y); }
            }
        }
    }
    else {
        // Quad 4 (+ -)
        if(x > 0) {
            if(c == 2 || c == 4) { printf("caminhada invalida\n"); }
            else {
                if(c==3) { printf("%d passos em y e %d passos em x\n", passos_y, passos_x); }
                else if(c==1) { printf("%d passos em x e %d passos em y\n", passos_x, passos_y); }
            }
        }
        // Quad 3 (- -)
        else {
            if(c == 1 || c == 3) { printf("caminhada invalida\n"); }
            else {
                if(c==4) { printf("%d passos em y e %d passos em x\n", passos_y, passos_x); }
                else if(c==2) { printf("%d passos em x e %d passos em y\n", passos_x, passos_y); }
            }
        }
    }

    return 0;
}