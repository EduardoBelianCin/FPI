#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pii pair<int,int>
#define FORi(n) for(int i=0;i<n;i++)
#define FORj(n) for(int j=0;j<n;j++)
#define all(a) (a).begin(),(a).end()
#define printn(v,n) for(int i=0;i<n;i++) cout << v[i] << (i == n-1 ? "\n" : " ")

const int MAXN = 1e6+1;
int Ciclo[MAXN];

void solve() {
    int n = 1; Ciclo[1] = 1;

    queue<int> q; q.push(1);
    while(!q.empty()) {
        int x = q.front(); q.pop();

        if(x%2 == 0) {
            int x2 = x*2;
            if(x2 <= 1e6 && Ciclo[x2] == 0) { Ciclo[x2] = Ciclo[x] + 1; q.push(x2); }

            int y = (x-1)/3;
            if(x > 8 && y*3 + 1 == x && Ciclo[y] == 0) { Ciclo[y] = Ciclo[x] + 1; q.push(y); }
        }
        else {
            int x2 = x*2;
            if(x2 <= 1e6 && Ciclo[x2] == 0) { Ciclo[x2] = Ciclo[x] + 1; q.push(x2); }
        }
    }
}

void queries() {
    //int l,r;
    //while(cin>>l>>r) {

    //}
    vector<int> a(1e6+1, -1);
    for(int i=1;i<=1e6;i++) {
        a[i] = Ciclo[i];
    }

    int gh=0;
}

int main() {
    ios::sync_with_stdio(false);cin.tie(0);

    solve();
    queries();
}