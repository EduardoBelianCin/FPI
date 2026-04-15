#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)

int Max(int a, int b) {
    if(a > b) { return a; }
    return b;
}

void Check_Null(void* p) {
    if(p == NULL) {
        printf("Erro Aloc\n");
        free(p);
        exit(1);
    }
}

int main() {
    int n; scanf("%d", &n);
    
    char* Linhas[n];
    char linha[150];
    int tamanhos[n], max_tamanho = 0, total_tamanho = 0;

    // Entradas linhas
    FORi(n) {
        scanf("%s", linha);
        int tamanho = strlen(linha)+1;
        Linhas[i] = malloc(tamanho * sizeof(char));
        Check_Null(Linhas[i]);

        strcpy(Linhas[i], linha);
        tamanhos[i] = tamanho-1;
        max_tamanho = Max(max_tamanho, tamanhos[i]);
        total_tamanho += tamanhos[i];
    }

    char* merged = malloc((total_tamanho+1) * sizeof(char));
    Check_Null(merged);

    // Merge
    int idx = 0;
    FORi(max_tamanho) {
        FORj(n) {
            if(i < tamanhos[j]) {
                merged[idx] = Linhas[j][i];
                idx++;
            }
        }
    }
    merged[idx] = '\0';
    printf("%s\n", merged);

    // Fusion
    int qtd_trocas = -1;
    int m = total_tamanho;
    char* merge_fusion = realloc(merged, total_tamanho * sizeof(char));
    while(qtd_trocas != 0) {
        qtd_trocas = 0;
        int qtd_atual = 0;

        char* new_merge = NULL;

        FORi(m) {
            if(qtd_trocas == 0) {
                if(i > 0) {
                    if(merge_fusion[i-1] == merge_fusion[i]) {
                        if(new_merge[qtd_atual-1] == 'z') { new_merge[qtd_atual-1] = 'a'; }
                        else { new_merge[qtd_atual-1] = merge_fusion[i] + 1; }
                        qtd_trocas++;
                    }
                    else {
                        qtd_atual++;
                        char* temp_new_merge = realloc(new_merge, qtd_atual * sizeof(char));
                        Check_Null(temp_new_merge);

                        new_merge = temp_new_merge;
                        new_merge[qtd_atual-1] = merge_fusion[i];
                    }
                }
                else {
                    qtd_atual++;
                    char* temp_new_merge = realloc(new_merge, qtd_atual * sizeof(char));
                    Check_Null(temp_new_merge);

                    new_merge = temp_new_merge;
                    new_merge[qtd_atual-1] = merge_fusion[i];
                }
            }
            else {
                qtd_atual++;
                char* temp_new_merge = realloc(new_merge, qtd_atual * sizeof(char));
                Check_Null(temp_new_merge);

                new_merge = temp_new_merge;
                new_merge[qtd_atual-1] = merge_fusion[i];
            }
        }
        if(qtd_trocas > 0) {
            merge_fusion = new_merge;
            m--;
        }
    }
    char* temp_merge_fusion = realloc(merge_fusion, (m+1) * sizeof(char));
    Check_Null(temp_merge_fusion);
    merge_fusion = temp_merge_fusion;
    merge_fusion[m] = '\0';
    printf("%s\n", merge_fusion);

    return 0;
}