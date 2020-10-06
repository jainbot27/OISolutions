/*
Problem: http://www.usaco.org/index.php?page=viewproblem2&cpid=996
Solution Idea:
Notice that at the end we will have a bunch of connected components each which will have their own number of ways to solve. This motivates that if we can find the connected
components and the number of ways each of them has, we can solve the problem. We can use DSU to help us.

We walk up the graph and each time we go to a new row, the ways for each connected component always increases by 1, (every single component has 1 at the beginning). Also, when 
combining them, we just have to notice we can multiply the ways for each. 

This suffices to solve the problem in O(nlog*(n))
*/

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
const int mxN = 1e3 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

int add(int x, int y){ x += y; while(x >= MOD) x -= MOD; while(x < 0) x += MOD; return x; } void ad(int &x, int y) {x = add(x, y);}
int sub(int x, int y){ x -= y; while(x >= MOD) x -= MOD; while(x < 0) x += MOD; return x; } void sb(int &x, int y) {x = sub(x, y);}
int mul(int x, int y){ return ((int64_t)x * (int64_t)y) % MOD; } void ml(int &x, int y) {x = mul(x, y);}
int binpow(int x, int y){ int z = 1; while(y > 0) { if(y % 2 == 1) z = mul(z, x); x = mul(x, x); y /= 2; } return z; }
int inv(int x){ return binpow(x, MOD - 2); }
int divide(int x, int y){ return mul(x, inv(y)); }

int n, m, g[mxN][mxN], res = 1; 
int sz[mxN*mxN], par[mxN*mxN], ways[mxN*mxN];
char tmp;
unordered_set<int> uni;

int Find(int x){
    return x == par[x] ? par[x] : Find(par[x]);
}

void Comb(int a, int b){
    a = Find(a); b = Find(b);
    if(a == b) return;
    if(sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    ways[a] = mul(ways[a], ways[b]);
    par[b] = a;
}

inline int hsh(int x, int y){
    return x*mxN+y;
}

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("cave.in", "r", stdin); freopen("cave.out", "w", stdout);
    cin >> n >> m;    
    F0R(i, mxN*mxN) sz[i] = 1, par[i] = i, ways[i] = 1;
    F0R(i, n)
        F0R(j, m) 
            cin >> tmp, g[i][j] = tmp == '.';
    R0F(i, n){
        F0R(j, m){
            if(g[i][j]){
                if(g[i+1][j]&&Find(hsh(i,j)!=Find(hsh(i+1, j)))){
                    Comb(hsh(i, j), hsh(i+1, j));
                }
                if(g[i][j+1]&&Find(hsh(i, j))!=Find(hsh(i, j+1))){
                    Comb(hsh(i,j), hsh(i, j+1));
                }
            }
        }
        F0R(j, m)
            if(g[i][j])
                uni.insert(Find(hsh(i,j)));
        trav(un, uni)
            ad(ways[un], 1);
        uni.clear();
    }
    F0R(i, n)
        F0R(j, m)
            uni.insert(Find(hsh(i, j)));
    trav(un, uni)
        ml(res, ways[un]);
    cout << res << nl;
    return 0;
}
