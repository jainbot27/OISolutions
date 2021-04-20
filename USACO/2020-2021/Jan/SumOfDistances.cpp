/*
We desire to compute the minimum distance to each node on the huge graph, so we first need to find the answer for the individual graphs. 
After that, notice that we can reach some node on the big graph, if there is a path to it if it contains subnodes with distances all even or odd. 
The problem is that we could have nodes which are reachable with both even and odd distances. However notice min(x, y)=x+y-max(x, y). 
The reason we can't just straight up calculate min(x, y) is because then we would be considering paths that are too small. But if we consider maxs, we will only consider the
maximum case and nothing else. 
After this, we just have to calculate the sum of all paths, and it is easy to see with a lazy segment tree with range mul, point add, and point query, it is possible to query
this. Notice that I used all operations that are lazy just because it was easier for implementation reasons. 

Complexity: O((n+m)logn)
*/
#include <bits/stdc++.h>
using namespace std;
const int mxK=5e4;
const int MOD=1e9+7;
const int mxN=1<<18;
int ad(int a, int b){
    int sum=a+b;
    while(sum>=MOD) sum-=MOD;
    while(sum<0) sum+=MOD;
    return sum;
}
int sb(int a, int b){
    return ad(a, -b);
}
int ml(int a, int b){
    return (1LL*a*b)%MOD;
}
struct segment{
    int madd[2*mxN], mmul[2*mxN], val[2*mxN];
    void init(){
        for(int i=0; i<2*mxN; i++) madd[i]=0, mmul[i]=1, val[i]=0;
    }
    void add(int L, int R, int x, int i=1, int lo=0, int hi=mxN){
        if(R<=lo||hi<=L) return;
        if(L<=lo&&hi<=R){
            madd[i]=ad(madd[i], x);
            val[i]=ad(val[i], ml(x,hi-lo));
            return;
        }
        push(lo, hi, i);
        int m=(lo+hi)/2;
        add(L, R, x, i*2, lo, m);
        add(L, R, x, i*2+1, m, hi);
        val[i]=ad(val[i*2], val[i*2+1]);
    }
    void mul(int L, int R, int x, int i=1, int lo=0, int hi=mxN){
        if(R<=lo||hi<=L) return;
        if(L<=lo&&hi<=R){
            madd[i]=ml(madd[i], x);
            mmul[i]=ml(mmul[i], x);
            val[i]=ml(val[i], x);
            return;
        }
        push(lo, hi, i);
        int m=(lo+hi)/2;
        mul(L, R, x, i*2, lo, m);
        mul(L, R, x, i*2+1, m, hi);
        val[i]=ad(val[i*2], val[i*2+1]);
    }
    int query(int L, int R, int i=1, int lo=0, int hi=mxN){
        if(R<=lo||hi<=L) return 0;
        if(L<=lo&&hi<=R){
            return val[i];
        }
        push(lo, hi, i);
        int m=(lo+hi)/2;
        return ad(query(L, R, i*2, lo, m), query(L, R, i*2+1, m, hi));
    }
    void push(int lo, int hi, int i){
        int m=(lo+hi)/2;
        if(mmul[i]!=1){
            mul(lo, m, mmul[i], i*2, lo, m);
            mul(m, hi, mmul[i], i*2+1, m, hi);
            mmul[i]=1;
        }
        if(madd[i]!=0){
            add(lo, m, madd[i], i*2, lo, m);
            add(m, hi, madd[i], i*2+1, m, hi);
            madd[i]=0;
        }
    }
};
int k;
segment odd, even, both;
void solve(segment& s, vector<int> dist, bool flag){
    int n=dist.size(); 
    if(flag){
        for(int i=0; i<n; i++){
            s.add(i, i+1, dist[i]);
        }
        return;
    }
    vector<int> nxt(n); 
    vector<int> pre(n);
    for(int i=0; i<n; i++) 
        pre[i]=s.query(0, i);
    int p=0;
    for(int i=0; i<n; i++){
        nxt[i]=ml(dist[i], pre[i]);
        p=ad(p, dist[i]);
        s.mul(i, i+1, p);
    }
    s.mul(n, mxN, p);
    for(int i=0; i<n; i++){
        s.add(i, i+1, nxt[i]);
    }
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> k;
    odd.init(); even.init(); both.init();
    for(int q=0; q<k; q++){
        int n, m;
        cin >> n >> m;
        vector<vector<int>>adj(2*n);
        adj.resize(2*n);
        for(int i=0, e1, e2; i<m; i++){
            cin >> e1 >> e2; e1--; e2--; 
            adj[e1].push_back(n+e2);
            adj[e2].push_back(n+e1);
            adj[n+e1].push_back(e2);
            adj[n+e2].push_back(e1);
        }
        vector<int> dist(2*n, MOD);
        dist[0]=0;
        queue<int> qq;
        qq.push(0);
        while(!qq.empty()){
            auto T=qq.front(); 
            qq.pop(); 
            for(auto&v:adj[T]){
                if(dist[v]>dist[T]+1){
                    dist[v]=dist[T]+1;
                    qq.push(v);
                }
            }
        }
        vector<int> cnte(2*n), cnto(2*n), cntb(2*n);
        for(int i=0; i<n; i++){
            if(dist[i]<MOD){
                cnte[dist[i]]++;
            }
            if(dist[n+i]<MOD){
                cnto[dist[n+i]]++;
            }
            if(dist[i]<MOD&&dist[n+i]<MOD){
                cntb[max(dist[i], dist[n+i])]++;
            }
        }
        solve(even, cnte, q==0); solve(odd, cnto, q==0); solve(both, cntb, q==0);
    }
    int ans=0;
    for(int i=0; i<mxN; i++){
        ans=ad(ans, ml(even.query(i, i+1), i));
        ans=ad(ans, ml(odd.query(i, i+1), i));
        ans=sb(ans, ml(both.query(i, i+1), i));
    }
    cout << ans << "\n";
}
