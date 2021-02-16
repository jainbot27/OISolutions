/*
Solution:
Basically, we can fix the position of a black segment ith black segment [x, y] and then solve a dp on the suffix and prefix after that segment is applied.
By that dp[x-1][i-1][0] and dp[n-1-(x+1)][k-(i+1)][1] and if both of these are true then we can put a black segment there
we can do this similar thing with white 

i basically reflected everything so that the impl was easier, and we can find that the dp transitions are nothing 

the dp recurance should hopefully be clear from the code.
ofc the time constraints are cancer so i had to pragma spam to get it to pass :kekw: 
*/

#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("avx,avx2,fma")
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
const int mxN = 2e5 + 10;
const int mxK = 101;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
int n, k;
string s[2], res; vi c[2];
int p[mxN][2];
bool dp[mxN][mxK][2], vis[mxN][mxK][2];
bool white[mxN];
int black[mxN];
 
inline int sum(int l, int r, int T){
    return p[r][T]-(!l?0:p[l-1][T]);
}
 
inline bool solve(int N, int K, int T){
    if(N < 0){
        if(K == 0) return 1;
        else return 0;
    }
    return dp[N][K][T];
}
 
inline bool query(int a, int b, int c, int d){
    return solve(a, b, 0)&&solve(c, d, 1);
}
 
string solve_puzzle(string S2, vi C2){
    s[0] = S2; c[0] = C2;
    s[1] = s[0], c[1] = c[0];
    reverse(all(s[1])); reverse(all(c[1]));
    n = siz(s[0]), k = siz(c[0]);
    c[0].insert(c[0].begin(), 0);
    c[1].insert(c[1].begin(), 0);
    F0R(i, n){
        p[i][0] = (!i?0:p[i-1][0])+(s[0][i]=='_');
        p[i][1] = (!i?0:p[i-1][1])+(s[1][i]=='_');
    }
    F0R(T, 2){
        FOR(K, 0, k+1){
            F0R(i, n){
                if(K == 0){
                    if(s[T][i]!='X') dp[i][K][T] |= solve(i-1, K, T);
                    continue;
                }
                if(s[T][i]!='X')dp[i][K][T]|=solve(i-1, K, T);
                if(i-c[T][K]+1>=0&&sum(i-c[T][K]+1, i, T)==0&&(i-c[T][K]<0||s[T][i-c[T][K]]!='X')) dp[i][K][T] |= solve(i-1-c[T][K], K-1, T);
            }
        }
    }
    F0R(i, n){
        if(s[0][i]!='X'){
            F0R(j, k+1){
                white[i] |= query(i-1, j, (n-1)-(i+1), (k)-j);
            }
        }
    }
    FOR(i, 1, 1+k){
        F0R(j, n+1-c[0][i]){
            if(sum(j, j+c[0][i]-1, 0)==0){
                if((j-1<0||s[0][j-1]!='X')&&(j+c[0][i]>=n||s[0][j+c[0][i]]!='X')){
                    if(query(j-2, i-1, (n-1)-(j+c[0][i]+1), (k)-(i+1)+1)){
                        black[j]++;
                        black[j+c[0][i]]--;
                    }
                }
            }
        }
    }
    res.resize(n);
    F0R(i, n){
        if(black[i]>0&&white[i]) res[i] = '?';
        else if(white[i]) res[i] = '_';
        else {
            res[i] = 'X';
        }
        black[i+1]+=black[i];
    }
    return res;
}
