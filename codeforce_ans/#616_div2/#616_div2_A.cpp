#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	int s_len;
	string s;
	scanf("%d",&t);
	vector<int> v;
	vector<vector<int>> result;
	for(int i=0;i<t;i++)
	{
		scanf("%d",&s_len);
		v.resize(s_len);
		int total=0,odd_idx=-1,check=0;
		cin >> s;
		for(int j=0;j<s_len;j++)
		{
			v[j]=s[j]-48;
			if(v[j]%2!=0 && check==0)
			{
				odd_idx=j;
				check=1;
			}
			total+=v[j];
		}
		int idx=-1;
		for(int j=s_len-1;j>=0;j--)
		{
			if(v[j]%2==0) 
			{
				total-=v[j];
				v[j]=-1;
			}
			else
			{
				idx=j;
				break;
			}
		}
		if(total%2==0 && idx!=-1 ) result.push_back(v);
		else if(total%2!=0) 
		{
			if(odd_idx<idx) 
			{
				v[odd_idx]=-1;
				result.push_back(v);
			}
			else result.push_back(vector<int>(1,-1));
		}
		else result.push_back(vector<int>(1,-1));
		v.clear();
	}
	for(int i=0;i<t;i++)
	{
		int len=result[i].size(),check=0,zero_check=0;
		for(int j=0;j<len;j++)
		{
			if(result[i][j]!=0 && result[i][j]!=-1) zero_check=1;
			if(result[i][j]!=-1 && zero_check!=0)
			{
				cout<<result[i][j];
				check=1;
			}
		}
		if(!check) cout<<-1;
		cout<<endl;
	}
	return 0;
}
