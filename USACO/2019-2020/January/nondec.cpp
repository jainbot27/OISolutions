/*
  notice that adding a value can be seen my multiplying a matrix which is very similar to an identity matrix so we can calulate inverses and almost be done.
  however, there are smarter ways to do many operations because of the matrices being very simple, so we can get a passing complexity.
  Time Complexity: O(K(Q+NK))
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
const int mxN=5e4+10;
const int mxK=20;
const int MOD=1e9+7;
const ll infLL=1e18;
const ld eps=1e-6;

template<int mod> struct mint {
    int v; explicit operator int() const{return v;} 
    mint() {v=0;}
    mint(ll _v) { v =int((-mod< _v&&_v<mod)?_v:_v%mod);
        if(v < 0) v+=mod;}
    friend bool operator==(const mint& a, const mint& b){ 
        return a.v==b.v;}
    friend bool operator!=(const mint& a, const mint& b){ 
        return !(a==b);}
    friend bool operator<(const mint& a, const mint& b){ 
        return a.v<b.v;}
    mint& operator+=(const mint& m) { 
        if((v+=m.v)>=mod) v-=mod; 
        return *this;}
    mint& operator-=(const mint& m) { 
        if((v-=m.v)<0) v+=mod; 
        return *this;}
    mint& operator*=(const mint& m){ 
        v=int((ll)v*m.v%mod); return *this;}
    mint& operator/=(const mint& m) {return (*this)*=inv(m);}
    friend mint pow(mint a, ll p) {
        mint ans = 1; assert(p >= 0);
        for (;p;p/=2,a*=a) if(p&1) ans*=a;
        return ans;}
    friend mint inv(const mint& a){assert(a.v!=0); 
        return pow(a,mod-2);}
    mint operator-() const{return mint(-v);}
    friend mint operator+(mint a, const mint& b) {return a+=b;}
    friend mint operator-(mint a, const mint& b) {return a-=b;}
    friend mint operator*(mint a, const mint& b) {return a*=b;}
    friend mint operator/(mint a, const mint& b) {return a/=b;}
};

using mi=mint<MOD>;

vector<mi> invs, fac, ifac; 
void genFac(int SZ=mxN) {
    invs.resize(SZ), fac.resize(SZ), ifac.resize(SZ); vi Invs(SZ);
    Invs[1]=1; invs[1]=fac[0]=ifac[0]=1; 
    FOR(i,2,SZ) Invs[i] = int(MOD-(ll)MOD/i*Invs[MOD%i]%MOD), invs[i]=mi(Invs[i]);
    FOR(i,1,SZ) {
        fac[i]=fac[i-1]*i;
        ifac[i]=ifac[i-1]*invs[i];
    }
}

mi choose(int n, int k){
    if(k>n) return 0;
    return fac[n]*ifac[n-k]*ifac[k];
}

mi v[mxN][mxK], iv[mxN][mxK];
mi mat[mxK][mxK], imat[mxK][mxK];

int N, K;

int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
#ifndef ACMX
    freopen("nondec.in", "r", stdin); 
    freopen("nondec.out", "w", stdout);
#endif
    const mi i2=inv(mi(2)); 
    cin >> N >> K;
    F0R(i, K) mat[i][i]=imat[i][i]=1;
    F0R(i, N+1){
        F0R(j, K) iv[i][j]=imat[0][j];
        F0R(j, K) FOR(k, j, K) v[i][j]+=mat[j][k];
        if(i==N) break;
        int x; cin >> x; x--; 
        F0R(j, x+1) ROF(k, j, x+1) mat[j][x]+=mat[j][k];
        F0R(j, x) FOR(k, x, K) imat[j][k]-=i2*imat[x][k];
        FOR(j, x, K) imat[x][j]*=i2;
    }
    int q;
    cin >> q;
    F0R(_, q){
        int L, R; cin >> L >> R; 
        L--; 
        mi ans=0;
        F0R(j, K) ans+=iv[L][j]*v[R][j];
        cout << ans.v << "\n";
    }
}
