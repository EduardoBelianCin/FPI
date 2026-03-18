#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)

int main() {
    char S[101];
    // Lê tudo até achar um '\n'
    scanf(" %[^\n]", S);

    char palavras[50][101];

    char c = S[0];
    int idx_S = 0, idx_palavra = 0;

    while(c != '\0') {
        int idx_letra = 0;
        // enquanto c for letra, minuscula ou maiuscula
        while(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
            palavras[idx_palavra][idx_letra] = c;
            idx_letra++;
            idx_S++;
            c = S[idx_S];
        }
        palavras[idx_palavra][idx_letra] = '\0';

        // enquanto c nao for letra
        while(!(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) && c != '\0') {
            idx_S++;
            c = S[idx_S];
        }

        idx_palavra++;
    }
    int qtd_palavras = idx_palavra;

    int freq_letras[50][26];
    // inicializa freq de cada letra com 0 pra cada palavra
    FORi(qtd_palavras) { FORj(26) { freq_letras[i][j] = 0; } }

    // preenche a freq de cada letra pra cada palavra
    FORi(qtd_palavras) {
        int j=0;
        c = palavras[i][j];
        while(c != '\0') {
            int letra = 0;
            if('a' <= c && c <= 'z') { letra = c-'a'; }
            else if('A' <= c && c <= 'Z') { letra = c-'A'; }

            freq_letras[i][letra]++;
            j++;
            c = palavras[i][j];
        }
    }

    int qtd_anagramas = 0;
    int ans1[1000], ans2[1000];

    // checa a comparação de todos os pares de palavras
    for(int i=0;i<qtd_palavras-1;i++) {
        for(int j=i+1;j<qtd_palavras;j++) {
            int anagrama_valido = 1;
            // compara a freq de todas as letras, se uma for diferente o anagrama é invalido
            FORk(26) { if(freq_letras[i][k] != freq_letras[j][k]) { anagrama_valido = 0; } }

            if(anagrama_valido == 1) {
                // salva os idx i e j pra printar no final
                ans1[qtd_anagramas] = i; ans2[qtd_anagramas] = j;

                qtd_anagramas++;
            }
        }
    }

    if(qtd_anagramas == 0) { printf("Nao existem anagramas na frase.\n"); }
    else {
        printf("Pares de anagramas encontrados:\n");

        FORi(qtd_anagramas) { printf("%s e %s\n", palavras[ans1[i]], palavras[ans2[i]]); }

        printf("\nTotal de pares: %d", qtd_anagramas);
    }

    return 0;
}