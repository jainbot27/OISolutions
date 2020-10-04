/*
Check Anthony for sol.
*/

#include <vector>
#include <iostream>
#include <queue>
#include <cassert>
#include <set>
#include <algorithm>
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
 
const char nl = '\n';
const int mxN = 2e5 + 10;
const int MOD = 1e9 + 7;
const long long infLL = 1e18;
 
vector<int> cur;
int a, b; int choose = 0;
set<vector<int>> lists  {
    {1,1,0,0,1},
    {1,0,0,1,0},
    {0,0,1,0,1},
    {0,1,0,1,1},
    {1,0,1,1,0},
    {0,1,1,0,0},
 
};
int lst = -1;
void Init(int A, int B){
    a = A, b = B;
    
}
int Move(vi y){
    if(a > 2){
        if(y[0] == 0 && y[1] == 0 && y[2] == 0){
            assert(false);
        }
        else if(y[0] == 0 && y[1] == 0){
            return 2;
        }
        else if(y[1] == 0 && y[2] == 0){
            return 0;
        }
        else if(y[2] == 0 && y[0] == 0){
            return 1;
        }
        else if(y[0] == 0){
            return 1;
        }
        else if(y[1] == 0){
            return 2;
        }
        else if(y[2] == 0){
            return 0;
        }
        else{
            assert(false);
        }
    }
    else{
        vi ny = y;
        if(lst!=-1) ny[lst]++;
        int amt = ny[0]+ny[1];
        if(amt!=2)choose=1;
        if(choose){
            if(amt==1){
                if(lst==-1) F0R(i, 2) if(y[i]) return lst=i;
                return -1;
            }
            else if(amt == 2){
                F0R(i, 2) if(y[i]) return lst = i;
            }
            else{
                F0R(i, 2) {
                    if(ny[i]==1){
                        if(!y[i]) return -1;
                        else return lst = i;
                    }
                }
            }
        }
        else{
            if(lst!=-1){
                F0R(i, 2) if(y[i]){
                    cur.pb(i);
                    if(cur.size()<5) return lst = i;
                    else {
                        choose = 1;
                        trav(v, lists)
                            if(v == cur) return lst = i;
                        return -1;
                    }
                }
            }
            else{
                F0R(i, 2){
                    if(y[i]){
                        cur.pb(i);
                        y[i]--;
                        F0R(j, 2){
                            if(y[j]){
                                cur.pb(j);
                                return lst = j;
                            }
                        }
                    }
                }
            }
        }
    }
}
#ifdef ACMX
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
 
 
    return 0;
}
#endif
