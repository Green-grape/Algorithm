#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	cin >> t;
	int* ex2=new int[61];
	for(int i=0;i<t;i++)
	{
		fill(ex2,ex2+61,0);
		int m;
		long long n,total=0;
		scanf("%lld %d",&n,&m);
		for(int j=0;j<m;j++)
		{
			int k;
			cin>>k;
			ex2[(int)log2(k)]++;
			total+=k;
		}
		if(total<n) cout<<-1<<endl;
		else
		{
			int j=0,res=0;
			long long k=1;
			while(j<60)
			{
				if((n & k)!=0)
				{
					if(ex2[j]>0)
					{
						ex2[j]-=1;
					}
					else
					{
						while(ex2[j]==0 && j<60)
						{
							j++;
							k=k<<1;
							res++;
						}
						ex2[j]-=1;
						continue;
					}
				}
				ex2[j+1]+=(ex2[j]/2);
				j++;
				k=k<<1;
			}
			cout<<res<<endl;
		}
	}
	delete[] ex2;
	return 0;
}
