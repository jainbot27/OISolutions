/*
Could'nt find construction decided to read someone else's code :(


*/

#include <bits/stdc++.h>
// #include "stations.h"
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
const int mxN = 1001;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
vi label(int N, int K, vi U, vi V){
    vector<vi> adj(N);
    F0R(i, N-1){
        adj[U[i]].pb(V[i]);
        adj[V[i]].pb(U[i]);
    }
    vi res(N); int idx = 0;
    function<void(int, int)> dfs;
    dfs = [&] (int u, int p){
        if(p == -1 || !res[p]) res[u] = ++idx;
        trav(v, adj[u]) if(v != p) dfs(v, u);
        if(!res[u]) res[u] = ++idx;
    };
    dfs(0, -1);
    return res;
}
 
int find_next_station(int s, int t, vi c){
    if(c.back() < s) reverse(all(c));
    trav(x, c) {
        if(min(s, x) <= t && t <= max(s, x)) return x;
    }
    return c.back();
}
 
// int main(){
//     int n, k; cin >> n >> k;
//     vi U, V;
//     F0R(i, n-1){
//         int uu, vv; cin >> uu;
//         U.pb(uu);
//     }
//     F0R(i, n-1){
//         int uu, vv; cin >> vv;
//         V.pb(vv);
//     }
 
//     vi ANS = label(n, k, U, V);
//     F0R(i, n){
//         cout << ANS[i] << "\n";
//     }
// }
