#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int n;
	scanf("%d",&n);
	int x,y;
	map<pair<int,int>,pair<int,int>> m;
	vector<pair<int,int>> v;
	double total_x=0,total_y=0;
	if(n%2!=0) 
	{
		cout<<"NO"<<endl;
		return 0;
	}
	for(int i=0;i<n;i++)
	{
		scanf("%d %d",&x,&y);
		m.insert(make_pair(make_pair(x,y),make_pair(x,y)));
		v.push_back(make_pair(x,y));
		total_x+=x;
		total_y+=y;
	}
	total_x/=n;
	total_y/=n;
	int check=1;
	if(2*total_x-int(2*total_x)!=0 || 2*total_y-int(2*total_y)!=0) check=0;
	for(int i=0;i<n/2;i++)
	{
		int find_x=2*total_x-v[i].first;
		int find_y=2*total_y-v[i].second;
		if(m.find(make_pair(find_x,find_y))==m.end())
		{
			check=0;
			break;
		}
	}
	if(check) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}
