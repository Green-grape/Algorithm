#include <bits/stdc++.h>

using namespace std;
const int mod=1e9+7;
long long int memo[1020][21]{0,};
long long int C(int,int);

int main(void)
{
	int n,m;
	cin >> n>>m;
	cout<<C(n+2*m-1,2*m)<<endl;
	return 0;
}

long long int C(int n,int r)
{
	if(n==r || r==0) return 1;
	if(memo[n][r]!=0) return memo[n][r];
	return memo[n][r]=(C(n-1,r-1)%mod+C(n-1,r)%mod)%mod;
}
