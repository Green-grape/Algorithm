#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	scanf("%d",&t);
	vector<int> v;
	int n;
	for(int i=0;i<t;i++)
	{
		scanf("%d",&n);
		v.push_back(n);
	}
	for(int i=0;i<t;i++)
	{
		int temp=v[i],check=0;
		int root_temp=int(sqrt(v[i]));
		for(int j=2;j<=root_temp;j++)
		{
			if(temp%j==0)
			{
				temp/=j;
				{
					root_temp=int(sqrt(temp));
					for(int k=j+1;k<=root_temp;k++)
					{
						if(temp%k==0)
						{
							temp/=k;
							if(temp!=k && temp!=j)
							{
								cout<<"YES"<<'\n'<<j<<' '<<k<<' '<<temp<<endl;
								check=1;
							}
						}
						if(check==1) break;
					}
				}
			}
			if(check==1) break;
		}
		if(check==0)
		{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}

