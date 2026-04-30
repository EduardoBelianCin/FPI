#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)

typedef struct {
    char Titulo[51];
    char Genero[51];
    char Estudio[51];
    char Console[51];
    int Nota;
    int Ano;
} Jogo;

Jogo Novo_Jogo(char titulo[51], char genero[51], char estudio[51], char console[51], int nota, int ano) {
    Jogo jogo;
    strcpy(jogo.Titulo, titulo);
    strcpy(jogo.Genero, genero);
    strcpy(jogo.Estudio, estudio);
    strcpy(jogo.Console, console);
    jogo.Nota = nota;
    jogo.Ano = ano;

    return jogo;
}

void Print_Ano(Jogo *Lista_Jogos, int n, int ano) {
    int qtd = 0;
    FORi(n) {
        Jogo jogo = Lista_Jogos[i];
        if(jogo.Ano == ano) {
            printf("%s\n", jogo.Titulo);
            qtd++;
        }
    }
    if(qtd > 0) { printf("Tenho %d jogos || %d.\n", qtd, ano); }
    else { printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n"); }
}

void Print_Letra(Jogo *Lista_Jogos, int n, char letra) {
    int qtd = 0;
    FORi(n) {
        Jogo jogo = Lista_Jogos[i];
        if(jogo.Titulo[0] == letra) {
            printf("%s\n", jogo.Titulo);
            qtd++;
        }
    }
    if(qtd > 0) { printf("Tenho %d jogos || %c.\n", qtd, letra); }
    else { printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n"); }
}

void Print_Estudio(Jogo *Lista_Jogos, int n, char estudio[51]) {
    int qtd = 0;
    FORi(n) {
        Jogo jogo = Lista_Jogos[i];
        if(strcmp(jogo.Estudio, estudio) == 0) {
            printf("%s\n", jogo.Titulo);
            qtd++;
        }
    }
    if(qtd > 0) { printf("Tenho %d jogos || %s.\n", qtd, estudio); }
    else { printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n"); }
}

void Print_Console(Jogo *Lista_Jogos, int n, char console[51]) {
    int qtd = 0;
    FORi(n) {
        Jogo jogo = Lista_Jogos[i];
        if(strcmp(jogo.Console, console) == 0) {
            printf("%s\n", jogo.Titulo);
            qtd++;
        }
    }
    if(qtd > 0) { printf("Tenho %d jogos || %s.\n", qtd, console); }
    else { printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n"); }
}

void Print_Colecao(Jogo *Lista_Jogos, int n) {
    FORi(n) {
        Jogo jogo = Lista_Jogos[i];
        printf("%s\n", jogo.Titulo);
    }
}



int main() {
    int n; scanf("%d", &n);

    Jogo Lista_Jogos[n];
    FORi(n) {
        char titulo[51], genero[51], estudio[51], console[51]; int nota, ano;
        scanf("%s %s %s %s %d %d", titulo,genero,estudio,console, nota,ano);

        Lista_Jogos[i] = Novo_Jogo(titulo,genero,estudio,console,nota,ano);
        if(nota > 7) { printf("AWESOME! Mais um GOTY pra minha coleção!\n"); }
        else if(nota < 4) { printf("Era melhor jogar mais um jogo de Mahjong.\n"); }
    }

    char funcao[21];
    while(scanf("%s", funcao) != EOF) {
        if(strcmp(funcao, "printAno") == 0) {
            int ano; scanf("%d", &ano);
            Print_Ano(Lista_Jogos, n, ano);
        }
        else if(strcmp(funcao, "printLetra") == 0) {
            char letra; scanf("%c", &letra);
            Print_Letra(Lista_Jogos, n, letra);
        }
        else if(strcmp(funcao, "printStudio") == 0) {
            char estudio[51]; scanf("%s", estudio);
            Print_Estudio(Lista_Jogos, n, estudio);
        }
        else if(strcmp(funcao, "printConsole") == 0) {
            char console[51]; scanf("%s", console);
            Print_Console(Lista_Jogos, n, console);
        }
        else if(strcmp(funcao, "printColecao") == 0) {
            Print_Colecao(Lista_Jogos, n);
        }
    }
    printf("Enjoei de jogar, agora vou ver TV.\n");

    return 0;
}