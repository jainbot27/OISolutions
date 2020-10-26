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
const int mxN = 4e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
vi R, B; 
ll pr[mxN], pb[mxN], dp[mxN];
int lst[mxN], bal = mxN/2, val[mxN];
vpii t;
 
ll f(pii x){
    if(x.s == 1){
        auto it = lower_bound(all(R), x.f);
        auto dist = infLL;
        if(it != begin(R)){
            ckmin(dist, (ll)x.f-*prev(it));
        }
        if(it != end(R)){
            ckmin(dist, (ll)*it-x.f);
        }
        return dist;
    }
    else{
        auto it = lower_bound(all(B), x.f);
        auto dist = infLL;
        if(it != begin(B)){
            ckmin(dist, (ll)x.f-*prev(it));
        }
        if(it != end(B)){
            ckmin(dist, (ll)*it-x.f);
        }
        return dist;
    }
}
ll min_total_length(vi r, vi b){
    R = r;
    B = b;
    int n = siz(r) + siz(b);
    F0R(i, siz(r)){
        t.pb({r[i], 0});
    }
    F0R(i, siz(b)){
        t.pb({b[i], 1});
    }
    sort(all(t));
    memset(lst, -1, sizeof lst);
    memset(val, -1, sizeof val);
    lst[bal] = -69;
    F0R(i, n){
        if(i) pb[i] = pb[i-1];
        if(i) pr[i] = pr[i-1];
        if(t[i].s) pb[i] += t[i].f;
        else pr[i] += t[i].f;
        bal+=(t[i].s?1:-1);
        if(lst[bal]!=-1)
            val[i] = lst[bal];
        lst[bal] = i;
    }
    fill(dp, dp+n, infLL);
    F0R(i, n){
        ll x = f(t[i]);
        //cout << x << endl;
        if(i)ckmin(dp[i], x + dp[i-1]);
        else ckmin(dp[i], x);
        if(val[i] != -1){
            if(val[i] == -69) ckmin(dp[i], abs(pb[i] - pr[i]));
            else ckmin(dp[i], dp[val[i]] + abs(pb[i] - pb[val[i]] - (pr[i] - pr[val[i]])));
        }
        //cout << "dp[i] " << i << " " << dp[i] << endl;
        //cout << "val[i] " << i << ' ' << val[i] << endl;
        //cout << "t[i] " << i << ' ' << t[i].f << ' ' << t[i].s << endl;
    }
    return dp[n-1];
}
//int32_t main(){
//    ios_base::sync_with_stdio(0); cin.tie(0);
//    int N, M;
//    cin >> N >> M;
//    vi a(N), b(M);
//    trav(A, a) cin >> A;
//    trav(B, b) cin >> B;
//    cout << min_total_length(a, b) << nl;
 
//    return 0;
//}
