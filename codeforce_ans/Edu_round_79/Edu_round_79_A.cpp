#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	cin >>t;
	for(int i=0;i<t;i++)
	{
		int c[3];
		int max_c=0,idx=0,total=0;
		for(int j=0;j<3;j++)
		{
			scanf("%d",&c[j]);
			if(max_c<c[j])
			{
				max_c=c[j];
				idx=j;
			}
			total+=c[j];
		}
		if(c[idx]-(total-c[idx])>1) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	return 0;
}
