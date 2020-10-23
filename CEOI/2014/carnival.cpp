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
const int mxN = 2e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

int query(int l, int r){
    cout << r - l + 1 << ' ';
    FOR(i, l, r+1) cout << i << ' ';
    cout << endl;
    int res; cin >> res;
    return res;
}
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n; 
    vi c(n+1);
    int k = 1;
    c[1] = 1;
    FOR(i, 2, n+1){
        if(query(1, i) == query(1, i-1) + 1){
            c[i] = ++k;
        }
        else{
            int l = 1, r = i-1;
            while(l < r) {
                int m = (l + r + 1)/2;
                if(query(m, i) == query(m, i - 1) + 1) r = m - 1;
                else l = m;
            }
            c[i] = c[l];
        }
    }
    cout << "0 ";
    FOR(i, 1, n+1){
        cout << c[i] << ' ';
    }
    cout << endl;
    return 0;
}
