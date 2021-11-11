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

void solve() {
	int n, m; 
	cin >> n >> m; 
	vector<vi> adj(2 * n); 
	vi dist(2 * n, 1 << 30); 
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

	if (dist[n] == (1 << 30)) {
		cout << n - 1 << "\n"; 
		return; 
	}

	vector<vi> groups(n); 
	vi seen(n, -2); 
	for (int i = 0; i < n; i++) {
		if (dist[i + n] < dist[i]) 
			swap(dist[i], dist[i + n]); 
		groups[(dist[i + n] + dist[i] - 1) / 2].pb((dist[i + n] - dist[i] - 1) / 2); 
		// the differences are important for the transition because we need them later 
	}

	int ans = 0; 

	for (int g = 0; g < n; g++) {
		auto v = groups[g]; 
		sort(v.begin(), v.end()); 
		vector<pii> proc; 
		for (auto &u : v) {
			if (!siz(proc) || proc.back().f != u) proc.pb({u, 0}); 
			proc.back().s++; 
		}
		dbg(g, proc); 
		reverse(proc.begin(), proc.end()); 
		int rep = 0, lst = n; 
		for (auto [diff, cnt] : proc) {
			ans += rep;
			if (lst > diff + 1) {
				rep = 0; 
			}	
			rep = max(0, cnt - rep); 
			ans += rep; 
			if (seen[diff] == g - 1) {
				rep = cnt - rep; 
			} else {
				rep = cnt; 
			}
			seen[diff] = g; 
			lst = diff; 
		}
		if (lst > 0) {
			ans += rep; 
		} else {
			ans += (rep + 1) / 2; 
		}
	}
	cout << ans - 1 << "\n"; 
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int t; 
	cin >> t; 
	while (t--) {
		solve(); 
	}
}
