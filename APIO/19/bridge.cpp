#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

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
const int mxN = 50011;
const int mxM = mxN*2;
const int BLK = 1000;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;

struct RollbackUF {
    int e[mxN]; vector<pii> st;
    void init() { memset(e, -1, sizeof(e)); st.clear();}
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    int time() { return siz(st); }
    void rollback(int t) {
        for (int i = time(); i --> t;)
            e[st[i].first] = st[i].second;
        st.resize(t);
    }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        st.push_back({a, e[a]});
        st.push_back({b, e[b]});
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

int e[mxM][3];
int q[mxM][3];
bool change[mxM];
vi upd[mxM];
int ans[mxM];
//timer TIMER;

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, qq;
    cin >> n >> m;
    F0R(i, m){
        cin >> e[i][0] >> e[i][1] >> e[i][2];
        e[i][0]--; e[i][1]--;
    }
    cin >> qq;
    F0R(i, qq){
        cin >> q[i][0] >> q[i][1] >> q[i][2];
        q[i][1]--;
    }
    RollbackUF dsu;
    for(int qqq=0; qqq<qq; ){
        memset(change, 0, sizeof(change));
        int l = qqq, r = min(qqq+BLK, qq);
        vi same, diff, al;
        dsu.init();
        FOR(i, l, r){
            if(q[i][0]==1){
                change[q[i][1]] = 1;
            }
            else{
                al.pb(i);
            }
        }
        F0R(i, m){
            if(!change[i]) same.pb(i);
            else diff.pb(i);
        }

        FOR(i, l, r){
            if(q[i][0]==1){
                e[q[i][1]][2] = q[i][2];
            }
            else{
                trav(j, diff){
                    if(e[j][2]>=q[i][2]){
                        upd[i].pb(j);
                    }
                }
            }
        }
        sort(all(al), [&](const int& e1, const int& e2){
            return q[e1][2]>q[e2][2];
        });
        sort(all(same), [&](const int& e1, const int& e2){
            return e[e1][2]>e[e2][2];
        });
        int pt = 0;
        trav(i, al){
            while(pt<siz(same)&&e[same[pt]][2]>=q[i][2]){
                dsu.join(e[same[pt]][0], e[same[pt]][1]);
                pt++;
            }
            int T = dsu.time();
            trav(j, upd[i]){
                dsu.join(e[j][0], e[j][1]);
            }
            ans[i] = dsu.size(dsu.find(q[i][1]));
            dsu.rollback(T);
        }
        qqq = r;
    }
    F0R(i, qq){
        if(q[i][0]==2){
            cout << ans[i] << nl;
        }
    }
    return 0;
}
