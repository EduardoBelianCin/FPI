#include <stdio.h>

int main() {
    long long n; scanf("%lld", &n);
    long long a,b; scanf("%lld %lld", &a, &b);
    
    long long soma = (n*(n+1))/2;

    long long qtd_mult_a = n/a;
    long long soma_mult_a = ((qtd_mult_a+1)*a*qtd_mult_a)/2;

    long long qtd_mult_b = n/b;
    long long soma_mult_b = ((qtd_mult_b+1)*b*qtd_mult_b)/2;

    long long ab = a*b;
    long long qtd_mult_ab = n/ab;
    long long soma_mult_ab = ((qtd_mult_ab+1)*ab*qtd_mult_ab)/2;

    long long ans = soma - soma_mult_a - soma_mult_b + soma_mult_ab;
    printf("%lld\n", ans);
    if(ans%2 == 0) { printf("Lá ele!!!\n"); }
    else { printf("Opa xupenio AULAS...\n"); }

    return 0;
}