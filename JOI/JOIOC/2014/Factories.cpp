/*
Main Idea:

Consider O(QN) solution where we answer each query by updating the value of bst[node] thats a parent of some x[i] in O(n) at worst (if the tree is a chain). Then answering
queries can also be done in O(n) by walking up all parents and taking bst[p] + dist(u, p). 

Now look at the centroid decomp of the tree and notice we can do the exact same thing, except now the height will be at most logn. This way we can queries in O(logn*(S+T))

Now one final thing is that logN LCA doesn't pass and we must do better. This is okay because finding LCA in a tree can actually be done in O(1) with rmq + euler tour.

This is how we arrive at O(sumof(S+T)logn+nlogn) as our solution, and we are done.

Couple extra notes:
This solution isn't the quickest and runs in 7911ms/8000. Additionally, the LCA template used is not my own implementation, it is benq's. 

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
const int mxN = 5e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

struct centroid{
    vector<vector<int>> adj;
    vector<bool> vis;
    vi par, sz;
    int n;
    void init(int _n){ n = _n; adj.resize(n); par.resize(n); sz.resize(n); vis.resize(n, 0);}
    void add(int a, int b) {adj[a].pb(b); adj[b].pb(a);}
    int find_size(int u, int p = -1) {
        if(vis[u]) return 0;
        sz[u] = 1;
        trav(v, adj[u]){
            if(v != p)
                sz[u] += find_size(v, u);
        }
        return sz[u];
    }
    int find_centroid(int u, int p, int N){
        trav(v, adj[u]){
            if(v!=p&&!vis[v]&&sz[v]>N/2)
                return find_centroid(v, u, N);
        }
        return u;
    }
    void init_centroid(int u = 0, int p = -1){
        find_size(u);
        int c = find_centroid(u, -1, sz[u]);
        vis[c] = 1;
        par[c] = p;
        trav(v, adj[c])
            if(!vis[v])
                init_centroid(v, c);
    }
}C;
#define rsz resize
#define pi pii
#define vpi vpii
#define eb emplace_back
#define sz siz
template<class T> struct RMQ {
	int level(int x) { return 31-__builtin_clz(x); } 
	vector<T> v; vector<vi> jmp;
	int comb(int a, int b) { 
		return v[a]==v[b]?min(a,b):(v[a]<v[b]?a:b); } 
	void init(const vector<T>& _v) {
		v = _v; jmp = {vi(sz(v))}; iota(all(jmp[0]),0);
		for (int j = 1; 1<<j <= sz(v); ++j) {
			jmp.pb(vi(sz(v)-(1<<j)+1));
			F0R(i,sz(jmp[j])) jmp[j][i] = comb(jmp[j-1][i],
									jmp[j-1][i+(1<<(j-1))]);
		}
	}
	int index(int l, int r) { 
		assert(l <= r); int d = level(r-l+1);
		return comb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
	T query(int l, int r) { return v[index(l,r)]; }
};
struct LCA {
	int N; vector<vi> adj;
	vi depth, pos, par, rev;
	vpi tmp; RMQ<pi> r;
	void init(int _N) { N = _N; adj.rsz(N); 
		depth = pos = par = rev = vi(N); }
	void ae(int x, int y) { adj[x].pb(y), adj[y].pb(x); }
	void dfs(int x) {
		pos[x] = sz(tmp); tmp.eb(depth[x],x); 
		trav(y,adj[x]) if (y != par[x]) {
			depth[y] = depth[par[y]=x]+1, dfs(y);
			tmp.eb(depth[x],x); }
	}
	void gen(int R = 0) { par[R] = R; dfs(R); r.init(tmp); }
	int lca(int u, int v){
		u = pos[u], v = pos[v]; if (u > v) swap(u,v);
		return r.query(u,v).s; }
	int dist(int u, int v) {
		return depth[u]+depth[v]-2*depth[lca(u,v)]; }
	vpi compress(vi S) {
		auto cmp = [&](int a, int b) { return pos[a] < pos[b]; };
		sort(all(S),cmp); R0F(i,sz(S)-1) S.pb(lca(S[i],S[i+1]));
		sort(all(S),cmp); S.erase(unique(all(S)),end(S));
		vpi ret{{0,S[0]}}; F0R(i,sz(S)) rev[S[i]] = i;
		FOR(i,1,sz(S)) ret.eb(rev[lca(S[i-1],S[i])],S[i]);
		return ret;
	}
} L;

int n, q; ll bst[mxN], dep[mxN]; vector<pair<int, ll>> adj[mxN];
void dfs(int u, int p){
    trav(v, adj[u]){
        if(v.f == p) continue;
        dep[v.f] = dep[u] + v.s;
        dfs(v.f, u);
    }
}
ll getDist(int u, int v){
    int l = L.lca(u, v);
    return dep[u] + dep[v] - 2 * dep[l];
}
void upd(int u, int d){
    int orig = u;
    while(u != -1){
        if(d==1)
            ckmin(bst[u], getDist(u, orig));
        else 
            bst[u] = infLL;
        u = C.par[u];
    }
}
ll qry(int u){
    int orig = u;
    ll res = infLL;
    while(u != -1){
        ckmin(res, getDist(u, orig) + bst[u]);
        u = C.par[u];
    }
    return res;
}
void Init(int N, int A[], int B[], int* D){
    n = N;
    L.init(n);
    C.init(n);
    F0R(i, n){
        bst[i] = infLL;
    }
    FOR(i, 0, n-1){
        int e1 = A[i], e2 = B[i]; ll e3 = D[i];
        adj[e1].pb({e2, e3});
        adj[e2].pb({e1, e3});
        L.ae(e1, e2);
        C.add(e1, e2);
    }
    L.dfs(0);
    dfs(0, -1);
    C.init_centroid();
    L.gen();
}
ll Query(int S, int x[], int T, int y[]){
    F0R(i, S){
        upd(x[i], 1);
    }
    ll ans = infLL;
    F0R(i, T){
        ckmin(ans, qry(y[i]));
    }
    F0R(i, S){
        upd(x[i], 0);
    }
    return ans;
}
