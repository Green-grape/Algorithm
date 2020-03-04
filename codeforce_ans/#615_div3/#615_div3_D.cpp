#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int q,x;
	scanf("%d %d",&q,&x);
	set<pair<int,int>> s;
	vector<int> mods(x);
	for(int i=0;i<x;i++)
	{
		s.insert(make_pair(mods[i],i));
	}
	int cur;
	for(int i=0;i<q;i++)
	{
		cin >>cur;
		cur%=x;
		s.erase(make_pair(mods[cur],cur));
		mods[cur]++;
		s.insert(make_pair(mods[cur],cur));
		cout<<s.begin()->first*x+s.begin()->second<<endl;
	}
	return 0;
}
	



