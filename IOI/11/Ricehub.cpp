/*

Main Idea: 

We can use two pointers. We will iterate over the the end bound (j) for the range we will "take". Then notice that there will be some i <= j such that we can pick all the trucks
from i...j. The key observation is that i is strictly increasing. 
We can use prefix sums to make our operations constant. 

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


int besthub(int R, int L, int* X, ll B){
    ll p[R], sum;
    F0R(i, R){
        if(i) p[i] = p[i-1] + X[i];
        else p[i] = X[i];
    } 
    auto GET = [&](int i, int j){
        return (((i+j)/2 - i + 1) - (j-(i+j)/2)) * X[(i+j)/2] - (p[(i+j)/2] - (i?p[i-1]:0)) + (p[j] - p[(i+j)/2]);
    };
    int i = 0, res = 0; 
    F0R(j, R){
        sum = GET(i, j);
        while(sum > B){
            i++;
            sum = GET(i, j);
        }
        ckmax(res, j - i + 1);
    }
    return res;
}
