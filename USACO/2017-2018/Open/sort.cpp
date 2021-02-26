/*
It will take i-j time to move an element into its proper position, but we can stop counting an element if its the right spot and the prefix before it all have spots less than i. 

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
const int mxN = 2e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

int n;
int a[mxN], pos[mxN];
vpii v;
set<int> vals;
ll ans = 0;

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifndef ACMX
    ifstream cin("sort.in"); ofstream cout("sort.out");
#endif
    cin >> n;
    if(n==1){
        cout << "0\n"; return 0;
    }
    F0R(i, n){
        cin >> a[i];
        v.pb({a[i], i});
    }
    sort(all(v));
    F0R(i, n) a[v[i].s]=i;
    F0R(i, n) pos[a[i]]=i;
    F0R(i, n){
        int time = max(pos[i]-i, 0);
        if(i){
            ckmax(time, *vals.rbegin()-(i-1));
        }
        if(!time) time++;
        vals.insert(pos[i]);
        ans+=time;
    }
    // we need to find the maximum position of the prefix and then th epoint of that node
    cout << ans << nl;
    return 0;
}
