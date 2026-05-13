#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)

void Check_Null(void* p) {
    if(p == NULL) {
        printf("Erro Aloc\n");
        free(p);
        exit(1);
    }
}

typedef struct {
    float SL;
    float SW;
    float PL;
    float PW;
    char Especie[50];
} Iris;

typedef struct {
    char Especie[50];
    int freq;
} Info_freq;

void calcularModa(Iris *dados, int n, char *resultado) {
    Info_freq *plantas_unicas = NULL;
    int qtd = 0, capacidade = 0;

    FORi(n) {
        // Compara com as que já existem
        int novo = 1;
        FORj(qtd) {
            if(strcmp(dados[i].Especie, plantas_unicas[j].Especie) == 0) {
                plantas_unicas[j].freq++;
                novo = 0;
                break;
            }
        }
        if(novo == 0) { continue; }

        // Se for um novo, cria uma posição nova se não tem capacidade
        if(qtd == capacidade) {
            if(capacidade == 0) { capacidade = 1; }
            else { capacidade *= 2; }

            Info_freq *temp_Info = realloc(plantas_unicas, capacidade * sizeof(Info_freq));
            Check_Null(temp_Info);
            
            plantas_unicas = temp_Info;
        }
        strcpy(plantas_unicas[qtd].Especie, dados[i].Especie);
        plantas_unicas[qtd].freq = 1;
        qtd++;
    }

    // Pegando a moda
    int max_freq = 0, idx_max = -1;
    FORi(qtd) {
        if(plantas_unicas[i].freq > max_freq) {
            max_freq = plantas_unicas[i].freq;
            idx_max = i;
        }
        // Empate, pega a menor lexic
        else if(plantas_unicas[i].freq == max_freq) {
            if(strcmp(plantas_unicas[i].Especie, plantas_unicas[idx_max].Especie) < 0) { idx_max = i; }
        }
    }
    strcpy(resultado, plantas_unicas[idx_max].Especie);

    free(plantas_unicas);
}

void processarArquivo(int id) {
    char nomeArquivo[20];
    sprintf(nomeArquivo, "iris%d.csv", id);

    FILE *arq = fopen(nomeArquivo, "r");
    if(!arq) {
        printf("Erro ao abrir %s\n", nomeArquivo);
        return;
    }

    // Ignora a linha 1
    char linha_0[100]; fgets(linha_0, 100, arq);

    // Malloc pras infos do arquivo
    int n = 0, capacidade = 1;
    Iris *dados = malloc(capacidade * sizeof(Iris));
    Check_Null(dados);

    printf("\nCONTEUDO iris%d.csv:\n", id);
    // Guarda as infos da Linha em dados
    while(fscanf(arq, "%f,%f,%f,%f,%[^ \n]", &dados[n].SL, &dados[n].SW, &dados[n].PL, &dados[n].PW, dados[n].Especie) == 5) {
        printf("%.1f, %.1f, %.1f, %.1f, %s\n", dados[n].SL, dados[n].SW, dados[n].PL, dados[n].PW, dados[n].Especie);

        if(n+1 == capacidade) {
            capacidade *= 2;
            Iris *temp_dados = realloc(dados, capacidade * sizeof(Iris));
            Check_Null(temp_dados);

            dados = temp_dados;
        }
        n++;
    }
    fclose(arq);

    float media_SL = 0, media_SW = 0, media_PL = 0, media_PW = 0;
    if(n > 0) {
        float soma_SL = 0, soma_SW = 0, soma_PL = 0, soma_PW = 0;

        FORi(n) {
            soma_SL += dados[i].SL; soma_SW += dados[i].SW;
            soma_PL += dados[i].PL; soma_PW += dados[i].PW;
        }

        media_SL = soma_SL/n; media_SW = soma_SW/n;
        media_PL = soma_PL/n; media_PW = soma_PW/n;
    }

    char moda[50]; calcularModa(dados, n, moda);

    // Gravação
    arq = fopen(nomeArquivo, "a");
    fprintf(arq, "\nRESULTADOS:\n");
    fprintf(arq, "Medias Dimensões: SL = %.2f, SW = %.2f, PL = %.2f, PW = %.2f\n", media_SL, media_SW, media_PL, media_PW);
    fprintf(arq, "Moda: %s\n", moda);
    fclose(arq);

    // NAO ESQUECER O FREE
    free(dados);
}

int main() {
    int n; scanf("%d", &n);

    FORi(n) { processarArquivo(i+1); }

    return 0;
}