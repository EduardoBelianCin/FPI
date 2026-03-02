#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)

int main() {
    int n,x,y,z; scanf("%d %d %d %d", &n,&x,&y,&z);
    int v[] = {x,y,z};

    if(v[0] > v[1]) { int temp = v[0]; v[0] = v[1]; v[1] = temp; }
    if(v[1] > v[2]) { int temp = v[1]; v[1] = v[2]; v[2] = temp; }
    if(v[0] > v[1]) { int temp = v[0]; v[0] = v[1]; v[1] = temp; }

    int soma = 0, ans = 0;
    FORi(3) {
        soma += v[i];
        if(soma <= n) { ans++; }
        else { break; }
    }
    printf("%d\n", ans);

    return 0;
}