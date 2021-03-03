#include <bits/stdc++.h>
using namespace std;

//#define int ll 
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
    int n, m=0; vi d; vector<ar<int, 25>> anc; vector<vi> adj;
    void init(int _n){ n = _n; adj.resize(n); d.resize(n, 0); anc.resize(n);}
    void add(int a, int b){ adj[a].pb(b); adj[b].pb(a); }
    void add1(int a, int b){ add(a-1, b-1); }
    void dfs(int u = 0, int p = -1){
        anc[u][0] = p; FOR(i, 1, 25) {anc[u][i]=(anc[u][i-1]==-1?-1:anc[anc[u][i-1]][i-1]);}
        trav(v, adj[u]){
            if(p == v) continue; d[v] = d[u]+1; dfs(v, u);
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
};

int n, m, a, b, k;
ll da[mxN], db[mxN];
int par[mxN], imp[mxN], sp[mxN];
vpii adj[mxN];
ar<int, 3> edges[mxN];
ll ans[mxN];
using MIN_HEAP = pair<ll, int>;
priority_queue<MIN_HEAP, vector<MIN_HEAP>, greater<MIN_HEAP>> pq;
LCA l;

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> a >> b; 
    F0R(i, m){
        F0R(j, 3) cin >> edges[i][j];
        edges[i+m] = edges[i]; swap(edges[i+m][0], edges[i+m][1]);
        adj[edges[i][0]].pb({edges[i][1], edges[i][2]});
        adj[edges[i][1]].pb({edges[i][0], edges[i][2]});
    }
    F0R(i, n+1) db[i] = infLL, da[i] = infLL;
    db[b] = 0;
    pq.push({0, b});
    while(!pq.empty()){
        MIN_HEAP t = pq.top();
        pq.pop();
        if(t.f!=db[t.s]) continue;
        trav(nxt, adj[t.s]){
            if(ckmin(db[nxt.f], nxt.s+t.f)){
                pq.push({db[nxt.f], nxt.f});
            }
        }
    }
    da[a] = 0;
    pq.push({0, a});
    while(!pq.empty()){
        MIN_HEAP t = pq.top();
        pq.pop();
        if(t.f!=da[t.s]) continue;
        trav(nxt, adj[t.s]){
            if(ckmin(da[nxt.f], t.f+nxt.s)){
                pq.push({da[nxt.f], nxt.f});
                par[nxt.f] = t.s;
            }
        }
    }
    cin >> k;
    F0R(i, k){
        cin >> imp[i]; 
        ans[i] = infLL;
        if(i) par[imp[i]] = imp[i-1];
    } 
    l.init(n+1);
    FOR(i, 1, n+1){
        if(par[i]!=0) l.add(par[i], i);
        //cout << par[i] << ' ';
    }
    //cout << nl;
    l.dfs(a, 0);
    F0R(i, 2*m){
        int u = edges[i][0], v = edges[i][1], d = edges[i][2];
        //if(sp[u]==v||sp[v]==u) continue;
        if(par[u]==v||par[v]==u) continue;
        int x = l.lca(u, b), y = l.lca(v, b);
        //if(u==x&&v==y) continue;
        //x = l.d[x], y = l.d[y];
        //cout << x << ' ' << y << nl;
        //cout << u << ' ' << v << ' ' << x << ' ' << y << ' ' << l.d[x] << ' ' << l.d[y] << ' ' << d << nl;
        FOR(j, l.d[x], l.d[y]){
            ckmin(ans[j], da[u]+db[v]+d); 
        }
    }
    //FOR(i, 1, n+1) cout << l.d[i] << ' ';
    //cout << nl;
    //F0R(i, n) cout << da[i+1] << ' ';
    //cout << nl;
    //F0R(i, n) cout << db[i+1] << ' ';
    //cout << nl;

    F0R(i, k-1){
        cout << (ans[i]==infLL?-1LL:ans[i]) << nl;
    }
    return 0;
}
