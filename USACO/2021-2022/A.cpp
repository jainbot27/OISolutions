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
inline namespace FastIO {
	const int BSZ = 1 << 15;
	char ibuf[BSZ];
	int ipos;
	int ilen;
	
	// Gives the next character in the input stream.
	char nc() {
		if (ipos == ilen) {
			ipos = 0;
			ilen = fread(ibuf, 1, BSZ, stdin);
			if (!ilen) {
				return EOF;
			}
		}
		return ibuf[ipos++];
	}

	// Reads an int or a long long into x.
	template<class T> void ri(T& x) {
		char ch;
		int sgn = 1;
		while (!isdigit(ch = nc())) {
			if (ch == '-') {
				sgn *= -1;
			}
		}

		x = ch - '0';
		while (isdigit(ch = nc())) {
			x = x * 10 + (ch - '0');
		}
		x *= sgn;
	}
}

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

struct segTree {
    int n, sz; 
    vi mx; 
    vector<array<int, 4>> tickets; 
    void pull(int i) {
        mx[i] = max(mx[i * 2], mx[i * 2 + 1]); 
    }
    segTree(vector<array<int, 4>> tickets) : tickets(tickets) {
        n = 1; 
        sz = siz(tickets); 
        while (n < sz) 
            n *= 2; 
        mx.assign(2 * n, 0); 
        for (int i = n; i < 2 * n; i++) {
            if (i - n < sz) {
                mx[i] = tickets[i - n][3]; 
            } else {
                mx[i] = -1; 
            }
        } 
        for (int i = n - 1; i >= 0; i--) 
            pull(i); 
    }
    void remove(vi &ind, int p, int i = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1; 
        if (l >= sz || tickets[l][2] > p || mx[i] < p)
            return;
        else if (l == r) 
            mx[i] = -1, ind.pb(l); 
        else {
            int m = (l + r) / 2; 
            remove(ind, p, i * 2, l, m); 
            remove(ind, p, i * 2 + 1, m + 1, r); 
            pull(i); 
        }
        
    }
};

const int mxN = 1 << 17; 

set<int> nodes[mxN * 2]; 

void ins(int L, int R, int v, int i = 1, int lo = 0, int hi = mxN) {
    // dbg(L, R, v, i, lo, hi); 
    if (L <= lo && hi <= R) {
        nodes[i].insert(v); 
        return;
    } else if (L >= hi || lo >= R) {
        return; 
    }
    int mid = (lo + hi) / 2; 
    ins(L, R, v, i * 2, lo, mid); 
    ins(L, R, v, i * 2 + 1, mid, hi); 
}
void rem(int L, int R, int v, int i = 1, int lo = 0, int hi = mxN) {
    if (L <= lo && hi <= R) {
        nodes[i].erase(v); 
        return; 
    } else if (L >= hi || lo >= R) {
        return; 
    }
    int mid = (lo + hi) / 2; 
    rem(L, R, v, i * 2, lo, mid); 
    rem(L, R, v, i * 2 + 1, mid, hi); 
}

inline void merge(set<int> &A, set<int> B) {
    for (auto &x : B) {
        A.insert(x); 
    }
}
void get(set<int>& cur, int x, int i = 1, int lo = 0, int hi = mxN) {
    merge(cur, nodes[i]); 
    if (lo + 1 == hi) {
        return;
    }
    int mid = (lo + hi) / 2; 
    if (x < mid) {
        get(cur, x, i * 2, lo, mid); 
    } else {
        get(cur, x, i * 2 +1, mid, hi); 
    }
}

int n, k; 
vector<array<int, 4>> v; 
vector<ll> res1, res2; 
template<class T> using max_pq = priority_queue<T, vector<T>, greater<T>>; 

vector<ll> solve(vector<ll> a) {
    for (int i = n; i < n + k; i++) {
        auto [P, C, A, B] = v[i - n]; 
        ckmin(a[P], a[i] + C); 
    }
    // for (int i = 0; i < k; i++) {
    //     ins(v[i][2], v[i][3] + 1, i); 
    // }
    segTree seg(v); 
    // dbg("????"); 
    max_pq<pair<ll, int>> order; 
    vi vis(n + 1); 
    for (int i = 0; i < n; i++) {
        order.push({a[i], i}); 
    }
    while (siz(order)) {
        auto [x, y] = order.top(); 
        order.pop(); 
        if (x > a[y]) continue; 
        vector<int> ranges; 
        seg.remove(ranges, y); 
        // dbg(y, ranges); 
        for (auto r : ranges) {
            if (ckmin(a[r + n], a[y])) {
                auto &[P, C, A, B] = v[r]; 
                if (ckmin(a[P], a[y] + C)) {
                    order.push({a[P], P}); 
                }
            }
        }
    }
    // dbg("END"); 
    return a; 
}


int main() {
    ri(n); 
    ri(k); 
    for (int i = 0; i < k; i++) {
        int C, P, A, B;
        ri(C), ri(P), ri(A), ri(B); 
        C--, A--, B--; 
        v.pb({C, P, A, B}); 
    }
    sort(v.begin(), v.end(), [&](auto &A, auto &B) {
        return A[2] < B[2];
    }); 
    // dbg(v); 
    vector<ll> curdist(n + k, ll(1e18)); 
    curdist[0] = 0; 
    res1 = solve(curdist); 
    curdist = vector<ll>(n + k, ll(1e18)); 
    curdist[n - 1] = 0; 
    res2 = solve(curdist); 
    for (int i = 0; i < n + k; i++) {
        curdist[i] = res1[i] + res2[i]; 
    }
    auto res3 = solve(curdist); 
    for (int i = 0; i < n; i++) {
        if (res3[i] >= 1e18) 
            printf("-1\n");
        else 
            printf("%lld\n", res3[i]); 
    }
}
