/*
  Simply DFS and realize there are only 2^5 states for each node.
  
  Complexity: O(n*2^k)
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
const int mxN=3e5+10;
const int MOD=1e9+7;
const ll infLL=1e18;
const ld eps=1e-6;

int n, m, k;
int col[mxN];
vi adj[mxN];
ll ans=0;
ll memo[mxN][1<<5];

ll dfs(int u, int msk){
    if((1<<col[u])&msk)
        return 0;
    msk|=1<<col[u];
    if(memo[u][msk]!=-1) return memo[u][msk];
    memo[u][msk]=1;
    trav(v, adj[u])
        memo[u][msk]+=dfs(v, msk);
    return memo[u][msk];
}

int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> k;
    memset(memo, -1, sizeof memo);
    F0R(i, n) cin >> col[i], col[i]--;
    F0R(i, m){
        int e1, e2; cin >> e1 >> e2; 
        e1--; e2--; 
        adj[e1].pb(e2); adj[e2].pb(e1);
    }
    F0R(i, n)
        ans+=dfs(i, 0);
    cout << ans-n << nl;
}
