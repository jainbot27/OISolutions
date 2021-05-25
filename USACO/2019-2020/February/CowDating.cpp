/*
  I love Ethan Y. Guo. 
  
  Complexity: O(n)
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

const int mxN=1e6+10;
const int MOD=1e9+7; 
const ll infLL=1e18;
const ld eps=1e-6;

int n; 
ld a[mxN];

int main(){
    cin.tie(0)->sync_with_stdio(0);
    freopen("cowdate.in", "r", stdin);
    freopen("cowdate.out", "w", stdout);
    cin >> n;
    F0R(i, n) cin >> a[i], a[i]/=1000000.0;
    ld prod=1, sum=0; int r=0; ld ans=0;
    F0R(i, n){
        while(r<n){
            ld prod2=prod*(1.0-a[r]); ld sum2=sum+a[r]/(1.0-a[r]);
            if(prod2*sum2>prod*sum){ 
                r++;
                prod=prod2, sum=sum2;
            }
            else
                break;
        }
        ckmax(ans, prod*sum);
        prod/=(1.0-a[i]);
        sum-=a[i]/(1.0-a[i]);
    }
    ans*=1000000;
    cout << floor(ans) << "\n";
    return 0; 
}

