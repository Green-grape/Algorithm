#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> a;
int n,m;
int a1=0,a2=0;
bool can(int);

int main(void)
{
	scanf("%d %d",&n,&m);
	a.resize(n,vector<int>(m));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	int lf=0;
	int rg=int(1e9)+61;
	while(rg-lf>1) //binary search
	{
		int mid=(rg+lf)/2;
		if(can(mid)) lf=mid;
		else rg=mid;
	}
	cout<<a1+1<<" "<<a2+1<<endl;
	return 0;
}

bool can(int mid)
{
	vector<int> M(1<<m,-1); // m-bit mask;
	for(int i=0;i<n;i++)
	{
		int cur=0;
		for(int j=0;j<m;j++)
		{
			if(a[i][j]>=mid) cur=(cur ^ (1<<j)); //on
		}
		M[cur]=i; //only 2*m distinct arrays 
	}
	for(int i=0;i<(1<<m);i++)
	{
		for(int j=i;j<(1<<m);j++)
		{
			if(M[i]!=-1 && M[j]!=-1 && (i|j)==(1<<m)-1)
			{
				a1=M[i];
				a2=M[j];
				return true;
			}
		}
	}
	return false;
}
