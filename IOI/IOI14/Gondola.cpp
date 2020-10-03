/*
Problem: https://oj.uz/problem/view/IOI14_gondola
My solution: https://oj.uz/submission/309516


Basic Idea: 
For subtasks 1-3 notice we only care about positions i such that a[i] <= n. With these positions we choose an arbitrary one and set it to our base position. 
Now for every position we just need to check if the value there is (a[base] + (i-base) + n)%n. I subtracted all numbers by 1 to make the math easier.

For subtasks 4-6 we must realize that we can just create any valid construction (which we learned how to do in the first subtask). After that, just simulate the increasing
and notice that we need max(gondolaSeq[i)-n numbers in our array which is enough to go through each position and use a map to see if we need to use a specific number. If 
we dont need to use a specific number, it suffices to put on our maximum number.

For subtasks 7-10 We can realize that we can check for validness with our solution from the first subtask. Then also notice that for x <= max(a[i]), the number of ways we can 
choose for the replacement of that number is all y such as a[y] > x. This is enough to get us the 9th subtask. For the final one, we can realize we are doing a lot of the 
same operations in a row and we can seperate these positions into "blocks". 
*/
#include <bits/stdc++.h>
#include "gondola.h"
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
const int mxN = 1e5 + 10;
const int MOD = 1'000'000'009;
const long long infLL = 1e18;
 
int32_t valid(int n, int* _inputSeq){
    vi inputSeq(n);
    F0R(i, n){
        inputSeq[i] = _inputSeq[i];
        inputSeq[i]--;
    }
    vi vals;
    F0R(i, n){
        vals.pb(inputSeq[i]);
    }
    sort(all(vals));
    vals.resize(unique(all(vals))-vals.begin());
    if(siz(vals)!=n) return 0;
    if(vals[0]>=n) return 1;
    int pos;
    F0R(i, n){
        if(inputSeq[i] < n){
            pos = i;
            break;
        }
    }
    int ff = inputSeq[pos];
    F0R(i, n){
        if(inputSeq[i]<n){
            int dif = i - pos;
            int should = (n + ff + dif)%n;
            if(inputSeq[i] != should) return 0;
        }
    }
    return 1;
}
int32_t replacement(int n, int _gondolaSeq[], int _replacementSeq[]){
    vi gs(n), rs;
    F0R(i, n){
        gs[i] = _gondolaSeq[i]-1;
    }
    int pos = 0, cnt = 0, mx = -1, sp, mxpos; 
    sp = 0;
    map<int, int> vals;
    F0R(i, n){
        if(ckmax(mx, gs[i])) mxpos = i;
        if(gs[i] < n){
            pos = i; 
            sp = gs[i];
            cnt++;
        }
    }
    if(cnt==n){
        return 0;
    }
    int foo;
    F0R(i, n){
        int dif = i - pos;
        int should=  (n + sp + dif) % n;
        if(mxpos==i){
            foo = should;
        }
        if(gs[i]==should)
            continue;
        vals[gs[i]]=should;     
    }
    int x = 0;
    FOR(i, n, mx+1){
        if(vals.find(i)!=vals.end()&&i!=mx){
            _replacementSeq[x] = vals[i]+1;
            x++;
            continue;
        }
        _replacementSeq[x] = foo+1;
        foo=i;
        x++;
    }
    return x;
}
// modulo class
int mul(int x, int y){ return ((int64_t)x * (int64_t)y) % MOD; } 
void ml(int &x, int y) {x = mul(x, y);}
int binpow(int x, int y){ int z = 1; while(y > 0) { if(y % 2 == 1) z = mul(z, x); x = mul(x, x); y /= 2; } return z; }
 
int32_t countReplacement(int n, int inputSeq[]){
    if(!valid(n, inputSeq)) return 0;
    int res = 1;
    sort(inputSeq, inputSeq+n);
    bool f = 1;
    F0R(i, n){
        if(inputSeq[i]>n){
            if(f){
                ml(res, binpow(n-i, inputSeq[i]-n-1));
            }
            else{
                ml(res, binpow(n-i, inputSeq[i]-inputSeq[i-1]-1));
            }
            f = 0;
        }
    }
    if(inputSeq[0]>n) ml(res, n);
    return res;
}
