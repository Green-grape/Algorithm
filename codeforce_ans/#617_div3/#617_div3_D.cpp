#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int n,a,b,k;
	scanf("%d %d %d %d",&n,&a,&b,&k);
	vector<int> remain;
	int hp,point=0;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&hp);
		hp%=(a+b);
		if(1<=hp && hp<=a) 
		{
			remain.push_back(0);
		}
		else
		{
			if(hp==0) hp=a+b;
			if(hp%a==0) hp=hp/a-1;
			else hp/=a;
			remain.push_back(hp);
		}
	}
	sort(remain.begin(),remain.end());
	for(int i=0;i<n;i++)
	{
		if(remain[i]==0) point++;
		else
		{
			k-=remain[i];
			if(k<0) break;
			point++;
		}
	}
	cout<<point<<endl;
	return 0;
}
