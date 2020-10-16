/*
Read editorial: 
Pretty cool idea of small the large and keeping a map to keep whats advantageous
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
template<class T, class U> std::ostream& operator<<(ostream& s, const pair<T, U>& x) {
    return s << "( " << x.first << ", " << x.second << ")"; 
}
template<class T> void stlts(T V){
    cout << "[";
    bool f = 1;
    trav(x, V){
        if(f)
            cout << x, f = 0;
        else{
            cout << ", " << x;
        }
    }
    cout << "]" << endl;
}
int n, m, k, p[mxN];
pair<ll, ll> f[mxN]; map<int, ll> dp[mxN];
ll res = 0;

void upd(map<int, ll>& c, ll d, ll w){
    //cout << "WE GOT HERE" << nl;
    c[d]+=w;
    auto it = c.find(d);
    it++;
    for(; it != c.end() && w != 0; ){
        int mn = min(w, it->s);
        w-=mn; it->s-=mn;
        if(it->s == 0){
            c.erase(it++);
        }
        else{
            break;
        }
    }
}
void comb(map<int, ll>&x, map<int, ll>& y){
    if(siz(x) < siz(y)) swap(x, y);
    trav(v, y){
        x[v.f]+=v.s;
    }
}
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    FOR(i, 2, n+1){
        cin >> p[i];
    }
    F0R(i, m){
        int x, y, z; cin >> x >> y >> z;
        f[x] = {y, z};
    }
    ROF(i, 2, n + 1){
        if(f[i].f) upd(dp[i], f[i].f, f[i].s);
        //stlts(dp[i]);
        comb(dp[p[i]], dp[i]);
    }
    trav(v, dp[1]){
        res += v.s;
    }
    cout << res << nl;
    return 0;
}
