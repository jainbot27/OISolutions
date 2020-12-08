/*
The solutions create a connected component

*/

#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5 + 10;

int n, m;
vector<int> adj[mxN], inCon[mxN], outCon[mxN];
int deg[mxN];
vector<int> all;
bool done[mxN];
int Ddeg[mxN];
int good[mxN];
void dfs(int u, int p){
    good[u] = 1;
    for(auto&v : adj[u]){
        if(v == p) continue;
        if((int)outCon[v].size() != 0) continue;
        dfs(v, u);
    }
}

int main(){
    ifstream cin("gathering.in");
    ofstream cout("gathering.out");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    //cout << "WE GOT HERE" << endl;
    for(int i = 1; i < n; i++){
        int e1, e2;
        cin >> e1 >> e2;
        e1--; e2--;
        adj[e1].push_back(e2);
        adj[e2].push_back(e1);
        deg[e1]++;
        deg[e2]++;
    }
    //cout << "WE GOT HERE" << endl;
    for(int i = 0; i < m; i++){
        int e1, e2;
        cin >> e1 >> e2;
        e1--; e2--;
        inCon[e2].push_back(e1);
        outCon[e1].push_back(e2);
        Ddeg[e2]++;
    }
    for(int i = 0; i < n; i++){
        if(deg[i] <= 1 && Ddeg[i] == 0){
            all.push_back(i);
            done[i] = 1;
        }
    }
    //cout << "WE GOT HERE" << endl;
    for(int  i=0 ; i < n-1; i++){
        if(i == (int)all.size()){
            for(int j =0; j < n; j++){
                cout << 0 << '\n';
            }
            //cout << "\n";
            return 0;
        }
        int u = all[i];
        for(auto& v : adj[u]){
            deg[v]--; 
            if(deg[v] <= 1 && Ddeg[v] == 0 && !done[v]){
                all.push_back(v);
                done[v] = 1;
            }
        }
        for(auto& v : outCon[u]){
            Ddeg[v]--;
            if(deg[v] <= 1 && Ddeg[v] == 0 && !done[v]){
                all.push_back(v);
                done[v] = 1;
            }
        }
    }
    int tot = all[n-1];
    dfs(tot, -1);
    for(int i=0; i < n ; i++){
        cout << good[i] << '\n';
    }
    return 0;
}
