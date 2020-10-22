/*
Greedily solve for both sides. It just works, idrk why. 

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

int n, ans = 0, a[mxN], vis[mxN], l[mxN], r[mxN];
vi b;
set<int> vals;

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    ifstream cin("cardgame.in");
    ofstream cout("cardgame.out");
    cin >> n;
    F0R(i, n) cin >> a[i], a[i]--, vis[a[i]] = 1;    
    F0R(i, 2*n){
        if(!vis[i]) b.pb(i);
    }
    trav(x, b) vals.insert(x);
    F0R(i, n){
        auto u = vals.upper_bound(a[i]);
        if(u != end(vals)){
            vals.erase(u);
            l[i] = (i == 0 ? 1 : l[i-1] + 1);
        }
        else{
            l[i] = (i == 0 ? 0 : l[i-1]);
        }
    }
    reverse(a, a+n);
    vals.clear();
    trav(x, b) vals.insert(x);
    F0R(i, n){
        auto u = vals.upper_bound(a[i]);
        if(u != begin(vals)){
            vals.erase(prev(u));
            r[i] = (i == 0 ? 1 : r[i-1] + 1);
        }
        else{
            r[i] = (i == 0 ? 0 : r[i-1]);
        }
    }
    reverse(r, r+n);
    ckmax(ans, l[n-1]);
    ckmax(ans, r[0]);
    F0R(i, n-1){
        ckmax(ans, l[i] + r[i+1]);
    }
    cout << ans << nl;
    return 0;
}
