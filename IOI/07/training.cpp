/*
dolphin garlic orz
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
const int mxN = 5001;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
int n, m, cost;
vi adj[mxN];
int depth[mxN];
int st[mxN], en[mxN];
pii par[mxN]; int dg[mxN];
int dp[mxN][1<<10];
 
int ti;
struct road{
    int a, b, c, lca;
    bool operator<(const road& other) const{
        return en[lca]<en[other.lca];
    };
};
 
vector<road> r;
 
void dfs(int u, int p){
    depth[u] = !depth[p];
    st[u] = ++ti; 
    trav(x, adj[u]){
        if(x != p){
            par[x] = {u, 1<<dg[u]++};
            dfs(x, u);
        }
    }
    en[u] = ++ti;
}
 
bool parent(int x, int y){
    return st[x] <= st[y]&&en[x] >= en[y];
}
int lca(int x, int y){
    while(!parent(x, y)) x=par[x].f;
    return x;
}
 
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    F0R(i, m){
        int e1, e2, e3; cin >> e1 >> e2 >> e3;
        cost += e3;
        if(e3==0){
            adj[e1].pb(e2);
            adj[e2].pb(e1);
        }
        r.pb({e1, e2, e3});
    }
    dfs(1, 0);
    F0R(i, m) r[i].lca=lca(r[i].a, r[i].b);
    sort(all(r));
    trav(i, r){
        if(i.c&&depth[i.a]^depth[i.b]) continue;
        int sm = i.c;
        pii A, B;
        for(A={i.a, 0}; A.f!=i.lca; A=par[A.f]) {
            sm+=dp[A.f][A.s];
        }
        for(B={i.b, 0}; B.f!=i.lca; B=par[B.f]) {
            assert(B.f!=0);
            sm+=dp[B.f][B.s];
        }
 
 
 
        R0F(msk, (1<<dg[i.lca])){
            if(!(msk&A.s||msk&B.s)){
                ckmax(dp[i.lca][msk], sm+dp[i.lca][msk|A.s|B.s]);
            }
        }
    }
    cout << cost-dp[1][0];
    return 0;
}
