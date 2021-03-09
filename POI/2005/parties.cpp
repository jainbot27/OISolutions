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
const int mxN = 201;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

int n;
bool g[mxN][mxN];

vi solve(vi nodes){
    if(siz(nodes)<=2) return {nodes[0]};
    trav(i, nodes){
        int deg = 0;
        FOR(x, 1, n+1) deg += g[i][x];
        if(deg%2==1){
            vi new_nodes;
            trav(x, nodes){
                if(x!=i){
                    new_nodes.pb(x);
                }
            }
            vi conn;
            FOR(x, 1, n+1) if(g[i][x]) conn.pb(x);
            F0R(x, deg){
                FOR(y, x+1, deg){
                    g[conn[x]][conn[y]] ^= 1; 
                    g[conn[y]][conn[x]] ^= 1; 
                }
                g[conn[x]][i] = 0;
            }
            vi split = solve(new_nodes);
            int cnt = 0;
            trav(x, split) cnt += g[i][x];
            if(cnt&1^1)  split.pb(i);
            return split;
        }
    }
    return nodes;
}

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    vi s;
    FOR(i, 1, n+1){
        int m; cin >> m;
        F0R(j, m){
            int x; cin >> x;
            g[i][x] = 1;
        }
        s.pb(i);
    }
    vi res = solve(s);
    cout << siz(res) << nl;
    trav(x, res) cout << x << ' ';
    cout << nl;;
    return 0;
}
