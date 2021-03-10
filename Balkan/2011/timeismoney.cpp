#include <bits/stdc++.h>
using namespace std;
 
#define int ll 
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
using ld = long double;
 
template<class T> inline bool ckmin(T&a, T b) {return b < a ? a = b, 1 : 0;}
template<class T> inline bool ckmax(T&a, T b) {return b > a ? a = b, 1 : 0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const char nl = '\n';
const int mxN = 201;
const int MOD = 1e5 + 10;
const long long infLL = 1e18;
int n, m;
 
struct dsu{
    int n; vector<int> sz, par;
    void init(int _n){
        n = _n; sz.resize(n); par.resize(n);
        F0R(i, n) sz[i] = 1, par[i] = i;
    }
    int find(int x){ return par[x] = ( x == par[x] ? par[x] : find(par[x])); }
    void comb(int a, int b) {
        a=find(a); b=find(b);  
        if(a!=b) {if(sz[a]<sz[b]) swap(a, b); sz[a]+=sz[b]; par[b] = a; }
    }
};
 
struct edge{
    int x, y;
    int w1, w2;
    ld w;
};
 
vector<edge> e;
 
pair<ll, vi> solve(ld ratio){
    dsu q;
    q.init(n);
    trav(it, e) it.w = ratio*it.w1+(MOD-ratio)*it.w2;
    sort(e.begin(), e.end(), [](edge A, edge B){
        return A.w < B.w;
    });
    vi res;
    ll s1 = 0;
    ll s2 = 0;
    F0R(i, m){
        if(q.find(e[i].x)!=q.find(e[i].y)){
            q.comb(e[i].x, e[i].y);
            res.pb(i);
            s1 += e[i].w1;
            s2 += e[i].w2;
        }
    }
    assert(siz(res)==n-1);
    return {s1*s2, res};
}
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    e.resize(m);
    F0R(i, m){
        cin >> e[i].x >> e[i].y >> e[i].w1 >> e[i].w2;
    }
    ld lo = 0, hi = MOD;
    while(abs(lo-hi)>1e-7){
        ld mid1 = (lo*2+hi)/3;
        ld mid2 = (lo+2*hi)/3;
        if(solve(mid1).f<solve(mid2).f){
            hi = mid2;
        } 
        else{
            lo = mid1;
        }
    }
    vi ans = solve(lo).s;
    ll fin[2] = {0, 0};
    trav(x, ans){
        fin[0] += e[x].w1;
        fin[1] += e[x].w2;
    }
    cout << fin[0] << ' ' << fin[1] << nl;
    trav(x, ans) cout << e[x].x << ' ' << e[x].y << nl;
    return 0;
}
