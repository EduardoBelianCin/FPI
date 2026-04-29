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


const char* Nomes_Tipos[] = {"Fogo", "Agua", "Eletricidade", "Planta"};
typedef enum {
    Fogo,
    Agua,
    Eletricidade,
    Planta
} Tipos_Elementais;

typedef struct {
    int ID;
    char Nome[20];
    Tipos_Elementais Tipo;
    int XP;
    int Atk;
    int Forca;
} Pokemon;

Pokemon Novo_Pokemon(int id, char* nome, int xp, int atk, int idx_tipo) {
    Pokemon pokemon;
    pokemon.ID = id;
    strcpy(pokemon.Nome, nome);
    pokemon.Tipo = idx_tipo;
    pokemon.XP = xp;
    pokemon.Atk = atk;
    pokemon.Forca = 2*xp + atk;

    return pokemon;
}
void Update_Pokemon(Pokemon *pokemon, char* nome, int xp, int atk, int idx_tipo) {
    strcpy(pokemon->Nome, nome);
    pokemon->Tipo = idx_tipo;
    pokemon->XP = xp;
    pokemon->Atk = atk;
    pokemon->Forca = 2*xp + atk;
}


typedef struct {
    char Nome[20];
    int CPF;
    int Idade;
    Pokemon* Lista_Pokemons;
    int Qtd_Pokemons;
    int Nivel;
} Treinador;

Treinador Novo_Treinador(char* nome, int cpf, int idade) {
    Treinador treinador;
    strcpy(treinador.Nome, nome);
    treinador.CPF = cpf;
    treinador.Idade = idade;
    treinador.Lista_Pokemons = NULL;
    treinador.Qtd_Pokemons = 0;
    treinador.Nivel = 0;

    return treinador;
}
void Update_Treinador_Forca(Treinador *treinador) {
    int qtd = treinador->Qtd_Pokemons, novo_nivel = 0;
    FORi(qtd) {
        Pokemon P = treinador->Lista_Pokemons[i];
        novo_nivel += P.Forca;
    }
    treinador->Nivel = novo_nivel;
}

Treinador* Copy_Treinadores(Treinador *Treinadores, int n) {
    Treinador* copia = (Treinador*) malloc(n * sizeof(Treinador));
    Check_Null(copia);

    FORi(n) { copia[i] = Treinadores[i]; }
    return copia;
}
Pokemon* Copy_Pokemons(Pokemon *Pokemons, int n) {
    Pokemon* copia = (Pokemon*) malloc(n * sizeof(Pokemon));
    Check_Null(copia);

    FORi(n) { copia[i] = Pokemons[i]; }
    return copia;
}


