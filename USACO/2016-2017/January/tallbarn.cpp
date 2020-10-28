/*
binary search on how much we remove. 
deal with some annoying precision stuff and write some hueristics to get full
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
using ld = long double;

template<class T> inline bool ckmin(T&a, T b) {return b < a ? a = b, 1 : 0;}
template<class T> inline bool ckmax(T&a, T b) {return b > a ? a = b, 1 : 0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const char nl = '\n';
const int mxN = 1e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
#define int ll
int n, k;
int a[mxN];

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    ifstream cin("tallbarn.in");
    ofstream cout("tallbarn.out");
    cin >> n >> k;
    F0R(i, n){
        cin >> a[i];
    }
    k-=n;
    ld lo = 0, hi = 2e9;
    F0R(i, 200){
        ld mid = (lo + hi)/2;
        ll tot = 0;
        F0R(j, n){
            tot += ll((sqrt(1+4*a[j]/mid)-1)/2);
        }
        if(tot >= k)
            lo = mid;
        else 
            hi = mid;
    }
    ld ans = 0;
    ll tot = 0;
    F0R(i, n){
        ll x = ll((sqrt(1+4*a[i]/lo)-1)/2);
        ans += 1.0*a[i]/(x+1);
        tot += x;
    }
    cout << (ll)round(ans-(k-tot)*lo) << nl;
    return 0;
}
