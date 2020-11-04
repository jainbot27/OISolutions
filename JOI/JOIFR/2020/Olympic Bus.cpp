/*
The key observation for this problem comes from thinking about the brute force. if we iterated over all the edges and did dijkstra for them we would have an 
O(m(n^2)) algorithm.

It is important to note however, we don't actually need to do this for every edge. 

In fact we only need to test everything if that edge is on the shortest path either from 0 -> n-1 or vice versa. 

This is because we might as well take the shortest path to both sides of the edge and then take the reverse edge. If the shortest path to an reverse edge uses taht edge, 
it doesn't really matter because then that edge is bad to take anyways compared to taking the regular shortest path.

I wrote this solution with a (n*m*log(n)) solution which passes in 900ms. It would be faster to use n^2 dijkstra instead. 

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
using pli = pair<ll, int>;
using vpli = vector<pli>;

template<class T> inline bool ckmin(T&a, T b) {return b < a ? a = b, 1 : 0;}
template<class T> inline bool ckmax(T&a, T b) {return b > a ? a = b, 1 : 0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const char nl = '\n';
const int mxN = 201;
const int mxM = 5e4 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

struct edge{
    int v, i; ll c;
    edge(int V, ll C, int I){
        v = V;
        c = C;
        i = I;
    }
};

int n, m;
int u[mxM], v[mxM]; ll c[mxM], d[mxM];
pii par[2][mxN][mxN]; ll dist[2][mxN][mxN];
int used[2][mxM];
vector<edge> adj[2][mxN];

ll ans = 0;

void go(int u, int gl){
    priority_queue<pli, vpli, greater<pli>> pq;
    fill(dist[gl][u], dist[gl][u] + n, infLL);
    dist[gl][u][u]=0;
    par[gl][u][u]={-1, -1};
    pq.push({0, u});
    while(!pq.empty()){
        pii cur = pq.top();
        pq.pop();
        if(cur.f != dist[gl][u][cur.s]){
            continue;
        } 
        trav(nxt, adj[gl][cur.s]){
            if(ckmin(dist[gl][u][nxt.v], cur.f + nxt.c)){
                pq.push({dist[gl][u][nxt.v], nxt.v});
                par[gl][u][nxt.v]= {nxt.i, cur.s};
            }
        }
    } 
}

void findPath(int gl){
    if(dist[0][(gl?n-1:0)][(gl?0:n-1)] == infLL){
        return;
    }
    int u = (gl ? n-1 : 0), v = (gl ? 0 : n - 1);
    while(v != u){
        used[gl][par[0][u][v].f]=1;
        v=par[0][u][v].s; 
    }
}

ll go(int u, int v, int cant){
    vector<ll> d(n, infLL);
    d[u]=0;
    priority_queue<pli, vpli, greater<pli>> pq;
    pq.push({0, u});
    while(!pq.empty()){
        pli cur = pq.top();
        pq.pop();
        if(cur.f != d[cur.s]) continue;
        trav(x, adj[0][cur.s]){
            if(x.i != cant){
                if(ckmin(d[x.v], cur.f + x.c)){
                    pq.push({d[x.v], x.v});
                }
            }
        }
        trav(x, adj[1][cur.s]){
            if(x.i == cant){
                if(ckmin(d[x.v], cur.f + x.c)){
                    pq.push({d[x.v], x.v});
                }
            }
        }
    }
    return d[v];
}

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    F0R(i, m){
        cin >> u[i] >> v[i] >> c[i] >> d[i]; u[i]--; v[i]--;
        adj[0][u[i]].pb({v[i], c[i], i});
        adj[1][v[i]].pb({u[i], c[i], i});
    } 
    F0R(i, n){
        go(i, 0);
    } 
    findPath(0); findPath(1);
    ans=dist[0][0][n-1]+dist[0][n-1][0];
    ll tmp[2] = {dist[0][0][n-1], dist[0][n-1][0]};
    F0R(i, m){
        ll res = d[i];
        F0R(chk, 2){
            if(used[chk][i]){
                res += go(chk?n-1:0, chk?0:n-1, i);
            }
            else{
                res += min(tmp[chk], dist[0][(chk?n-1:0)][v[i]]+dist[0][u[i]][chk?0:n-1]+c[i]);
            }
        }
        ckmin(ans, res);
    }
    cout << (ans >= infLL ? -1 : ans) << nl;
    return 0;
}
