/*
Problem: https://oj.uz/problem/view/IOI14_wall
My solution: https://oj.uz/submission/309256
Basic idea: we use lazy propogation to apply a series of max and min operations. The key idea is that after applying a series of max and min operations they can be reduced down to
simply just the 2 operations. So all we do is maintain the maximum possible value of something and the minimum possible. Other then that this is basic lazy propogation code. 
*/
#include <bits/stdc++.h>
using namespace std;
 
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
const int mxN = 2e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
int mn[1<<22], mx[1<<22];
void apply_op(int i, int l, int r){
    mn[i]=min(max(mn[i], l), r);
    mx[i]=min(max(mx[i], l), r);
}
void propogate(int i){
    apply_op(2*i+1, mn[i], mx[i]);
    apply_op(2*i+2, mn[i], mx[i]);
    mn[i] = 0, mx[i] = MOD;
}
void update(int l, int r, int xl, int xr, int i, int low, int high){
    if(r < xl || l > xr){
        return;
    }
    if(l <= xl && xr <= r){
        apply_op(i, low, high);
        return;
    }
    propogate(i);
    int m = (xl+xr)/2;
    update(l, r, xl, m, i*2+1, low, high);
    update(l, r, m+1, xr, i*2+2, low, high);
}
int query(int i, int pos,  int xl, int xr){
    if(xl == xr){
        assert(pos == xl);
        return mn[i];
    }
    propogate(i);
    int m = (xl+xr)/2;
    if(pos <= m){
        return query(i*2+1, pos, xl, m);
    }
    else{
        return query(i*2+2, pos, m+1, xr);
    }
}
 
void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalheight[]){
    F0R(i, k){
        op[i]--;
        update(left[i], right[i], 0, n-1, 0, op[i]==0?height[i]:0, op[i]==1?height[i]:MOD);
    }
    F0R(i, n){
        finalheight[i] = query(0, i, 0, n-1);
    }
}
