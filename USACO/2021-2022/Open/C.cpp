#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 19;

int dp[N][2], p[N];

void ckmax(auto &X, auto Y) {
    X = max(X, Y); 
}

struct segment {
    int mx[N * 2]; 

    segment() {
        for (int i = 0; i < N * 2; i++) 
            mx[i] = -2; 
    }

    void update(int x, int v, int i = 1, int lo = 0, int hi = N) {
        if (lo + 1 == hi) 
            mx[i] = v; 
        else {
            int mid = (lo + hi) / 2; 
            if (x < mid) {
                update(x, v, i * 2, lo, mid); 
            } else {
                update(x, v, i * 2 + 1, mid, hi); 
            }
            mx[i] = max(mx[i * 2], mx[i * 2 + 1]); 
        }    
    }

    int query(int L, int R, int i = 1, int lo = 0, int hi = N) {
        if (L <= lo && hi <= R) {
            return mx[i]; 
        } else if (L >= hi || lo >= R) {
            return -2; 
        } else {
            auto mid = (lo + hi) / 2; 
            return max(query(L, R, i * 2, lo, mid), query(L, R, i * 2 + 1, mid, hi)); 
        }
    }
} seg[2][2];


int main() {
    cin.tie(0)->sync_with_stdio(0);
    memset(dp, -1, sizeof dp);
    int n; 
    cin >> n; 
    for (int i = 0; i < n; i++)
        cin >> p[i]; 
    string s;
    cin >> s; 
    int mx = 0; 
    for (int i = 0; i < n; i++) {
        int val[2] = {-1, -1}; 
        if (s[0] == 'U') val[0] = 0; 
        else val[1] = 0; 
        ckmax(val[0], seg[0][0].query(0, p[i]) + 1); 
        ckmax(val[0], seg[1][0].query(p[i], N) + 1); 
        ckmax(val[1], seg[0][1].query(0, p[i]) + 1); 
        ckmax(val[1], seg[1][1].query(p[i], N) + 1); 
        if (val[0] != -1) {
            seg[0][s[val[0] + 1] != 'U'].update(p[i], val[0]); 
        }
        if (val[1] != -1) {
            seg[1][s[val[1] + 1] != 'U'].update(p[i], val[1]); 
        }
        ckmax(mx, val[0]);
        ckmax(mx, val[1]);
    }
    cout << mx << "\n";
}