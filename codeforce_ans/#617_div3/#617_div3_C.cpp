#include <bits/stdc++.h>

using namespace std;

#define MAX 200000

int main(void)
{
	int t;
	scanf("%d",&t);
	vector<pair<int,int>> v;
	for(int i=0;i<t;i++)
	{
		int len;
		scanf("%d",&len);
		map<pair<int,int>,int> m;
		int x=0,y=0;char c;
		m.insert(make_pair(make_pair(0,0),0));
		pair<int,int> result=make_pair(0,MAX);
		for(int j=0;j<len;j++)
		{
			scanf(" %c",&c);
			switch(c)
			{
			case 'L':
				x-=1;
				break;
			case 'R':
				x+=1;
				break;
			case 'U':
				y+=1;
				break;
			case 'D':
				y-=1;
				break;	
			}
			map<pair<int,int>,int>::iterator f=m.find(make_pair(x,y));
			if(f==m.end())
				m.insert(make_pair(make_pair(x,y),j+1));
			else
			{
				result=((result.second-result.first) > (j+1-(f->second+1))) ? make_pair(f->second+1,j+1) : result;
				m.erase(make_pair(x,y));
				m.insert(make_pair(make_pair(x,y),j+1));
			}
		}
		v.push_back(result);
	}
	for(int i=0;i<t;i++)
	{
		if(v[i].second-v[i].first==MAX) cout<<-1<<endl;
		else cout<<v[i].first<<" "<<v[i].second<<endl;
	}
	return 0;
}
