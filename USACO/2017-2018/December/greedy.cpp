#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5 + 10;

int n;
int a[mxN];

bool works(int k){
    vector<int> amt(n+1);
    for(int i=0; i < k - 1; i++)
        amt[a[i]]++;
    int sum = 0;
    for(int i = 1; i <= n; i++){
        sum += amt[i];
        if(sum >= i) 
            return 0;
    }
    return 1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    ifstream cin("greedy.in"); ofstream cout("greedy.out");
    cin >> n;
    for(int i=0; i < n; i++) 
        cin >> a[i], a[i] = n - a[i];
    int lo = 0, hi = n;
    int ans;
    while(lo <= hi){
        int mid = (lo + hi)/2;
        if(works(mid)){
            lo=mid+1;
            ans=mid;
        }
        else{
            hi=mid-1;
        }
    }
    cout << n - ans << "\n";
    return 0;
}
