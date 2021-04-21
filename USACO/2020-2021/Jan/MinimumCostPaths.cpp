/*
Notice how the first column will just be dist[1][x]=c[1]*(x-1). Similarly, notice for the second column, if we were to never to use values from the second column, we 
would have dist[2][x]=c[1]*(x-1)+x*x. However, there would be some point where dist[2][x-1]+c[2]<dist[2][x] if we only calculated points using the last function, so clearly, 
if we find that point we will be good. Notice how this works in general, as we are always adding quadratics monotonically. The only question is how to maintain these functions. 
Notice all the functions are quadratics, and we just need which quadratic is optimal on what range. Thus, we can do the convex hull, except with quadratics. We initally add 
a line, as a new item will have to pay x^2 0 times. So we can just find the point in the function where the derivative is more than the new line we are going to add. Notice
the points will be concave, and so we can just use a vector to process all the nodes. To find the answer for a certain query, we will just process the queries offline, and 
binary search under which quadratic we fall under for a certain X. 

Time Complexity:O(m+qlogm) 
*/
#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define ar array
#define all(x) x.begin(), x.end()
#define siz(x) (int) x.size()

#define FOR(i, a, b) for(int i=(a); i<(b); i++)
#define ROF(i, a, b) for(int i=(b-1); i>=(a); i--)
#define F0R(i, n) FOR(i, 0, n)
#define R0F(i, n) ROF(i, 0, n)
#define trav(x, y) for(auto&x:y)

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpii = vector<pii>;

template<class T> inline bool ckmin(T& a, const T& b) {return b<a?a=b,1:0;}
template<class T> inline bool ckmax(T& a, const T& b) {return b>a?a=b,1:0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const char nl = '\n';
const int mxM = 2e5+10;
const int MOD = 1e9+7;
const ll infLL = 1e18;
const ld eps = 1e-6;

int n, m, q;
int c[mxM];
vpii Q[mxM];
ll ans[mxM];

int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    F0R(i, m) cin >> c[i];
    cin >> q;
    F0R(i, q){
        int X, Y; cin >> X >> Y; 
        X--; Y--;
        Q[Y].pb({X, i});
    }
    vector<ar<ll, 4>> pts;
    F0R(i, m){
        auto calc=[&](ar<ll, 4> p, ll pt){
            return (i-p[0])*(pt+1)*(pt+1)+p[1]*(pt+1)+p[2];
        };
        auto ff=[&](ar<ll, 4> p, ll pt){
            ll a=i-p[0], b=p[1];
            ll val=(pt-b)/(2*a);
            if(calc(p, val-1)+pt>calc(p, val)) return val+1;
            else return val;
        };
        while(siz(pts)&&ff(pts.back(), c[i])<=pts.back()[3]) pts.pop_back();
        if(!siz(pts)) pts.pb({i, c[i], i-c[i], 0});
        else if(ff(pts.back(), c[i])<n){
            ll X=ff(pts.back(), c[i]);
            ll Y=calc(pts.back(), X-1);
            pts.pb({i, c[i], Y-c[i]*X, X});
        }
        trav(v, Q[i]){
            int lo=0, hi=siz(pts)-1;
            while(lo<hi){
                int m=(lo+hi+1)/2;
                if(v.f>=pts[m][3]) lo=m;
                else hi=m-1;
            }
            ans[v.s]=calc(pts[hi], v.f);
        }
    }
    F0R(i, q) cout << ans[i] << nl;
    return 0;
}
