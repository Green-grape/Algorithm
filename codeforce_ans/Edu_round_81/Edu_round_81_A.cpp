#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	cin >> t;
	for(int i=0;i<t;i++)
	{
		int n;
		cin >> n;
		bool check=false;
		if(n%2==0) n/=2;
		else{
			n-=3;
			n/=2;
			check=true;
		}
		if(check)
		{
			cout<<7;
		}
		for(int i=0;i<n;i++)
		{
			cout<<1;
		}
		cout<<endl;
	}
	return 0;
}
