/*
Key observation is that if we have a max for a certain range which includes some pos x, if we split it, we dont have to worry about that cows existance anymore. 

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
const int mxN = 305;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

int n, m;
int mx[mxN][mxN][mxN];
int dp[mxN][mxN];

int go(int l, int r){
    if(l > r) return 0;
    if(dp[l][r]!=-1) return dp[l][r];
    int& res = dp[l][r];
    res=0;
    FOR(i, l, r){
        ckmax(res, go(l, i)+go(i+1, r));
    }
    FOR(i, l, r+1){
        ckmax(res, go(l, i-1)+go(i+1, r)+mx[i][l][r]);
    }
    return  res;
}
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("pieaters.in", "r", stdin);
    freopen("pieaters.out", "w", stdout);
    memset(dp, -1, sizeof dp);
    cin >> n >> m;
    F0R(i, m){
        int w, l, r;
        cin >> w >> l >> r;
        l--; r--; 
        FOR(i, l, r+1){
            ckmax(mx[i][l][r], w);
        }
    }
    F0R(i, n){
        R0F(j, i+1){
            FOR(k, i, n){
                if(j) ckmax(mx[i][j-1][k], mx[i][j][k]);
                if(k < n-1) ckmax(mx[i][j][k+1], mx[i][j][k]);
            }
        }
    }
    cout << go(0, n-1) << nl;
    return 0;
}
