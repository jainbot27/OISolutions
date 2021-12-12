#include <cassert>
#include <stack>
#include <bitset>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>
#include <deque>
using namespace std;

#define f first
#define s second
#define pb push_back
#define siz(x) (int)x.size()

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

bool ckmin(auto &a, const auto &b) { return b < a ? a = b, 1 : 0; }
bool ckmax(auto &a, const auto &b) { return b > a ? a = b, 1 : 0; }

string to_string(char c) { return string(1, c); }
string to_string(bool b) { return b ? "true" : "false"; }
string to_string(const char *s) { return (string)s; }
string to_string(string s) { return s; }
string to_string(vector<bool> v) {
    string res = "{";
    for (int i = 0; i < (int)v.size(); i++)
        res += char('0' + v[i]);
    res += "}";
    return res;
}
template <size_t SZ> string to_string(bitset<SZ> b) {
    string res = "";
    for (int i = 0; i < b.size(); i++)
        res += char('0' + b[i]);
    return res;
}
template <class A, class B> string to_string(pair<A, B> p);
template <class T> string to_string(T v) {
    bool fst = 1;
    string res = "{";
    for (const auto &x : v) {
        if (!fst) res += ", ";
        fst = 0, res += to_string(x);
    }
    res += "}";
    return res;
}
template <class A, class B> string to_string(pair<A, B> p) { 
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; 
}
void DBG() { cerr << "]" << endl; }
template <class H, class... T> void DBG(H h, T... t) {
    cerr << to_string(h);
    if (sizeof...(t)) cerr << ", ";
    DBG(t...);
}

#ifdef ATHARV 
#define dbg(...) cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
#define dbg(...) 0
#endif


const int mod = 1e9 + 7;

template <int mod> struct mint {
    int v;
    explicit operator int() const { return v; }
    mint() { v = 0; }
    mint(ll _v) {
        v = int((-mod < _v && _v < mod) ? _v : _v % mod);
        if (v < 0) v += mod;
    }
    mint &operator+=(const mint &m) {
        if ((v += m.v) >= mod) v -= mod;
        return *this;
    }
    mint &operator-=(const mint &m) {
        if ((v -= m.v) < 0) v += mod;
        return *this;
    }
    mint &operator*=(const mint &m) {
        v = int((ll)v * m.v % mod);
        return *this;
    }
    friend mint pow(mint a, ll p) {
        mint ans = 1;
        assert(p >= 0);
        for (; p; p /= 2, a *= a)
            if (p & 1) ans *= a;
        return ans;
    }
    friend istream &operator>>(istream &is, mint &a) {
        long long x;
        is >> x, a = mint(x);
        return is;
    }
    friend ostream &operator<<(ostream &os, mint a) {
        os << a.v;
        return os;
    }
    friend mint inv(const mint &a) { return pow(a, mod - 2); }
    friend mint operator+(mint a, const mint &b) { return a += b; }
    friend mint operator-(mint a, const mint &b) { return a -= b; }
    friend mint operator*(mint a, const mint &b) { return a *= b; }
    friend mint operator/(mint a, const mint &b) { return a /= b; }
    friend bool operator==(const mint &a, const mint &b) { return a.v == b.v; }
    friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
    friend bool operator<(const mint &a, const mint &b) { return a.v < b.v; }
    friend string to_string(mint a) { return to_string(a.v); }
    mint &operator/=(const mint &m) { return (*this) *= inv(m); }
    mint operator-() const { return mint(-v); }
};

using mi = mint<mod>;

vector<mi> invs, fac, ifac;
void genfac(int sz) {
    invs.resize(sz), fac.resize(sz), ifac.resize(sz);
    invs[1] = fac[0] = ifac[0] = 1;
    for (int i = 2; i < sz; i++)
        invs[i] = int(mod - (ll)mod / i * invs[mod % i].v % mod);
    for (int i = 1; i < sz; i++) {
        fac[i] = fac[i - 1] * i;
        ifac[i] = ifac[i - 1] * invs[i];
    }
}

mi choose(int n, int k) {
    if (k > n) return 0;
    return fac[n] * ifac[n - k] * ifac[k];
}

