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

ll n;
unordered_set<ll> ans;
vl factors;
map<ll, unordered_set<ll>> mp;
vl print;


int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    // the goal is to construct all the ways we can factor something 
    // say we have like 12 -> 1,1,1,1,1,1,1,1
    for(ll i = 1; i * i <= n; i++){
        if((n%i)==0){
            factors.pb(i);
            if(i != n / i)
                factors.pb(n/i);
        }
    }
    sort(all(factors));
    // we would have 4 there because 3 * 2 * 2 
    // so basically wee need to find all ways to factor something 
    // where the idea is that we check for like all of a certain type 
    //
    // we can choose like most 30 things lol
    // where is the technique
    // vector<int> for like a group and transition 

    mp[1].insert(0);
    
    while(!mp.empty()){
        ll cur = mp.begin()->f;
        unordered_set<ll> al = mp.begin()->s;
        if(cur == n){
            ans = al;
            break;
        }
        mp.erase(mp.begin());
        trav(fact, factors){
            if(fact == 1) continue;
            if(n%(cur * fact) == 0){
                trav(val, al){
                    mp[cur*fact].insert(val+fact-1);
                    //mp.insert(val, fact-1+)
                }
            }
        }
    }
    trav(x, ans){
        print.pb(x);
    }
    sort(all(print));
    cout << siz(print) << nl;
    trav(A, print) cout << A << ' ';
    cout << nl;
    return 0;
}
