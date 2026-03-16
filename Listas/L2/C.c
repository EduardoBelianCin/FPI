#include <stdio.h>
#include <math.h>

int main() {
    int x,n; scanf("%d %d", &x,&n);

    int best_dist = -1;
    int best_canal = -1;
    int best_minuto = -1;
    int best_idx = -1;

    for(int i=1;i<=n;i++) {
        int a1,a2; scanf("%d %d", &a1,&a2);

        int cnt = 1;
        while(x >= a1 || x >= a2) {
            int dist1 = abs(x - a1), dist2 = abs(x - a2);

            if(best_dist == -1) {
                best_dist = dist1;
                best_canal = i;
                best_minuto = a1;
                best_idx = cnt;
            }
            else if(dist1 < best_dist) {
                best_dist = dist1;
                best_canal = i;
                best_minuto = a1;
                best_idx = cnt;
            }
            else if(dist1 == best_dist) {
                if(best_canal < i) {
                    best_dist = dist1;
                    best_canal = i;
                    best_minuto = a1;
                    best_idx = cnt;
                }
            }

            if(dist2 < best_dist) {
                best_dist = dist2;
                best_canal = i;
                best_minuto = a2;
                best_idx = cnt + 1;
            }
            else if(dist2 == best_dist) {
                if(best_canal < i) {
                    best_dist = dist2;
                    best_canal = i;
                    best_minuto = a2;
                    best_idx = cnt + 1;
                }
            }

            int temp = a2;
            a2 += a1;
            a1 = temp;
            cnt++;
        }
        int dist1 = abs(x - a1), dist2 = abs(x - a2);

        if(best_dist == -1) {
            best_dist = dist1;
            best_canal = i;
            best_minuto = a1;
            best_idx = cnt;
        }
        else if(dist1 < best_dist) {
            best_dist = dist1;
            best_canal = i;
            best_minuto = a1;
            best_idx = cnt;
        }
        else if(dist1 == best_dist) {
            if(best_canal < i) {
                best_dist = dist1;
                best_canal = i;
                best_minuto = a1;
                best_idx = cnt;
            }
        }

        if(dist2 < best_dist) {
            best_dist = dist2;
            best_canal = i;
            best_minuto = a2;
            best_idx = cnt + 1;
        }
        else if(dist2 == best_dist) {
            if(best_canal < i) {
                best_dist = dist2;
                best_canal = i;
                best_minuto = a2;
                best_idx = cnt + 1;
            }
        }
    }

    int valor = best_minuto;
    int soma_vip = 0;
    while(valor > 0) {
        soma_vip += valor%10;
        valor /= 10;
    }

    printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d", best_canal, best_idx);
    if(soma_vip > 10) { printf(" e com o VIP garantido!!!\n"); }
    else { printf(", mas o ingresso VIP não vai rolar :(\n"); }

    return 0;
}