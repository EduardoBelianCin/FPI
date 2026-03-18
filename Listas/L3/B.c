#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)

int main() {
    int n; scanf("%d", &n);
    int x; scanf("%d", &x);
    int y; scanf("%d", &y);

    // qtd de latas que cada cliente comprou
    int latas_clientes[1000];

    FORi(1000) {
        int pos_cliente = i+1;
        if(x > 0 && pos_cliente%x == 0 && pos_cliente <= n) { latas_clientes[i] = 1; }
        else { latas_clientes[i] = 0; }
    }

    FORi(y) {
        int hh,mm,z; scanf("%d:%d %d", &hh,&mm,&z);

        int minutos = (hh-7)*60 + mm;
        int idx_cliente = minutos/3;
        latas_clientes[idx_cliente-1] = z;
    }

    int soma = 0;
    int vencedor = -1;
    int latas_vencedor = 0;
    FORi(n) {
        soma += latas_clientes[i];
        if(vencedor == -1 && soma >= 50) { vencedor = i+1; latas_vencedor = latas_clientes[i]; }
    }

    if(vencedor != -1) {
        int minutos_passados = vencedor*3;
        int hh = (minutos_passados + 7*60) / 60, mm = (minutos_passados + 7*60) % 60;

        if(latas_vencedor > 1) { printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.\n", vencedor,hh,mm,latas_vencedor); }
        else { printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou 1 lata.\n", vencedor,hh,mm); }
    }
    else {
        int latas_faltantes = 50-soma;

        if(latas_faltantes > 1) { printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.\n", latas_faltantes); }
        else { printf("Ainda nao foram vendidas latas suficientes. Falta 1 lata.\n"); }
    }

    return 0;
}