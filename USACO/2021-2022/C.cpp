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
#include <bitset>
#include <cassert>
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

struct mint {
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
    friend mint operator+(mint a, const mint &b) { return a += b; }
    friend mint operator-(mint a, const mint &b) { return a -= b; }
    friend mint operator*(mint a, const mint &b) { return a *= b; }
};


vector<mint> invs, fac, ifac;
void genFac(int SZ) {
    invs.resize(SZ), fac.resize(SZ), ifac.resize(SZ);
    invs[1] = fac[0] = ifac[0] = 1;
    for (int i = 2; i < SZ; i++)
        invs[i] = int(mod - (ll)mod / i * invs[mod % i].v % mod);
    for (int i = 1; i < SZ; i++) {
        fac[i] = fac[i - 1] * i;
        ifac[i] = ifac[i - 1] * invs[i];
    }
}

mint choose(int n, int k) {
    if (k > n) return 0;
    return fac[n] * ifac[n - k] * ifac[k];
}

const int mxN = 5001; 
int n, x;
mint dp[mxN][mxN][2]; // ev if value is 
mint sumi[mxN], sumj[mxN];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    genFac(mxN); 
    cin >> n >> x; 
    int y = n - x; 
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            dp[i][j][0] += invs[i + j] * (sumi[i] + sumj[j]); 
            dp[i][j][1] += invs[i + j] * (sumi[i] + sumj[j] + i); 
            sumi[i] += dp[i][j][1]; 
            sumj[j] += dp[i][j][0]; 
        }
    }
    mint ans = dp[x][y][0]; 
    for (int i = 1; i <= n; i++) 
        ans *= i; 
    cout << ans.v << "\n"; 
}

