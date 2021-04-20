/*
we say the range is [mn[i], mx[i]] is the range where cow i can be a delegate 
Any correct range will have [L, M, R] 
So we will fix L, and query numbers from [L+1, mx[L]]. We will use a segment tree to keep track which elements are relevant for M, and R, as we add them as L >= mn[M] or L >= mn[R]
You need to activate nodes as we traverse throughout the array. 
A modded Lazy-Segment Tree can do this, so we are done.

Complexity: O(nlog(n)) 
*/
#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define ar array
#define all(x) x.begin(), x.end()
#define siz(x) (int) x.size()

#define FOR(i, a, b) for(int i=(a); i<(b); i++)
#define ROF(i, a, b) for(int i=(b-1); i>=(a); i--)
#define F0R(i, n) FOR(i, 0, n)
#define R0F(i, n) ROF(i, 0, n)
#define trav(x, y) for(auto&x:y)

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpii = vector<pii>;

template<class T> inline bool ckmin(T& a, const T& b) {return b<a?a=b,1:0;}
template<class T> inline bool ckmax(T& a, const T& b) {return b>a?a=b,1:0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const char nl = '\n';
const int mxN = 1<<18;
const int MOD = 1e9+7;
const ll infLL = 1e18;
const ld eps = 1e-6;

struct segment{
    ll mon[2*mxN], madd[2*mxN], val[2*mxN], sum[2*mxN];
    void add(int L, int R, ll v, int i=1, int lo=0, int hi=mxN){
        if(R<=lo||hi<=L) return;
        if(L<=lo&&hi<=R){
            madd[i]+=v;
            sum[i]+=v*(hi-lo);
            val[i]+=v*mon[i];
            return;
        }
        push(i, lo, hi);
        int m=(lo+hi)/2;
        add(L, R, v, i*2, lo, m);
        add(L, R, v, i*2+1, m, hi);
        mon[i]=mon[2*i]+mon[2*i+1];
        val[i]=val[2*i]+val[2*i+1];
        sum[i]=sum[2*i]+sum[2*i+1];
    }
    void on(int V, int i=1, int lo=0, int hi=mxN){
        if(hi<=V||lo>V) return;
        if(lo+1==hi){
            mon[i]=1;
            val[i]=sum[i];
            return;
        }
        push(i, lo, hi);
        int m=(lo+hi)/2; 
        on(V, i*2, lo, m);
        on(V, i*2+1, m, hi);
        mon[i]=mon[2*i]+mon[2*i+1];
        val[i]=val[2*i]+val[2*i+1];
        sum[i]=sum[2*i]+sum[2*i+1];
    }
    ll query(int L, int R, int i=1, int lo=0, int hi=mxN){
        if(R<=lo||hi<=L) return 0;
        if(L<=lo&&hi<=R){
            return val[i];
        }
        push(i, lo, hi);
        int m=(lo+hi)/2;
        return query(L, R, i*2, lo, m)+query(L, R, i*2+1, m, hi);
    }
    void push(int i, int lo, int hi){
        int m=(lo+hi)/2;
        if(madd[i]!=0){
            add(lo, m, madd[i], i*2, lo, m);
            add(m, hi, madd[i], i*2+1, m, hi);
            madd[i]=0;
        }
    }
}seg;
int n;
int occ[mxN];
int a[mxN], mn[mxN], mx[mxN];
pii v[mxN];
ll ans=0;
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n; 
    F0R(i, n) cin >> a[i];
    F0R(i, n){
        mn[i]=occ[a[i]];
        occ[a[i]]=i+1;
    }
    F0R(i, n) occ[i]=n-1;
    R0F(i, n){
        mx[i]=occ[a[i]];
        occ[a[i]]=i-1;
    }
    F0R(i, n) v[i]={mn[i], i};
    sort(v, v+n);
    for(int i=0, j=0; i<n; i++){
        while(j<n&&v[j].f<=i){
            seg.add(v[j].s+1, mx[v[j].s]+1, 1);
            seg.on(v[j].s);
            j++;
        }
        seg.add(i+1, mx[i]+1, -1);
        ans+=seg.query(i+1, mx[i]+1);
    }
    cout << ans << nl;
    return 0;
}
