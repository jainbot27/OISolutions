#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>
#include <deque>
#include <bitset>
#include <cassert>
#include <limits.h>
#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define siz(x) (int)x.size()

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

bool ckmin(auto &a, const auto &b) { return b < a ? a = b, 1 : 0; }
bool ckmax(auto &a, const auto &b) { return b > a ? a = b, 1 : 0; }


const int mxN = 1 << 17; 

int mn[mxN * 2], mx[mxN * 2]; 
int n, k, a[mxN], nxt[mxN], prv[mxN]; 

void minUpd(int pos, int val) {
    for (mn[pos += n] = val; pos /= 2;) 
        mn[pos] = min(mn[pos * 2], mn[pos * 2 + 1]); 
}
void maxUpd(int pos, int val) {
    for (mx[pos += n] = val; pos /= 2;) 
        mx[pos] = max(mx[pos * 2], mx[pos * 2 + 1]); 
}
int minQuery(int l, int r) {
    int L = INT_MAX, R = INT_MAX; 
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2) L = min(L, mn[l++]); 
        if (r % 2) R = min(R, mn[--r]); 
    }
    return min(L, R); 
}
int maxQuery(int l, int r) {
    int L = INT_MIN, R = INT_MIN; 
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2) L = max(L, mx[l++]); 
        if (r % 2) R = max(R, mx[--r]); 
    }
    return max(L, R); 
}

multiset<int> values[mxN]; 

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k; 
    for (int i = 0; i < n; i++)
        cin >> a[i], minUpd(i, a[i]), maxUpd(i, a[i]), nxt[i] = i + 1, prv[i] = i - 1, values[i].insert(a[i]); 
    for (int i = 0; i < n; i++) {
        int L = -1, R = i; 
        while (L + 1 < R) {
            int M = (L + R) / 2; 
            // (doesn't work, works]
            if (minQuery(M, i + 1) >= a[i] - k) {
                R = M; 
            } else {
                L = M; 
            }
        }
        int l = -1, r = i; 
        while (l + 1 < r) {
            int m = (l + r) / 2; 
            if (maxQuery(m, i + 1) <= a[i] + k) {
                r = m; 
            } else {
                l = m; 
            }
        }
        int bar = max(R, r); 
        int lo = bar, hi = i + 1; 
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2; 
            if (maxQuery(bar, mid) < a[i]) {
                lo = mid; 
            } else {
                hi = mid; 
            }
        }
        // cout << i << " " << bar << "\n";
        bar = lo; 
        // now we just have to move a[i] -> a[bar] 
        if (bar == i) continue; 
        values[i].erase(a[i]); 
        minUpd(i, INT_MAX); 
        maxUpd(i, INT_MIN); 
        values[bar].insert(a[i]); 
        minUpd(bar, *values[bar].begin()); 
        maxUpd(bar, *values[bar].rbegin()); 
    }
    for (int i = 0; i < n; i++) 
        for (auto &v : values[i])
            cout << v << "\n"; 
}
