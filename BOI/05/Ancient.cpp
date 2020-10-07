/*
The main idea for this problem is that any polynomial dp essentially passes. I did O(len(s)*26*26*ve*vc). 

Just iterate over the letters and update the dp accordingly. 

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
 
inline bool is_vowel(char t){
    return (t == 'a' ||  t == 'e' || t == 'i' || t == 'o' ||  t == 'u');
}
 
inline bool is_letter(char t){
    return (t!='*');
}
 
int VE, VC, CE, CC, n; ll dp[16][26][5][5];
string a;
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> VE >> VC >> CE >> CC;
    cin >> a; n = siz(a);
    if(is_letter(a[0]))
        dp[0][a[0]-'a'][1][1] = 1;
    else
        F0R(i, 26)
            dp[0][i][1][1] = 1;
    FOR(i, 1, n){
        F0R(j, 26){
            if(is_letter(a[i])&&j!=a[i]-'a') 
                continue;
            F0R(k, 26){
                if(j == k){
                    if(is_vowel(k+'a'))
                        FOR(c, 1, 1 + VE)
                            FOR(d, 1, 1 + VC)
                                dp[i][j][d][c] += dp[i-1][j][d-1][c-1];
                    else
                        FOR(c, 1, 1 + CE)
                            FOR(d, 1, 1 + CC)
                                dp[i][j][d][c] += dp[i-1][j][d-1][c-1];
                }
                else{
                    if(is_vowel(j+'a')&&is_vowel(k+'a'))
                        FOR(c, 1, 1+VE)
                            FOR(d, 1, 1+VC)
                                dp[i][j][d][1] += dp[i-1][k][d-1][c];
                    else if(is_vowel(j + 'a'))
                        FOR(c, 1, 1+CE)
                            FOR(d, 1, 1+CC)
                                dp[i][j][1][1] += dp[i-1][k][d][c];
                    else if(is_vowel('a'+k))
                        FOR(c, 1, 1+VE)
                            FOR(d, 1, 1+VC)
                                dp[i][j][1][1] += dp[i-1][k][d][c];
                    else
                        FOR(c, 1, 1+CE)
                            FOR(d, 1, 1+CC)
                                dp[i][j][d][1] += dp[i-1][k][d-1][c];
                }
            }
        }
    }
    ll res = 0;
    F0R(i, 26)
        F0R(j, 5)
            F0R(k, 5)
                res += dp[n-1][i][j][k];
    cout << res << nl;
    return 0;
}
