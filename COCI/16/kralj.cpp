/*
there exist components where certain numbers could possibly be, finding those components with dsu in nlogn is possible.
assume everything forwards is done modulo n
the key observation is that if there are x elements j such that a[j]=i, then the range [i, i+x) will contain that number. However, if we find a new number in that range, we can
extend even further. Note is impossible to wrap all the way around. Once that is done just use the greedy solution from the subtask 1 where u take the cheapest one u can for
each element. 


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
const int mxN = 5e5+10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
int n;
int a[mxN];
int st[mxN];
int par[mxN];
vi v[mxN];
int nums[mxN];
int ans = 0;
 
int p(int q){
    if(par[q]==q) return par[q];
    return par[q]=p(par[q]);
}
 
void comb(int e1, int e2){
    e1 = p(e1); e2 = p(e2);
    par[e2] = e1;
}
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    F0R(i, n){
        par[i] = i;
        cin >> a[i]; a[i]--;
    }
    F0R(i, n){
        cin >> st[i];
    }
    F0R(i, n){
        int x; cin >> x;
        v[a[i]].pb(x);
    }
    int q = 0;
    F0R(i, 2*n){
        bool good = 1;
        if(q>0){
            comb((i-1)%n, i%n);
            q--;
            good = 0;
        }
        q += max(siz(v[i%n])-good,0);
    }
    F0R(i, n){
        nums[par[i]]++;
    }
    F0R(i, n){
        set<int> al;
        FOR(j, i, i+nums[i]){
            trav(x, v[j%n]){
                al.insert(x);
            }
            auto it = al.lower_bound(st[j%n]);
            if(it==al.end()) al.erase(al.begin());
            else{
                ans++;
                al.erase(it);
            }
        }
    }
    cout << ans << nl;
    return 0;
}
