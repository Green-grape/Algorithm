#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int n,q;
	cin >> n >> q;
	map<pair<int,int>,pair<int,int>> pro;
	vector<vector<bool>> l(3,vector<bool>(n+1,1));
	for(int i=0;i<q;i++)
	{
		int x,y;
		cin >> x >>y;
		if(!l[x][y]) 
		{
			if(x==1) 
			{
				if(pro.find(make_pair(y,y-1))!=pro.end()) pro.erase(pro.find(make_pair(y,y-1)));
				if(pro.find(make_pair(y,y+1))!=pro.end()) pro.erase(pro.find(make_pair(y,y+1)));
			}
			if(x==2)
			{
				if(pro.find(make_pair(y-1,y))!=pro.end()) pro.erase(pro.find(make_pair(y-1,y)));
				if(pro.find(make_pair(y+1,y))!=pro.end()) pro.erase(pro.find(make_pair(y+1,y)));
			}
			if(pro.find(make_pair(y,y))!=pro.end()) pro.erase(pro.find(make_pair(y,y)));
		}
		else
		{
			if(x==1)
			{
				if(y!=1 && l[2][y-1]==0) pro.insert(make_pair(make_pair(y,y-1),make_pair(y,y-1)));
				if(y!=n && l[2][y+1]==0) pro.insert(make_pair(make_pair(y,y+1),make_pair(y,y+1)));
				if(l[2][y]==0) pro.insert(make_pair(make_pair(y,y),make_pair(y,y)));
			}
			if(x==2)
			{
				if(y!=1 && l[1][y-1]==0) pro.insert(make_pair(make_pair(y-1,y),make_pair(y-1,y)));
				if(y!=n && l[1][y+1]==0) pro.insert(make_pair(make_pair(y+1,y),make_pair(y+1,y)));
				if(l[1][y]==0) pro.insert(make_pair(make_pair(y,y),make_pair(y,y)));
			}
		}
		if(pro.size()==0) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
		l[x][y]=!l[x][y];
	}
	return 0;
}
