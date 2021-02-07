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
const int mxN = 2e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
// modulo class
namespace modulo{
    int fact[mxN], invfact[mxN];
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
        invfact[mxN-1] = inv(fact[mxN-1]);
        for(int i = mxN - 2; i >= 0; i--) invfact[i] = mul(invfact[i+1], i+1);
    }
    int choose(const int& n, const int& k){ if(k > n) return 0; return mul(fact[n], mul(invfact[n-k], invfact[k])); }
    int invchoose(const int& n, const int& k){ if(k > n) return 0; return mul(invfact[n], mul(fact[n-k], fact[k])); }
};
using namespace modulo;
 
int n, k;
int a[mxN];
stack<int> stk;
vi l[mxN], r[mxN];
int lc[mxN], rc[mxN];
int ans[mxN];
 
void update(int pos, int val, int lx, int add){
    //cout << pos << ' ' << val << ' ' << lx << ' ' << add << 
    //' ' << lc[val] << ' ' << rc[val] << ' ' << invchoose(lc[val]+rc[val], lc[val]) << nl;
    ml(ans[pos], invchoose(lc[val]+rc[val], lc[val]));
    if(lx){
        if(add) lc[val]++;
        else lc[val]--;        
    }
    else{
        if(add) rc[val]++;
        else rc[val]--;
    }
    ml(ans[pos], choose(lc[val]+rc[val], lc[val]));
}
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    precalc();
    F0R(i, n) cin >> a[i];
    F0R(i, n){
        while(siz(stk)&&stk.top()>a[i]){
            l[i].pb(stk.top());
            stk.pop();
        }
        stk.push(a[i]);
    }
    stk=stack<int>();
    R0F(i, n){
        while(siz(stk)&&stk.top()>a[i]){
            r[i].pb(stk.top());
            rc[stk.top()]--;
            stk.pop();
        }
        stk.push(a[i]);
        rc[a[i]]++;
    }
    F0R(i, n){
        ans[i] = (i==0?1:ans[i-1]);
        if(i){
            update(i, a[i-1], 1, 1);
            trav(v, l[i-1]) update(i, v, 1, 0);
        }
        update(i, a[i], 0, 0);
        trav(v, r[i]) update(i, v, 0, 1);
    }
    while(k--){
        int q; cin >> q;
        cout << ans[q-1] << nl;
    }
    return 0;
}
