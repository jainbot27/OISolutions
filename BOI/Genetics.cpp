/*
  Just hash or use rng. 
  
  Complexity: O(mn)
*/
#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define ar array
#define all(x) x.begin(), x.end()
#define siz(x) (int) x.size()
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

#define FOR(i, a, b) for(int i=(a); i<(b); i++)
#define ROF(i, a, b) for(int i=(b-1); i>=(a); i--)
#define F0R(i, n) FOR(i, 0, n)
#define R0F(i, n) ROF(i, 0, n)
#define trav(x, y) for(auto&x:y)

using ll=long long;
using ld=long double;
using pii=pair<int, int>;
using pll=pair<ll, ll>;
using pli=pair<ll, int>;
using vi=vector<int>;
using vl=vector<ll>;
using vpii=vector<pii>;
using us=unsigned int;

template<class T> inline bool ckmin(T&a, const T&b) {return b<a?a=b,1:0;}
template<class T> inline bool ckmax(T&a, const T&b) {return b>a?a=b,1:0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const char nl='\n';
const int mxN=4101;
const int MOD=1e9+7;
const ll infLL=1e18;
const ld eps=1e-6;

int n, m, k;
string s[mxN];
int rnd[mxN];
ll cnt[mxN][4];
ll tot=0;

int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    auto cti=[&](char x){
        if(x=='A') return 0;
        if(x=='C') return 1;
        if(x=='G') return 2;
        return 3;   
    };
    cin >> n >> m >> k;
    F0R(i, n){
        rnd[i]=uid(1, INT_MAX);
        cin >> s[i];
        tot+=rnd[i];
        F0R(j, m) cnt[j][cti(s[i][j])]+=rnd[i];
    }
    F0R(i, n){
        ll hsh=0; 
        F0R(j, m) F0R(l, 4){
            if(l!=cti(s[i][j]))
                hsh+=cnt[j][l];
        }
        if(hsh==k*(tot-rnd[i])){
            cout << i+1 << nl; return 0;
        }
    }
    assert(false);
}
