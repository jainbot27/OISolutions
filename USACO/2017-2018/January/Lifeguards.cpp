/*
Get rid of all nested segments, then notice how we only need to consider the last segment x such last a[x].s > a[i].f. we need to keep track of dp[N][K] which we can do 
with plenty of time to spare. 

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
const int mxK = 110;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
int dp[mxN][mxK], mx[mxN][mxK], n, k, p, ptr = 0, res = 0;
vpii a, A;

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    ifstream cin("lifeguards.in");
    ofstream cout("lifeguards.out");
    cin >> n >> k;
    a = vpii(n);
    F0R(i, n) cin >> a[i].f >> a[i].s;
    sort(all(a));
    F0R(i, n){
        if(ckmax(p, a[i].s)){
            A.pb(a[i]);
        } 
        else{
            k--;
        }
    }
    swap(a, A);
    ckmax(k, 0);
    n = siz(a);
    F0R(i, n){
        while(a[ptr].s < a[i].f) ptr++;
        F0R(j, k+1){
            if(j > i) dp[i][j] = -MOD;
            else{
                if(ptr < i)
                    ckmax(dp[i][j], dp[ptr][max(0, j- (i - ptr) + 1)]+a[i].s-a[ptr].s);
                ckmax(dp[i][j], (ptr?mx[ptr-1][max(0, j - (i - ptr))]:0)+ a[i].s - a[i].f);
            }
           mx[i][j] = max(dp[i][j], ((i&&j)?mx[i-1][j-1]:(-MOD)));
        }
        ckmax(res, dp[i][max(k-(n-1-i), 0)]);
    }
    cout << res << nl;
    return 0;
}
