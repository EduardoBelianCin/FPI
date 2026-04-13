#include <stdio.h>
#include <stdlib.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)

// Retorna 0 se já está ordenado, 1 caso contrário
int Compare(int a, int b) {
    if(a%2 == 0 && b%2 == 1) { return 1; }
    return 0;
}

int main() {
    int* Valores = NULL;
    int n = 0;
    int x;
    while(scanf("%d", &x) != EOF) {
        n++;
        int* temp_Valores = realloc(Valores, n * sizeof(int));
        
        if(temp_Valores == NULL) {
            free(Valores);
            return 1;
        }
        
        Valores = temp_Valores;
        Valores[n-1] = x;
    }
    printf("Mais um bom dia de trabalho!\n");

    // Ordena Primeiro pela paridade, depois pelo valor
    FORi(n) {
        FORj(n-i-1) {
            if(Compare(Valores[j], Valores[j+1])) {
                int temp = Valores[j];
                Valores[j] = Valores[j+1];
                Valores[j+1] = temp;
            }
        }
    }
    FORi(n) { printf("%d\n", Valores[i]); }
    printf("Vou visitar esses lugares de novo... algum dia.\n");

    return 0;
}