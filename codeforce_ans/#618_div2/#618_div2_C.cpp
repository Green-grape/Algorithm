#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int n;
	scanf("%d",&n);
	vector<int> result;
	int num;
	int* pref=new int[n];
	int* suff=new int[n];
	pref[0]=0;suff[n-1]=0;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&num);
		result.push_back(num);
		if(i!=0) pref[i]=pref[i-1]|result[i-1];
	}
	for(int i=n-1;i>0;i--)
	{
		suff[i-1]=suff[i]|result[i];
	}
	int max=0,idx=0;
	for(int i=0;i<n;i++)
	{
		int temp=result[i]&(~(pref[i]|suff[i]));
		if(temp>=max)
		{
			max=temp;
			idx=i;
		}
	}
	int temp=result[0];
	result[0]=result[idx];
	result[idx]=temp;
	for(int i=0;i<n;i++)
	{
		printf("%d ",result[i]);
	}
	delete[] pref;
	delete[] suff;
	return 0;
}

