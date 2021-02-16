/*
path will be some u->x->y->v, where x is a parent of v on the dag-tree. you can find this by maintaining dp and you can insure only taking the shortest path with a dijkstra. 

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
using T = pair<ll, int>;
using T2 = pair<ll, pii>;
 
int n, m, s, t, u, v;
vector<pair<int, ll>> adj[mxN];
ll du[mxN], dv[mxN], ans = infLL;
ll dist[mxN];
ll dp[2][mxN];
bool vis[mxN];
 
void dij(int sc, ll arr[]){
    F0R(i, n) arr[i] = infLL;
    arr[sc] = 0;
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({0, sc});
    while(!pq.empty()){
        int U = pq.top().s; ll dU = pq.top().f;
        pq.pop();
        if(dU!=arr[U]) continue;
        trav(V, adj[U]){
            if(ckmin(arr[V.f], arr[U]+V.s)){
                pq.push({arr[V.f], V.f});
            }
        }
    }
}
 
void dij2(int sc, int en){
    F0R(i, n) dist[i] = dp[0][i] = dp[1][i] = infLL, vis[i] = 0;
    priority_queue<T2, vector<T2>, greater<T2>> pq;
    pq.push({0, {sc, -1}});
    while(!pq.empty()){
        int U = pq.top().s.f, P = pq.top().s.s; ll dU = pq.top().f;
        //cout << U << ' ' << P << ' ' << dU << '\n';
        pq.pop();
        if(!vis[U]){
            dist[U] = dU;
            vis[U] = 1;
            dp[0][U] = du[U];
            dp[1][U] = dv[U];
            if(P!=-1) {
                ckmin(dp[0][U], dp[0][P]);
                ckmin(dp[1][U], dp[1][P]);
            }
            trav(V, adj[U]) pq.push({dU+V.s, {V.f, U}});
        }
        else if(dU==dist[U]){
            if(min(dp[0][P], du[U])+min(dp[1][P], dv[U])<dp[0][U]+dp[1][U]){
                dp[0][U]=min(dp[0][P], du[U]);
                dp[1][U]=min(dp[1][P], dv[U]);
            }
        }
    }
    ckmin(ans, dp[0][en]+dp[1][en]);
}
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> s >> t >> u >> v;
    s--; t--; u--; v--;
    F0R(i, m){
        int e1, e2; ll e3; 
        cin >> e1 >> e2 >> e3;
        e1--; e2--; 
        adj[e1].pb({e2, e3});
        adj[e2].pb({e1, e3});
    }
    dij(u, du); dij(v, dv);
    ans = du[v];
    dij2(s, t); dij2(t, s);
    cout << ans << nl;
    return 0;
}
