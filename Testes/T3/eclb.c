#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)
#define FORl(n) for(int l=0;l<n;l++)

int main() {
    char S[101]; scanf("%[^\n]", &S);

    int idx_palavra = 0;
    char Palavras[200];
    int Sizes_Palavras[10];
    FORi(10) { Sizes_Palavras[i] = 0; }

    // RECEBIMENTO DAS PALAVRAS
    int idx = 0, idx_j = 0;
    char c = S[idx];
    while(c != '\0') {
        int pos = idx_palavra*20 + idx_j;

        if(c == ' ') {
            Palavras[pos] = '\0';
            idx_palavra++;
            idx_j = 0;
        }
        else {
            Palavras[pos] = c;
            Sizes_Palavras[idx_palavra]++;
            idx_j++;
        }

        idx++;
        c = S[idx];
    }
    int qtd_palavras = idx_palavra+1;


    // COMPARAÇÃO DOS PARES
    int idx_ans = 0;
    int Ans1[10], Ans2[10];

    for(int i=0;i<qtd_palavras-1;i++) {
        for(int j=i+1;j<qtd_palavras;j++) {
            int Valid = 1;

            // COMPARA OS TAMANHOS

            // SE TAMANHOS IGUAIS, ANALISO A SUBSTITUIÇÃO
            if(Sizes_Palavras[i] == Sizes_Palavras[j]) {
                int SizeP = Sizes_Palavras[i];

                int difs = 0;
                FORk(SizeP) {
                    int pos1 = i*20 + k, pos2 = j*20 + k;
                    char c1 = Palavras[pos1], c2 = Palavras[pos2];

                    int letra1, letra2;
                    if('a' <= c1 && c1 <= 'z') { letra1 = c1-'a'; }
                    else { letra1 = c1-'A'; }
                    if('a' <= c2 && c2 <= 'z') { letra2 = c2-'a'; }
                    else { letra2 = c2-'A'; }

                    if(letra1 != letra2) { difs++; }
                }
                // SE TEM MAIS DE 1 CARACTERE DIFERENTE É INVALIDO
                if(difs > 1) { Valid = 0; }
            }
            // SE OS TAMANHOS TIVEREM 1 DE DIFERENÇA. CHECA REMOÇÃO/INSERÇÃO
            else if(Sizes_Palavras[i] == Sizes_Palavras[j]+1) {
                int SizeP = Sizes_Palavras[i];

                int min_difs = 20;
                // ITERA REMOVENDO O CARACTERE DE IDX
                FORk(SizeP) {
                    int pos1 = i*20, pos2 = j*20;

                    int difs = 0;
                    FORl(SizeP) {
                        if(k == l) { pos1++; }
                        else {
                            char c1 = Palavras[pos1], c2 = Palavras[pos2];

                            int letra1, letra2;
                            if('a' <= c1 && c1 <= 'z') { letra1 = c1-'a'; }
                            else { letra1 = c1-'A'; }
                            if('a' <= c2 && c2 <= 'z') { letra2 = c2-'a'; }
                            else { letra2 = c2-'A'; }

                            if(letra1 != letra2) { difs++; }

                            pos1++; pos2++;
                        }
                    }
                    if(difs < min_difs) { min_difs = difs; }
                }

                // SE O NUMERO MINIMO DE DIFERENÇAS FOI MAIOR QUE 1, É INVALIDO
                if(min_difs > 0) { Valid = 0; }
            }
            // SE OS TAMANHOS TIVEREM 1 DE DIFERENÇA. CHECA REMOÇÃO/INSERÇÃO
            else if(Sizes_Palavras[i]+1 == Sizes_Palavras[j]) {
                int SizeP = Sizes_Palavras[j];

                int min_difs = 20;
                // ITERA REMOVENDO O CARACTERE DE IDX
                FORk(SizeP) {
                    int pos1 = i*20, pos2 = j*20;

                    int difs = 0;
                    FORl(SizeP) {
                        if(k == l) { pos2++; }
                        else {
                            char c1 = Palavras[pos1], c2 = Palavras[pos2];

                            int letra1, letra2;
                            if('a' <= c1 && c1 <= 'z') { letra1 = c1-'a'; }
                            else { letra1 = c1-'A'; }
                            if('a' <= c2 && c2 <= 'z') { letra2 = c2-'a'; }
                            else { letra2 = c2-'A'; }

                            if(letra1 != letra2) { difs++; }

                            pos1++; pos2++;
                        }
                    }
                    if(difs < min_difs) { min_difs = difs; }
                }

                // SE O NUMERO MINIMO DE DIFERENÇAS FOI MAIOR QUE 1, É INVALIDO
                if(min_difs > 0) { Valid = 0; }
            }
            // SE OS TAMANHOS TIVEREM 2 OU MAIS DE DIFERENÇA, É INVALIDO
            else {
                Valid = 0;
            }

            if(Valid == 1) {
                Ans1[idx_ans] = i;
                Ans2[idx_ans] = j;
                idx_ans++;
            }
        }
    }

    int qtd_pares = idx_ans;
    if(qtd_pares > 0) {
        printf("Pares de palavras vizinhas encontrados:\n");
        FORi(qtd_pares) {
            FORj(Sizes_Palavras[Ans1[i]]) {
                printf("%c", Palavras[Ans1[i]*20+j]);
            }
            printf(" e ");
            FORj(Sizes_Palavras[Ans2[i]]) {
                printf("%c", Palavras[Ans2[i]*20+j]);
            }
            printf("\n");
        }

        printf("\nTotal de pares: %d\n", qtd_pares);
    }
    else {
        printf("Nao existem palavras vizinhas na frase.\n");
    }

    return 0;
}