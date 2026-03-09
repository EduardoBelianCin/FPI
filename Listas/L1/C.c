#include <stdio.h>

int main() {
    int n,x,y,z; scanf("%d %d %d %d", &n, &x, &y, &z);
    int qtd_x = (x*n)/100, qtd_y = (y*n)/100, qtd_z = (z*n)/100;

    int rebeka = 3;

    if((x*n)%100 == 0 && (y*n)%100 == 0 && (z*n)%100 == 0) {
        printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", qtd_x, qtd_y, qtd_z);
        int resto = n - qtd_x - qtd_y - qtd_z;
        rebeka += resto;
    }
    else {
        int inc = 1; n++; rebeka--;
        qtd_x = (x*n)/100; qtd_y = (y*n)/100; qtd_z = (z*n)/100;
        int resto = n - qtd_x - qtd_y - qtd_z;

        if(resto >= 2 && (x*n)%100 == 0 && (y*n)%100 == 0 && (z*n)%100 == 0) {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", qtd_x, qtd_y, qtd_z);
            rebeka += resto;
        }
        else {
            inc = 2; n++; rebeka--;
            qtd_x = (x*n)/100; qtd_y = (y*n)/100; qtd_z = (z*n)/100;
            resto = n - qtd_x - qtd_y - qtd_z;

            if(resto >= 3 && (x*n)%100 == 0 && (y*n)%100 == 0 && (z*n)%100 == 0) {
                printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", qtd_x, qtd_y, qtd_z);

                char c1,c2,c3; scanf(" %c %c %c", &c1, &c2, &c3);
                int soma = c1-'a'+1 + c2-'a'+1 + c3-'a'+1;
                printf("%d\n", soma);
                rebeka += resto;
            }
            else {
                inc = 3; n++; rebeka--;
                qtd_x = (x*n)/100; qtd_y = (y*n)/100; qtd_z = (z*n)/100;
                resto = n - qtd_x - qtd_y - qtd_z;

                if(resto >= 4 && (x*n)%100 == 0 && (y*n)%100 == 0 && (z*n)%100 == 0) {
                    printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", qtd_x, qtd_y, qtd_z);

                    int i1,i2,i3; scanf(" %d %d %d", &i1, &i2, &i3);
                    int soma_parcelas = 0;
                    if(i1%3 == 0 || i2%3 == 0 || i3%3 == 0) { soma_parcelas = i1/3 + i2/3 + i3/3; printf("%d\n", soma_parcelas); }
                    rebeka += resto;
                }
                else {
                    printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
                }
            }
        }
    }

    if(rebeka < 7) { printf("E parece que Rebeka vai ter que voltar andando...\n"); }
    else { printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n"); }

    return 0;
}