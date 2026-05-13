#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)

// Structs
typedef struct {
    int codigo;
    char nome[50];
    int qtd;
    float preco;
} Produto;

typedef struct {
    int codigo;
    char mov;
    int qtd;
} Movimento;

typedef struct {
    Movimento Mov;
    char motivo[30];
} Inconsistencia;

// Funcoes de Criação
Produto Criar_Produto(int codigo, char nome[50], int qtd, float preco) {
    Produto produto;
    produto.codigo = codigo;
    strcpy(produto.nome, nome);
    produto.qtd = qtd;
    produto.preco = preco;
    return produto;
}
Movimento Criar_Movimento(int codigo, char mov, int qtd) {
    Movimento movimento;
    movimento.codigo = codigo;
    movimento.mov = mov;
    movimento.qtd = qtd;
    return movimento;
}
Inconsistencia Criar_Inconsistencia(Movimento movimento, int idx_motivo) {
    Inconsistencia inc;
    inc.Mov = movimento;
    if(idx_motivo == 0) { strcpy(inc.motivo, "ESTOQUE_INSUFICIENTE"); }
    else { strcpy(inc.motivo, "PRODUTO_INEXISTENTE"); }
    return inc;
}


int main() {
    int n; scanf("%d", &n);

    FILE *arq_produtos = fopen("produtos.txt", "r");
    if(!arq_produtos) {
        printf('Erro ao abrir arquivo: "produtos.txt"\n');
        exit(1);
    }
    FILE *arq_movimentos = fopen("movimentos.txt", "r");
    if(!arq_movimentos) {
        printf('Erro ao abrir arquivo: "movimentos.txt"\n');
        exit(1);
    }



    return 0;
}