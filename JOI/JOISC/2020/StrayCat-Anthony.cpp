/*
Submission: https://oj.uz/submission/309659

Solution Idea:
For first 4 subtasks you can color edges based on the depth of the 2 nodes they connect. Do this in a way that ensures that we always know which edge to take to get closer to
0. Since we have 3 colors, we can always do it. 

For the last 3, notice that coloring edges can be done in a very similar way except we need to be able to figure out where we are in a chain of edges.
For that we will use a specific coloring 
                                                  0 -> 1 -> 0 -> 0 -> 1 -> 1 -> 0 -> 1 -> 0 -> 0 -> 1 -> 
which will be a pattern. Now we just check for the first time we visit 5 edges, which only take 3 queries wasted, both up and down. 

Now the problem is just a very long impl...
which was extremely painful. I didn't come up with all the impl ideas on my own cause my initial impl approach was a lot of tiring casework. I got inspired of DolphinGarlic's
solution which was pretty clean. Check below for specifics. 
*/
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <string>
#include <set>
 
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
 
const char nl = '\n';
const int mxN = 20010;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
int n, m, a, b, d[mxN]; 
vi U, V, adj[mxN], res; vpii g[mxN];
queue<int> q;
 
// set<string> good{"01001", "10110", "00110", "01101", "11010", "10100"};
vector<int> list = {0, 1, 0, 0, 1, 1};
int amt[3] = {0, 1, 2};
void dfs(int u, int cur_edge, int cur = 0){
    if(cur_edge!=-1) res[cur_edge] = list[cur];
    trav(v, g[u]){
        if(cur_edge==v.s) continue;
        if(siz(g[u]) == 2 && u != 0){
            dfs(v.f, v.s, (cur+1)%6);
        }
        else{
            dfs(v.f, v.s, list[cur]^1);
        }
    }
}
vi Mark(int N, int M, int A, int B, vi Uu, vi Vv){
    U = Uu; V = Vv; n = N; m = M; a = A; b = B;
    if(a==2){
        res.resize(m);
        // 0 -> 1 -> 0 -> 0 -> 1 -> 1 -> 0 -> 1 -> 0 -> 0 -> 1 -> 1
        F0R(i, m){
            g[U[i]].pb({V[i], i});
            g[V[i]].pb({U[i], i});
        }
        dfs(0, -1, 0);
        return res;
    }
    else{
        res.resize(m);
        F0R(i, n) d[i] = MOD;
        F0R(i, m){
            adj[U[i]].pb(V[i]);
            adj[V[i]].pb(U[i]);
        }
        d[0] = 0;
        q.push(0);
        while(!q.empty()){
            int u = q.front(); q.pop();
            trav(v, adj[u]){
                if(ckmin(d[v], d[u]+1)){
                    q.push(v);
                }
            }
        }
        F0R(i, m){
            // we want to give them the value of the vertex with the higher value so that we know where to go
            if(d[U[i]]<d[V[i]])
                swap(U[i], V[i]);
            if(d[U[i]]==d[V[i]]){
                res[i] = amt[d[U[i]]%3];
            }
            else{
                res[i] = amt[d[V[i]]%3];
                // if we have distance 2 and 3
                // we will at 3 see that we have 2
            }
        }
        return res;
    }
}
 
#ifdef ACMX
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M, A, B; cin >> N >> M >> A >> B;
    U.resize(M);
    V.resize(M);
    F0R(i, M){
        cin >> U[i] >> V[i];     
    }
    vi res = Mark(N, M, A, B, U, V);
    trav(x, res){
        cout << x << " ";
    }
    cout << nl;
 
    return 0;
}
#endif
