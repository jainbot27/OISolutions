/*
Main Idea:
Consider the problem where each of the m sets only consist of 2 nodes. Then we can process offline and add one to both the nodes and subtract 2 at LCA. 

This idea spreads to when we have multiple nodes as long as we sort by preorder. Also we double count, so divide by 2.

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
const int mxN = 2e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
struct LCA{
    int n, m=0, ctr = 0; vi d; vector<ar<int, 25>> anc; vector<vi> adj; vi st, en, sum;
    void init(int _n){ n = _n; adj.resize(n); d.resize(n, 0); anc.resize(n); st.resize(n); en.resize(n), sum.resize(n, 0); }
    void add(int a, int b){ adj[a].pb(b); adj[b].pb(a); }
    void add1(int a, int b){ add(a-1, b-1); }
    void dfs(int u = 0, int p = -1){
        anc[u][0] = p; FOR(i, 1, 25) {anc[u][i]=(anc[u][i-1]==-1?-1:anc[anc[u][i-1]][i-1]);}
        st[u] = en[u] = ctr; ctr++;
        trav(v, adj[u]){
            if(p == v) continue; d[v] = d[u]+1; dfs(v, u);
            ckmax(en[u], en[v]);
        }
    }
    void dfs2(int u = 0, int p = -1){
        trav(v, adj[u]){
            if(v==p) continue;
            dfs2(v, u);
            sum[u] += sum[v];
        }
    }
    int lca(int a, int b){
        if(d[a] < d[b]) swap(a, b);
        int dif = d[a] - d[b];
        R0F(i, 25){if(dif&(1<<i)) a = anc[a][i];}
        if(a==b) return a;
        R0F(i, 25){if(anc[a][i] == anc[b][i]) continue;a = anc[a][i]; b = anc[b][i];}
        return anc[a][0];
    }
    int dist(int a, int b){ int l = lca(a, b); return d[a]+d[b]-2*d[l];}
} L;
 
int n, m, k; map<pii, int> e;
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    L.init(n);
    F0R(i, n-1){
        int x, y; cin >> x >> y; L.add1(x, y); 
        e[{x-1, y-1}] = i + 1;
        e[{y-1, x-1}] = i + 1;
    }
    L.dfs();
    F0R(ii, m){
        int S; cin >> S;
        vi x(S);
        F0R(i, S) cin >> x[i], x[i]--;
        sort(all(x), [&](int e1, int e2){
            return L.st[e1] < L.st[e2];
        });
        F0R(i, S){
            int j = (i + 1) % S;
            L.sum[x[i]]++, L.sum[x[j]]++;
            // cout << i << " " << j << " " << L.lca(i, j) << nl;
            L.sum[L.lca(x[i], x[j])]-= 2;
        }
    }
    L.dfs2();
    vi res;
    FOR(i, 1, n){
        // cout << L.sum[i] << " ";
        if(L.sum[i]>=2*k){
            res.pb(e[{i, L.anc[i][0]}]);
        }
    }
    // cout << nl;
    sort(all(res));
    cout << siz(res) << nl;
    trav(r, res){
        cout << r << " ";
    }
    cout << nl;
    return 0;
}
