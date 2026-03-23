#include <stdio.h>

int main() {
    int V1,V2,V3,D; scanf("%d %d %d %d", &V1,&V2,&V3,&D);

    int Energia_1_3 = V1 + V3, Energia_123 = V1 + V2 + V3;

    int d1 = D/10, d2 = D%10;
    if(d1 > d2) { Energia_1_3 += (d1-d2); }
    else if(d2 > d1) { Energia_123 += (d2-d1); }
    else { Energia_1_3 += (d1+d2); Energia_123 += (d1+d2); }

    int Energia;
    if(Energia_123 >= Energia_1_3) { Energia = Energia_123; printf("Caminho: P2. "); }
    else { Energia = Energia_1_3; printf("Caminho: direto. "); }

    if(Energia > 30) { printf("Xupenio aprova! Nível: ELITE.\n"); }
    else if(Energia >= 10) { printf("Boa caminhada! Nível: SÓLIDO.\n"); }
    else if(Energia >= 0) { printf("Passou por pouco. Nível: BÁSICO.\n"); }
    else { printf("Xupenio reprova. Nível: CRÍTICO.\n"); }

    return 0;
}