/*
there is a fixed const of k * x
we need to find all paths, which we can do with a dp 

the transitions are outlined in the editorial which i had to read

Thinking time: 30 minutes
Understanding editorial: 1 hour :/
Coding time: 30 minutes

*/


#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define f first
#define s second

const int MOD = 1e9 + 7;

int add(int a, int b){
    int res = (a + b);
    if(res >= MOD) res -= MOD;
    return res;
}

int mul(int a, int b){
    return (1LL * a * 1LL * b) % MOD;
}

pii operator+(const pii& l, const pii& r){
    return make_pair(add(l.f, r.f), add(l.s, r.s));
}

pii operator+=(pii&l, const pii& r){
    return l = r + l;
}

pii operator*(const pii&l, const pii& r){
    return make_pair(add(mul(l.f, r.s), mul(l.s, r.f)), mul(l.s, r.s));
}

const int mxN = 2800;
int n, m, x, y, k;


int vis[mxN];
pii res[mxN], tmp[mxN];
vector<int> comp;
map<int, pii> dist;

vector<pii> adj[mxN];

void dfs(int u){
    //cout << u << endl;
    vis[u]=1;
    comp.push_back(u);
    for(auto&v : adj[u]){
        if(!vis[v.f]) dfs(v.f);
    }
}

void dfs2(int u, int p, int j, int d){
    for(auto& v : adj[u]){
        if(v.f == p) continue;
        if(v.f < j) dist[min(d+v.s, y)] += make_pair(v.s+d, 1);
        dfs2(v.f, u, j, v.s + d);
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    ifstream cin("mooriokart.in");
    ofstream cout("mooriokart.out");
    cin >> n >> m >> x >> y;
    k=n-m;
    for(int i=0; i < m; i++){
        int e1, e2, e3;
        cin >> e1 >> e2 >> e3;
        e1--; e2--;
        adj[e1].push_back({e2, e3});
        adj[e2].push_back({e1, e3});
    }
    res[min(k*x, y)]={k*x, 1};
    //cout << "WE GOT HERE" << endl;
    for(int i=0; i < n; i++){
        //cout << "WE GOT HERE" << endl;
        if(vis[i]) continue;
        comp.clear();
        dfs(i);
        dist.clear();
        for(auto& j : comp) dfs2(j, -1, j, 0);
        for(int j = 0; j <= y; j++)
            tmp[j]={0, 0};
        for(auto& val : dist){
            for(int j = 0; j <= y; j++){
                tmp[min(j + val.f, y)] += res[j]*val.s;
            }
        }
        for(int j = 0; j <= y; j++){
            res[j]=tmp[j];
        }
    }
    for(int i = 0; i < k - 1; i++)
        tmp[y].f=mul(tmp[y].f, 2);
    for(int i = 1; i < k; i++)
        tmp[y].f=mul(tmp[y].f, i);
    cout << tmp[y].f << '\n';
}
