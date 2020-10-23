/*

notice that there is a group of winning people and losing people and the winning people have an edge to every losing person.
It's also important to process nodes in topo sort order. 


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


int n, vis[mxN], deg[mxN], e, ans = -1; 
vi adj[mxN], order;

void dfs(int u){
    vis[u] = 1;
    trav(v, adj[u])
        if(!vis[v])
            dfs(v);
    order.pb(u);
}
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    F0R(i, n){
        int sz; cin >> sz;
        F0R(j, sz){
            int x; cin >> x;
            adj[i].pb(--x);
        }
    }
    F0R(i, n)
        if(!vis[i])
            dfs(i);
    reverse(all(order));
    memset(vis, 0, sizeof vis);
    F0R(i, n){
        int x = order[i];
        vis[x] = 1;
        e-=deg[x];
        trav(v, adj[x]){
            if(vis[v]) continue;
            e++;
            deg[v]++;
        }
        //cout << e << ' ' << i << ' ' << x  << endl;
        if(e == 1LL * (i + 1) * (n - i - 1)){
            ans = i;
            break;
        }
    }
    cout << ans + 1 << ' ';
    sort(order.begin(), order.begin() + ans + 1);
    F0R(i, ans+1){
        cout << order[i] + 1 << ' ';
    }
    cout << nl;
    return 0;
}
