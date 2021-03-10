/*

solution main idea: if for each node A, we consider, what is the most B we can get away with taking while still getting the points for A, we get a bunch of pairs

(i, low[i]) blue vertices

we can do same thing for ms too

(low[j], j) red vertices

once we have that, consider any path to the node (n, m), it will consist of taking some of these nodes, because those are the points we want
we have to take some path with some positive slope, and we can hit multiple vertices on the way.
Now lets consider that for some path we take, all blue vertices above our path, we can get the points for.
For red, it would be all the nodes below our path. 

Solving for this (apparently is theoretically possible) but there is a reduction to just blue vertices,
make a red vertex (x, y) into a blue vertex(x-1, y+1) and add the value of that blue vertex to the answer before, and then once we do that, we can consider whether we will
remove that value or not.

Thus we use a lazy segment tree with range add, point max updates and query range max.

O((n+m)log(n+m))

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
const int mxN = 1e6+10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
//use to make shit go faster (magic from KACTL)
static char buf[450 << 20];
void* operator new(size_t s) {
    static size_t i = sizeof buf;
    assert(s < i);
    return (void*)&buf[i -= s];
}
void operator delete(void*) {}
// implicit lazy segment tree adapted from KACTL
template<class V> struct Node {
    Node *l = 0, *r = 0;
    const V no_op = infLL;
    int lo, hi; V madd = 0, val = 0;
    Node(int lo,int hi):lo(lo),hi(hi){} 
    Node(vector<V>& v, int lo, int hi) : lo(lo), hi(hi) {
        if (lo + 1 < hi) {
            int mid = lo + (hi - lo)/2;
            l = new Node(v, lo, mid); r = new Node(v, mid, hi);
            val = l->val+r->val;
        }
        else val = v[lo];
    }
    V query(int L, int R) {
        if (R <= lo || hi <= L) return -infLL;
        if (L <= lo && hi <= R) return val;
        push();
        return max(l->query(L, R), r->query(L, R));
    }
    void mx(int L, V x) {
        if(lo==hi-1) {
            ckmax(val, x);
        }
        else{
            push();
            int m = (lo+hi)/2; if(L<m) l->mx(L, x);
            else r->mx(L, x);
            val = max(l->val, r->val);
        }
    }
    void add(int L, int R, V x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) {
            madd += x;
            val += x;
        }
        else {
            push(), l->add(L, R, x), r->add(L, R, x);
            val = max(l->val, r->val);
        }
    }
    void push() {
        if (!l) {
            int mid = lo + (hi - lo)/2;
            l = new Node(lo, mid); r = new Node(mid, hi);
        }
        if(madd) l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
    }
};
 
Node<ll>* st = new Node<ll>(0, mxN);
pair<int, pair<ll, ll>> a[mxN], b[mxN];
ll pa[mxN], pb[mxN];
ll ans;
map<pii, ll> mp;
int n, m;
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    FOR(i, 1, n+1){
        cin >> a[i].f >> a[i].s.f >> a[i].s.s;
        pa[i] = pa[i-1]+a[i].f;
    }
    FOR(i, 1, m+1){
        cin >> b[i].f >> b[i].s.f >> b[i].s.s;
        pb[i] = pb[i-1]+b[i].f;
    }
    FOR(i, 1, n+1){
        if(pa[i]>a[i].s.f) continue;
        if(pb[m]+pa[i]<=a[i].s.f) {
            ans += a[i].s.s ;
            continue;
        }
        mp[{i-1, -(upper_bound(pb+1, pb+1+m, a[i].s.f-pa[i])-pb-1+1)}] += a[i].s.s;
    } 
    FOR(i, 1, m+1){
        if(pb[i]>b[i].s.f) continue;
        if(pb[i]+pa[n]<=b[i].s.f) {
            ans += b[i].s.s;
            continue;
        }
        ans += b[i].s.s;
        mp[{upper_bound(pa+1, pa+n+1, b[i].s.f-pb[i])-pa-1, -i}] -= b[i].s.s;
 
    }
    trav(cur, mp){
        int x = cur.f.f, y = -cur.f.s, z = cur.s;
        ll t = st->query(0, y);
        st->mx(y, t);
        st->add(0, y, z);
    }
    cout << st->query(0, mxN)+ans << nl;
    return 0;
}
