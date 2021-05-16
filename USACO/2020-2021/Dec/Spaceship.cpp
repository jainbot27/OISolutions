/*
The general idea is that we basically can solve the problem for no starting points useing a dp and then do casework on what we have found when answering queries.

Complexity: O(qn^2k+kn^3)
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
const int mxN=60;
const int MOD=1e9+7;
const ll infLL=1e18;
const ld eps=1e-6;


struct mint {
    static const int mod = MOD;
    int v; explicit operator int() const { return v; } // explicit -> don't silently convert to int
    mint() { v = 0; }
    mint(ll _v) { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
        if (v < 0) v += MOD; }
    friend bool operator==(const mint& a, const mint& b) { 
        return a.v == b.v; }
    friend bool operator!=(const mint& a, const mint& b) { 
        return !(a == b); }
    friend bool operator<(const mint& a, const mint& b) { 
        return a.v < b.v; }
    mint& operator+=(const mint& m) { 
        if ((v += m.v) >= MOD) v -= MOD; 
        return *this; }
    mint& operator-=(const mint& m) { 
        if ((v -= m.v) < 0) v += MOD; 
        return *this; }
    mint& operator*=(const mint& m) { 
        v = int((ll)v*m.v%MOD); return *this; }
    mint& operator/=(const mint& m) { return (*this) *= inv(m); }
    friend mint pow(mint a, ll p) {
        mint ans = 1; assert(p >= 0);
        for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans; }
    friend mint inv(const mint& a) { assert(a.v != 0); 
        return pow(a,MOD-2); }
    mint operator-() const { return mint(-v); }
    mint& operator++() { return *this += 1; }
    mint& operator--() { return *this -= 1; }
    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
};

template<class T, int N> struct Mat{
    array<array<T, N>, N> d{};
    Mat(T X=T()) {F0R(i, N) d[i][i]=X; }
    Mat operator-(const Mat&m)const{
        Mat res; 
        F0R(i, N) F0R(j, N) res[{i, j}]=d[i][j]-m[{i, j}];
        return res;
    }
    Mat operator+(const Mat&m)const{
        Mat res;
        F0R(i, N) F0R(j, N) res[{i, j}]=d[i][j]+m[{i, j}];
        return res; 
    }
    Mat operator*(const Mat& m)const{
        Mat a;
        F0R(i, N) F0R(j, N) F0R(k, N){
            a[{i, j}]+=d[i][k]*m[{k, j}];
        }
        return a;
    };
    T&operator[](ar<int, 2> b){
        return d[b[0]][b[1]];
    }
    const T&operator[](ar<int, 2> b)const{
        return d[b[0]][b[1]];
    }
    Mat operator^(ll p){
        Mat a, b(*this);
        F0R(i, N) a.d[i][i] = 1;
        while(p){
            if(p&1) a = a * b;
            b = b * b;
            p/=2;
        }
         return a;
    };
};

using mat=Mat<mint, mxN>;

int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int n, k, q; cin >> n >> k >> q;
    vector<mat> ways(k); 
    F0R(i, n){
        string s; cin >> s;
        F0R(j, siz(s)){
            ways[0][{i, j}]=s[j]-'0';
        }
    }
    F0R(i, k-1){
        ways[i+1]=ways[i]+(ways[i]*ways[i]);
    }
    while(q--){
        int u, f, v, s;
        cin >> f >> u >> s >> v;
        u--; v--; f--; s--; 
        mint ans=0;
        ar<mint, mxN> LHS, RHS;
        LHS[u]=1, RHS[v]=1; 
        bool chu=0, chv=0;
        FOR(cnt, max(f, s), k){
            while(f<cnt){
                ar<mint, mxN> nxt; 
                F0R(i, n) F0R(j, n) nxt[j]+=LHS[i]*ways[f][{i, j}];
                if(!chu) LHS[u]=0;
                F0R(i, n) LHS[i]+=nxt[i];
                f++; chu=1;
            }
            while(s<cnt){
                ar<mint, mxN> nxt; 
                F0R(i, n) F0R(j, n) nxt[i]+=ways[s][{i, j}]*RHS[j];
                if(!chv) RHS[v]=0;
                F0R(i, n) RHS[i]+=nxt[i];
                s++; chv=1; 
            }
            F0R(j, n) ans+=LHS[j]*RHS[j];
        }
        cout << ans.v << nl;
    }
}
