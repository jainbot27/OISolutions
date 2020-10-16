/*
We can always accurately figure out the absolute values of the differences by repeatedly querying the nearest 2 and then nearest 3 elements.
Then we need to fix our answer to the constraints and use the a[1] < a[n] condition. 

*/

#include <bits/stdc++.h>
#include "xylophone.h"
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
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
void solve(int N){
    vi a(N + 1);
    a[1] = 0;
    a[2] = query(1, 2);
    FOR(i, 2, N){
        int t = query(i, i+1);
        int u = query(i-1, i+1);
        if(t + abs(a[i] - a[i-1]) == u){
            if(a[i] - a[i-1] >= 0) a[i+1] = a[i] + t;
            else a[i+1] = a[i] - t;
        }
        else{
            if(a[i] - a[i-1] >= 0) a[i+1] = a[i] - t;
            else a[i+1] = a[i] + t;
        }
    }
    int mn = *min_element(1+all(a));
    FOR(i, 1, N+1) a[i] -= mn;
    int l, r;
    FOR(i, 1, N+1){
        if(a[i] == 0) l = i;
        if(a[i] == N-1) r = i;
    }
    FOR(i, 1, N+1){
        if(l < r){
            answer(i, a[i]+1);
        }
        else{
            answer(i, N-a[i]);
        }
    }
}
 
