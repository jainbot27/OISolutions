/*
Solve the two queries seperately.

Both use the idea that edges have to be increasing.

The first type can be killed by focusing on LCAs.

The second type needs centroid and sweeping over paths that pass over some node X. 

Complexity: O(nlog^2n)

*/
// Inside Information
#include <bits/stdc++.h>
using namespace std;

using ll=long long;

#define FOR(i, a, b) for(int i=a; i<b; i++) 
#define ROF(i, a, b) for(int i=b-1; i>=a; i--)
#define F0R(i, n) FOR(i, 0, n) 
#define R0F(i, n) ROF(i, 0, n) 

#define f first
#define s second
#define pb push_back
#define siz(x) (int)x.size() 
#define ar array

const int mxN=2.4e5+10;
const int LG=20;

int n, q;
ar<int, 3> qq[mxN];
vector<pair<int, int>> adj[mxN];
int depth[mxN];
int anc[mxN][LG];
int mx[mxN][LG];

int mX[mxN], mN[mxN];

template<class T>void ckmax(T&A, T B){
    A=max(A, B);
}

void dfs(int u, int p, int c=-1){
    anc[u][0]=p; mx[u][0]=c;
    FOR(i, 1, LG){
        if(anc[u][i-1]==-1) anc[u][i]=-1, mx[u][i]=-1;
        else anc[u][i]=anc[anc[u][i-1]][i-1], mx[u][i]=max(mx[u][i-1], mx[anc[u][i-1]][i-1]);
    }
    for(auto[v, w]:adj[u]){
        if(v==p) continue;
        depth[v]=depth[u]+1;
        dfs(v, u, w);
    }
}

void dfs2(int u, int p, int L, int MX, int MN){
    mX[u]=MX, mN[u]=MN;
    for(auto[v, w]:adj[u]){
        if(v==p) continue;
        int nx=MX, ny=MN;
        if(w<L) nx=depth[u];
        if(w>L) ny=depth[u];
        dfs2(v, u, w, nx, ny);
    }
}

pair<int, int> lft(int u, int d){
    int maxx=0;
    for(int i=0; i<LG; i++){
        if(d&(1<<i)) ckmax(maxx, mx[u][i]), u=anc[u][i];
    }
    return {u, maxx};
}

pair<int, int> lca(int X, int Y){
    if(depth[X]<depth[Y]) swap(X, Y); 
    auto[XXX, maxx]=lft(X, depth[X]-depth[Y]);
    X=XXX;
    if(X==Y) return {X, maxx};
    R0F(i, LG){
        if(anc[X][i]!=anc[Y][i]){
            ckmax(maxx, mx[X][i]); 
            ckmax(maxx, mx[Y][i]); 
            X=anc[X][i]; Y=anc[Y][i];
        }
    }
    ckmax(maxx, mx[X][0]);
    ckmax(maxx, mx[Y][0]);
    return {anc[X][0], maxx};
}

int qry(int A, int B, int T){
    auto[L, V]=lca(A, B);
    if(V>T){
        return 0;
    }
    if(mN[A]<=depth[L]&&mX[B]<=depth[L]){
        if(A==L||B==L){
            return 1;
        }
        else{
            int AA=lft(A, depth[A]-depth[L]-1).f, BB=lft(B, depth[B]-depth[L]-1).f;
            if(mx[AA][0]<mx[BB][0]) return 1;
            else return 0;
        }
    }
    else
        return 0;
}

const int MOD=1e9+7; 

int par[mxN], sz[mxN], vis[mxN];
vector<int> proc[mxN];

int bit[mxN];

int occdfs3=0, occdfs4=0, occdfs5, occfindcent=0;

void upd(int x, int v){
    for(x++; x<mxN; x+=x&-x) 
        bit[x]+=v;
}
int qry(int x){
    int r=0;
    for(x++; x; x-=x&-x)
        r+=bit[x];
    return r;
}

int dfs3(int u, int p){
    if(vis[u]) return 0; 
    occdfs3++; 
    sz[u]=1;
    for(auto [v, w]:adj[u]){
        if(v==p) continue;
        sz[u]+=dfs3(v, u);
    }
    return sz[u];
}

int find_cent(int u, int p, int SZ){
    occfindcent++;
    for(auto[v, w]:adj[u]){
        if(!vis[v]&&v!=p&&sz[v]>SZ/2){
            return find_cent(v, u, SZ); 
        }
    }
    return u;
}

int in[mxN];

void dfs4(int u, int t, int p, int DIF){
    occdfs4++; 
    in[u]=(DIF==1?t:MOD);
    upd(t, DIF);
    for(auto[v, w]:adj[u]) 
        if(v!=p&&!vis[v]) 
            if(w>=t)
                dfs4(v, w, u, DIF);
}

void solve(int u){
    for(auto v:proc[u]){
        qq[v][2]+=qry(v);
    }
}

void dfs5(int u, int t, int p){
    occdfs5++; 
    solve(u);
    for(auto[v, w]:adj[u]) 
        if(v!=p&&!vis[v]) 
            if(w<t)
                dfs5(v, w, u);
}

void cent(int u){
    dfs3(u, -1);
    int c=find_cent(u, -1, sz[u]);
    sort(adj[c].begin(), adj[c].end(), [&](const pair<int, int>&X, const pair<int, int>&Y){
        return X.s<Y.s;
    });
    vis[c]=1; 
    dfs4(c, 0, -1, 1);
    solve(c);
    for(auto[v, w]:adj[c]){
        if(vis[v]) continue;
        dfs4(v, w, c, -1);
        upd(in[c], -1);
        upd(in[c]=w, 1);
        dfs5(v, w, c);
    }
    upd(in[c], -1);
    in[c]=MOD;
    for(auto[v, w]:adj[c])
        if(!vis[v])
            cent(v);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q;
    F0R(i, n+q-1){
        char T; cin >> T;
        if(T=='S'){
            int X, Y; cin >> X >> Y; X--; Y--; 
            adj[X].pb({Y, i}); 
            adj[Y].pb({X, i});
            qq[i]={1, X, Y};
        }
        else if(T=='Q'){
            int A, B; cin >> A >> B; A--; B--; 
            qq[i]={2, A, B};
        }
        else{
            int C; cin >> C; C--; 
            proc[C].pb(i);
            qq[i]={3, C, 0};
        }
    }
    memset(in, 0x3f, sizeof in);
    dfs(0, -1);
    dfs2(0, -1, 0, 0, 0);
    cent(0);
    F0R(i, n+q-1){
        if(qq[i][0]==2){
            int A=qq[i][1], B=qq[i][2];
            swap(A, B);
            cout << (qry(A, B, i)?"yes":"no") << "\n";
        }
        else if(qq[i][0]==3){
            cout << qq[i][2] << "\n";
        }
    }
}
