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

const int MOD = 1e9 + 7;

struct mint {
    int v;
    explicit operator int() const { return v; }
    mint() { v = 0; }
    mint(ll _v) {
        v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
        if (v < 0) v += MOD;
    }
    mint &operator+=(const mint &m) {
        if ((v += m.v) >= MOD) v -= MOD;
        return *this;
    }
    mint &operator-=(const mint &m) {
        if ((v -= m.v) < 0) v += MOD;
        return *this;
    }
    mint &operator*=(const mint &m) {
        v = int((ll)v * m.v % MOD);
        return *this;
    }
    friend mint operator+(mint a, const mint &b) { return a += b; }
    friend mint operator-(mint a, const mint &b) { return a -= b; }
    friend mint operator*(mint a, const mint &b) { return a *= b; }
    mint operator-() const { return mint(-v); }
    friend string to_string(mint a) {
        return to_string(a.v); 
    }
};


vector<mint> invs, fac, ifac;
void factorials(int SZ) {
    invs.resize(SZ), fac.resize(SZ), ifac.resize(SZ);
    invs[1] = fac[0] = ifac[0] = 1;
    for (int i = 2; i < SZ; i++)
        invs[i] = int(MOD - (ll)MOD / i * invs[MOD % i].v % MOD);
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

void solve() {
    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (*max_element(a.begin(), a.end()) == 3) {
        cout << choose(n, count(a.begin(), a.end(), 2)).v << "\n"; 
        return; 
    }

    vector<mint> dp(1, 1); 
    bool force = 1; 
    int G, R; 

    for (int i = 0; i < n; ) {
        int A = a[i], ca = 0; 
        if (!force) {
            A = G, ca = R; 
        }
        for (int j = i; j < n; j++) {
            if (abs(a[j] - a[i]) > 1) 
                break; 
            if (a[i] == a[j]) 
                ca++; 
        }
        if (!force) {
            A = G, ca = R; 
        }
        int B = -1, cb = 0; 
        for (int j = i; j < n; j++) {
            if (abs(a[j] - A) == 1) {
                B = a[j]; 
                break;
            }
        }
        for (int j = i; j < n; j++) {
            if (abs(B - a[j]) > 1) 
                break;
            if (B == a[j]) 
                cb++; 
        }
        if (cb == 0) {
            i += ca;
            force = 1; 
            dp = vector<mint>(1, accumulate(dp.begin(), dp.end(), mint(0))); 
            continue; 
        }
        int mode = 2, foo = 0; 
        for (int j = i; j < n; j++) {
            if (a[j] != A && a[j] != B) {
                if (abs(a[j] - A) == 1) {
                    mode = 0; 
                    foo = a[j];
                    break; 
                }
                if (abs(a[j] - B) == 1) {
                    mode = 1; 
                    foo = a[j];
                    break; 
                }
            }
        }
        bool passA = 0, passB = 0; 
        for (int j = i; j < n; j++) {
            if (foo == a[j]) break;
            if (abs(A - a[j]) > 1) passA = 1; 
            if (abs(B - a[j]) > 1) passB = 1; 
            if (a[j] == A && !passA) continue;
            if (a[j] == B && !passB) continue; 
            if (abs(a[j] - foo) > 1) {
                mode = 2; 
                break;
            }
        }
        if (mode == 0) {
            vector<mint> ndp(ca + 1); 
            for (int x = 0; x < siz(dp); x++) {
                for (int y = 0; y <= ca - x; y++) {
                    int amtb = cb - 1; 
                    int amta = y; 
                    ndp[y + x] += dp[x] * choose(amtb + amta, amta); 
                }
            }
            swap(dp, ndp); 
            force = 0; 
            G = A; 
            R = ca; 
            bool okay = 0; 
            for (int j = i; j < n; j++) {
                if (a[j] != A && a[j] != B)  {
                    i = j; 
                    okay = 1; 
                    break;
                }
            }
            if (!okay) break;
        } else {
            vector<mint> ndp(cb + 1); 
            for (int x = 0; x < siz(dp); x++) {
                for (int y = 0; y <= cb; y++) {
                    int amta = ca - 1 - x;
                    int amtb = y; 
                    if (y == 0) {
                        ndp[y] += dp[x]; 
                        }
                    else {
                        ndp[y] += dp[x] * choose(amta + amtb, amta); 
                    }
                }
            }
            swap(dp, ndp); 
            if (mode == 1) {

                force = 0; 
                G = B; 
                R = cb; 
                bool okay = 0; 
                for (int j = i; j < n; j++) {
                    if (a[j] != A && a[j] != B)  {
                        i = j; 
                        okay = 1; 
                        break;
                    }
                }
                if (!okay) break;
            } else {
                dp = vector<mint>(1, accumulate(dp.begin(), dp.end(), mint(0))); 
                force = 1; 
                bool okay = 0; 
                for (int j = i; j < n; j++) {
                    if (a[j] != A && a[j] != B)  {
                        i = j; 
                        okay = 1; 
                        break;
                    }
                }
                if (!okay) break;
            }
        }
    }
    cout << accumulate(dp.begin(), dp.end(), mint(0)).v << "\n";
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    factorials(mxN); 
    int t; 
    cin >> t;
    while (t--) {
        solve(); 
    }
}
