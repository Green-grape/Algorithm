#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	cin >> t;
	for(int i=0;i<t;i++)
	{
		string s;
		cin >> s;
		int tot=0,cnt=0;
		bool check=false;
		for(int j=0;j<s.size();j++)
		{
			if(check==false && s[j]=='1')
			{
				check=true;
			}
			if(check)
			{
				if(s[j]=='0') cnt++;
				else
				{
					tot+=cnt;
					cnt=0;
				}
			}
		}
		cout<<tot<<endl;
	}
	return 0;
}
