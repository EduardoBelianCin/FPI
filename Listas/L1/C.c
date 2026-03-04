#include <stdio.h>

int main() {
    int n,x,y,z; scanf("%d %d %d %d", &n, &n, &n, &n);
    int qtd_x = (x*n)/100, qtd_y = (y*n)/100, qtd_z = (z*n)/100;

    if(qtd_x + qtd_y + qtd_z == n) {
        printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", qtd_x, qtd_y, qtd_z);
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }
    else {

    }

    return 0;
}