const int mxN = 1 << 17; 
const int mxK = 11; 
array<mi, mxK> seg[mxN * 2]; 
mi lz[mxN * 2];
array<mi, 11> identity; 

void push(int i, int lo, int hi); 

array<mi, mxK> conv(array<mi, mxK> a) {
    // transition from a^k to a^(k + 1) 
    array<mi, mxK> res = identity; 
    for (int i = 0; i < mxK; i++) {
        for (int j = 0; j <= i; j++) {
            res[i] += a[j] * choose(i, j); 
        }
    }
    return res; 
}
array<mi, mxK> add(array<mi, mxK> a, array<mi, mxK> b) {
    for (int i = 0; i < mxK; i++) {
        a[i] += b[i]; 
    }
    return a; 
}

array<mi, mxK> sum(int L, int R, int i = 1, int lo = 0, int hi = mxN) {
    if (lo >= R || L >= hi) {
        return identity; 
    }
    if (L <= lo && hi <= R) {
        return seg[i]; 
    }
    push(i, lo, hi); 
    int mid = (lo + hi) / 2; 
    return add(sum(L, R, i * 2, lo, mid), sum(L, R, i * 2 + 1, mid, hi)); 
}

void multi(int L, int R, mi v, int i = 1, int lo = 0, int hi = mxN) {
    if (lo >= R || L >= hi) {
        return; 
    }
    if (L <= lo && hi <= R) {
        lz[i] *= v; 
        for (int j = 0; j < mxK; j++) {
            seg[i][j] *= v; 
        }
        return; 
    }
    push(i, lo, hi); 
    int mid = (lo + hi) / 2; 
    multi(L, R, v, i * 2, lo, mid); 
    multi(L, R, v, i * 2 + 1, mid, hi); 
    seg[i] = add(seg[i * 2], seg[i * 2 + 1]); 
}

void update(int L, int R, array<mi, mxK> v, int i = 1, int lo = 0, int hi = mxN) {
    if (lo >= R || L >= hi) {
        return; 
    }
    if (L <= lo && hi <= R) {
        seg[i] = add(seg[i], v); 
        return;
    }
    push(i, lo, hi); 
    int mid = (lo + hi) / 2; 
    update(L, R, v, i * 2, lo, mid); 
    update(L, R, v, i * 2 + 1, mid, hi); 
    seg[i] = add(seg[i * 2], seg[i * 2 + 1]); 
}

void push(int i, int lo, int hi) {
    int mid = (lo + hi ) / 2; 
    if (lz[i] != mi(1)) {
        multi(lo, mid, lz[i], i * 2, lo, mid); 
        multi(mid, hi, lz[i], i * 2 + 1, mid, hi); 
    }
    lz[i] = mi(1); 
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    freopen("help.in", "r", stdin); 
    freopen("help.out", "w", stdout); 
    genfac(mxN); 
    int N, K; 
    cin >> N >> K; 
    vi rights; 
    vector<pii> segs; 
    rights.pb(0); 
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y; 
        segs.pb({x, y}); 
        rights.pb(y); 
    }
    sort(segs.begin(), segs.end()); 
    sort(rights.begin(), rights.end()); 
    identity.fill(mi()); 

    auto proc = [&](int x, int y) {
        // finding where the shit at  
        auto L = lower_bound(rights.begin(), rights.end(), x) - rights.begin(); 
        auto R = upper_bound(rights.begin(), rights.end(), y) - rights.begin(); 
        dbg(x, y); 
        dbg(sum(0, L), sum(L, R)); 
        auto A = sum(0, L); 
        auto B = sum(L, R); 
        auto C = conv(sum(0, L));  
        dbg(A, B, C); 
        update(R - 1, R, add(C, B)); 
        multi(R, mxN, 2); 
    };
    dbg(rights, segs); 
    {
        auto st = identity; 
        st[0] = 1; 
        update(0, 1, st); 
    }
    for (auto [x, y] : segs) {
        for (int i = 0; i < 4; i++) {
            dbg(sum(i, i + 1));
        }
        dbg("----"); 
        proc(x, y); 
    }
    auto answer = sum(0, mxN); 
    dbg(answer); 

    cout << answer[K] << "\n"; 
}
