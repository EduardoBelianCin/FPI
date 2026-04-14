#include <stdio.h>
#include <stdlib.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)

float Media(float* Notas, int n) {
    float soma = 0.0;
    FORi(n) { soma += Notas[i]; }
    return soma/n;
}

float MaiorNota(float* Notas, int* Indices, int n) {
    float max_nota = 0.0;
    int idx_max_nota = -1;
    FORi(n) { if(Notas[i] > max_nota) { max_nota = Notas[i]; idx_max_nota = Indices[i]; } }
    return max_nota;
}
int IdxMaiorNota(float* Notas, int* Indices, int n) {
    float max_nota = 0.0;
    int idx_max_nota = -1;
    FORi(n) { if(Notas[i] > max_nota) { max_nota = Notas[i]; idx_max_nota = Indices[i]; } }
    return idx_max_nota;
}

float MenorNota(float* Notas, int* Indices, int n) {
    float min_nota = 1000.0;
    int idx_min_nota = -1;
    FORi(n) { if(Notas[i] < min_nota) { min_nota = Notas[i]; idx_min_nota = Indices[i]; } }
    return min_nota;
}
int IdxMenorNota(float* Notas, int* Indices, int n) {
    float min_nota = 1000.0;
    int idx_min_nota = -1;
    FORi(n) { if(Notas[i] < min_nota) { min_nota = Notas[i]; idx_min_nota = Indices[i]; } }
    return idx_min_nota;
}

int AcimaMedia(float* Notas, int n, int media) {
    int qtd_acima = 0;
    FORi(n) { if(Notas[i] > media) { qtd_acima++; } }
    return qtd_acima;
}

float Mediana(float* Notas, int n) {
    if(n%2 == 1) { return Notas[n/2]; }
    else { return (Notas[n/2]+Notas[n/2-1])/2; }
}

float Moda(float* Notas, int n) {
    int Moda_Unica = 0;
    int qtd_max = 0, prev = -1;
    float moda;
    int* freq = NULL;

    int qtd = 0;
    FORi(n) {
        float nota = Notas[i];
        if(nota != prev) {
            qtd++;
            int* temp_freq = realloc(freq, qtd * sizeof(float));

            if(temp_freq == NULL) {
                free(freq);
                return 1;
            }
            
            freq = temp_freq;
            freq[qtd-1] = 1;
        }
        else { freq[qtd-1]++; }

        // Analisa as freq
        if(freq[qtd-1] > qtd_max) {
            qtd_max = freq[qtd-1];
            moda = nota;
            Moda_Unica = 1;
        }
        else if(freq[qtd-1] == qtd_max && nota != moda) {
            Moda_Unica = 0;
        }

        prev = nota;
    }

    if(Moda_Unica) { return moda; }
    else { return -1.0; }
}


int main() {
    int n,k;

    // Valores iniciais
    scanf("%d", &n);
    float* Notas = malloc(n * sizeof(float));
    int* Indices = malloc(n * sizeof(int));
    if(Notas == NULL || Indices == NULL) {
        printf("ERROU!\n");
        free(Notas);
        free(Indices);
        return 1;
    }

    // Notas
    int acima_media, max_indice, min_indice;
    float media, max_nota, min_nota, mediana, moda = -1.0;

    float x;
    FORi(n) {
        scanf("%f", &x);
        Notas[i] = x;
        Indices[i] = i+1;
    }
    // Ordena Crescente
    FORi(n) {
        FORj(n-i-1) {
            if(Notas[j] > Notas[j+1]) {
                float temp_n = Notas[j];
                Notas[j] = Notas[j+1];
                Notas[j+1] = temp_n;

                int temp_i = Indices[j];
                Indices[j] = Indices[j+1];
                Indices[j+1] = temp_i;
            }
        }
    }

    media = Media(Notas, n);
    max_nota = MaiorNota(Notas, Indices, n);
    max_indice = IdxMaiorNota(Notas, Indices, n);
    min_nota = MenorNota(Notas, Indices, n);
    min_indice = IdxMenorNota(Notas, Indices, n);
    acima_media = AcimaMedia(Notas, n, media);
    mediana = Mediana(Notas, n);
    moda = Moda(Notas, n);

    printf("Relatorio inicial\n");
    printf("Media: %.2f\n", media);
    printf("Maior nota: %.2f (aluno %d)\n", max_nota, max_indice);
    printf("Menor nota: %.2f (aluno %d)\n", min_nota, min_indice);
    printf("Acima da media: %d\n", acima_media);
    printf("Mediana: %.2f\n", mediana);
    if(moda != -1.0) { printf("Moda: %.2f\n", moda); }
    else { printf("Moda: Nao ha moda unica\n"); }


    // Valores novos
    scanf("%d", &k);
    Notas = realloc(Notas, (n+k) * sizeof(float));
    Indices = realloc(Indices, (n+k) * sizeof(int));
    if(Notas == NULL || Indices == NULL) {
        free(Notas);
        free(Indices);
        return 1;
    }

    FORi(k) {
        scanf("%f", &x);
        Notas[n+i] = x;
        Indices[n+i] = n+i+1;
    }
    n += k;
    // Ordena Crescente
    FORi(n) {
        FORj(n-i-1) {
            if(Notas[j] > Notas[j+1]) {
                float temp_n = Notas[j];
                Notas[j] = Notas[j+1];
                Notas[j+1] = temp_n;

                int temp_i = Indices[j];
                Indices[j] = Indices[j+1];
                Indices[j+1] = temp_i;
            }
        }
    }

    media = Media(Notas, n);
    max_nota = MaiorNota(Notas, Indices, n);
    max_indice = IdxMaiorNota(Notas, Indices, n);
    min_nota = MenorNota(Notas, Indices, n);
    min_indice = IdxMenorNota(Notas, Indices, n);
    acima_media = AcimaMedia(Notas, n, media);
    mediana = Mediana(Notas, n);
    moda = Moda(Notas, n);

    printf("\nRelatorio atualizado\n");
    printf("Media: %.2f\n", media);
    printf("Maior nota: %.2f (aluno %d)\n", max_nota, max_indice);
    printf("Menor nota: %.2f (aluno %d)\n", min_nota, min_indice);
    printf("Acima da media: %d\n", acima_media);
    printf("Mediana: %.2f\n", mediana);
    if(moda != -1.0) { printf("Moda: %.2f\n", moda); }
    else { printf("Moda: Nao ha moda unica\n"); }

    return 0;
}