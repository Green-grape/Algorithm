#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	scanf("%d",&t);
	vector<int> v;
	vector<string> result;
	for(int i=0;i<t;i++)
	{
		int num_size=0,n=0;
		scanf("%d",&num_size);
		for(int j=0;j<num_size;j++)
		{
			scanf("%d",&n);
			v.push_back(n);
		}
		int check=0;
		int pref=0,suff=num_size-1;
		for(int j=0;j<num_size;j++)
		{
			if(v[j]<j) break;
			pref=j;
		}
		for(int j=num_size-1;j>=0;j--)
		{
			if(v[j]<num_size-1-j) break;
			suff=j;
		}
		if(pref>=suff) result.push_back("YES");
		else result.push_back("NO");
		v.clear();
	}
	for(int i=0;i<t;i++)
	{
		cout<<result[i]<<endl;
	}
	return 0;
}
