#include <bits/stdc++.h>
using namespace std;
#define int ll 
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
 
#define int ll
int n;
int sob(int x){
    if(x==0) return 0;
    else return __builtin_ctz(x);
}
vpii proc;
 
vector<pii> al;
map<int, pii> lstx, lsty;
vector<vector<pii>> adj;
map<pii, int> tot;
vi weight;
ll ans = 0;
int cnt = 0;
vpii cords;
 
int dist(pii A, pii B){
    return abs(A.f-B.f)+abs(A.s-B.s);
}
 
void dfs(int u, int p){
    //cout << u << ' ' << p << nl;
    trav(x, adj[u]){
        if(x.f != p){
            dfs(x.f, u);
            weight[u] += weight[x.f];
            ans += weight[x.f]*x.s;
            //cout << u << ' ' << x.f << ' ' << x.s << nl;
            //cout << u << ' ' << x.f << ' ' << cords[u].f << ' ' << cords[u].s << ' ' << cords[x.f].f << ' ' << cords[x.f].s << ' ' << x.s << nl;
        }
    }
}
 
void dfs2(int u, int p, ll cur){
    ckmin(ans, cur);
    //cout << cur << nl;
    trav(v, adj[u]){
        if(v.f==p) continue;
        cur += (n-weight[v.f])*v.s;
        cur -= weight[v.f]*v.s;
        //cout << weight[u] << ' ' << weight[v.f] << ' '  << u << ' ' << v.f << ' ' << v.s << ' ' << cur << nl;
        dfs2(v.f, u, cur);
        cur -= (n-weight[v.f])*v.s;
        cur += weight[v.f]*v.s;
    }
}
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    F0R(i, n){
        int A, B;
        cin >> A >> B;
        tot[{A, B}]++;
        //cout << "NEW\n";
        al.pb({A, B});
        while(A!=0||B!=0){
            proc.pb({A, B});
            if((B==0||sob(A)<sob(B))&&A!=0){
                A -= 1<<sob(A);
            }
            else{
                B -= 1<<sob(B);
            }
        }        
        proc.pb({0, 0});
    }    
    //exit(0);
    sort(all(proc), [](const pii& e1, const pii& e2){
        if(e1.f+e1.s==e2.f+e2.s) return e1.f < e2.f;
        return e1.f+e1.s<e2.f+e2.s;
    });
    proc.resize(unique(all(proc))-proc.begin());
    trav(x, proc){
        //cout << "A: " << x.f << ' ' << x.s << nl;
        adj.pb({});
        if(!x.f&&!x.s){
            lstx[0] = {0, cnt};
            lsty[0] = {0, cnt};
        }     
        else{
            if((x.s==0||sob(x.f)<sob(x.s))&&x.f!=0){
                int lst = lsty[x.s].f;
                int v = lsty[x.s].s;
                //cout << "A: " << x.f << ' ' << x.s << ' ' << lst << ' ' << x.s << ' ' << v <<  nl;
                adj[cnt].pb({v, dist(x, {lst, x.s})});
                adj[v].pb({cnt, dist(x, {lst, x.s})});
            }
            else{
                int lst = lstx[x.f].f;
                int v = lstx[x.f].s;
                //cout << "B: " << x.f << ' ' << x.s << ' ' << x.f << ' ' << lst << ' ' << v << nl;
                adj[cnt].pb({v, dist(x, {x.f, lst})});
                adj[v].pb({cnt, dist(x, {x.f, lst})});
            }
        }
        //cout << cnt << ' ' << x.f << ' ' << x.s << nl;
        ckmax(lstx[x.f], {x.s, cnt});
        ckmax(lsty[x.s], {x.f, cnt});
        cords.pb({x.f, x.s});
        weight.pb(tot.count({x.f, x.s})?tot[{x.f, x.s}]:0);
        cnt++;
    }
    dfs(0, -1);
    //cout << ans << nl;
    dfs2(0, -1, ans);
    cout << ans << nl;
 
    return 0;
}
