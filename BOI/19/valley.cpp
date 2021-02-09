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
const int mxN = 1e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
int n, s, q, e;
vector<pair<int, ll>> adj[mxN];
bool shop[mxN];
int depth[mxN];
ll near[mxN];
ll dist[mxN];
int anc[mxN][20];
ll magic[mxN];
ll best[mxN][20];
pii edges[mxN];
 
void dfs(int u, int p){
    anc[u][0] = p;
    //cout << u << ' '<< dist[u] << nl;
    FOR(i, 1, 20){
        if(anc[u][i-1]==-1) anc[u][i] = -1;
        else anc[u][i] = anc[anc[u][i-1]][i-1];
    }
    near[u] = infLL;
    trav(v, adj[u]){
        if(v.f == p) continue;
        dist[v.f] = dist[u]+v.s;
        depth[v.f] = depth[u]+1;
        dfs(v.f, u);
        ckmin(near[u], near[v.f]+v.s);
    }
    if(shop[u]) near[u] = 0;
    magic[u] = -dist[u]+near[u];
    best[u][0] = magic[u];
}
void dfs2(int u, int p){
    //cout << u << ' ' << magic[u] << nl;
    FOR(i, 1, 20){
        if(anc[u][i-1]==-1) best[u][i]=magic[u];
        else best[u][i] = min(best[anc[u][i-1]][i-1], best[u][i-1]);
    }
    trav(v, adj[u]){
        if(v.f!=p){
            dfs2(v.f, u); 
        }
    }
}
 
int lca(int e1, int e2){
    if(depth[e1] < depth[e2]){
        swap(e1, e2);
    }
    int Dist = depth[e1] - depth[e2];
    R0F(i, 20){
        if((Dist)&(1<<i)){
            e1 = anc[e1][i];
        }
    }
    assert(depth[e1]==depth[e2]);
    if(e1 == e2) return e1;
    R0F(i, 20){
        if(anc[e1][i]!=anc[e2][i]) e1 = anc[e1][i], e2 = anc[e2][i];
    }
    assert(anc[e1][0] == anc[e2][0]);
    return anc[e1][0];
}
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> s >> q >> e; e--;
    F0R(i, n-1){
        int e1, e2, e3;
        cin >> e1 >> e2 >> e3; e1--; e2--;
        edges[i] = {e1, e2};
        adj[e1].pb({e2, e3});
        adj[e2].pb({e1, e3});
    }
    F0R(i, s){
        int e1; cin >> e1;
        shop[e1-1] = 1;
    }
    dfs(e, -1);
    dfs2(e, -1);
    F0R(qq, q){
        int i, r;
        cin >> i >> r;
        i--; r--; 
        if(depth[edges[i].f]<depth[edges[i].s]) swap(edges[i].f, edges[i].s);
        int ans = lca(edges[i].f, r);
        if(ans != edges[i].f) cout << "escaped\n";
        else{
            ll res = infLL;
            int R = r;
            F0R(j, 20){
                if((depth[R]-depth[edges[i].f]+1)&(1<<j)){
                    ckmin(res, dist[R]+best[r][j]);
                    r=anc[r][j];
                }
            }
            if(res>=(ll)1e15) cout << "oo\n";
            else cout << res << nl;
        }
    }
 
    return 0;
}
