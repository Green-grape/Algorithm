#include <bits/stdc++.h>

using namespace std;

int closest(vector<int>,vector<int>,int,int);

int main(void)
{
	int t;
	cin >> t;
	for(int i=0;i<t;i++)
	{
		int n,s,k;
		cin >> n >> s >>k;
		vector<int> u(1002,1);
		vector<int> d(1002,1);
		for(int j=0;j<k;j++)
		{
			int num;
			cin >> num;
			if(num>=s && num-s<1002) 
				u[num-s]=0;
			if(num<=s && s-num<1002) 
				d[s-num]=0;
		}
		cout<<closest(u,d,s,n)<<endl;
	}
	return 0;
}

int closest(vector<int> u,vector<int> d,int s,int n)
{
	int idx=0;
	while(1)
	{
		if(u[idx]!=0 && idx<=n-s) return idx;
		if(d[idx]!=0 && idx<=s-1) return idx;
		idx++;
	}
}
