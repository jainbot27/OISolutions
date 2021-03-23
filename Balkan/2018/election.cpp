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
 
struct Tree {
    typedef pii T;
    T Unit = {0, 0};
    T f(T a, T b) { return {a.f+b.f, max(a.s, a.f+b.s)}; } // (any associative fn)
    vector<T> s; int n;
    Tree(int n = 0) : s(2*n, Unit), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) { // query [b, e)
        T ra = Unit, rb = Unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};
 
typedef int node;
struct BIT{
    //ask for queries 0 idxed or remove ++idx/++r
    vector<node> bit;
    int n;
    void init(int x){
        n=x+1;
        bit.assign(n + 1,0);
    }
    node sum(int r){
        node ret = 0;
        for(r++; r ; r -= r & -r){
            ret += bit[r];
        }
        return ret;
    }
    node sum(int l, int r){
        return sum(r) - sum(l-1);
    }
    void add(int idx, node delta){
        for(idx++; idx < n; idx += idx & -idx){
            bit[idx] += delta;
        }
    }
}bit;
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; string s;
    cin >> n; cin >> s;
    int q; cin >> q;
    vector<vpii> qq(n);
    F0R(i, q){
        int l, r;
        cin >> l >> r;
        l--; r--; 
        qq[r].pb({l, i});
    }
    Tree seg(n);
    bit.init(n);
    stack<int> vals;
    vi ans(q);
    F0R(i, n){
        if(s[i]=='C'){
            seg.update(i, pii{-1, 0});
            if(!vals.empty()){
                int T = vals.top(); vals.pop();
                seg.update(T, {1, 1});
                bit.add(T, -1);
                //cout << "WE GOT HERE" << endl;
            }
        }
        else{
            vals.push(i);
            bit.add(i, 1);
        }
        trav(v, qq[i]){
            int r = bit.sum(v.f, i);
            //cout << bit.sum(i, v.f) << ' ' << seg.query(i, v.f+1).s << nl;
            r += seg.query(v.f, i+1).s;
            ans[v.s] = r;
        }
    }
    trav(x, ans) cout << x << nl;
 
    return 0;
}
