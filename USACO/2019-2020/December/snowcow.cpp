*/ 
Coded up editorial solution, refer there.

/*

#include <bits/stdc++.h>
using namespace std;

#define f first
#define int long long
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

using node = ll;
struct BIT{
    //ask for queries 0 idxed or remove ++idx/++r
    vector<node> bit;
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
        for(idx++; idx < n; idx += idx & -idx){
            bit[idx] += delta;
        }
    }
};


int n, q, st[mxN], en[mxN], sz[mxN], ctr = 0;
vi adj[mxN];
BIT sub, val;
map<int, int> m[mxN];
void dfs(int u, int p){
    st[u] = ctr;
    en[u] = ctr;
    ctr++;
    trav(v, adj[u]){
        if(v == p) continue;
        dfs(v, u);
        ckmax(en[u], en[v]);
    }
    sz[u] = en[u] - st[u] + 1;
}
int updateSeg(int x, int y){
    sub.add(st[x], y); sub.add(en[x]+1, -y);
    val.add(st[x], y*sz[x]);
}
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("snowcow.in", "r", stdin);
    freopen("snowcow.out", "w", stdout);
    cin >> n >> q;
    sub.init(n); val.init(n);
    F0R(i, n-1){
        int a, b; cin >> a >> b; 
        a--; b--; adj[a].pb(b); adj[b].pb(a);
    }
    dfs(0, -1);
    while(q--){
        int t; cin >> t;
        if(t == 1){
            int upd, node; cin >> node >> upd;            
            node--;
            int& L = st[node], R = en[node];
            auto it = m[upd].upper_bound(L);
            if(it!=m[upd].begin() && en[prev(it)->s]>=R) continue;
            for(; it!=m[upd].end()&&en[it->s] <= R;){
                updateSeg(it->s, -1);
                m[upd].erase(it++);
            }
            m[upd][st[node]] = node; updateSeg(node, 1);
        } 
        else{
            int node; cin >> node;
            node--; cout << sz[node]*sub.sum(st[node])+val.sum(st[node]+1, en[node]) << nl;
        }
        
    }
    return 0;
}
