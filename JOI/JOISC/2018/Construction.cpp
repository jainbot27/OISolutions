/*
Notice that when we update stuff we are setting a lot of things equal to each other meaning they don't have to be treated seperately. 
In this way, for each chain in the HLD of the tree we with every update can write over chains but we amortized won't have that many to go through.
I don't have a proof but apparently with the properties of HLD we can prove something like logn per query over many of them.


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
const int mxN = 1e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
const int inf = 1e9;
 
 
int n, a[mxN], par[mxN], heavy[mxN], depth[mxN], root[mxN]; 
pii e[mxN];
vi adj[mxN];
vpii vals[mxN];
typedef int node;
struct BIT{
    vector<node> bit;
    vpii ops;
    int n;
    void init(int x){
        n=x+1;
        bit.assign(n + 1,0);
    }
    node sum(int r){
        node ret = 0;
        for(r++; r ; r -= r & -r){
            ret += bit[r];
        }
        return ret;
    }
    node sum(int l, int r){
        return sum(r) - sum(l-1);
    }
    void add(int idx, node delta){
        ops.pb({idx, delta});
        for(idx++; idx < n; idx += idx & -idx){
            bit[idx] += delta;
        }
    }
    void clear(){
        trav(x, ops){
            add(x.f, -x.s);
        }
        ops.clear();
    }
};
 
BIT B;
int dfs(int u, int p){
    int sz = 1, mxSub = 0;
    trav(v, adj[u]){
        if(v == p)
            continue;
        par[v] = u;
        depth[v] = depth[u] + 1;
        int d = dfs(v, u);
        if(ckmax(mxSub, d)) heavy[u] = v;
        sz += d;
    }
    return sz;
}
ll query(int v){
    int r = root[v], tot = depth[v]-depth[r]+1;
    vpii tmp;
    R0F(i, siz(vals[r])){
        auto cur = vals[r][i];
        if(cur.s >= tot){
            tmp.pb({cur.f, tot});
            break;
        }
        else{
            tot -= cur.s;
            tmp.pb(cur);
        }
    }
    reverse(all(tmp));
    ll res = 0;
    trav(x, tmp){
        res += (ll)x.s * B.sum(x.f-1);
        B.add(x.f, x.s);
    }
    return res;
}
ll queryAns(int v){
    ll ans = 0;
    B.clear();
    for(; v != -1; v = par[root[v]]) ans+= query(v);
    return ans;
}
void upd(int v, int val){
    int r = root[v], tot = depth[v] - depth[r] + 1;
    int tmp=tot;
    while(vals[r].back().s < tot) {
        tot -= vals[r].back().s;
        vals[r].pop_back();
    }
    vals[r].back().s -= tot;
    if(vals[r].back().s == 0) vals[r].pop_back();
    vals[r].pb({val, tmp});
}
void updAns(int v, int val){
    for(; v != -1; v = par[root[v]]) upd(v, val);
}
void compress(){
    map<int, int> m;
    F0R(i, n) m[a[i]]=0;
    int xx = 0;
    trav(xd, m) xd.s = xx ++;
    F0R(i, n) a[i] = m[a[i]];
}
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    B.init(mxN);
    cin >> n;
    F0R(i, n) cin >> a[i];
    compress();
    F0R(i, n-1){
        cin >> e[i].f >> e[i].s;
        e[i].f--; e[i].s--;
        adj[e[i].f].pb(e[i].s);
        adj[e[i].s].pb(e[i].f);
    }
    F0R(i, n) heavy[i] = -1;
    par[0] = -1; depth[0] = 0;
    dfs(0, -1);
    F0R(i, n){
        if(par[i] == -1 || heavy[par[i]] != i){
            for(int j = i; j != -1; j = heavy[j]){
                root[j] = i;
                vals[i].pb({0, 1});
            }
        }
    }
    updAns(0, a[0]);
    F0R(i, n-1){
        cout << queryAns(e[i].f) << nl;
        updAns(e[i].s, a[e[i].s]);
    }
    return 0;
}
