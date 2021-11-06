#include <bits/stdc++.h>
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

#ifdef ACMX 
#define dbg(...) cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
#define dbg(...) 0
#endif

const int MOD = 1e9 + 7;

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

using mi = mint<MOD>;

vector<mi> invs, fac, ifac;
void genFac(int SZ) {
	invs.resize(SZ), fac.resize(SZ), ifac.resize(SZ);
	invs[1] = fac[0] = ifac[0] = 1;
	for (int i = 2; i < SZ; i++)
		invs[i] = int(MOD - (ll)MOD / i * invs[MOD % i].v % MOD);
	for (int i = 1; i < SZ; i++) {
		fac[i] = fac[i - 1] * i;
		ifac[i] = ifac[i - 1] * invs[i];
	}
}

mi choose(int n, int k) {
	if (k > n) return 0;
	return fac[n] * ifac[n - k] * ifac[k];
}


void solve() {
	int n, k; 
	cin >> n >> k; 
	string S; 
	cin >> S; 
	vi deg(n + 1); 
	vector<vi> grid(n + 1, vi(n + 1)), sp(n + 1, vi(n + 1, -1)); 
	vector<vector<vector<mi>>> dp(n + 1, vector<vector<mi>>(n + 1, vector<mi>(n + 1))); 
	vector<pii> nodes; 
	for (int i = 1; i <= n; i++) {
		if (S[i - 1] == 'S') {
			deg[i]++; 
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			char c; 
			cin >> c; 
			if (c == '1') {
				dbg(i, j); 
				grid[i][j] = 1; 
				deg[j]++; 
				if (i > j) {
					sp[i][j] = siz(nodes); 
					nodes.pb({i, j}); 
				}
			}
		}
	}
	while (siz(nodes) < 2) {
		nodes.pb({0, 0}); 
	}
	dp[0][nodes[0].s][nodes[1].s] = 1; 
	dbg(deg); 
	dbg(dp[0]); 
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k <= n; k++) {
				mi add = dp[i - 1][j][k] * (fac[deg[i] - (i == j) - (i == k)]); 
				auto proc = [&](int x, int y) {
					if (x <= i || nodes[0].f <= i) x = 0; 
					if (y <= i || nodes[1].f <= i) y = 0; 
					dp[i][x][y] += add; 
				}; 
				vi go; 
				if (i != j && i != k) {
					proc(j, k); 
					continue;
				}
				for (int nex = 1; nex <= n; nex++) {
					if (grid[i][nex] || (nex == i && S[i - 1] == 'R'))
						go.pb(nex); 
				}
				if (i == j && i == k) {
					for (auto A : go) {
						for (auto B : go) {
							if (A == B) continue; 
							if (sp[j][A] == 0 || sp[k][B] == 1) {
								continue;
							}
							if (sp[j][A] == 1 && sp[k][B] == 0) {
								continue; 
							}
							if (sp[j][A] == 1) {
								proc(B, 0); 
							} else if (sp[k][B] == 0) {
								proc(0, A); 
							} else {
								proc(A, B); 
							}
						}
					}
				} else if (i == j) {
					for (auto A : go) {
						if (sp[j][A] == 0) continue; 
						if (sp[j][A] == 1) proc(k, 0); 
						else proc(A, k); 
					}
				} else if (i == k) {
					for (auto B : go) {
						if (sp[k][B] == 1) continue; 
						if (sp[k][B] == 0) proc(0, j); 
						else proc(j, B); 
					}
				}
			}
		}
		dbg(dp[i]); 
	}
	cout << dp[n][0][0] << "\n"; 
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	genFac(101); 
	int t; 
	cin >> t; 
	while (t--) {
		solve(); 
	}
}
