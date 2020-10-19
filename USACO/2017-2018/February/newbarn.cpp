/*
The farthest node will always be either of the edges of the diameter. We can update the diameters length whenever we add a node, and keep track of distances by 
dynamically using binary lifting. 


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

int n = 0, d[mxN], anc[mxN][25], c[mxN];
pii stat[mxN];
int q;

int lca(int a, int b){
    if(d[a] < d[b]) swap(a, b);
    R0F(i, 20) if((d[a]-d[b])&(1<<i)) a = anc[a][i];
    if(a == b) return a;
    R0F(i, 20) if(anc[a][i] != anc[b][i]){
        a = anc[a][i]; b = anc[b][i];
    }
    return anc[a][0];
}
int dist(int a, int b){
    return d[a] + d[b] - 2 * d[lca(a, b)];
}
int32_t main(){
    ifstream cin("newbarn.in");
    ofstream cout("newbarn.out");

    cin >> q;
    F0R(i, q){
        char x; int v; cin >> x >> v;
        if(x == 'B'){
            n++;
            if(v == -1){
                stat[n] = {n, n};
                c[n] = n;
            }
            else{
                c[n] = c[v];
                d[n] = d[v] + 1;
                anc[n][0] = v;
                FOR(i, 1, 20){
                    anc[n][i] = anc[anc[n][i-1]][i-1];
                }
                pii &x = stat[c[n]];
                int cd = dist(x.f, x.s);
                if(dist(x.f, n) > cd){
                    x.s = n;
                }
                else if(dist(x.s, n) > cd){
                    x.f = n;
                }
            }
        }
        else{
            //cout << n << ' ' << c[n] << ' ' << stat[c[n]].f << ' ' << stat[c[n]].s << endl;
            cout << max(dist(stat[c[v]].f, v), dist(stat[c[v]].s, v)) << nl;
        }
    }
}
