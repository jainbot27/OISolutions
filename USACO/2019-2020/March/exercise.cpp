/*
  Notice the prinicple that an answer for a fixed permutation is the LCM of the cycles of that permutation. 
  So its worth considering -> what can we do with DP to calculate this quickly.
  It's easy to see we can calulate the answer for each prime factor individually (we only need to check numbers p^k)
  from there the array f represents number of ways to represent having all ways to have only cycle lengths of p^k
  r represents having none of these cycles. 
  We can then just raise to fac[n]-r and we do this all mod (MOD-1) since we want power (fermats little theorem). 
  Just do this for every number.
  
  Complexity: O(N^2) 
*/
#include <bits/stdc++.h>
using namespace std;

using ll=long long;

const int mxN=7501;

typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
FastMod F(2), G(2); 

int N, MOD;

int add(int x, int y, int mod=MOD-1){
    x+=y; if(x>=mod) x-=mod; return x;
}
int sub(int x, int y, int mod=MOD-1){
    x-=y; if(x<0) x+=mod; return x;
}
int mul(int x, int y, FastMod&q=F){
    return q.reduce(1LL*x*y);
}

bool comp[mxN];
int ans=1; 

int choose[mxN][mxN];
int fac[mxN];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); 
#ifndef ACMX
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
#endif
    cin >> N >> MOD; F=FastMod(MOD-1); G=FastMod(MOD); 
    choose[0][0]=1;
    for(int i=1; i<mxN; i++){
        choose[i][0]=choose[i][i]=1;
        for(int j=1; j<i; j++){
            choose[i][j]=add(choose[i-1][j-1], choose[i-1][j]);
        }
    }
    fac[0]=1; 
    for(int i=1; i<mxN; i++) fac[i]=mul(fac[i-1], i);
    for(int d=2; d<=N; d++){
        if(comp[d]) continue;
        for(int k=d; k<=N; k*=d){
            vector<int> f(N/k+1), r(N/k+1); 
            f[0]=1;
            for(int i=1; i<=N/k; i++){
                for(int j=1; j<=i; j++){
                    f[i]=add(f[i], mul(f[i-j], mul(fac[k*j-1], choose[i*k-1][j*k-1])));
                }
            }
            for(int i=N/k; i>=0; i--){
                r[i]=fac[N-i*k];
                for(int j=i+1; j<=N/k; j++){
                    r[i]=sub(r[i], mul(choose[N-i*k][N-j*k], mul(f[j-i], r[j])));
                }
            }
            int expo=sub(fac[N], r[0]); int base=d; 
            while(expo){
                if(expo&1){
                    ans=mul(ans, base, G);
                }
                base=mul(base, base, G);
                expo/=2;
            }
        }
        for(int dd=d*2; dd<=N; dd+=d){
            comp[dd]=1;
        }
    }
    cout << ans << '\n';
}
