#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	cin >> t;
	for(int i=0;i<t;i++)
	{
		int a;
		string b;
		cin >> a>> b;
		int len=b.size();
		bool check=true;
		for(int i=0;i<len;i++)
		{
			if(b[i]!='9') 
			{
				check=false;
				break;
			}
		}
		if(!check) len--; 
		long long res=(long long)a*len;
		printf("%lld\n",res);
	}
	return 0;
}
