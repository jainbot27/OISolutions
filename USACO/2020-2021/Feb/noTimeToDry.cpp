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
};

template<class T> struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= siz(V); pw *= 2, ++k) {
            jmp.emplace_back(siz(V) - pw * 2 + 1);
            FOR(j,0,siz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

int n, q;
vi a;
int ans[mxN];
vpii quer[mxN];
int lst[mxN];
BIT bit;

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    memset(lst, -1, sizeof(lst));
    a.resize(n);
    F0R(i, n){
        cin >> a[i], a[i]--;
    }
    F0R(i, q){
        int l, r; cin >> l >> r; l--; r--; 
        quer[r].pb({l, i});
    }
    bit.init(n);
    RMQ<int> rmq(a);
    F0R(i, n){
        if(lst[a[i]]!=-1&&rmq.query(lst[a[i]], i)>=a[i]) {
            bit.add(lst[a[i]], 1);
        }
        trav(x, quer[i]){
            ans[x.s] = i-x.f+1-bit.sum(x.f, i);
        }
        lst[a[i]] =  i;
    }
    F0R(i, q) cout << ans[i] << nl;
    return 0;
}
