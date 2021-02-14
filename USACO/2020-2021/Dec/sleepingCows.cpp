#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define ar array
#define all(x) x.begin(), x.end()
#define siz(x) (int)x.size()

#define FOR(x, y, z) for(int x = (y); x < (z); x++)
#define ROF(x, z, y) for(int x = (y-1); x >= (z); x--)
#define F0R(x, z) FOR(x, 0, z)
#define R0F(x, z) ROF(x, 0, z)
#define trav(x, y) for(auto&x:y)

using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using pii = pair<int, int>;
using vpii = vector<pair<int, int>>;

template<class T> inline bool ckmin(T&a, T b) {return b < a ? a = b, 1 : 0;}
template<class T> inline bool ckmax(T&a, T b) {return b > a ? a = b, 1 : 0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const char nl = '\n';
const int mxN = 3001;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

namespace modulo{
    int fact[mxN];
    int add(const int& x, const int& y){ int res = x; res += y; while(res >= MOD) res -= MOD; while(res < 0) res += MOD; return res; } 
    void ad(int &x, const int& y) {x = add(x, y);}
    int sub(const int& x, const int& y){ int res = x; res -= y; while(res >= MOD) res -= MOD; while(res < 0) res += MOD; return res; } 
    void sb(int &x, const int& y) {x = sub(x, y);}
    int mul(const int& x, const int& y){ return (1LL*x*y) % MOD; } 
    void ml(int &x, const int& y) {x = mul(x, y);}
    int binpow(int x, int y){ int z = 1; while(y > 0) { if(y % 2 == 1) z = mul(z, x); x = mul(x, x); y /= 2; } return z; }
    int inv(const int& x){ return binpow(x, MOD - 2); }
    int divide(const int& x, const int& y){ return mul(x, inv(y)); }
    void precalc(){ 
        fact[0] = 1; 
        for(int i = 1; i < mxN; i++) fact[i] = mul(i, fact[i - 1]); 
    }
};
using namespace modulo;

int n;
pii arr[2*mxN];
int v[2*mxN];
int dpf[2*mxN][mxN], dpb[2*mxN][mxN], dp[2*mxN][mxN];
int ans = 0;

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    precalc();
    cin >> n;
    F0R(i, n) arr[i].s = 0, cin >> arr[i].f;
    F0R(i, n) arr[n+i].s = 1, cin >> arr[n+i].f;
    sort(arr, arr+2*n);
    F0R(i, 2*n) v[i] = arr[i].s;
    F0R(type, 2){
        dp[0][0] = 1;
        F0R(i, 2*n){
            if(v[i] == 0){
                F0R(j, n) 
                    dp[i+1][j+1] = dp[i][j];
            }
            else{
                FOR(j, 1, n+1)
                    dp[i+1][j-1] = mul(dp[i][j], j);
                F0R(j, n+1)
                    ad(dp[i+1][j], dp[i][j]);
            }
        }
        if(!type) memcpy(dpf, dp, sizeof(dp));
        else memcpy(dpb, dp, sizeof(dp));
        memset(dp, 0, sizeof(dp));
        reverse(v, v+2*n);
        F0R(i, 2*n) v[i] ^= 1;
    }
    reverse(dpb, dpb+2*n+1);
    ad(ans, dpf[2*n][0]);
    F0R(i, 2*n){
        if(v[i]==0){
            F0R(j, n+1){
                ad(ans, mul(fact[j], mul(dpf[i][j], dpb[i+1][j])));
            }
        }
    }
    cout << ans << nl;
    return 0;
}
