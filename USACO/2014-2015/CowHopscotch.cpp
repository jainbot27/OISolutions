/*
  You can sweep with a bit, but we just need to have coord compression so we can don't allocate O(km) memory. 
  
  Time Complexity: O(nmlog(m)) 
*/
#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define ar array
#define all(x) x.begin(), x.end()
#define siz(x) (int) x.size()
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

#define FOR(i, a, b) for(int i=(a); i<(b); i++)
#define ROF(i, a, b) for(int i=(b-1); i>=(a); i--)
#define F0R(i, n) FOR(i, 0, n)
#define R0F(i, n) ROF(i, 0, n)
#define trav(x, y) for(auto&x:y)

using ll=long long;
using ld=long double;
using pii=pair<int, int>;
using pll=pair<ll, ll>;
using pli=pair<ll, int>;
using vi=vector<int>;
using vl=vector<ll>;
using vpii=vector<pii>;

template<class T> inline bool ckmin(T&a, const T&b) {return b<a?a=b,1:0;}
template<class T> inline bool ckmax(T&a, const T&b) {return b>a?a=b,1:0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const char nl='\n';
const int mxN=752;
const int mxK=mxN*mxN;
const int MOD=1e9+7;
const ll infLL=1e18;
const ld eps=1e-6;

struct mint{
    int v;
    mint() {v=0;}
    mint(int V) {v=V;}
    explicit operator int() const{return v;}
    mint& operator+=(const mint&m){
        if((v+=m.v)>=MOD) v-=MOD; return *this;
    }
    mint& operator-=(const mint&m){
        if((v-=m.v)<0) v+=MOD; return *this;
    }
    mint& operator*=(const mint&m){
        v=int(1LL*v*m.v%MOD); return *this;
    }
    friend mint operator+(mint a, const mint&b){
        return a+=b;
    }
    friend mint operator-(mint a, const mint&b){
        return a-=b;
    }
    friend mint operator*(mint a, const mint&b){
        return a*=b;
    }
};

struct bit{
    vector<mint> vals; int n;
    bit(int N): n(N+1), vals(N+1){}
    bit(){}
    void add(int u, mint v){
        for(u++; u<n; u+=u&-u)
            vals[u]+=v;
    }
    mint sum(int u){
        mint res=0;
        for(u++; u>0; u-=u&-u){
            res+=vals[u];
        }
        return res;
    }
    mint sum(int e1, int e2){
        return sum(e2)-sum(e1-1);
    }
};

int n, m, k;
int a[mxN][mxN];
vpii pts[mxK];
bit b[mxK], g;
map<int, int> cc[mxK];

int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    #ifndef ACMX
        freopen("hopscotch.in", "r", stdin);
        freopen("hopscotch.out", "w", stdout);
    #endif
    cin >> n >> m >> k;
    g=bit(m);
    F0R(i, n) F0R(j, m){
        cin >> a[i][j]; a[i][j]--;
        pts[a[i][j]].pb({i, j});
    }
    F0R(i, k){
        for(auto[x, y]:pts[i]){
            cc[i][y]=0;
        }
        int num=0;
        for(auto& v:cc[i]){
            v.s=num++;
        }
        b[i]=bit(num);
    }
    F0R(i, n){
        vector<mint> sav;
        F0R(j, m){
            mint ways=g.sum(j-1);
            ways-=b[a[i][j]].sum(cc[a[i][j]][j]-1);
            sav.pb(ways);
        }
        if(i==0){
            sav[0]+=1;
        }
        F0R(j, m){
            g.add(j, sav[j]);
            b[a[i][j]].add(cc[a[i][j]][j], sav[j]);
        }
        if(i==n-1){
            cout << sav.back().v << nl;
        }
    }
}
