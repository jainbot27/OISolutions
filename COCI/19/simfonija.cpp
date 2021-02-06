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
 
int n, k, m;
ll a[mxN], b[mxN], c[mxN], p[mxN], ans=infLL;
 
ll get(int e2, int e1){
    return p[e1]-(e2==0?0:p[e2-1]);
}
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    m = n-k;
    F0R(i, n) cin >> a[i];
    F0R(i, n) {
        cin >> b[i];
        c[i] = b[i]-a[i];
    }
    sort(c, c+n);
    F0R(i, n){
        p[i] = (i==0?0:p[i-1])+c[i];
    }
    if(m==0){
        cout << 0 << nl;
        return 0;
    }
    for(int i=0;i+m-1<n;i++){
        int l = i, r = i+m-1;
        int mid = (l+r)/2;
        ckmin(ans, -((get(l, mid)-c[mid]*(mid-l+1))+(c[mid]*(r-mid)-get(mid+1, r))));
    }
    cout << ans << nl;
    return 0;
}
