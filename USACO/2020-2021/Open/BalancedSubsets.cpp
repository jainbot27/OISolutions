/*
the observation is that any valid subset will first increase and then decrease in both x and y coordinates
we can traverse down one dimensions, so we only have to care about the other one, giving us
dp[i][l][r], and we can keep track of whether we are increasing or decreasing on which sides at all times. 
We need 2d prefix sums to calculate this in decent time.

Complexity: O(n^3) 
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
const int mxN = 152;
const int MOD = 1e9+7;
const ll infLL = 1e18;
const ld eps = 1e-6;

struct mint{
    int v; 
    explicit operator int() const {return v;}
    mint(int V):v(V) {}
    mint(): v(0) {}
    mint &operator+=(const mint&m){
        if((v+=m.v)>=MOD) v-= MOD; 
        return *this;
    }
    mint &operator-=(const mint&m){
        if((v-=m.v)<0) v+=MOD;
        return *this;
    }
    mint &operator*=(const mint&m){
        v=(int)((ll)v*m.v%MOD);
        return *this;
    }
    friend mint operator+(mint a, const mint&b){
        return a+=b;
    }
    friend mint operator-(mint a, const mint&b){
        return a-=b;
    }
    friend mint operator*(mint a, const mint&b){
        return a*=b;
    }
} dp[mxN][mxN][mxN][2][2], p[mxN][mxN][2][2];

int n; 
bool g[mxN][mxN];
int p2[mxN][mxN];
mint ans=0;

mint get(int x0, int y0, int x1, int y1, int e, int r){
    return p[x1][y1][e][r]-p[x0-1][y1][e][r]-p[x1][y0-1][e][r]+p[x0-1][y0-1][e][r];
}

int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    F0R(i, n) F0R(j, n){
        char c; cin >> c; 
        if(c=='G') g[i+1][j+1]=1;
        p2[i+1][j+1]=p2[i+1][j]+(!g[i+1][j+1]);
    }
    FOR(i, 1, n+1){
        FOR(j, 1, n+1)
            FOR(k, 1, n+1)
                F0R(e, 2)
                    F0R(r, 2)
                        p[j][k][e][r]=p[j-1][k][e][r]+p[j][k-1][e][r]-p[j-1][k-1][e][r]+dp[i-1][j][k][e][r];
        FOR(j, 1, n+1){
            FOR(k, 1, n+1){
                dp[i][j][k][0][0]+=1+get(j, j, k, k, 0, 0);
                dp[i][j][k][0][1]+=get(j, k, k, n, 0, 1)+get(j, k+1, k, n, 0, 0);
                dp[i][j][k][1][0]+=get(1, j, j, k, 1, 0)+get(1, j, j-1, k, 0, 0);
                dp[i][j][k][1][1]+=get(1, k, j, n, 1, 1)+get(1, k, j-1, n, 0, 1)+get(1, k+1, j, n, 1, 0)+get(1, k+1, j-1, n, 0, 0);
            }
        }
        FOR(j, 1, n+1){
            FOR(k, 1, n+1){
                if(j>k||p2[i][k]-p2[i][j-1]>0){
                    F0R(e, 2) F0R(r, 2) dp[i][j][k][e][r]=0;
                }
                F0R(e, 2) F0R(r, 2) ans+=dp[i][j][k][e][r];
            }
        }
    }
    cout << ans.v << nl;
    return 0;
}
