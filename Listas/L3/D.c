#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)

int main() {
    char ans[100]; int idx_ans = 0;

    int t; scanf("%d", &t);
    FORi(t) {
        char S[61];
        int f; scanf("%s %d", S,&f);

        // calcula o tamanho de S
        int S_size = 0;
        while(S[S_size] != '\0') { S_size++; }

        
        // inteiro x pra representar a string S como se fossem bits
        long long x = 0;
        FORj(S_size) {
            // se o bit j ta ligado, eu adiciono 2^j a x
            if(S[j] == 'O') { x += (1LL << j); }
        }
        // adiciono os clocks, se x passar do limite de bits, tira o mod
        x += f; x %= (1LL << S_size);
        // converto x pra string novamente
        FORj(S_size) {
            // checa se o bit j de x é 1
            if(x & (1LL << j)) { S[j] = 'O'; }
            else { S[j] = 'X'; }
        }

        // Print do estado final de S
        printf("%s\n", S);

        // Ornamento
        if(i > 0) {
            // tamanho par
            if(idx_ans%2 == 0) {
                // estados iguais
                if(ans[idx_ans-1] == S[0]) { ans[idx_ans] = '@'; }
                // estados diferentes
                else { ans[idx_ans] = '$'; }
            }
            // tamanho impar
            else {
                // estados iguais
                if(ans[idx_ans-1] == S[0]) { ans[idx_ans] = '#'; }
                // estados diferentes
                else { ans[idx_ans] = '%'; }
            }
            idx_ans++; 
        }
        // Adiciona S na Resposta final
        FORj(S_size) { ans[idx_ans] = S[j]; idx_ans++; }
    }
    // Print final
    ans[idx_ans] = '\0';
    printf("%s\n", ans);

    return 0;
}