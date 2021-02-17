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
 
int dp[2][mxN], vis[mxN];
vi g[mxN];
 
int minimumInstructions(int n, int m, int k, vi c, vi a, vector<vi> b){
    F0R(i, m){
        trav(x, b[i]){
            g[x].pb(i);
        }
    }
    R0F(i, n){
        trav(v, g[c[i+2]])
            dp[i%2][v] = 0;
        trav(v, g[c[i]]){
            dp[i%2][v] = dp[(i+1)%2][(v+1)%m]+1;
            if(dp[i%2][v]>=m) vis[i] = 1;
        }
    }
    int ans = 0, lst = -1, mx = -m;
    F0R(i, n){
        if(vis[i]) mx = i;
        if(i > lst) {
            if(mx+m==i) return -1;
            ans++;
            lst = mx+m-1;
        }
    }
    return ans;
}
 
