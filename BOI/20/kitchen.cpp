/*
dp[x] most amount of stuff we can hvae to give x out of the nk things we need. 
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
 
int n, m, k;
int a[mxN], b[mxN];
int dp[mxN*mxN];
 
void no(){
    cout << "Impossible\n";
    exit(0);
}
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    F0R(i, n) cin >> a[i];
    F0R(i, m) cin >> b[i];
    if(*min_element(a, a+n)<k) no();
    F0R(i, mxN*mxN) dp[i] = -MOD;
    dp[0] = 0;
    F0R(i, m){
        R0F(j, mxN*mxN-b[i]){
            ckmax(dp[j+b[i]], dp[j]+min(n, b[i]));
        }    
    }
    FOR(i, accumulate(a, a+n, 0), mxN*mxN){
        if(dp[i] >= n*k){
            cout << i-accumulate(a, a+n, 0) << nl;
            return 0;
        }
    }
    no();
    return 0;
}