void CadastraTreina(Treinador treinador, Treinador **Treinadores, int *n) {
    int repetido = 0;
    FORi((*n)) { if((*Treinadores)[i].CPF == treinador.CPF) { repetido = 1; break; } }

    if(repetido == 0) {
        // REALOC AUMENTA A LISTA E INSERE O NOVO TREINADOR
        (*n)++;
        Treinador *temp_Treinadores = realloc(*Treinadores, *n * sizeof(Treinador));
        Check_Null(temp_Treinadores);

        *Treinadores = temp_Treinadores;
        (*Treinadores)[(*n)-1] = treinador;
    }
}
void CadastraPoke(int cpf, Pokemon pokemon, Treinador **Treinadores, int *n) {
    FORi((*n)) {
        if((*Treinadores)[i].CPF == cpf) {
            int qtd = (*Treinadores)[i].Qtd_Pokemons, repetido = 0;
            FORj(qtd) {
                // SE JA TEM UM POKEMON COM ESSE ID
                if(pokemon.ID == (*Treinadores)[i].Lista_Pokemons[j].ID) { repetido = 1; break; }
            }
            if(repetido == 1) { break; }

            (*Treinadores)[i].Qtd_Pokemons++;
            qtd = (*Treinadores)[i].Qtd_Pokemons;

            Pokemon *temp_Pokemons = realloc((*Treinadores)[i].Lista_Pokemons, qtd * sizeof(Pokemon));
            Check_Null(temp_Pokemons);

            (*Treinadores)[i].Lista_Pokemons = temp_Pokemons;
            (*Treinadores)[i].Lista_Pokemons[qtd-1] = pokemon;
            Update_Treinador_Forca(&(*Treinadores)[i]);
            break;
        }
    }
}
void Listar(Treinador **Treinadores, int *n) {
    if((*n) == 0) { printf("Classificação atual\n"); return; }

    Treinador *Treinadores_Ordenado = Copy_Treinadores(*Treinadores, *n);
    FORi((*n)) {
        FORj((*n)-i-1) {
            if(Treinadores_Ordenado[j].Nivel < Treinadores_Ordenado[j+1].Nivel) {
                Treinador temp = Treinadores_Ordenado[j];
                Treinadores_Ordenado[j] = Treinadores_Ordenado[j+1];
                Treinadores_Ordenado[j+1] = temp;
            }
        }
    }

    printf("Classificação atual\n");
    FORi((*n)) {
        printf("T: %s, CPF: %d, Nivel: %d\n", Treinadores_Ordenado[i].Nome, Treinadores_Ordenado[i].CPF, Treinadores_Ordenado[i].Nivel);

        int qtd = Treinadores_Ordenado[i].Qtd_Pokemons;
        if(qtd > 0) {
            Pokemon *Pokemons_Ordenado = Copy_Pokemons(Treinadores_Ordenado[i].Lista_Pokemons, qtd);
            FORj(qtd) {
                FORk(qtd-j-1) {
                    if(Pokemons_Ordenado[k].Forca < Pokemons_Ordenado[k+1].Forca) {
                        Pokemon temp = Pokemons_Ordenado[k];
                        Pokemons_Ordenado[k] = Pokemons_Ordenado[k+1];
                        Pokemons_Ordenado[k+1] = temp;
                    }
                }
            }

            FORj(qtd) {
                Pokemon pokemon = Pokemons_Ordenado[j];
                printf("  P: %d, %s, %d, %d, %s\n", pokemon.ID, pokemon.Nome, pokemon.XP, pokemon.Atk, Nomes_Tipos[pokemon.Tipo]);
            }
            free(Pokemons_Ordenado);
        }
    }
    free(Treinadores_Ordenado);
}
void Remover(int cpf, Treinador **Treinadores, int *n) {
    int x = 0;
    Treinador *temp_Treinadores = NULL;

    FORi((*n)) {
        if((*Treinadores)[i].CPF != cpf) {
            x++;
            temp_Treinadores = realloc(temp_Treinadores, x * sizeof(Treinador));
            Check_Null(temp_Treinadores);

            temp_Treinadores[x-1] = (*Treinadores)[i];
        }
        else {
            free((*Treinadores)[i].Lista_Pokemons);
        }
    }
    free(*Treinadores);
    *Treinadores = temp_Treinadores;
    *n = x;
}
void Atualizar(int cpf, int id, Pokemon pokemon, Treinador **Treinadores, int *n) {
    FORi((*n)) {
        if((*Treinadores)[i].CPF == cpf) {
            int qtd = (*Treinadores)[i].Qtd_Pokemons;
            FORj(qtd) {
                if(pokemon.ID == (*Treinadores)[i].Lista_Pokemons[j].ID) {
                    (*Treinadores)[i].Lista_Pokemons[j] = pokemon;
                }
            }
            Update_Treinador_Forca(&(*Treinadores)[i]);
            break;
        }
    }
}

typedef struct {
    void (*Cadastrar_Treinador)(Treinador, Treinador**, int*);
    void (*Cadastrar_Pokemon)(int, Pokemon, Treinador**, int*);
    void (*Listar_Classificacao)(Treinador**, int*);
    void (*Remover_Treinador)(int, Treinador**, int*);
    void (*Atualizar_Pokemon)(int, int, Pokemon, Treinador**, int*);
} Operacoes;



int main() {
    Treinador *Treinadores = NULL;
    int n = 0;

    Operacoes Ops;
    Ops.Cadastrar_Treinador = CadastraTreina;
    Ops.Cadastrar_Pokemon = CadastraPoke;
    Ops.Listar_Classificacao = Listar;
    Ops.Remover_Treinador = Remover;
    Ops.Atualizar_Pokemon = Atualizar;


    int cmd; scanf("%d", &cmd);
    while(cmd != 0) {
        if(cmd == 1) {
            char Nome[20]; int cpf, idade; scanf("%s %d %d", Nome, &cpf, &idade);
            Treinador novo_treinador = Novo_Treinador(Nome, cpf, idade);
            Ops.Cadastrar_Treinador(novo_treinador, &Treinadores, &n);
        }
        else if(cmd == 2) {
            int cpf, id; char Nome[20]; int xp, atk, tipo; scanf("%d %d %s %d %d %d", &cpf, &id, Nome, &xp, &atk, &tipo);
            Pokemon pokemon = Novo_Pokemon(id, Nome, xp, atk, tipo);
            Ops.Cadastrar_Pokemon(cpf, pokemon, &Treinadores, &n);
        }
        else if(cmd == 3) {
            Ops.Listar_Classificacao(&Treinadores, &n);
        }
        else if(cmd == 4) {
            int cpf; scanf("%d", &cpf);
            Ops.Remover_Treinador(cpf, &Treinadores, &n);
        }
        else if(cmd == 5) {
            int cpf, id; char Nome[20]; int xp, atk, tipo; scanf("%d %d %s %d %d %d", &cpf, &id, Nome, &xp, &atk, &tipo);
            Pokemon pokemon = Novo_Pokemon(id, Nome, xp, atk, tipo);
            Ops.Atualizar_Pokemon(cpf, id, pokemon, &Treinadores, &n);
        }
        scanf("%d", &cmd);
    }

    // NAO ESQUECER OS FREE
    FORi(n) { free(Treinadores[i].Lista_Pokemons); }
    free(Treinadores);

    return 0;
}