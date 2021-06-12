/*
  Alien's Trick 
  
  Complexity: O(log(m*m)n) 
*/

#include <bits/stdc++.h>
#include "aliens.h"
using namespace std;
 
#define f first
#define s second
#define pb push_back
#define ar array
#define all(x) x.begin(), x.end()
#define siz(x) (int) x.size()
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
#define FOR(i, a, b) for(auto i=(a); i<(b); i++)
#define ROF(i, a, b) for(auto i=(b)-1; i>=(a); i--)
#define F0R(i, n) FOR(i, 0, n)
#define R0F(i, n) ROF(i, 0, n)
 
using ll=long long;
using ld=long double;
using pii=pair<int, int>;
using pll=pair<ll, ll>;
using vi=vector<int>;
using vl=vector<ll>;
using vpii=vector<pii>;
 
template<class T> bool ckmin(T&a, const T&b) {return b<a?a=b,1:0;}
template<class T> bool ckmax(T&a, const T&b) {return b>a?a=b,1:0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const int mxN=1e5+10;
const int MOD=1e9+7; 
const ll infLL=1e18;
const ld eps=1e-6;
 
ll n, m, k; 
vi r, c; 
vector<pair<ll, ll>> pts, pts2;
 
struct line{
	ll M, B; int idx;
	ll operator()(ll q)const{
		assert(idx!=-1);
		return M*q+B;
	}
	line(){M=-1, B=-1, idx=-1;}
	line(ll m, ll b, int IDX):M(m), B(b), idx(IDX){}
};
 
int L, R;
 
// we can do convex hull in linear cause we only have x is decreasing order
 
line A[mxN];
 
ll ccw(line& o, line& p, line& q) {
	return (o.M-p.M)*(o.B-q.B)-(o.B-p.B)*(o.M-q.M);
}
 
void add(line V){
	while(R-L>1&&ccw(A[R-2], A[R-1], V)>=0) R--; 
	A[R]=V; R++;
}
 
pair<ll, ll> qry(ll X){
	while(R-L>1&&A[L](X)>A[L+1](X)) L++; 
	assert(L!=R);
	return {A[L](X), A[L].idx};
}
 
pair<ll, ll> solve(ll x){
	pair<ll, ll> dp={0, 0};
	L=0, R=0; 
	F0R(i, siz(pts)){
		ll A=max(i?pts[i-1].f-pts[i].s+1:0LL, 0LL), B=pts[i].s; 
		add(line(-2*B, dp.f-A*A+B*B, dp.s));;
		A=pts[i].f+1; 
		dp=qry(A);
		dp.s++; dp.f+=A*A+x; 
	}
	return dp;
}
 
ll take_photos(int N, int M, int K, vi R, vi C){
	n=N, m=M, k=K, r=R, c=C; 
	pts2.clear(); pts.clear();
	F0R(i, n){
		pts.pb({r[i], c[i]});
		if(pts[i].s>pts[i].f) swap(pts[i].s, pts[i].f);
	}
	sort(all(pts));
	// F0R(i, n){
	// 	cout << "PTS: " << pts[i].f << ' ' << pts[i].s << "\n";
	// }
	F0R(i, n){
		while(!pts2.empty()&&pts[i].s<=pts2.back().s)
			pts2.pop_back(); 
		pts2.pb(pts[i]);
	}
	// for(auto v:pts2) cout << v.f << ' ' << v.s << "\n";
	pts=pts2; 
	ll lo=0, hi=(ll)m*m; ll ans=0;
	ckmin(k, (ll)siz(pts));
	while(lo<=hi){
		ll m=(lo+hi)/2; 
		auto cur=solve(m);
		if(cur.s<=k) 
			ans=cur.f, hi=m-1;
		else 
			lo=m+1;
	}
	return ans-lo*k;
}
 
/*
 
	XXXXXXX
	OXXXXXX
	XXXXXXX
	XXOXXXX
	XXXXXXX
	XXXOXXX
	XXXXXXX
*/
