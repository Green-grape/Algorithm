#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	cin >>t;
	vector<int> result;
	for(int i=0;i<t;i++)
	{
		int n,x;
		string s;
		cin >> n >>x>>s;
		int cnt0=(int)count(s.begin(),s.end(),'0');
		int tot=cnt0-(n-cnt0);
		int bal=0,ans=0;
		bool Noans=false;
		for(int j=0;j<n;j++) 
		{
			if(tot==0 && bal==x) Noans=true;
			else if(tot!=0 && abs(x-bal)%abs(tot)==0 && (x-bal)/tot>=0) ans++;
			
			if(s[j]=='0') bal++;
			else bal--;
		}
		if(Noans) result.push_back(-1);
		else result.push_back(ans);
	}
	for(int i=0;i<t;i++)
	{
		cout<<result[i]<<endl;
	}
	return 0;
}
