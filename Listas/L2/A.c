#include <stdio.h>

int main() {
    char c; scanf("%c", &c);
    
    int Altura = c - 'A' + 1;

    for(int i=1;i<=Altura;i++) {
        int qtd_pontos = Altura-i;
        
        for(int j=0;j<qtd_pontos;j++) { printf("."); }

        for(int j=0;j<i;j++) { char x = 'A'+j; printf("%c", x); }
        for(int j=i-2;j>=0;j--) { char x = 'A'+j; printf("%c", x); }

        for(int j=0;j<qtd_pontos;j++) { printf("."); }
        printf("\n");
    }

    return 0;
}