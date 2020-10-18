/*
state : a[i][j] = a[1][1] ^ a[i][1] ^ a[j][1] ^ (i%2==0&&j%2==0)
from this we can notice that if a square is fixed, depending on that square we fix whether a[i][1] and a[1][j] should be equal or not.
Some other cases we have to worry about like if the square has x=1 or y=1, but these are mostly trivial cases. 
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
const int mxN = 3e5 + 10;
const int MOD = 1e9;
const long long infLL = 1e18;

int add(int x, int y){ x += y; while(x >= MOD) x -= MOD; while(x < 0) x += MOD; return x; } void ad(int &x, int y) {x = add(x, y);}
int sub(int x, int y){ x -= y; while(x >= MOD) x -= MOD; while(x < 0) x += MOD; return x; } void sb(int &x, int y) {x = sub(x, y);}
int mul(int x, int y){ return ((int64_t)x * (int64_t)y) % MOD; } void ml(int &x, int y) {x = mul(x, y);}
int binpow(int x, int y){ int z = 1; while(y > 0) { if(y % 2 == 1) z = mul(z, x); x = mul(x, x); y /= 2; } return z; }
int inv(int x){ return binpow(x, MOD - 2); }
int divide(int x, int y){ return mul(x, inv(y)); }

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    struct P{
        int x, y, t; 
    };
    int n, m, k;
    cin >> n >> m >> k;
    auto get = [&](int x, int y){
        if(x == 1) return y;
        else return x + m;
    };
    vector<P> Q(k);
    F0R(i, k){
        cin >> Q[i].x >> Q[i].y >> Q[i].t;
    }
    //cout << "HERE" << endl;
    int ans = 0;
    F0R(type, 2){
        int res = 1;
        vector<vi> adj(2 * (m + n) + k);
        vi c(2 * (m + n) + k);
        vi vis(2 * (m + n) + k);
        int tmp = n + m + 1 ;
        F0R(i, k){
            if(Q[i].x == 1 && Q[i].y == 1){
                if(Q[i].t != type)
                    res = 0;
            }
            else if(Q[i].x == 1 || Q[i].y == 1){
                c[get(Q[i].x, Q[i].y)] = Q[i].t + 1;
            }
            else{
                int cur = type ^ Q[i].t ^ (Q[i].x%2 == 0 && Q[i].y%2 == 0);
                if(cur){
                    adj[get(1, Q[i].y)].pb(get(Q[i].x, 1));
                    adj[get(Q[i].x, 1)].pb(get(1, Q[i].y));
                }
                else{
                    adj[get(1, Q[i].y)].pb(tmp);
                    adj[tmp].pb(get(1, Q[i].y));
                    adj[tmp].pb(get(Q[i].x, 1));
                    adj[get(Q[i].x, 1)].pb(tmp);
                    tmp++;
                }
            }
        }
        //cout << "HERE" << endl;
        function<void(int)> dfs;
        dfs = [&](int u){
            vis[u] = 1;
            trav(v, adj[u]){
                if(c[v] != 0 && c[v] == c[u]){
                    res = 0;
                }
                else{
                    c[v] = 3 - c[u];
                    if(!vis[v]) dfs(v);
                }
            }
        };
        FOR(i, 2, (m + n) + 1){
            if(i == m+1) continue;
            if(c[i] && !vis[i]){
                dfs(i);
            }
        }
        FOR(i, 2, (m + n) + 1){
            if(i == m+1) continue;
            if(!vis[i]){
                c[i] = 1; dfs(i); ml(res, 2);
            }
        }
        ad(ans, res);
    }
    cout << ans << nl;
    return 0;
}
