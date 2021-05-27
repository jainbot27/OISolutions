/*
  Just fix the x2 coordinate and do inclusion exclusion on the other (x1, y1, y2) there are not that many cases. 
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
#define FOR(i, a, b) for(auto i=(a); i<(b); i++)
#define ROF(i, a, b) for(auto i=(b)-1; i>=(a); i--)
#define F0R(i, n) FOR(i, 0, n)
#define R0F(i, n) ROF(i, 0, n)

using ll=long long;
using ld=long double;
using pii=pair<int, int>;
using pll=pair<ll, ll>;
using vi=vector<int>;
using vl=vector<ll>;
using vpii=vector<pii>;

template<class T> bool ckmin(T&a, const T&b) {return b<a?a=b,1:0;}
template<class T> bool ckmax(T&a, const T&b) {return b>a?a=b,1:0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int mxN=1e5+10;
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

int n;
int Y[mxN];
int mx[mxN], mn[mxN];
int cut[mxN];
const mi i2=(MOD+1)/2;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    #ifndef ACMX
        freopen("sprinklers.in", "r", stdin);
        freopen("sprinklers.out", "w", stdout);
    #endif
    cin >> n;
    F0R(_, n){
        int X, Y; cin >> X >> Y;
        ::Y[X]=Y;
    }
    mn[0]=mx[0]=n;
    ROF(i, 1, n)
        mx[i]=max(mx[i+1], Y[i]);
    F0R(i, n-1)
        mn[i+1]=min(mn[i], Y[i]+1);
    FOR(i, 1, n)
        FOR(j, mn[i], mn[i-1])
            cut[j]=i-1;
    // we need to sweep over some x2 and find all points (x1, y1, y2)
    int R=n-1, L=n-1; mi sum=0, p=0, ans=0;
    FOR(i, 1, n){
        while(L>=mn[i]){
            p+=cut[L];
            sum+=mi(R-L+1)*cut[L]; 
            L--; 
        }
        while(R>mx[i]&&R>=L){
            sum-=p;
            p-=cut[R];
            R--; 
        }
        ans+=mi(mx[i])*mi(mx[i]+1)*i2*i;
        ans-=sum;
        ans-=(mi(mn[i]-1)*mi(mx[i])-mi(mn[i]-1)*mi(mn[i]-2)*i2)*i; 
    }
    cout << ans.v << "\n";
    return 0; 
}

