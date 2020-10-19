/*

Notice that we can just set all of the connectors to -1 and build a binary tree. 

My impl is kinda bad, mb look at someone elses :/

*/


#include <bits/stdc++.h>
#include "doll.h"
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
const int mxN = 1e6 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
int switches, m, n, p2 = 1, val = 1; vi x(mxN), y(mxN), c, a, arr;
 
vi label(int node){
    if(node >= p2) return vi{node - p2};
    vi l = label(node*2);
    vi r = label(node*2 + 1);
    vi res;
    F0R(i, siz(l)){
        res.pb(l[i]);
        res.pb(r[i]);
    }
    return res;
}
int cnt = 0;
int dfs(int u, int l, int r){
    if(r < p2 - n){
        return -1;
    }   
    if(l == r){
        return a[arr[l]];
    }
    int xyz = u;
    int m = (l + r)/2;
    cnt++;
    x[xyz] = dfs(cnt, l, m);
    y[xyz] = dfs(cnt, m+1, r);
    return -u-1;
}
void create_circuit(int M, vi A){
    a = A, m = M; n = siz(a);
    F0R(i, m+1){
        c.pb(-1);
    }
    while(p2 <= n){
        p2*=2;
    }
    n++;
    arr = label(1);
    set<int> com;
    map<int, int> mp;
    FOR(i, p2 - n, p2){
        com.insert(arr[i]);
    }
    int ctr = 0;
    trav(v, com){
        mp[v] = ctr++;
    }
    FOR(i, p2-n, p2){
        arr[i] = mp[arr[i]];
    }
    a.pb(0);
    dfs(0, 0, p2-1);
    x.resize(cnt); 
    y.resize(cnt);
    answer(c, x, y);
}
