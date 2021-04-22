/*
  Basically, we can just travel across the grid and use a bit to maintain which points are currently in our grid with a Binary Indexed Tree. 
  There are a couple annoying special cases to work out.
  
  Complexity: O(n^2logn)
*/
#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define ar array
#define all(x) x.begin(), x.end()
#define siz(x) (int) x.size()
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

#define FOR(i, a, b) for(int i=(a); i<(b); i++)
#define ROF(i, a, b) for(int i=(b-1); i>=(a); i--)
#define F0R(i, n) FOR(i, 0, n)
#define R0F(i, n) ROF(i, 0, n)
#define trav(x, y) for(auto&x:y)

using ll=long long;
using ld=long double;
using pii=pair<int, int>;
using pll=pair<ll, ll>;
using pli=pair<ll, int>;
using vi=vector<int>;
using vl=vector<ll>;
using vpii=vector<pii>;

template<class T> inline bool ckmin(T&a, const T&b) {return b<a?a=b,1:0;}
template<class T> inline bool ckmax(T&a, const T&b) {return b>a?a=b,1:0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const char nl='\n';
const int mxN=1002;
const int MOD=1e9+7;
const ll infLL=1e18;
const ld eps=1e-6;

int n; 
int a[mxN][mxN];
int bit[mxN];
int val[mxN*mxN][4];
vector<ar<int, 3>> upd[mxN];
bool bad[mxN*mxN];
int ans;
int tot=0;

void add(int u, int d){
    for(u++; u<mxN; u+=u&-u)
        bit[u]+=d;
}
int sum(int u){
    int res=0;
    for(u++; u>0; u-=u&-u){
        res+=bit[u]; 
    }
    return res;
}

int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    #ifndef ACMX 
        freopen("art.in", "r", stdin);
        freopen("art.out", "w", stdout);
    #endif
    cin >> n;
    ans=n*n;
    F0R(i, n*n)
        val[i][0]=val[i][1]=MOD, val[i][2]=val[i][3]=-MOD;
    F0R(i, n) F0R(j, n) {
        cin >> a[i][j]; a[i][j]--;
        if(a[i][j]==-1) continue;
        ckmin(val[a[i][j]][0], i);
        ckmin(val[a[i][j]][1], j);
        ckmax(val[a[i][j]][2], i);
        ckmax(val[a[i][j]][3], j);
    }
    F0R(i, n*n){
        if(val[i][0]!=MOD){
            tot++;
            upd[val[i][0]].pb({val[i][1], val[i][3], 1});
            upd[val[i][2]+1].pb({val[i][1], val[i][3], -1});
        }
    }
    if(tot==0){
        cout << "0\n";
        return 0;
    }
    if(tot==1){
        if(n==1) cout << "1\n";
        else cout << n*n-1 << nl;
        return 0;
    }
    F0R(i, n){
        for(auto [lo, hi, d]:upd[i]){
            add(lo, d);
            add(hi+1, -d);
        }
        F0R(j, n){
            if(a[i][j]==-1||bad[a[i][j]]) continue;
            add(val[a[i][j]][1], -1);
            add(val[a[i][j]][3]+1, 1);
            if(sum(j)) bad[a[i][j]]=1;
            add(val[a[i][j]][1], 1);
            add(val[a[i][j]][3]+1, -1);
        }
    }
    F0R(i, n*n) ans-=bad[i];
    cout << ans << nl;
}
