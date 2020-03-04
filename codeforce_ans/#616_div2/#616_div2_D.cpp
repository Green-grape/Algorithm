#include <bits/stdc++.h>

using namespace std;

bool check_ir(int,int,int[][26],string);

#define MAX 200000

int main(void)
{
	int t;
	string s;
	cin >>s>>t;
	int len=s.length();
	int sum_a[MAX][26];
	sum_a[0][s[0]-'a']++;
	for(int i=1;i<len;i++)
	{
		for(int j=0;j<26;j++)
		{
			sum_a[i][j]=sum_a[i-1][j];
		}
		sum_a[i][s[i]-'a']++;
	}
	vector<string> result;
	for(int i=0;i<t;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		bool check=check_ir(x-1,y-1,sum_a,s);
		if(check) result.push_back("YES");
		else result.push_back("NO");
	}
	for(int i=0;i<t;i++)
	{
		cout<<result[i]<<endl;
	}
	return 0;
}

bool check_ir(int x,int y,int sum_a[][26],string s)
{
	if(x==y) return true;
	bool check=(s[x]==s[y])? true:false;
	if(!check) return true;
	else
	{
		int cnt=0;
		for(int i=0;i<26;i++)
		{
			cnt+=((sum_a[y][i]-sum_a[x][i])>0 ? 1:0);
		}
		if(cnt>=3) return true;
		else return false;
	}
}
	
	
	
