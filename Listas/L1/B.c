#include <stdio.h>

int main() {
    int n; scanf("%d", &n);
    int a,b; scanf("%d %d", &a, &b);
    
    int soma = (n*(n+1))/2;

    int qtd_mult_a = n/a;
    int soma_mult_a = ((qtd_mult_a+1)*a*qtd_mult_a)/2;

    int qtd_mult_b = n/b;
    int soma_mult_b = ((qtd_mult_b+1)*b*qtd_mult_b)/2;

    int ab = a*b;
    int qtd_mult_ab = n/ab;
    int soma_mult_ab = ((qtd_mult_ab+1)*ab*qtd_mult_ab)/2;

    int ans = soma - soma_mult_a - soma_mult_b + soma_mult_ab;
    printf("%d\n", ans);
    if(ans%2 == 0) { printf("Lá ele!!!\n"); }
    else { printf("Opa xupenio AULAS...\n"); }

    return 0;
}