#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	cin >>t;
	for(int i=0;i<t;i++)
	{
		int n,g,b;
		cin >> n >> g>> b;
		int least=(n+1)/2;
		long long rotation=(least/g)*(long long)(g+b);
		if(least%g==0) rotation-=b;
		else 
		{
			rotation+=least%g;
			rotation=max(rotation,(long long)n);
		}
		printf("%lld\n",rotation);
	}
	return 0;
}
