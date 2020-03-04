#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	cin >>t;
	for(int i=0;i<t;i++)
	{
		int n,s;
		cin>>n>>s;
		vector<int> a(n);
		long long int total=0;
		for(int j=0;j<n;j++)
		{
			scanf("%d",&a[j]);
			total+=a[j];
		}
		if(total<=s) cout<<0<<endl;
		else
		{
			int temp=0,maxN=0,j=0,idx=0;
			while(temp<=s && j<n)
			{
				if(maxN<a[j])
				{
					maxN=a[j];
					idx=j;
				}
				temp+=a[j];
				j++;
			}
			if(j==n)
			{
				cout<<idx+1<<endl;
			}
			else
			{
				if((temp-a[idx])-a[j]<s) cout<<idx+1<<endl;
				else cout<<0<<endl;
			}
			
		}
	}
	return 0;
}
