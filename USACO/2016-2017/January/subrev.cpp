/*
Main Idea:
Realize that we are essentially swapping opposite elements with our reverse. 
dp[i][j][lo][hi] = max we can get with lowest element = lo, highest element = hi, i = right bound, j = left bound.

*/

#include <bits/stdc++.h>
using namespace std;

const int mxN = 51;
int n, a[mxN], dp[mxN][mxN][mxN][mxN];

int umax(int& A, int B) {
    A = max(A, B);
    return A;
}
int go(int i, int j, int lo, int hi){
    if(lo > hi ) return -(1<<25);
    if(i > j) return 0;
    if(i==j) return (a[i] >= lo && a[i] <= hi) ? 1 : 0;
    int &res = dp[i][j][lo][hi];
    if(res!=-1) return res;
    res = 0;
    if(a[j] <= hi) umax(res, go(i, j-1, lo, a[j])+1);
    if(a[i] >= lo) umax(res, go(i+1, j, a[i], hi)+1);
    umax(res, go(i+1, j, lo, hi));
    umax(res, go(i, j-1, lo, hi));
    umax(res, go(i+1, j-1, lo, hi));
    if(a[i] <= hi) umax(res, go(i+1, j-1, lo, a[i])+1);
    if(a[j] >= lo) umax(res, go(i+1, j-1, a[j], hi)+1);
    if(a[i] <= hi && a[j] >= lo && a[j] <= a[i]) umax(res, go(i+1, j-1, a[j], a[i])+2);
    return res;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("subrev.in");  
    ofstream cout("subrev.out"); 
    cin >> n;
    for(int i=0; i < n; i++) cin >> a[i];
    memset(dp, -1 ,sizeof(dp));
    cout << go(0, n-1, 1, 50) << "\n";
}
