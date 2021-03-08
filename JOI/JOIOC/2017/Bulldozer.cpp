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
using pll = pair<ll, ll>;
using vpii = vector<pair<int, int>>;
 
template<class T> inline bool ckmin(T&a, T b) {return b < a ? a = b, 1 : 0;}
template<class T> inline bool ckmax(T&a, T b) {return b > a ? a = b, 1 : 0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const char nl = '\n';
const int mxN = 2001;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
struct Frac{
    long long n, d;
    Frac(long long n, long long d){
        if(d == 0){
            this->d = 0;
            this->n = 1;
            return;
        } 
        this->n = n; this->d = d;
        long long g = __gcd(n, d); this->n/=g;  this->d/=g;
        if(this->d < 0){ this->n*=-1; this->d*=-1; };
    }
    Frac(long long n){
        this->n = n; d = 1;
    }
    Frac(){n = 0; d = 1;}
    
    Frac operator-(){return Frac(-n, d);}
    Frac operator+=(const Frac& other){return Frac(n*other.d + other.n*d, d*other.d);}
    Frac operator-=(const Frac& other){return Frac(n*other.d - other.n*d, d*other.d);}
    Frac operator*=(const Frac& other){return Frac(n*other.n, d*other.d);}
    Frac operator/=(const Frac& other){return Frac(n*other.d, d*other.n);}
 
    friend Frac operator+(Frac a, const Frac& b){ return a+=b; }
    friend Frac operator-(Frac a, const Frac& b){ return a-=b; }
    friend Frac operator*(Frac a, const Frac& b){ return a*=b; }
    friend Frac operator/(Frac a, const Frac& b){ return a/=b; }
 
    bool operator==(const Frac& other){ return n==other.n && d==other.d; }
    bool operator<(const Frac& other){ return n*other.d < other.n*d; }
    bool operator!=(const Frac& other){ return !((*this)==other);}
    
    friend string ts(const Frac& a){ return to_string(a.n) + "/" + to_string(a.d); }
    friend ostream& operator<<(ostream& out, Frac &a) { return out << ts(a); } 
};
 
    typedef ar<ll, 4> T;
    T unit = {0, 0, 0, 0};
struct Tree {
    //[maxpref, maxsuf, maxsum, sum]
    T f(T a, T b) { 
        T res;
        res[0] = max({a[0], a[3]+b[0], 0LL});
        res[1] = max({b[1], a[1]+b[3], 0LL});
        res[2] = max({a[2], b[2], a[1]+b[0], 0LL});
        res[3] = a[3]+b[3];
        //cout << "a: " << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << a[3] << nl;
        //cout << "b: " << b[0] << ' ' << b[1] << ' ' << b[2] << ' ' << b[3] << nl;
        //cout << "res: " << res[0] << ' ' << res[1] << ' ' << res[2] << ' ' << res[3] << nl;
        return res;
    } // (any associative fn)
    vector<T> s; int n;
    Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = f(val, unit); pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) { // query [b, e)
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};
 
int n;
pair<pll, ll> a[mxN];
vector<pair<Frac, pii>> v;
int pos[mxN];
ll ans = 0;
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    F0R(i, n)
        cin >> a[i].f.f >> a[i].f.s >> a[i].s;
    sort(a, a+n);
    F0R(i, n){
        F0R(j, i){
            if(i==j) continue;
            v.pb({Frac(a[i].f.s-a[j].f.s, a[i].f.f-a[j].f.f), {j, i}});
        }
    }
    sort(all(v), [](pair<Frac, pii> A, pair<Frac, pii> B){
        if(A.f==B.f) return A.s < B.s;
        return A.f < B.f;
 
    });
    F0R(i, n) pos[i] = i;
    Tree st(n);
    F0R(i, n){
        ll val = a[i].s;
        st.update(i, {val, val, val, val});
    }
    //cout << st.query(0, n)[2] << nl;
    //exit(0);
    ckmax(ans, st.query(0, n)[2]);
    F0R(i, siz(v)){
        swap(pos[v[i].s.f], pos[v[i].s.s]);
        ll val = a[v[i].s.f].s;
        st.update(pos[v[i].s.f], {val, val, val, val});
        val = a[v[i].s.s].s;
        st.update(pos[v[i].s.s], {val, val, val, val});
        if(i==siz(v)-1||v[i].f!=v[i+1].f){
            ckmax(ans, st.query(0, n)[2]);
        }
    }
    cout << ans << nl;
    return 0;
}
