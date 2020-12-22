ter
#include <bits/stdc++.h>
using namespace std;
 
const int mxN = 25001;
 
string word[mxN];
int n, maxi, maxs;
pair<pair<int, string>, int> v[mxN];
string lst = "";
string res;
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i=0; i < n; i++) {
        cin >> word[i];
        if(word[i].size() > maxs)
            maxs=word[i].size(), maxi=i;
    }
    for(int i=0; i < n; i++){
        int cnt=0;
        for(int j = 0; j < word[i].size(); j++){
            if(word[i][j]!=word[maxi][j]) break;
            cnt++;
        }
        v[i]={{cnt, word[i]}, i};
    }
    sort(v, v+ n);
    for(int i=0; i < n; i++){
        string cur = v[i].first.second;
        int cnt = 0;
        for(int j =0; j < min(cur.size(), lst.size()); j++){
            if(lst[j]!=cur[j]) break;
            cnt++;
        }
        for(int j =0; j < lst.size() - cnt; j++)  res += '-';
        for(int j = cnt; j < cur.size(); j++) res += (cur[j]);
        res+='P';
        lst=cur;
    }
    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); i++) cout << res[i] << '\n';
    return 0;
}
