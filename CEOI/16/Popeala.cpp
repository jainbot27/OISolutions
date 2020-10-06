/*
Problem: https://oj.uz/problem/view/CEOI16_popeala
Main Idea:

O(K^2S) dp should be obvious. We have an array to split into  **************** and for each of i till S we need to choose bars to partition the array. 
                                                              ******|****|****** (i=2 example)
You can make a dp this way checking the answers for prev. states. 
Optimize O(K^2S) to O(KNS) by realizing that we can keep pointers for each of the N amounts for the last value we saw where they dont work, and these values always are increaseing
meaning we can run over them in O(nks). 
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
const int mxN = 2e4 + 10;
const int mxM = 51;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

int p[mxN], v[mxN], l[mxN][mxM], b[mxN], dp[mxN][mxM], n, t, s;
string x[mxM];

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> t >> s;
    FOR(i, 1, t+1){
        cin >> v[i];
        p[i] = p[i-1] + v[i];
    } 
    FOR(j, 1, n+1){
        cin >> x[j];
        F0R(i, t){
            if(x[j][i]=='1') l[i+1][j]=l[i][j];
            else l[i+1][j]=i+1;
        }
    }
    FOR(i, 1, t+1){
        l[i][0] = i;
        sort(l[i], l[i]+1+n);
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    FOR(j, 1, s+1){
        memset(b, 0x3f, sizeof(b));
        FOR(i, 1, t+1){
            F0R(k, n+1){
                FOR(cur, l[i-1][k], l[i][k]){
                    b[k] = min(b[k], dp[cur][j-1]-p[cur]*k);
                } 
                dp[i][j] = min(dp[i][j], b[k]+p[i]*k);
            }
            // cout << dp[i][j] << " " << i << " " << j << endl;
        }
        cout << dp[t][j] << nl;
    }
    return 0;
}
