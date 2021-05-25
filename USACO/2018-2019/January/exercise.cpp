/*
  Read the editorial (:weary:) 
  Just do casework but its really annoying to figure out all the tiny details.
  
  Complexity: O(nlogn)
*/
#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define ar array
#define all(x) x.begin(), x.end()
#define siz(x) (int) x.size()
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
#define FOR(i, a, b) for(auto i=(a); i<(b); i++)
#define ROF(i, a, b) for(auto i=(b)-1; i>=(a); i--)
#define F0R(i, n) FOR(i, 0, n)
#define R0F(i, n) ROF(i, 0, n)

using ll=long long;
using ld=long double;
using pii=pair<int, int>;
using pll=pair<ll, ll>;
using vi=vector<int>;
using vl=vector<ll>;
using vpii=vector<pii>;

template<class T> bool ckmin(T&a, const T&b) {return b<a?a=b,1:0;}
template<class T> bool ckmax(T&a, const T&b) {return b>a?a=b,1:0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int mxN=2e5+10;
const int MOD=1e9+7; 
const ll infLL=1e18;
const ld eps=1e-6;

struct LCA{
    int n, m=0; vi d; vector<ar<int, 25>> anc; vector<vi> adj;
    void init(int _n){ n = _n; adj.resize(n); d.resize(n, 0); anc.resize(n);}
    void add(int a, int b){ adj[a].pb(b); adj[b].pb(a); }
    void add1(int a, int b){ add(a-1, b-1); }
    void dfs(int u = 0, int p = -1){
        anc[u][0] = p; FOR(i, 1, 25) {anc[u][i]=(anc[u][i-1]==-1?-1:anc[anc[u][i-1]][i-1]);}
        for(auto v:adj[u]){
            if(p == v) continue; d[v] = d[u]+1; dfs(v, u);
        }
    }
    int lift(int a, int k){
        if(k<0) return -1;
        R0F(i, 25){if(k&(1<<i)) a = anc[a][i];}
        return a;
    }
    int lca(int a, int b){
        if(d[a] < d[b]) swap(a, b);
        a=lift(a, d[a]-d[b]);
        if(a==b) return a;
        R0F(i, 25){if(anc[a][i] == anc[b][i]) continue;a = anc[a][i]; b = anc[b][i];}
        return anc[a][0];
    }
    int dist(int a, int b){ int l = lca(a, b); return d[a]+d[b]-2*d[l];}
};

template<class F> struct y_combinator_result{
    F f;
    template<class T> explicit y_combinator_result(T &&f): f(forward<T>(f)){ }
    template<class ...Args> decltype(auto) operator()(Args &&...args){ return f(ref(*this), forward<Args>(args)...); }
};
template<class F> decltype(auto) y_combinator(F &&f){
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    #ifndef ACMX
        freopen("exercise.in", "r", stdin);
        freopen("exercise.out", "w", stdout);
    #endif
    int n, m; cin >> n >> m;
    const int q=m-(n-1);
    LCA L; L.init(n); 
    F0R(i, n-1){
        int e1, e2; cin >> e1 >> e2; L.add1(e1, e2);
    }
    L.dfs();
    vector<int> u(q), v(q), lca(q), comp(n);
    ll ans=0;
    map<pii, int> mp;
    F0R(i, q){
        cin >> u[i] >> v[i]; u[i]--; v[i]--; 
        lca[i]=L.lca(u[i], v[i]);
        int l=L.lift(u[i], L.d[u[i]]-L.d[lca[i]]-1);
        if(l!=-1){
            ans-=++comp[l];
        }
        int r=L.lift(v[i], L.d[v[i]]-L.d[lca[i]]-1);
        if(r!=-1){
            ans-=++comp[r];
        }
        if(l!=-1&&r!=-1){
            if(l>r) swap(l, r);
            ans-=mp[{l, r}]++; 
        }    
    }
    vl ps(n);
    y_combinator([&](auto dfs, int u, int p, ll amt)->void{
        ps[u]=amt+comp[u];
        for(auto v:L.adj[u]) 
            if(v!=p){
                dfs(v, u, ps[u]);
            }
    })(0, -1, 0); 
    F0R(i, q){
        ans+=ps[u[i]]+ps[v[i]]-2*ps[lca[i]];
    }
    cout << ans << "\n";
    return 0; 
}

