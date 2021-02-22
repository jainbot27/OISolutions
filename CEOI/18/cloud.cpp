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

template<class T> inline bool ckmin(T&a, T b) {return b < a ? a = b, 1 : 0;}
template<class T> inline bool ckmax(T&a, T b) {return b > a ? a = b, 1 : 0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const char nl = '\n';
const int mxN = 2e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

struct event{
    int v, f, c, t;
};

int n, m;
vector<event> e;
int dp[100005];

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    F0R(i, n){
        int V, F, C; cin >> C >> F >> V; e.pb({V, F, C, 0});
    }
    cin >> m;
    F0R(i, m){
        int V, F, C; cin >> C >> F >> V; e.pb({V, F, C, 1});
    }
    sort(all(e), [](event a, event b){
        if(a.f!=b.f) return a.f>b.f;
        if(a.t!=b.t) return a.t == 0;
        return a.v<b.v;
    });
    F0R(i, 100005) dp[i] = -infLL;
    dp[0] = 0;
    trav(x, e){
        if(x.t==0){
            R0F(j, 100005-x.c){
                ckmax(dp[j+x.c], dp[j]-x.v);
            }
        }
        else{
            FOR(j, x.c, 100005){
                ckmax(dp[j-x.c], dp[j]+x.v);
            }
        }
    }
    cout << *max_element(dp, dp+100005) << nl;
    return 0;
}
