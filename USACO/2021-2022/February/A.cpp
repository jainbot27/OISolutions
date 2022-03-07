#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstring>

using namespace std;

const int N = 1 << 18; 

struct Rect {
    int x1, y1, x2, y2; 
    Rect() {
        cin >> x1 >> y1 >> x2 >> y2; 
        x1--, y1--, x2--, y2--; 
    };
}; 

struct Event {
    int x, y1, y2, fir; 
};

int n, t; 
vector<Rect> r;
int sz[N], par[N]; 
int cnt[2 * N], node[2 * N]; 
vector<Event> e; 
long long white = 1, black = 0; 

int Find(int a) {
    if (a == par[a]) return a; 
    return par[a] = Find(par[a]); 
}

void merge(int a, int b) {
    a = Find(a), b = Find(b); 
    if (a == b) return;     
    if (sz[a] < sz[b]) swap(a, b); 
    sz[a] += sz[b];
    par[b] = a; 
    sz[b] = 0; 
}

void apply(int idx, int lo, int hi, int cur) {
    if (cnt[idx] == 0) return; 
    // cout << idx << " " << lo << " " << hi << " " << cur << "\n";
    if (node[idx] == -1) node[idx] = cur; 
    else merge(cur, node[idx]); 
}

void push(int i, int lo, int hi) {
    if (node[i] != -1) {
        // cout << "PUSH: " << lo << " " << hi << "\n";
        assert(hi - lo > 1); 
        int mid = (lo + hi) / 2; 
        apply(i * 2, lo, hi, node[i]); 
        apply(i * 2 + 1, lo, hi, node[i]); 
        node[i] = -1; 
    }
}

void add(int x, int y, int i = 1, int lo = 0, int hi = N) {
    if (lo + 1 == hi) {
        cnt[i] += y; 
    } else {
        push(i, lo, hi); 
        int mid = (lo + hi) / 2; 
        if (x < mid) add(x, y, i * 2, lo, mid); 
        else add(x, y, i * 2 + 1, mid, hi); 
        cnt[i] = cnt[i * 2] + cnt[i * 2 + 1]; 
    }
}


void comb(int L, int R, int v, int i = 1, int lo = 0, int hi = N) {
    if (L >= hi || lo >= R) return; 
    else if (L <= lo && hi <= R) {
        apply(i, lo, hi, v); 
    } else {
        push(i, lo, hi); 
        int mid = (lo + hi) / 2; 
        comb(L, R, v, i * 2, lo, mid); 
        comb(L, R, v, i * 2 + 1, mid, hi);     
    }
}


struct fenwick {
    int bit[N]; 
    fenwick() {
        memset(bit, 0, sizeof bit);
    }
    void update(int i, int x) {
        for (i++; i < N; i += i & -i) 
            bit[i] += x; 
    }
    int sum(int idx) {
        assert(idx >= -1);
        int ret = 0; 
        for (idx++; idx; idx -= idx & -idx) 
            ret += bit[idx]; 
        return ret; 
    }
    int sum(int l, int r) { // [l, r] 
        return sum(r) - sum(l - 1); 
    }
};

fenwick gl; 

void solve(vector<int> index, int color) {
    long long w = 1, b = 0; 
    vector<Event> e2; 
    for (auto v : index) {
        e2.push_back({r[v].x1, r[v].y1, r[v].y2, 0}); 
        e2.push_back({r[v].x2, r[v].y1, r[v].y2, 1}); 
    }
    sort(e2.begin(), e2.end(), [&](Event &A, Event &B) {
        return A.x < B.x; 
    });
    for (auto [x, y1, y2, typ] : e2) {
        if (typ == 0) {
            gl.update(y1, 1);
            gl.update(y2, 1);
            int l = gl.sum(y1 - 1), r = gl.sum(y2 - 1);
            b += (r + 1) / 2 - (l + 1) / 2 - 1; 
            w += r - l - 1 - ((r + 1) / 2 - (l + 1) / 2 - 1); 
        } else {
            int l = gl.sum(y1 - 1), r = gl.sum(y2 - 1);
            b += (r + 1) / 2 - (l + 1) / 2; 
            w += r - l - 1 - ((r + 1) / 2 - (l + 1) / 2); 
            gl.update(y1, -1);
            gl.update(y2, -1);
        }
    }
    if (color) swap(w, b); 
    // cout << w << " " << b << "\n";
    white += w, black += b; 
}

int main() {
    memset(node, -1, sizeof node); 
    cin >> n >> t; 
    for (int i = 0; i < 2 * n; i++) 
        par[i] = i, sz[i] = 1; 
    for (int i = 0; i < n; i++) {
        r.emplace_back(); 
        e.push_back({r.back().x1, r.back().y1, r.back().y2, 0}); 
        e.push_back({r.back().x2, r.back().y1, r.back().y2, 1}); 
    }
    sort(e.begin(), e.end(), [&](Event &A, Event &B) {
        return A.x < B.x; 
    });
    for (auto [x, y1, y2, typ] : e) {
        // cout << x << " " << y1 << " " << y2 << " " << typ << "\n";
        merge(y1, y2); 
        if (!typ) {
            add(y1, 1);
            add(y2, 1);           
            comb(y1, y2 + 1, y1); 
        } else {
            comb(y1, y2 + 1, y1); 
            add(y1, -1);
            add(y2, -1);           
        }
    }
    for (int i = 0; i < 2 * n; i++) 
        add(i, 0); 
    vector<vector<int>> index(2 * n); 
    vector<int> color(2 * n); 
    for (int i = 0; i < n; i++) {
        index[Find(r[i].y1)].push_back(i); 
    }

    fenwick low, high;
    set<int> used; 
    for (auto [x, y1, y2, typ] : e) {
        if (!used.count(Find(y1))) {
            color[Find(y1)] = (high.sum(y2, N - 1) - low.sum(y2, N - 1)) % 2;
            used.insert(Find(y1));
        }
        if (typ == 0) {
            low.update(y1, 1); 
            high.update(y2, 1); 
        } else {
            low.update(y1, -1); 
            high.update(y2, -1); 
        }
    }

    for (int i = 0; i < 2 * n; i++) {
        if (index[i].size()) {
            solve(index[i], color[i]); 
        }
    }

    if (t == 1) cout << white + black << "\n"; 
    else cout << white << " " << black << "\n";
}