// Difficult(y) Choice

/*
  Just realize that you lose nothing if you always make jumps of less than A. So you can binary search for first spot X such that x[X]>=A. 
  
  Then in 2*K queries, you can realize that you will never be making a jump bigger than A, and just try everything. 
  
  Complexity: O(logn+k)
*/

#include <bits/stdc++.h>
#include "books.h"
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
 
const int mxN=1e5+10;
 
ll memo[20];

void solve(int N, int K, ll A, int S){
    FOR(i, 1, K+1) memo[i]=skim(i); 
    ll sum=0; 
    FOR(i, 1, K+1) sum+=memo[i];
    if(sum>2*A) impossible(); 
    int lo=K, hi=N, ans;
    while(lo<=hi){
        int mid=(lo+hi)/2; 
        if(skim(mid)+sum-memo[K]<=2*A){
            ans=mid, lo=mid+1;
        }
        else hi=mid-1;
    }
    int cur=K; 
    ROF(i, ans-K+1, ans+1){
        sum-=memo[cur--];
        sum+=skim(i);
        if(sum>=A){
            vector<int> res;
            FOR(j, i, ans+1) res.pb(j); 
            FOR(j, 1, cur+1) res.pb(j);
            answer(res);
        }
    }
    impossible(); 
}
 
