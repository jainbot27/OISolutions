/*
Basically copied tmw's solution but the idea is everytime we take a turn we lose the ability to choose the type of 1 sprinkler so we take inv of 2.
Turns out this is enough because for everypath way we will reach the end and we will be able to multiply 2*numberofdots to the answer.
works in O(n^2)
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
const int mxN = 2e3 + 5;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

int add(int x, int y){ x += y; while(x >= MOD) x -= MOD; while(x < 0) x += MOD; return x; } void ad(int &x, int y) {x = add(x, y);}
int sub(int x, int y){ x -= y; while(x >= MOD) x -= MOD; while(x < 0) x += MOD; return x; } void sb(int &x, int y) {x = sub(x, y);}
int mul(int x, int y){ return ((int64_t)x * (int64_t)y) % MOD; } void ml(int &x, int y) {x = mul(x, y);}
int binpow(int x, int y){ int z = 1; while(y > 0) { if(y % 2 == 1) z = mul(z, x); x = mul(x, x); y /= 2; } return z; }
int inv(int x){ return binpow(x, MOD - 2); }
int divide(int x, int y){ return mul(x, inv(y)); }

const int i2 = (MOD+1)/2;
int n, dp1[mxN][mxN], dp2[mxN][mxN], ans = 1; 
string g[mxN];

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    ifstream cin("sprinklers2.in");
    ofstream cout("sprinklers2.out");
    cin >> n;
    dp1[0][0]=dp2[0][0]=1;
    F0R(i, n){
        cin >> g[i];
    }
    F0R(i, n+1){
        F0R(j, n+1){
            if(i < n){
                ad(dp1[i+1][j],dp1[i][j]);
                if(j&&g[i][j-1]=='.'){
                    ad(dp1[i+1][j], mul(dp2[i][j], i2));
                }
            }
            if(j < n){
                ad(dp2[i][j+1], dp2[i][j]);
                if(i&&g[i-1][j]=='.'){
                    ad(dp2[i][j+1], mul(dp1[i][j], i2));
                }
            }
        }
    }
    ans = add(dp1[n][n], dp2[n][n]);
    F0R(i, n){
        F0R(j, n){
            if(g[i][j]=='.')
                ml(ans, 2);
        }
    }
    cout << ans << nl;
    return 0;
}
