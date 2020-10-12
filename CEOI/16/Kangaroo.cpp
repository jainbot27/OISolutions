// Basically the exact editorial solution that I don't even completely understand yet.
#include "iostream"
using namespace std;
 
const int64_t MOD = 1e9 + 7;
int64_t dp[2001][2001];
 
int main(){
    int n, a, b;
    cin >> n >> a >> b;
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++){
            if(i == a || i == b) 
                dp[i][j] = (dp[i-1][j] + dp[i-1][j-1]) % MOD;
            else 
                dp[i][j] = (dp[i-1][j+1] * j + dp[i-1][j-1] * (j - (i > a) - (i > b))) % MOD;
        }
    cout << dp[n][1];
}
