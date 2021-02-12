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
using pll = pair<ll, ll>;
using vpii = vector<pair<int, int>>;

template<class T> inline bool ckmin(T&a, T b) {return b < a ? a = b, 1 : 0;}
template<class T> inline bool ckmax(T&a, T b) {return b > a ? a = b, 1 : 0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const char nl = '\n';
const int mxN = 101;
const int mxK = 1001;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

int n, m, k;
pll cost[mxN][mxK];
ll dist[mxN][mxN];
ll profit[mxN][mxN];
ll dist2[mxN][mxN];

void go(ll arr[mxN][mxN]){
    F0R(i, n){
        F0R(j, n){
            F0R(q, n){
                ckmin(arr[j][q], arr[j][i]+arr[i][q]);
            }
        }
    }
}

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    F0R(i, n){
        F0R(j, k){
            cin >> cost[i][j].f >> cost[i][j].s;
        }
    }
    F0R(i, n){
        F0R(j, n) {
            dist[i][j] = infLL;
            //profit[i][j] = -1;
        }
    }
    F0R(i, m){
        int e1, e2; ll e3;
        cin >> e1 >> e2 >> e3;
        e1--; e2--; 
        ckmin(dist[e1][e2], e3);
    }
    go(dist);
    F0R(i, n){
        F0R(j, n){
            F0R(K, k){
                if(cost[j][K].s!=-1&&cost[i][K].f!=-1){
                    ckmax(profit[i][j], cost[j][K].s-cost[i][K].f);
                }
            }
        }
    }
    ll l = 1, r = 1e9;
    while(l <= r){
        ll mid = (l + r)/2;
        F0R(i, n) F0R(j, n){
            dist2[i][j]=mid*min(infLL/mid, dist[i][j])-profit[i][j];
        }
        go(dist2);
        bool g = 0;
        F0R(i, n) g |= dist2[i][i] <= 0;
        if(g) l = mid+1;
        else r = mid-1;
    }
    cout << r << nl;
    return 0;
}
