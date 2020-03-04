#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int n;
	string s;
	cin >> n>> s;
	
	vector<int> dp(n,1);
	vector<int> max_alpha(26,0);
	int res=0;
	for(int i=0;i<n;i++)
	{
		for(int c=25;c>s[i]-'a';c--)
		{
			dp[i]=max(dp[i],max_alpha[c]+1);
		}
		max_alpha[s[i]-'a']=max(dp[i],max_alpha[s[i]-'a']);
		res=max(res,max_alpha[s[i]-'a']);
	}
	cout<<res<<endl;
	for(int i=0;i<n;i++)
		cout<<dp[i]<<" ";
	return 0;
}
