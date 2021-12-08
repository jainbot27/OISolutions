#include <cassert>
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


template <class F> struct y_combinator_result {
    F f;
    template <class T> explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
    template <class... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), forward<Args>(args)...);
    }
};
template <class F> decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

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

const mi i2 = inv(mi(2)); 
const mi i6 = inv(mi(6)); 

mi c3(mi x) {
    return x * (x - 1) * (x - 2) * i6; 
}

mi c2(mi x) {
    return x * (x - 1) * i2; 
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K; 
    cin >> N >> K;
    K++; 
    int B = 0; 
    while ((1 << B) <= K) {
        B++; 
    }
    const int P = 1 << B; 
    K -= P / 2; 
    mi sing = c2(K) * P + 2 * c3(P / 2); 
    mi ans = 0; 
    map<int, vector<pii>> mp; 
    for (int i = 0; i < N; i++) {
        int L, R; 
        cin >> L >> R; 
        int LL = L / P, RR = R / P; 
        if (LL != RR) {
            ans += (RR - LL - 1) * sing; 
            mp[LL].pb({L % P, P - 1}); 
            mp[RR].pb({0, R % P}); 
        } else {
            mp[LL].pb({L % P, R % P}); 
        }
    }
    auto sum = [&](vector<pii> v) {
        mi tot = 0; 
        for (auto &[L, R] : v) {
            tot += R - L + 1; 
        }
        return tot; 
    };
    auto dp = y_combinator([&](auto dp, vector<pii> a, vector<pii> b, int sz, mi cur) {
        if (!siz(a))
            return; 
        if (!siz(b)) {
            ans += sum(a) * c2(cur); 
            return; 
        }
        if (siz(b) == 1 && b[0] == pii{0, sz - 1}) {
            // then we can take the whole range 
            // there will be match for every guy for each thing that is & 
            cur += (sz - 1) & K;
            ans += sum(a) * c2(cur); 
            return; 
        }
        // we have to then transition to the next state 
        auto add = [&](vector<pii> &dest, pii t) {
            // its basically like we are given all these various numbers, and their various modulos 
            // we can connect people of the same colors if its possible 
            // otherwise we have to solve to make sure that we dont break any rules with matching with the other type 
            ckmin(t.s, sz / 2 - 1);
            ckmax(t.f, 0); 
            if (t.f > t.s) return; 
            dest.pb(t); 
        };
        array<vector<pii>, 2> A, B; 
        for (auto it : a) {
            add(A[0], it);
            add(A[1], {it.f - sz / 2, it.s - sz / 2}); 
        }
        for (auto it : b) {
            add(B[0], it);
            add(B[1], {it.f - sz / 2, it.s - sz / 2}); 
        }
        for (int i = 0; i < 2; i++) {
            if (K & (sz / 2)) {
                mi nxt = cur + sum(B[i]); 
                dp(A[i], B[i ^ 1], sz / 2, nxt); 
            } else {
                dp(A[i], B[i], sz / 2, cur); 
            }
        }
    }); 

    auto solve = [&](vector<pii> proc) {
        dbg(proc); 
        array<vector<pii>, 2> nxt; 
        for (auto &[L, R] : proc) {
            int LL = L / (P / 2); 
            int RR = R / (P / 2); 
            if (LL == RR) {
                nxt[LL].pb({L % (P / 2), R % (P / 2)}); 
            } else {
                nxt[LL].pb({L % (P / 2), P / 2 - 1}); 
                nxt[RR].pb({0, R % (P / 2)}); 
            }
        }
        dbg(nxt); 
        for (int i = 0; i < 2; i++) {
            dp(nxt[i], nxt[i ^ 1], P / 2, mi()); 
            ans += c3(sum(nxt[i])); 
        }
    };
    for (auto &v : mp) {
        solve(v.s); 
        dbg(ans); 
    }
    cout << ans << "\n"; 
}
