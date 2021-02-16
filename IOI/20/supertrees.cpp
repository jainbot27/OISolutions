/*

Connect all the ones together and makes sure they dont have a 2 among them. Then connect all the 2s together to the root of every 1 tree. Make sure we didn't override any 0's.

3's are irrelevant. 
*/
#include <bits/stdc++.h>
#include "supertrees.h"
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
const int mxN = 1001;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

struct dsu{
    vi par, sz; 
    void init(int n) {
        par.resize(n);
        sz.resize(n, 1);
        F0R(i, n) par[i] = i;
    }
    int find(int x){
        return par[x] = (par[x] == x ? x : find(par[x]));
    }
    void comb(int a, int b){
        a = find(a), b = find(b);
        if(a != b){
            if(sz[a] < sz[b]) swap(a, b);
            sz[a] += sz[b];
            par[b] = a;
        }
    }
};
vector<vi> res;
dsu o, t;
vpii q[4];
vector<vi> tot;
construct(vector<vi> g){
    int n = siz(g);
    res = g;
    F0R(i, n) fill(all(res[i]), 0);
    F0R(i, n){
        F0R(j, n){
            q[g[i][j]].pb({i, j});
        }
    }
    o.init(n);
    tot.resize(n);
    if(siz(q[3])) return 0;
    trav(x, q[1]){
        o.comb(x.f, x.s);
    }
    F0R(i, n){
        if(o.find(i)!=i)
            res[o.find(i)][i]=res[i][o.find(i)]=1;
    }
    t.init(n);
    trav(x, q[2]){
        t.comb(o.find(x.f), o.find(x.s));
    }
    F0R(i, n){
        F0R(j, n){
            if(o.find(i)==o.find(j)){
                if(g[i][j]==2 || g[i][j] == 0) return 0;
            }
        }
    }
    F0R(i, n){
        if(t.sz[t.find(i)] == 1) continue;
        if(t.sz[t.find(i)] == 2) return 0;
        tot[t.find(i)].pb(i);
    }
    F0R(i, n){
        if(siz(tot[i])){
            res[tot[i][0]][tot[i].back()]=res[tot[i].back()][tot[i][0]]=1;
            F0R(j, siz(tot[i])-1){
                o.comb(tot[i][j], tot[i][j+1]);
                res[tot[i][j]][tot[i][j+1]]=
                res[tot[i][j+1]][tot[i][j]]=1;
            }
        }
    }
    trav(x, q[0]){
        if(o.find(x.f)==o.find(x.s)) return 0;
    }
    build(res);
    return 1;
}
