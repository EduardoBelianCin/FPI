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
    if(idx_motivo == 0) { strcpy(inc.motivo, "PRODUTO_INEXISTENTE"); }
    else if(idx_motivo == 1) { strcpy(inc.motivo, "ESTOQUE_INSUFICIENTE"); }
    else { printf("Motivo Inválido!\n"); }
    return inc;
}


int main() {
    FILE *arq_produtos = fopen("produtos.txt", "r");
    if(!arq_produtos) {
        printf("Erro ao abrir arquivo: 'produtos.txt'\n");
        exit(1);
    }

    int qtd_prod = 0, capacidade_prod = 2;
    Produto *Produtos = malloc(capacidade_prod * sizeof(Produto));
    Check_Null(Produtos);

    // Produtos
    int codigo, qtd; char nome[50]; float preco;
    while(fscanf(arq_produtos, "%d %s %d %f", &codigo, nome, &qtd, &preco) == 4) {
        Produto prod = Criar_Produto(codigo, nome, qtd, preco);

        if(qtd_prod == capacidade_prod) {
            capacidade_prod *= 2;
            Produto *temp_Produtos = realloc(Produtos, capacidade_prod * sizeof(Produto));
            Check_Null(temp_Produtos);

            Produtos = temp_Produtos;
        }

        Produtos[qtd_prod] = prod;
        qtd_prod++;
    }
    fclose(arq_produtos);


    FILE *arq_movimentos = fopen("movimentos.txt", "r");
    if(!arq_movimentos) {
        printf("Erro ao abrir arquivo: 'movimentos.txt'\n");
        exit(1);
    }

    // Variaveis Relatorio
    int mov_aplicados = 0, saidas_rec = 0, mov_semcad = 0;

    int qtd_incons = 0, capacidade_inc = 2;
    Inconsistencia *Incs = malloc(capacidade_inc * sizeof(Inconsistencia));
    Check_Null(Incs);

    // Movimentos
    char c_mov;
    while(fscanf(arq_movimentos, "%d %c %d", &codigo, &c_mov, &qtd) == 3) {
        Movimento mov = Criar_Movimento(codigo, c_mov, qtd);

        int idx_produto = -1, qtd_estoque = -1;
        FORi(qtd_prod) {
            if(Produtos[i].codigo == codigo) { idx_produto = i; qtd_estoque = Produtos[i].qtd; break; }
        }

        // Inconsistencia no Movimento
        if(idx_produto == -1 || (c_mov == 'S' && qtd_estoque < qtd)) {
            int motivo = -1;
            if(idx_produto == -1) { motivo = 0; mov_semcad++; }
            else if(c_mov == 'S' && qtd_estoque < qtd) { motivo = 1; saidas_rec++; }

            Inconsistencia inc = Criar_Inconsistencia(mov, motivo);

            if(qtd_incons == capacidade_inc) {
                capacidade_inc *= 2;
                Inconsistencia *temp_Incs = realloc(Incs, capacidade_inc * sizeof(Inconsistencia));
                Check_Null(temp_Incs);

                Incs = temp_Incs;
            }

            Incs[qtd_incons] = inc;
            qtd_incons++;
        }
        // Movimento Válido
        else {
            if(c_mov == 'E') { Produtos[idx_produto].qtd += qtd; }
            else if(c_mov == 'S') { Produtos[idx_produto].qtd -= qtd; }
            mov_aplicados++;
        }
    }
    fclose(arq_movimentos);


    // ESTOQUE FINAL
    FILE *arq_estoque = fopen("estoque_atualizado.txt", "w");
    if(!arq_estoque) { printf("Erro ao abrir arquivo: 'estoque_atualizado.txt'\n"); }

    int qtd_estoque_low = 0;
    FORi(qtd_prod) {
        Produto prod = Produtos[i];
        fprintf(arq_estoque, "%d %s %d %.2f\n", prod.codigo, prod.nome, prod.qtd, prod.preco);
        if(prod.qtd <= 5) { qtd_estoque_low++; }
    }
    fclose(arq_estoque);


    // RELATORIO FINAL
    FILE *arq_relatorio = fopen("relatorio.txt", "w");
    if(!arq_relatorio) { printf("Erro ao abrir arquivo: 'relatorio.txt'\n"); }

    fprintf(arq_relatorio, "PRODUTOS PROCESSADOS: %d\n", qtd_prod);
    fprintf(arq_relatorio, "MOVIMENTOS APLICADOS: %d\n", mov_aplicados);
    fprintf(arq_relatorio, "SAIDAS RECUSADAS: %d\n", saidas_rec);
    fprintf(arq_relatorio, "MOVIMENTOS SEM CADASTRO: %d\n", mov_semcad);
    // Estoque Baixo
    if(qtd_estoque_low > 0) {
        fprintf(arq_relatorio, "ESTOQUE BAIXO:\n");

        FORi(qtd_prod) {
            Produto prod = Produtos[i];
            if(prod.qtd <= 5) { fprintf(arq_relatorio, "%d %s %d\n", prod.codigo, prod.nome, prod.qtd); }
        }
    }
    // Inconsistencias
    if(qtd_incons > 0) {
        fprintf(arq_relatorio, "INCONSISTENCIAS:\n");

        FORi(qtd_incons) {
            Inconsistencia inc = Incs[i];
            fprintf(arq_relatorio, "%d %c %d %s\n", inc.Mov.codigo, inc.Mov.mov, inc.Mov.qtd, inc.motivo);
        }
    }
    fclose(arq_relatorio);

    // NAO ESQUECER OS FREE
    free(Produtos);
    free(Incs);

    return 0;
}