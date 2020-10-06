/*
Problem: https://oj.uz/problem/view/IOI08_linear_garden

Read Editorial and refer to official editorial for my idea. 
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
const int mxN = 1e6 + 10;
int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
int dp_cur[2][2][2][2];
int dp_next[2][2][2][2];
int add(int x, int y){ x += y; while(x >= MOD) x -= MOD; while(x < 0) x += MOD; return x; } void ad(int &x, int y) {x = add(x, y);}
int sub(int x, int y){ x -= y; while(x >= MOD) x -= MOD; while(x < 0) x += MOD; return x; } void sb(int &x, int y) {x = sub(x, y);}
int mul(int x, int y){ return ((int64_t)x * (int64_t)y) % MOD; } void ml(int &x, int y) {x = mul(x, y);}
int binpow(int x, int y){ int z = 1; while(y > 0) { if(y % 2 == 1) z = mul(z, x); x = mul(x, x); y /= 2; } return z; }
int inv(int x){ return binpow(x, MOD - 2); }
int divide(int x, int y){ return mul(x, inv(y)); }
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    MOD = m; 
    string s; cin >> s;
    int mn = 0, mx = 0, cur = 0, ans = 0;
    F0R(i, n){
        if(s[i]=='L') {
            ckmax(mx, ++cur);
        }
        else{
            int newmx = max(mx, cur+1);
            int k = n-1-i;
            if(newmx-mn == 1){
                ad(ans, binpow(2, k/2));
                ad(ans, binpow(2, (k+1)/2));
                sb(ans, 1);
            }
            else if(newmx-mn==2){
                if(cur+1==newmx-1){
                    ad(ans, binpow(2, (k+1)/2));
                }
                else{
                    ad(ans, binpow(2, k/2));
                }
            }
            ckmin(mn, --cur);
        }
        // cout << cur << " " << ans << nl;
    }
    cout << add(ans,1) << nl;
    return 0;
}
