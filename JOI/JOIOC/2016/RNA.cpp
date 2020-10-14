/*
Main Idea:

Find all the strings that satisfy the second condition with binary search, then put them on a segment tree of vectors and binary search for the ones that satisfy the first 
condition. Pretty sure you need recursive segtree to pass memory limit. 


*/

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
using vpii = vector<pair<int, int>>;

template<class T> inline bool ckmin(T&a, T b) {return b < a ? a = b, 1 : 0;}
template<class T> inline bool ckmax(T&a, T b) {return b > a ? a = b, 1 : 0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const char nl = '\n';
const int mxN = 1e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
int LB, RB;
struct Tree {
	using T = int;
	using U = vector<int>;
	vector<U> vals; int n;
	Tree(int n = 0) : vals(2*n), n(n) {}
	int qry(int pos){
		return lower_bound(all(vals[pos]), RB) - lower_bound(all(vals[pos]), LB);
	}
	void update(int pos, T val) {
		for (pos+=n; pos ; pos/=2){
			vals[pos].pb(val);
		}
	}
	void normalize(){
		trav(x, vals){
			sort(all(x));
		}
	}
	T query(int b, int e) { // query [b, e)
		T ans = 0;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if( b % 2 ) ans += qry(b++);
			if( e % 2 ) ans += qry(--e);
		}
		return ans;
	}
};
int n, m; 
string s[mxN], p[mxN], q[mxN];
int lba[mxN], uba[mxN], lbb[mxN], ubb[mxN], pos[mxN];
vector<pair<string, int>> tot;
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
	Tree seg(n);
    F0R(i, n){
        cin >> s[i];
    }
    sort(s, s+n);
    F0R(i, m){
		cin >> p[i] >> q[i];
		reverse(all(q[i]));
		lba[i] = lower_bound(s, s+n, p[i])- s;
		p[i].back()++;
		uba[i] = lower_bound(s, s+n, p[i]) -s;
    }
	F0R(i, n){
		reverse(all(s[i]));
		tot.pb({s[i], i});
	}
	sort(all(tot));
	sort(s, s+n);
	F0R(i, m){
		lbb[i] = lower_bound(s, s+n, q[i])-s;
		q[i].back()++;
		ubb[i] = lower_bound(s, s+n, q[i])-s;
	}
	F0R(i, n){
		pos[tot[i].s] = i;
	}
	F0R(i, n){
		seg.update(i, pos[i]);
	}
	seg.normalize();
	F0R(i, m){
		LB = lbb[i], RB = ubb[i];
		cout << seg.query(lba[i], uba[i]) << nl;
	}
    return 0;
}
