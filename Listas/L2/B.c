#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)

int main() {
    int n,k,p; scanf("%d %d %d", &n,&k,&p);

    int qtd_validos = 0;
    int min_valido = -1;

    for(int i=n;i<k;i++) {
        int valid = 1;
        int x = i;
        int cnt = 0;
        while(x%2 == 0) { x /= 2; }
        int freq_3 = 0;
        while(x%3 == 0) { x /= 3; freq_3++; }

        if(freq_3 > 1) { valid = 0; }
        else { cnt += freq_3; }
        

        int teste = 6;
        while(valid == 1 && cnt <= p && x > 1) {
            int tent1 = teste-1, freq1 = 0;
            while(x%tent1 == 0) { x /= tent1; freq1++; }

            int tent2 = teste+1, freq2 = 0;
            while(x%tent2 == 0) { x /= tent2; freq2++; }

            if(freq1 > 1 || freq2 > 1) { valid = 0; }
            else { cnt += freq1; cnt += freq2; }

            teste += 6;
        }
        if(valid == 1 && cnt == p) {
            if(min_valido == -1) { min_valido = i; }
            qtd_validos++;
        }
    }

    if(min_valido != -1) {
        qtd_validos--;
        printf("%d %d\n", min_valido, qtd_validos );
    }
    else {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    }

    return 0;
}