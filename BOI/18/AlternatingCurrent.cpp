/*
  If some current is inside another, we always can just set it to the opposite color. 
  Thus we remain with some amount of relevant segments that arent going to be inside others.
  Notice it is optimal to alternate their color, so for any even amount of them, thats all we have to do. 
  For an odd number, we will have to pair two segments of the same color together, but this is very easy to do by trying all of them.
  All of the checking will be supported by a lazy segment tree. 
  Complexity: O(nlogn+mlogm)
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
const int mxN=1<<17;
const int MOD=1e9+7;
const ll infLL=1e18;
const ld eps=1e-6;
int m, n, p[mxN];
vector<ar<int, 3>> v;
vpii v2;
int Find(int u){
    return p[u]=(u==p[u]?u:Find(p[u]));
}
void comb(int e1, int e2){
    e1=Find(e1); e2=Find(e2); 
    if(e1!=e2)
        p[e2]=e1;
}
struct segment{
    int val[2*mxN], mset[2*mxN];
    segment() {memset(mset, -1, sizeof mset);}
    void set(int L, int R, int v, int i=1, int lo=0, int hi=mxN){
        if(lo>=R||L>=hi) return;
        if(L<=lo&&hi<=R){
            mset[i]=v;
            val[i]=v*(hi-lo);
            return;
        }
        push(i, lo, hi);
        int m=(lo+hi)/2;
        set(L, R, v, i*2, lo, m);
        set(L, R, v, i*2+1, m, hi);
        val[i]=val[2*i]+val[2*i+1];
    }
    int query(int L, int R, int i=1, int lo=0, int hi=mxN){
        if(lo>=R||L>=hi) return 0;
        if(L<=lo&&hi<=R)
            return val[i];
        push(i, lo, hi);
        int m=(lo+hi)/2;    
        return query(L, R, i*2, lo, m)+query(L, R, i*2+1, m, hi);
    }
    void push(int i, int lo, int hi){
        int m=(lo+hi)/2;
        if(mset[i]!=-1){
            set(lo, m, mset[i], i*2, lo, m);
            set(m, hi, mset[i], i*2+1, m, hi);
            mset[i]=-1;
        }
    }
} st[2];
set<pii> vals;
vi r;
vector<vi> pts;
void se(int l, int r, int t){
    if(r>=m){
        st[t].set(0, r+1-m, 1);
        st[t].set(l, m, 1);
    }
    else
        st[t].set(l, r+1, 1);
}
int qq(int l, int r, int t){
    int res=0;
    if(r>=m){
        res+=st[t].query(0, r+1-m);
        res+=st[t].query(l, m);
    }
    else
        res+=st[t].query(l, r+1);
    return res;
}
void proc(int v, int t){
    se(v2[v].f, v2[v].s, t);
    for(auto q:pts[v])
        se(v2[q].f, v2[q].s, t^1);
}
int sz(int l, int r){
    if(r>=m)
        return r+1-m+(m-l);
    return r-l+1;
}
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> m >> n;
    pts.resize(n);
    F0R(i, n) p[i]=i; 
    F0R(i, n){
        int l, r; cin >> l >> r; 
        l--; r--; 
        if(r<l) v.pb({l, r+m, i});
        else v.pb({l, r, i}), v.pb({l+m, r+m, i});
        if(r>=l)
            v2.pb({l, r});
        else   
            v2.pb({l, r+m});
        se(v2[i].f, v2[i].s, 0);
    }
    if(st[0].query(0, m)!=m){
        cout << "impossible\n";
        return 0;
    }
    st[0].set(0, m, 0);
    sort(all(v), [&](ar<int, 3> A, ar<int, 3> B){
        if(A[0]==B[0]) return A[1]>B[1];
        return A[0]<B[0];
    });
    for(auto[x, y, i]:v){
        auto it=vals.lower_bound({y, -MOD});
        if(i==Find(i)&&it!=vals.end()){
            comb(it->s, i);
        }
        vals.insert({y, i});
    }
    F0R(i, n){
        if(Find(i)!=i)
            pts[Find(i)].pb(i);
        else
            r.pb(i);
    }
    sort(all(r), [&](int e1, int e2){
        return v2[e1]<v2[e2];
    });
    int R=siz(r);
    if(R==1){
        proc(r[0], 0);
        if(qq(0, m-1, 0)!=m||qq(0, m-1, 1)!=m){
            cout << "impossible\n";
        }
        else{
            F0R(i, n){
                if(i==r[0]) cout << 1;
                else cout << 0;
            }
            cout << nl;
        }
        return 0;
    }
    F0R(i, R){
        int lb=r[(i-1+R)%R], mb=r[i], rb=r[(i+1)%R];
        proc(lb, 0); proc(mb, 1); proc(rb, 0);
        if(qq(v2[mb].f, v2[mb].s, 0)!=sz(v2[mb].f, v2[mb].s)){
            cout << "impossible\n";
            return 0;
        }
        st[0].set(0, m, 0);
        st[1].set(0, m, 0);
    }
    if(R&1){
        F0R(i, R){
            int lb=r[(i-1+R)%R], mb1=r[i], mb2=r[(i+1)%R], rb=r[(i+2)%R];
            proc(lb, 0); proc(mb1, 1); proc(mb2, 1); proc(rb, 0);
            if(v2[mb1].s>=v2[mb2].f-1&&qq(v2[mb1].f, v2[mb1].s, 0)==sz(v2[mb1].f, v2[mb1].s)&&qq(v2[mb2].f, v2[mb2].s, 0)==sz(v2[mb2].f, v2[mb2].s)){
                vi ans(n, -1);
                int x=0;
                F0R(j, R){
                    ans[r[j]]=j&1^x;
                    trav(v, pts[r[j]]) ans[v]=j&1^1^x;
                    if(j==i)
                        x=1;
                }
                F0R(i, n) cout << ans[i];
                cout << nl;
                return 0;
            }
            st[0].set(0, m, 0); st[1].set(0, m, 0);
        }
        cout << "impossible\n";
    }
    else{
        vi ans(n, -1);
        F0R(i, R){
            ans[r[i]]=i&1;
            trav(v, pts[r[i]]) ans[v]=i&1^1;
        }
        F0R(i, n) cout << ans[i];
        cout << nl;
    }
}
