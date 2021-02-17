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
const int mxN = 1e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
const double eps = 1e-6;
 
double ans[mxN];
int a[mxN], b[mxN];
vpii adj[mxN];
int n, m;
vector<double> vals;
vi cur, al;
 
void bad(){
    cout<<"NO\n";
    exit(0);
}
 
void dfs(int u, int A, int B){
    if(a[u]==0){
        a[u] = A, b[u] = B;
        cur.pb(u); al.pb(A*B);
        trav(v, adj[u]) dfs(v.f, -A, v.s-B);
    }
    else if(a[u]!=A||b[u]!=B){
        if(a[u]==A) bad();
        vals.pb(1.0*(B-b[u])/(a[u]-A));
    }
}
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    F0R(i, m){
        int e1, e2, e3; cin >> e1 >> e2 >> e3; e1--; e2--; 
        adj[e1].pb({e2, e3}); adj[e2].pb({e1, e3});
    }
    F0R(i, n){
        if(a[i]==0){
            vals.clear(); al.clear(); cur.clear();
            dfs(i, 1, 0);
            if(siz(vals)){
                sort(all(vals));
                if(abs(vals[0]-vals.back())>eps) bad();
                trav(q, cur) ans[q] = vals[0]*a[q]+b[q];
 
            }
            else{
                sort(all(al));
                trav(q, cur) ans[q] = -al[siz(al)/2]*a[q]+b[q];
            }
        }
    }
    cout << fixed << setprecision(12);
    cout << "YES\n";
    F0R(i, n) cout << ans[i] << ' ';
    cout << nl;
    return 0;
}
