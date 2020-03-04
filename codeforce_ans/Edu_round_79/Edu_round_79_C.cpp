#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	cin >> t;
	for(int i=0;i<t;i++)
	{
		int n,m;
		cin >> n>>m;
		vector<int> pos(n+1);
		vector<pair<int,int>> li(m,make_pair(-1,0));
		for(int j=0;j<n;j++)
		{
			int num;
			cin >> num;
			pos[num]=j;
		}
		int ins_deg=0;
		for(int j=0;j<m;j++) 
		{
			cin>>li[j].first;
			if(j!=0) 
			{
				ins_deg=max(ins_deg,pos[li[j-1].first]);
				li[j].second=ins_deg;
			}
		}
		long long total=0;
		for(int j=0;j<m;j++)
		{
			if(pos[li[j].first]>li[j].second)
			{
				total+=2*(pos[li[j].first]-j)+1;
			}
			else
			{
				total+=1;
			}
		}
		cout<<total<<endl;
	}
	return 0;	
}
