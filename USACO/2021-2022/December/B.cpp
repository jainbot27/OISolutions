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

const int mxN = 5001; 


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; 
    cin >> T;
    if (T == 1) {
        int n, k; 
        cin >> n >> k; 
        vector<pii> G, H; 
        ll tot = 0; 
        for (int i = 0; i < n; i++) {
            char c; 
            cin >> c; 
            int X, Y; 
            cin >> X >> Y; 
            tot += Y; 
            if (c == 'G') {
                G.pb({X, Y}); 
            } else {
                H.pb({X, Y}); 
            }
        }
        vector<vector<ll>> dp(siz(G) + 1, vector<ll>(siz(H) + 1)); 
        for (int i = 0; i <= siz(G); i++) {
            for (int j = 0; j <= siz(H); j++) {
                if (i < siz(G) && j < siz(H) && abs(G[i].f - H[j].f) <= k) {
                    ckmax(dp[i + 1][j + 1], dp[i][j] + G[i].s + H[j].s); 
                }
                if (i < siz(G))
                    ckmax(dp[i + 1][j], dp[i][j]); 
                if (j < siz(H)) 
                    ckmax(dp[i][j + 1], dp[i][j]); 
            }
        }
        cout << tot - dp[siz(G)][siz(H)] << "\n"; 
    } else {
        int n, k; 
        cin >> n >> k; 
        vector<pii> g, h; 
        for (int i = 0; i < n; i++) {
            char c; 
            int x, y;
            cin >> c >> x >> y; 
            if (c == 'G') g.pb({x, y});
            else h.pb({x, y}); 
        }
        int G = siz(g), H = siz(h); 
        vector<vector<vector<ll>>> dp(G + 1, vector<vector<ll>>(H + 1, vector<ll>(2, -(1LL << 60)))); 
        vector<vector<int>> trans(G + 1, vector<int>(H + 1)); 
        vector<int> lasth(G + 1), lastg(H + 1); 
        for (int i = G; i >= 0; i--) {
            for (int j = H; j >= 0; j--) {
                if (i < G && j < H && abs(g[i].f - h[j].f) <= k) {
                    trans[i][j] = trans[i + 1][j + 1]; 
                } else {
                    trans[i][j] = i; 
                }
            }
        }
        for (int i = 0; i < G; i++) {
            while (lasth[i + 1] < H && h[lasth[i + 1]].f <= g[i].f + k)
                lasth[i + 1]++; 
            lasth[i + 1]--; 
        }
        for (int i = 0; i < H; i++) {
            while (lastg[i + 1] < G && g[lastg[i + 1]].f <= h[i].f + k) 
                lastg[i + 1]++; 
            lastg[i + 1]--; 
        }
        dp[0][0][0] = dp[0][0][1] = 0; 
        dbg(lasth, lastg); 
        for (int i = 0; i <= G; i++) {
            for (int j = 0; j <= H; j++) {
                // (1, 0, 0) -> (2, 1, 1) 
                {
                    int nextY = max(j, lasth[i] + 1); 
                    int minTrans = trans[i][j] - i + j; 
                    if (minTrans >= nextY) {
                        ckmax(dp[nextY - j + i][nextY][1], dp[i][j][0]); 
                    }
                }
                {
                    int nextX = max(i, lastg[j] + 1); 
                    int minTrans = trans[i][j]; 
                    if (minTrans >= nextX) {
                        ckmax(dp[nextX][nextX - i + j][0], dp[i][j][1]); 
                    }
                }
                if (trans[i][j] > i) {
                    for (int k = 0; k < 2; k++)
                        ckmax(dp[i + 1][j + 1][k], dp[i][j][k]); 
                }
                if (i < G) {
                    ckmax(dp[i + 1][j][0], dp[i][j][0] + g[i].s); 
                } 
                if (j < H) {
                    ckmax(dp[i][j + 1][1], dp[i][j][1] + h[j].s); 
                }
                dbg(i, j, dp[i][j], trans[i][j]); 
            }
        }
        
        cout << max(dp[G][H][0], dp[G][H][1]) << "\n"; 
    }
}
