/*
Got idea but having precision issues so I just copied the editorial solution lmao

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstdio>
using namespace std;
#define MAXN 100000
 
int N;
long long f[MAXN+2];
int l[MAXN+2];
int r[MAXN+2];
 
int main()
{
    ifstream cin("balance.in");
    ofstream cout("balance.out");
	cin >> N;
	for(int i=1;i<=N;i++)
		cin >> f[i];
	f[0] = f[N+1] = 0;
	vector<int> hull;
	hull.push_back(0);
	for(int k=1;k<=N+1;k++)
	{
		while(hull.size() >= 2)
		{
			int i = hull[hull.size()-2];
			int j = hull[hull.size()-1];
			if((k-i)*f[j] < (j-i)*f[k] + (k-j)*f[i])
				hull.pop_back();
			else
				break;
		}
		hull.push_back(k);
	}
	for(int j=0;j<hull.size()-1;j++)
	{
		for(int i=hull[j]+1;i<hull[j+1];i++)
		{
			l[i] = hull[j];
			r[i] = hull[j+1];
		}
		l[hull[j]] = r[hull[j]] = hull[j];
	}
	l[N+1] = r[N+1] = N+1;
	for(int i=1;i<=N;i++)
	{
		if(l[i]==r[i]) cout << 100000LL*f[i] << '\n';
                else cout << (100000ULL*(((unsigned long long)(r[i]-i))*((unsigned long long)f[l[i]]) + ((unsigned long long)(i - l[i]))*((unsigned long long)f[r[i]])))/((unsigned long long)(r[i]-l[i])) << '\n';
        }
	return 0;
}
