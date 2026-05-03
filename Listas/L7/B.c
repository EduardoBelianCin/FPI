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
    char Frase[201];
    char Nome[101];
    int Habitantes;
    int Periculosidade;
    char Funcao[101];
    int Especial;
} Cidade;

void swap_cidade(Cidade *a, Cidade *b) {
    Cidade temp = *a;
    *a = *b;
    *b = temp;
}

Cidade Nova_Cidade(char frase[201]) {
    Cidade cidade;
    strcpy(cidade.Frase, frase);
    cidade.Habitantes = 0;
    cidade.Periculosidade = 0;

    int especial = 0, i_nome = 0, i_func = 0;
    FORi(200) {
        char c = frase[i];
        if(c == '\0') { break; }

        if(c == '!') {
            especial = 1;
        }
        else if('A' <= c && c <= 'Z') {
            if(i_nome == 0) { cidade.Nome[i_nome] = c; }
            else { cidade.Nome[i_nome] = 'a' + (c-'A'); }
            i_nome++;
        }
        else if('0' <= c && c <= '9') {
            cidade.Habitantes = cidade.Habitantes*10 + (c-'0');
        }
        else if(c == '*') {
            cidade.Periculosidade++;
        }

        if(i > 1 && frase[i-2] == ' ' && frase[i-1] == ' ' && (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))) {
            if(i_func == 0) {
                if('a' <= c && c <= 'z') { cidade.Funcao[i_func] = 'A' + (c-'a'); }
                else { cidade.Funcao[i_func] = c; }
            }
            else {
                if('a' <= c && c <= 'z') { cidade.Funcao[i_func] = c; }
                else { cidade.Funcao[i_func] = 'a' + (c-'A'); }
            }
            i_func++;
        }
    }
    cidade.Nome[i_nome] = '\0';
    cidade.Funcao[i_func] = '\0';
    cidade.Especial = especial;

    return cidade;
}


int main() {
    int n = 0;
    Cidade *Cidades = NULL;

    char Frase[201];
    while(scanf(" %200[^\n]", Frase) != EOF) {
        n++;
        Cidade* temp_Cidades = realloc(Cidades, n * sizeof(Cidade));
        
        if(temp_Cidades == NULL) {
            free(Cidades);
            return 1;
        }
        
        Cidades = temp_Cidades;
        Cidades[n-1] = Nova_Cidade(Frase);
    }

    FORi(n) {
        FORj(n-i-1) {
            if(Cidades[j].Especial != Cidades[j+1].Especial) {
                if(Cidades[j].Especial > Cidades[j+1].Especial) {
                    swap_cidade(&Cidades[j], &Cidades[j+1]);
                }
                continue;
            }

            if(Cidades[j].Habitantes < Cidades[j+1].Habitantes) {
                swap_cidade(&Cidades[j], &Cidades[j+1]);
            }
            else if(Cidades[j].Habitantes == Cidades[j+1].Habitantes) {
                if(Cidades[j].Periculosidade < Cidades[j+1].Periculosidade) {
                    swap_cidade(&Cidades[j], &Cidades[j+1]);
                }
                else if(Cidades[j].Periculosidade == Cidades[j+1].Periculosidade) {
                    if(Cidades[j].Nome[0] > Cidades[j+1].Nome[0]) {
                        swap_cidade(&Cidades[j], &Cidades[j+1]);
                    }
                }
            }
        }
    }

    int Especial = 0, i_Especial;
    if(Cidades[n-1].Especial == 1) {
        Especial = 1;
        i_Especial = Cidades[n-1].Habitantes;
    }

    if(Especial == 0) { printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n"); }
    else {
        Cidade cidade = Cidades[i_Especial-1];

        char Periculosidade[201];
        FORi(cidade.Periculosidade+1) {
            if(i == cidade.Periculosidade) { Periculosidade[i] = '\0'; }
            else { Periculosidade[i] = '*'; }
        }

        printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade %s.", cidade.Nome,cidade.Habitantes,cidade.Funcao,Periculosidade);

        if(cidade.Habitantes >= 1000 && cidade.Periculosidade > 3) { printf(" Talvez seja melhor desistir..."); }
        else if(cidade.Habitantes >= 1000) { printf(" Um lugar denso, vai ser difícil achar ela."); }
        else if(cidade.Periculosidade > 3) { printf(" Vai ser complicado entrar lá."); }
        printf("\n");
    }

    free(Cidades);

    return 0;
}