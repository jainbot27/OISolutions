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
 
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
//#define int long long
using namespace __gnu_pbds;
#define ordered_set tree<pair<ll, ll>, null_type,less<pair<ll, ll>>, rb_tree_tag,tree_order_statistics_node_update>
 
const char nl = '\n';
const int mxN = 2e5 + 10;
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
};
 
struct Stack{
    int a[mxN];
    int cur = -1;
    int size(){
        return cur + 1;
    }
    int top(){
        return a[cur];
    }
    void pop(){
        cur--;
    }
    void push(int x){
        cur++;
        a[cur] = x;
    }
};
 
centroid C;
int n;
vector<pair<int, ll>> adj[mxN];
int sz[mxN];
//stack<int> al;
Stack al;
set<int> nodes[mxN];
bool active[mxN];
ll cost[mxN];
int a[mxN];
vl costs; vi to_remove;
ll ans = 0;
 
void dfs(int u, int p, ll Cost, ll sum){
    cost[u] = Cost;
    trav(v, adj[u]){
        if(v.f == p || !active[v.f]) continue;
        dfs(v.f, u, min(sum+a[u]-v.s, Cost), sum+a[u]-v.s);
    }
}
 
void dfs2(int u, int p, ll Cost, ll sum){
    to_remove.pb(u);
    if(Cost >= 0){
        costs.pb(sum);
    }
    trav(v, adj[u]){
        if(p == v.f || !active[v.f]) continue;
            dfs2(v.f, u, min(a[v.f] - v.s, Cost + (a[v.f] - v.s)), sum + a[v.f] - v.s);
    }
}
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    F0R(i, n){
        cin >> a[i];
    }
    C.init(n);
    F0R(i, n-1){
        int e1, e2; ll w;
        cin >> e1 >> e2 >> w;
        e1--; e2--; 
        adj[e1].pb({e2, w});
        adj[e2].pb({e1, w});
        C.add(e1, e2);
    }
    C.init_centroid();
    F0R(i, n){
        if(C.par[i]!=-1){
            sz[C.par[i]]++;
        }
    }
    F0R(i, n){
        if(sz[i] == 0) al.push(i);
        //al.insert({sz[i], i});
        nodes[i].insert(i);
    }
    while(siz(al)){
        pii x;
        x.s = al.top();
        al.pop();
        //al.erase(al.begin());
        trav(X, nodes[x.s]){
            active[X] = 1;
        }
        cost[x.s] = 0;
        trav(c, adj[x.s]){
            if(!active[c.f]) continue;
            dfs(c.f, x.s, a[x.s]-c.s, a[x.s]-c.s);
        }
        ordered_set S;
        trav(X, nodes[x.s]){
            S.insert({cost[X], X});
            if(cost[X] >= 0) {
                ans++;
            }
        }
        trav(c, adj[x.s]){
            int child = c.f; 
            if(!active[child]) continue;
            to_remove.clear(); costs.clear();
            dfs2(child, x.s, a[c.f]-c.s, a[c.f]-c.s);
            trav(X, to_remove){
                S.erase({cost[X], X});
            }
            trav(X, costs){
                ans += siz(S) - S.order_of_key({-X, -1});
            }
            trav(X, to_remove){
                S.insert({cost[X], X});
            }
        }
        trav(X, nodes[x.s]){
            active[X] = 0;
        }
        if(C.par[x.s] != -1){
            int p = C.par[x.s];
            sz[p]--;
            if(sz[p]==0) al.push(p);
            if(siz(nodes[p]) < siz(nodes[x.s])){
                swap(nodes[p], nodes[x.s]);
            }
            trav(X, nodes[x.s]){
                nodes[p].insert(X);
            }
        }
    }
    cout << ans - n << nl;
    return 0;
}
