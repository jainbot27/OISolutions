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
 
int n, q;
vl a;
vl p;
vl t;
 
ll pos(int idx, ll time){
    ll num = time / t[idx];
    return num*p[idx]-idx;
}
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    a=p=t=vl(n+1);
    FOR(i, 1, 1+n){
        cin >> a[i];
    }
    p[0] = 1;
    t[0] = 1;
    FOR(i, 1, 1+n){
        // so we need to know how many days it will take to go dist
        // clearly we just wait when the distance is a[i]+1 or more -> which means its just when they travel a[i]?
        // so we need the number of periods
        ll per = (p[i-1]+a[i]-1)/p[i-1];
        p[i] = per*p[i-1];
        t[i] = per*t[i-1];
    }
    while(q--){
        ll t, l, r;
        cin >> t >> l >> r;
        int L = 0, R = n;
        int mn=-MOD, mx=MOD;
        while(L<=R){
            int M = (L+R)/2;
            //cout << M << ' ' << t << ' ' << pos(M, t) << nl;
            if(pos(M, t) >= l){
                mn = M;
                L = M+1;
            }
            else{
                R = M-1;
            }
        }
        L = 0, R = n;
        while(L<=R){
            int M = (L+R)/2;
            if(pos(M, t) <= r){
                mx = M;
                R = M-1;
            }
            else{
                L = M+1;
            }
        }
        //cout << mn << ' ' << mx << nl;
        cout << max(0, mn-mx+1) << nl;
    }
    return 0;
}
