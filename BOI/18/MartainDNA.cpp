/*
  Just sweep with 2 pointers. 
  
  Complexity: O(n)
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
const int mxN=2e5+10;
const int MOD=1e9+7;
const ll infLL=1e18;
const ld eps=1e-6;

int n, m, k;
int a[mxN];
int cnt[mxN];
int need[mxN];
int tot=0;
int ans=MOD;

int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> k;
    F0R(i, n) cin >> a[i];
    F0R(i, k){
        int b, q; cin >> b >> q;
        need[b]+=q;
    }
    for(int l=0, r=0; l<n; l++){
        if(l){
            cnt[a[l-1]]--;
            if(need[a[l-1]]==cnt[a[l-1]]+1) tot--;
        }
        while(r<n&&tot<k){
            cnt[a[r]]++;
            if(need[a[r]]==cnt[a[r]]) tot++;
            r++;
        }
        if(r==n&&tot<k){
            break;
        }
        if(tot==k){
            ckmin(ans, r-l);
        }
    }
    if(ans==MOD) cout << "impossible\n";
    else cout << ans << nl;
}

