/*
Notice we can find the first best edge by just finding the diameter. It actually remains true that we can do this for the second loop too, except we have to notice that if
we interfere with our first loop then we actually have to go over that edge again twice. Therefore, we can just reverse the weight of that edge. 

This runs is O(nlogn) but it is possible to get O(n) complexity if we are smarter with how we update edges. 

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

int n, k;
vector<set<pii>> adj;
vpii mx;
vector<pair<int, pii>> dp;

void dfs(int u, int p){
    pii a, b; a=b={0, 0};
    //cout << u << " " << p << nl;
    trav(v, adj[u]){
        if(v.f!=p){
            dfs(v.f, u);
            if(mx[v.f].f+v.s>a.f){
                b = a;
                a = {mx[v.f].f+v.s, v.f};
            }
            else if(mx[v.f].f+v.s>b.f){
                b = {mx[v.f].f+v.s, v.f};
            }
        }
    }
    mx[u] = a;
    dp[u] = {a.f+b.f, {a.s, b.s}};
}

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    adj.resize(n);
    mx.resize(n);
    dp.resize(n);
    F0R(i, n-1){
        int a, b;
        cin >> a >> b; a--; b--; 
        adj[a].insert({b, 1});
        adj[b].insert({a, 1});
    }
    dfs(0, -1);
    if(k==1) cout << 2*n-2+1-max_element(all(dp))->f << nl;
    else{
        int root = max_element(all(dp))-dp.begin();
        int res = dp[root].f;
        for(int p=root, l=dp[root].s.f; l; p = l, l = mx[l].s){
            adj[p].erase({l, 1});
            adj[p].insert({l, -1});
        }
        for(int p=root, l=dp[root].s.s; l; p = l, l = mx[l].s){
            adj[p].erase({l, 1});
            adj[p].insert({l, -1});
        }
        dfs(0, -1);
        res += max_element(all(dp))->f;
        cout << 2*(n-1)+2-res << nl;
    }
    return 0;
}
