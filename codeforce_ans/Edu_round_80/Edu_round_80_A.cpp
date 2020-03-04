#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	cin >> t;
	for(int i=0;i<t;i++)
	{
		int n,d;
		cin>>n>>d;
		int x=sqrt(d)-1;
		int days=x+d/(x+1);
		if(d%(x+1)!=0) days++;
		if(days<=n) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
