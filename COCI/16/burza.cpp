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
const int mxN = 401;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
void no(){
    cout << "DA\n"; exit(0);
}
 
int n, k;
vi adj[mxN];
int d[mxN], st[mxN], en[mxN];
int CNT=0;
int vis[mxN];
bool dp[401][1<<20];
vi node[mxN];;
 
void dfs(int u, int p){
    vis[u]=1;
    if(d[u]==k-1){
        st[u]=CNT++;
        en[u]=CNT;
        return;
    }  
    st[u]=CNT;
    trav(v, adj[u]){
        if(v==p) continue;
        d[v] = d[u]+1;
        dfs(v, u);
    }
    en[u]=CNT;
}
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    if(k*k>=n) {
        no();
    }
    F0R(i, n-1){
        int x, y; cin >> x >> y; x--; y--;
        adj[x].pb(y); adj[y].pb(x);
    }
    d[0]=-1;
    dfs(0, -1);
    FOR(i, 1, n) node[st[i]].pb(i);
    //F0R(i, n) cout << d[i] << ' ';
    //cout << nl;
    dp[0][0]=1;
    F0R(i, CNT){
        trav(v, node[i]){
            F0R(msk, 1<<k){
                if(!dp[i][msk]) continue;
                if((msk&(1<<d[v]))==0){
                    dp[en[v]][msk|(1<<d[v])]|=dp[i][msk];
                }
            }
        }    
    }
    int ans =0 ;
    F0R(msk, 1<<k){
        if(dp[CNT][msk]){
            ans=1;
        }
    }
    cout << (ans?"DA":"NE")<<nl;
    return 0;
}
