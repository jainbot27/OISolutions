/*
Notice that we should pair all pairs that are together from the beginning always. After this, if someone has no one that loves them (sad), we can always show its optimal to pair
them with the person they love. After this, we basically can do a psuedo-topological sort on the graph until we have just cycles. The cycles just have the cost of 
ceil(sz[cycle]/2) to pair up. The only thing is to find the cycle size quickly, you can use dfs or dsu, I chose dsu. 

Complexity: O(nlog*(n)) 
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

template<class T> inline bool ckmin(T&a, const T&b) {return b<a?a=b,1:0;}
template<class T> inline bool ckmax(T&a, const T&b) {return b>a?a=b,1:0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const char nl='\n';
const int mxN=1e5+10;
const int MOD=1e9+7;
const ll infLL=1e18;
const ld eps=1e-6;

int n; 
string s[mxN], t[mxN];
unordered_map<string, int> mp;
int a[mxN];
int deg[mxN];
int par[mxN], sz[mxN];
bool alive[mxN];
int used[mxN];
queue<int> q;
int ans=0;

int Find(int u){
    return par[u]=(par[u]==u?par[u]:Find(par[u]));
}
bool comb(int e1, int e2){
    e1=Find(e1); e2=Find(e2); 
    if(e1==e2) return 0;
    if(sz[e1]<sz[e2]) swap(e1, e2);
    sz[e1]+=sz[e2]; sz[e2]=0;
    par[e2]=e1;
    return 1;
}

int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    if(n&1) {cout << "-1\n"; return 0;}
    F0R(i, n) par[i]=i, sz[i]=1;
    F0R(i, n)
        cin >> s[i] >> t[i], mp[s[i]]=i;
    F0R(i, n){
        a[i]=mp[t[i]];
        deg[a[i]]++;
        alive[i]=1;
    }    
    F0R(i, n){
        if(alive[i]&&a[i]!=i&&a[a[i]]==i){
            alive[a[i]]=0;
            alive[i]=0;
            deg[a[i]]--;
            deg[i]--;
        }
    }
    F0R(i, n)
        if(deg[i]==0){
            q.push(i);
        }       
    while(!q.empty()){
        auto T=q.front(); q.pop();
        if(alive[T]==0) continue;
        if(alive[a[T]]==0) continue;
        alive[T]=0;
        alive[a[T]]=0;
        ans++;
        if(alive[a[a[T]]]) {
            deg[a[a[T]]]--;
            if(deg[a[a[T]]]==0)
                q.push(a[a[T]]);
        }
    }
    F0R(i, n){
        if(alive[i]&&alive[a[i]]){
            comb(a[i], i);
        }
    }
    F0R(i, n){
        if(alive[i]&&!used[Find(i)]){
            used[Find(i)]=1;
            ans+=(sz[Find(i)]+1)/2;
        }
    }
    cout << ans << nl;
}

