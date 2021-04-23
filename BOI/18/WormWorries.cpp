/*
https://boi2018.progolymp.se/spoiler-day1.pdf

Complexity: O(n*m*k)
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
const int mxN=2e5+10;
const int MOD=1e9+7;
const ll infLL=1e18;
const ld eps=1e-6;
 
int n, m, k, q;
vector<vector<vi>> vis;
 
int query(int N, int M=0, int K=0){
    if(N<0||M<0||K<0||N>=n||M>=m||K>=k) return 0;
    if(vis[N][M][K]!=-1) return vis[N][M][K];
    cout << "? " <<  N+1 << ' ' << M+1 << ' ' << K+1 << endl;
    cin >> vis[N][M][K]; return vis[N][M][K];
}
 
int answer(int N, int M=0, int K=0){
    cout << "! " << N+1 << ' ' << M+1 << ' ' << K+1 << endl;
    exit(0); 
}
 
void solve1(){
    int l=0, r=n-1, m1=-1, m2=-1, lst=0;
    while(l<r){
        swap(m1, m2); 
        if(lst!=1)
            m1=ceil(0.62*l+0.38*r);
        if(lst!=2)
            m2=floor(0.38*l+0.62*r);
        if(m1>m2) swap(m1, m2); 
        if(m1==m2) {
            if(m1>l) m1--; else m2++; 
        }
        assert(m1<m2);
        if(query(m1)>=query(m2))
            r=m2-1, lst=2; 
        else
            l=m1+1, lst=1;
    }
    answer(l);
}
 
void solve2(){
    int l1=0, r1=n-1, l2=0, r2=n-1, x=-1, y=-1;
    while(l1<r1||l2<r2){
        if(r1-l1>r2-l2){
            int m=(l1+r1)/2, a=m, b=l2; 
            FOR(i, l2, r2+1)
                if(query(m, i)>query(a, b))
                    a=m, b=i;
            if(query(a, b)<query(x, y)){
                if(x>a)
                    l1=m+1;
                else 
                    r1=m-1;
            } 
            else if(query(a+1, b)>query(a, b))
                l1=m+1, x=a, y=b;
            else if(query(a-1, b)>query(a, b))
                r1=m-1, x=a, y=b;
            else 
                answer(a, b);
        }
        else{
            int m=(l2+r2)/2, a=l1, b=m;
            FOR(i, l1, r1+1)
                if(query(i, m)>query(a, b))
                    a=i, b=m;
            if(query(a, b)<query(x, y)){
                if(y>b)
                    l2=m+1;
                else    
                    r2=m-1;
            }
            else if(query(a, b+1)>query(a, b))
                l2=m+1, x=a, y=b;
            else if(query(a, b-1)>query(a, b))
                r2=m-1, x=a, y=b;
            else 
                answer(a, b);
        }
    }
    answer(l1, l2);
}
 
void solve3(){
    int qq=0;
    int x=-1, y=-1, z=-1;
    while(qq++<50000){
        int a=rng()%n, b=rng()%m, c=rng()%k;
        if(query(a, b, c)>query(x, y, z)) 
            x=a, y=b, z=c;
    }
    int dx[]={0, 0, 0, 0, -1, 1};
    int dy[]={0, 0, -1, 1, 0, 0};
    int dz[]={-1, 1, 0, 0, 0, 0};
    while(true){
        int a, b, c; 
        bool good=1;
        F0R(d, 6){
            a=x+dx[d], b=y+dy[d], c=z+dz[d];
            if(query(a, b, c)>query(x, y, z)){
                good=0;
                break;
            }
        }
        if(good)
            answer(x, y, z);
        x=a, y=b, z=c;
    }
}
 
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> k >> q;
    vis=vector<vector<vi>>(n, vector<vi>(m, vi(k, -1))); 
    if(m==1&&k==1) solve1();
    else if(k==1) solve2();
    else solve3();
}
