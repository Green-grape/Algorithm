#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t1;
	int c[26];
	cin >>t1;
	for(int i=0;i<t1;i++)
	{
		string s,t;
		cin>>s>>t;
		int len=s.size();
		vector<int> a[26];
		fill(c,c+26,0);
		for(int j=0;j<len;j++)
		{
			a[s[j]-'a'].push_back(j);
		}
		int t_len=t.size();
		bool check=false;
		vector<int> d;
		int cnt=1;
		for(int j=0;j<t_len;j++)
		{
			int idx=t[j]-'a';
			if(a[idx].size()==0) {
				check=true;
				cout<<-1<<endl;
				break;
			}
			if(c[idx]>=a[idx].size())
			{
				fill(c,c+26,0);
				cnt++;
			}
			else if(j!=0 && a[idx][c[idx]]<=d[j-1])
			{
				bool y=false;
				for(int k=c[idx]+1;k<a[idx].size();k++)
				{
					if(a[idx][k]>=d[j-1]) 
					{
						c[idx]=k;
						y=true;
						break;
					}
				}
				if(!y)
				{
					fill(c,c+26,0);
					cnt++;
				}
			}
			d.push_back(a[idx][c[idx]]);
			c[idx]++;
		}
		if(!check)
		{
			cout<<cnt<<endl;
		}
	}
	return 0;
}
