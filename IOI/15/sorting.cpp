/*
Observation:
if we can do it in N turns, we can do it in N + 1
it suffices to binary search
be careful with impl or you will spend 45 minutes debugging like me :GWvictoriaNotLikeBlob:
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
const int mxN = 2e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

int findSwapPairs(int n, int* s, int M, int* x, int *y, int *p, int *q){
    int l = 0, r = M + 1;
    vpii ans;
    while(l < r){
        int m = l + r; m = m / 2;
        vi pos(n);
        vi cur(n);
        vpii ops;
        F0R(i, n){
            cur[i] = s[i];
        }
        F0R(i, m){
            swap(cur[x[i]], cur[y[i]]);
        }
        F0R(i, n){
            pos[cur[i]] = i;
        }
        F0R(i, n){
            if(cur[i] != i){
                int x = cur[i];
                int z = pos[i];
                ops.pb({i, x});
                cur[z] = x;
                cur[i] = i;
                pos[i] = i;
                pos[x] = z;

            }
        }
        if(siz(ops) <= m){
            ans = ops;
            r = m;
        }
        else{
            l = m + 1;
        }
    }
    vi pos(n);
    vi cur(n);
    vpii res;
    F0R(i, n){
        pos[s[i]] = i;
        cur[i] = s[i];
    }
    F0R(i, siz(ans)){
        swap(pos[cur[x[i]]], pos[cur[y[i]]]);
        swap(cur[x[i]], cur[y[i]]);
        res.pb({pos[ans[i].f], pos[ans[i].s]});
        swap(pos[ans[i].f], pos[ans[i].s]);
        swap(cur[pos[ans[i].f]], cur[pos[ans[i].s]]);
    }
    F0R(i, l){
        if(i < res.size()){
            p[i] = res[i].f; q[i] = res[i].s;
        }
        else{
            p[i] = 0; q[i] = 0;
        }
    }
    return l;
}
