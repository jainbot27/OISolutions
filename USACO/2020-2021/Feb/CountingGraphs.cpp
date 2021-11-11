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
	int n, m; 
	cin >> n >> m; 
	vector<vi> adj(n * 2); 
	vi dist(n * 2, INT_MAX); 
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v; 
		u--, v--; 
		adj[u].pb(v + n); 
		adj[v + n].pb(u); 
		adj[v].pb(u + n); 
		adj[u + n].pb(v); 
	}
	dist[0] = 0; 
	queue<int> q; 
	q.push(0); 
	while (siz(q)) {
		int u = q.front(); 
		q.pop(); 
		for (auto &v : adj[u]) {
			if (ckmin(dist[v], dist[u] + 1)) {
				q.push(v); 
			}
		}
	}
	if (dist[n] == INT_MAX) { 
		// cout << "HELLO\n"; 
		mi res = 1; 
		vi cnt(n); 
		for (int i = 0; i < n; i++) 
			cnt[min(dist[i], dist[i + n])]++;
		for (int i = 1; i < n; i++) {
			res *= pow(pow(mi(2), cnt[i - 1]) - 1, cnt[i]); 
		}
		cout << res << "\n"; 
		return; 
	}
	vector<vi> count(4 * n, vi(4 * n)); 
	for (int i = 0; i < n; i++) {
		if (dist[i] > dist[i + n]) 
			swap(dist[i], dist[i + n]); 
		count[dist[i]][dist[i + n]]++; 
	}
	mi ans = 1; 
	for (int sum = 1; sum < 4 * n; sum += 2) {
		vector<mi> dp(count[0][sum] + 1); 
		dp.back() = 1; 
		for (int a = 1; a <= sum / 2; a++) {
			auto b = sum - a, num = count[a][b], pnum = count[a - 1][b + 1], lnum = count[a - 1][b - 1]; 
			vector<mi> dp_int(num + 1); // represents that there are i things that we still need to deal with 
			for (int x = 0; x <= num; x++) {
				for (int y = 0; y <= pnum; y++) {
					mi prod = 0; 
					for (int k = 0; k <= y; k++) {
						mi mp = choose(y, k) * pow(pow(mi(2), pnum - k) - 1, num - x); 
						// so we need to connect each of the y mfs with the other x mfs 
						// so its just PIE at the end of the day 
						if (k & 1) prod -= mp; 
						else prod += mp; 
					}
					dp_int[x] += dp[y] * prod; 
				}
				dp_int[x] *= choose(num, x); 
			}
			dp = vector<mi>(num + 1); 
			// we have to make a real dp transition now ?
			for (int x = 0; x <= num; x++) {
				mi prod = 0; 
				for (int y = 0; x + y <= num; y++) {
					prod += dp_int[y] * choose(num - y, x) * pow(pow(mi(2), lnum) - 1, num - x); 
				}	
				dp[x] += prod; 
			}
		}
		auto num = count[sum / 2][sum / 2 + 1]; 
		mi res = 0; 
		for (int x = 0; x <= num; x++) { // so we have like x edges that need to be connected 
			// we need to make sure each of them get at least 1 
			// so we connect each one to some set of the others
			// PIE 
			mi mp = 0; 
			for (int k = 0; k <= x; k++) {
				mp += (k % 2 == 0 ? 1 : -1) * choose(x, k) * pow(mi(2), 1LL * (num - k) * (num - k + 1) / 2); 
			}
			// dbg(mp); 
			res += mp * dp[x]; 
		}
		ans *= res; 
	}
	cout << ans << "\n"; 
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	genFac(10005); 
	int t; 
	cin >> t; 
	while (t--) {
		solve(); 
	}
}
