#include <stdio.h>
#include <stdlib.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)

float Media(float* Notas, int n) {
    float soma = 0.0;
    FORi(n) { soma += Notas[i]; }
    return soma/n;
}

float MaiorNota(float* Notas, int n) {
    float max_nota = 0.0;
    int idx_max_nota = -1;
    FORi(n) { if(Notas[i] > max_nota) { max_nota = Notas[i]; idx_max_nota = i+1; } }
    return max_nota;
}
int IdxMaiorNota(float* Notas, int n) {
    float max_nota = 0.0;
    int idx_max_nota = -1;
    FORi(n) { if(Notas[i] > max_nota) { max_nota = Notas[i]; idx_max_nota = i+1; } }
    return idx_max_nota;
}

float MenorNota(float* Notas, int n) {
    float min_nota = 1000.0;
    int idx_min_nota = -1;
    FORi(n) { if(Notas[i] < min_nota) { min_nota = Notas[i]; idx_min_nota = i+1; } }
    return min_nota;
}
int IdxMenorNota(float* Notas, int n) {
    float min_nota = 1000.0;
    int idx_min_nota = -1;
    FORi(n) { if(Notas[i] < min_nota) { min_nota = Notas[i]; idx_min_nota = i+1; } }
    return idx_min_nota;
}

int main() {
    int n,k;
    float* Notas = NULL;
    int* Indices = NULL;

    // Valores iniciais
    scanf("%d", &n);
    Notas = realloc(Notas, n * sizeof(int));
    Indices = realloc(Indices, n * sizeof(int));
    if(Notas == NULL || Indices == NULL) {
        free(Notas);
        free(Indices);
        return 1;
    }

    // Notas
    int acima_media = 0, max_indice, min_indice;
    float media, max_nota = 0.0, min_nota = 1000.0, mediana, moda;

    float x;
    FORi(n) {
        scanf("%f", &x);
        Indices[i] = i+1;
    }

    printf("Relatorio inicial\n");
    printf("Media: %.2f\n", media);
    printf("Maior nota: %.2f (aluno %d)\n", max_nota, max_indice);
    printf("Menor nota: %.2f (aluno %d)\n", min_nota, min_indice);
    printf("Acima da media: %d\n", acima_media);
    printf("Mediana: %.2f\n", mediana);
    if(1 == 0) { printf("Moda: %.2f\n", moda); }
    else { printf("Moda: Nao ha moda unica\n"); }


    // Valores novos
    scanf("%d", &k);
    n += k;
    Notas = realloc(Notas, n * sizeof(int));
    Indices = realloc(Indices, n * sizeof(int));
    if(Notas == NULL || Indices == NULL) {
        free(Notas);
        free(Indices);
        return 1;
    }

    FORi(k) {
        scanf("%f", &x);
        Indices[i] = i+1;
    }

    printf("Relatorio atualizado\n");
    printf("Media: %.2f\n", media);
    printf("Maior nota: %.2f (aluno %d)\n", max_nota, max_indice);
    printf("Menor nota: %.2f (aluno %d)\n", min_nota, min_indice);
    printf("Acima da media: %d\n", acima_media);
    printf("Mediana: %.2f\n", mediana);
    if(1 == 0) { printf("Moda: %.2f\n", moda); }
    else { printf("Moda: Nao ha moda unica\n"); }

    return 0;
}