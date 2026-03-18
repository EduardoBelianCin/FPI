#include <stdio.h>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define FORk(n) for(int k=0;k<n;k++)

int main() {
    int t; scanf("%d", &t);

    FORi(t) {
        int n; scanf("%d", &n);

        int Seq[100];
        int Best_Seq[100];
        int idx = 0;
        int best_size = 0;

        FORj(n) {
            int x; scanf("%d", &x);
            
            if(j==0) { Seq[idx] = x; idx++; }
            else {
                if(x >= Seq[idx-1]) {
                    if(idx > best_size) {
                        FORk(idx) { Best_Seq[k] = Seq[k]; }
                        best_size = idx;
                    }
                    idx = 0; Seq[idx] = x; idx++;
                }
                else { Seq[idx] = x; idx++; }

                if(j == n-1) {
                    if(idx > best_size) {
                        FORk(idx) { Best_Seq[k] = Seq[k]; }
                        best_size = idx;
                    }
                }
            }
        }

        if(best_size == 1) { best_size = 0; }

        printf("%d\n", best_size);
        FORi(best_size) {
            printf("%d", Best_Seq[i]);
            if(i < best_size-1) { printf(" "); }
        }
        if(best_size > 0) { printf(" \n"); }
    }

    return 0;
}