/*
It turns out we can denote any operation by adding x to the suffix, because doing anything else in non-optimal.
So we can just partion the array into two areas, and maintain LIS like normal with a bsearch on vectors. 

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
const int mxN = 2e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
int n; ll ans = 1; ll x, v[mxN], lst[mxN];
vi l, r; 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> x;
    F0R(i, n) cin >> v[i];
    F0R(i, n){
        if(siz(l))
            lst[i] = lower_bound(all(l), v[i] + x)-l.begin();
        else 
            lst[i]  = 0;
        int cur;
        if(siz(l))
            cur = lower_bound(all(l), v[i]) - l.begin();
        else 
            cur = 0;
        if(cur == siz(l)) l.pb(v[i]);
        else l[cur] = v[i];
    }
    R0F(i, n){
        int cur;
        if(siz(r)) cur = lower_bound(all(r), -v[i]) - r.begin();
        else cur = 0;
        if(cur == siz(r)) r.pb(-v[i]);
        else r[cur] = -v[i];
        ckmax(ans, lst[i] + cur + 1);
    }
    cout << ans << nl;
    return 0;
}
