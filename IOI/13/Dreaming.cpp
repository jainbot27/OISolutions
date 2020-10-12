/*
Problem: https://oj.uz/problem/view/IOI13_dreaming
My submission: https://oj.uz/submission/309582

Main Idea:
Let CC be short for connected components. Our job is to connect CCs in a way that is advantagous to minimizing path size. We want to pick to connecting points as the center
of our tree. In my code you can find the center by maintaining a range update range query segment tree that supports range add and query max. There are faster ways to do this 
but this suffices as well. Connecting CCs should also be done in the following way. Connect the CC with largest max distance to the center to every other node. This way our 
answer is max(mxCC+2ndmxCC+L, 2ndmxCC+3rdmxCC+2*L). Additionally, we also need consider the largest diameter of the tree in our calculations.
Complexity:O(nlogn)
*/
#include <bits/stdc++.h>
#include <dreaming.h>
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
const int mxN = 100010;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
using node = int;
 
struct lazy{
    int size;
    vector<node> operations;
    vector<node> vals;
    const node NEUTRAL_ELEMENT = 0;
    const node NO_OPERATION = 0;
    const node START_VAL = 0;
    node query_op(node a, node b, int len){
        return a + b;
    }
    node calc_op(node a, node b){
        return max(a, b);
    }
    void apply_mod_op(node & a, node b, int c){
        a = query_op(a, b, c);
    }
    void propogate(int x, int lx, int rx){
        if(rx - lx == 1) return;
        int m = (lx + rx)/2;
        apply_mod_op(operations[2*x+1], operations[x], 1);
        apply_mod_op(vals[2*x+1], operations[x], m-lx);
        apply_mod_op(operations[2*x+2], operations[x], 1);
        apply_mod_op(vals[2*x+2], operations[x], rx-m);
        operations[x] = NO_OPERATION;
    }
    void build(int x, int lx, int rx){
        if(rx == lx + 1){
            vals[x] = START_VAL;
            return;
        }
        int m = (lx + rx)/2;
        build(2*x + 1, lx, m);
        build(2*x + 2, m, rx);
        vals[x] = calc_op(vals[x * 2 + 1], vals[x * 2 + 2]);
    }
    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        operations.assign(2 * size, 0);
        vals.assign(2 * size, 0);
        // build(0, 0, size);
    }
    void update(int l, int r, node v, int x, int lx, int rx){
        propogate(x, lx, rx);
        if(lx >= r || l >= rx) return;
        if(lx >= l && rx <= r){
            apply_mod_op(operations[x], v, 1);
            apply_mod_op(vals[x], v, rx - lx);
            return;
        }
        int m = (lx + rx)/2;
        update(l, r, v, 2 * x + 1, lx , m);
        update(l, r, v, 2 * x + 2, m , rx);
        vals[x] = calc_op(vals[x * 2 + 1], vals[x * 2 + 2]);
    }
    void update(int l, int r, node v){
        update(l, r, v, 0, 0, size);
    }
    node query(int l, int r, int x, int lx, int rx){
        propogate(x, lx, rx);
        if(lx >= r || l >= rx) return NEUTRAL_ELEMENT;
        if(lx >= l && rx <= r){
            return vals[x];
        }
        int m = (lx + rx)/2;
        node m1 = query(l, r, 2 * x + 1, lx, m);
        node m2 = query(l, r, 2 * x + 2, m, rx);
        return calc_op(m1, m2);
    }
    node query(int l , int r){
        return query(l, r, 0, 0, size);
    }
};
 
vpii adj[mxN]; 
int n, m, l, ctr, eu1[mxN], eu2[mxN], d[mxN], bst, diam = 0;
vi a, b, t, cur, coms;
bool vis[mxN];
 
void dfs(int u, int p, int dist){
    vis[u] = 1;
    eu1[u] = ctr;
    eu2[u] = ctr;
    ctr++;
    d[u] = dist;
    cur.pb(u);
    trav(v, adj[u]){
        if(v.f==p)
            continue;
        dfs(v.f, u, v.s + dist);
        ckmax(eu2[u], eu2[v.f]);
    }
}
void dfs2(int u, int p, int dist, lazy&st){
    st.update(eu1[u], eu2[u]+1, -2*dist);
    st.update(0, ctr, dist);
    ckmin(bst, (int)st.query(0, ctr));
    ckmax(diam, (int) st.query(0, ctr));
    trav(v, adj[u]){
        if(v.f == p) 
            continue;
        dfs2(v.f, u, v.s, st);
    }
    st.update(eu1[u], eu2[u]+1, 2*dist);
    st.update(0, ctr, -dist);
}
int travelTime(int N, int M, int L, int A[], int B[], int T[]){
    n = N, m = M, l = L;
    a = b = t = vi(m);
    F0R(i, m){
        a[i] = A[i];
        b[i] = B[i];
        t[i] = T[i];
    }
    F0R(i, m){
        adj[a[i]].pb({b[i], t[i]});
        adj[b[i]].pb({a[i], t[i]});
    }
    F0R(i, n){
        if(vis[i]) 
            continue;
        ctr = 0;
        cur.clear();
        bst = MOD;
        dfs(i, -1, 0);
        lazy st;
        st.init(ctr);
        trav(x, cur){
            st.update(eu1[x], eu1[x]+1, d[x]);
        }
        dfs2(i, -1, 0, st);
        coms.pb(bst);
    }
    sort(all(coms), greater<int>());
    if(siz(coms)==1){
        return max(coms[0], diam);
    }
    else if(siz(coms)==2){
        return max(coms[0] + coms[1] + L, diam);
    }
    else{
        return max({diam,coms[0]+coms[1]+L, coms[2]+coms[1]+2*L});
    }
}
