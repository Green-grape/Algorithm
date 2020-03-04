#include <bits/stdc++.h>

using namespace std;

void adj_print_l(vector<pair<int,int>>*,int,int*);
void adj_print_r(vector<pair<int,int>>*,int,int*);

int main(void)
{
	int t;
	cin >> t;
	for(int i=0;i<t;i++)
	{
		string s;
		cin >> s;
		int len=s.size();
		int c[26]{0,};
		int p_c[26]{0,};
		c[s[0]-'a']=1;
		vector<pair<int,int>> v(26,make_pair(-1,-1));
		bool check=true;
		for(int j=0;j<len-1;j++)
		{
			if(c[s[j+1]-'a']!=0)
			{
				if(v[s[j+1]-'a'].first!=s[j]-'a' && v[s[j+1]-'a'].second!=s[j]-'a')
				{
					cout<<"NO"<<endl;
					check=false;
					break;
				}
			}
			else
			{
				if(v[s[j]-'a'].first==-1) 
				{
					v[s[j]-'a'].first=s[j+1]-'a';
					v[s[j+1]-'a'].second=s[j]-'a';
				}
				else if(v[s[j]-'a'].second==-1)
				{
					v[s[j]-'a'].second=s[j+1]-'a';
					v[s[j+1]-'a'].first=s[j]-'a';
				}
				else
				{
					cout<<"NO"<<endl;
					check=false;
					break;
				}
				c[s[j+1]-'a']=1;
			}
		}
		if(check)
		{
			cout<<"YES"<<endl;
			adj_print_l(&v,s[0]-'a',p_c);
			adj_print_r(&v,s[0]-'a',p_c);
			for(int i=0;i<26;i++)
			{
				if(c[i]==0) printf("%c",i+'a');
			}
			cout<<endl;
		}
	}
	return 0;
}

void adj_print_l(vector<pair<int,int>> *v, int start,int* p)
{
	if((*v)[start].first==-1) 
	{
		printf("%c",start+'a');
		p[start]=1;
		return;
	}
	adj_print_l(v,(*v)[start].first,p);
	printf("%c",start+'a');
	p[start]=1;
}

void adj_print_r(vector<pair<int,int>> *v, int start,int* p)
{
	if((*v)[start].second==-1)
	{
		if(p[start]!=1) printf("%c",start+'a');
		return;
	}
	if(p[start]!=1) printf("%c",start+'a');
	adj_print_r(v,(*v)[start].second,p);
}
