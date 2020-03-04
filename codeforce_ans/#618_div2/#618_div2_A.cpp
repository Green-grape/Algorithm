#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	scanf("%d",&t);
	vector<int> result;
	for(int i=0;i<t;i++)
	{
		int num;
		scanf("%d",&num);
		int zero_cnt=0,total=0,n;
		for(int i=0;i<num;i++)
		{
			scanf("%d",&n);
			if(n==0)
			{
				zero_cnt++;
				n++;
			}
			total+=n;
		}
		if(total!=0) result.push_back(zero_cnt);
		else result.push_back(zero_cnt+1);
	}
	for(int i=0;i<t;i++)
	{
		cout<<result[i]<<endl;
	}
	return 0;
}
