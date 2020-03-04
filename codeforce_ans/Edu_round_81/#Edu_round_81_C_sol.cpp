#include <bits/stdc++.h>

using namespace std;

#define MAX 100001
#define INF 200000

int main(void)
{
	int t1;
	int **nxt=new int*[MAX];
	for(int i=0;i<MAX;i++)
	{
		nxt[i]=new int[26];
	}
	cin >> t1;
	for(int i=0;i<t1;i++)
	{
		string s,t;
		cin >> s>>t;
		for(int j=0;j<s.size()+1;j++)
		{
			for(int k=0;k<26;k++)
			{
				nxt[j][k]=INF;
			}
		}
		for(int j=s.size()-1;j>=0;j--)
		{
			for(int k=0;k<26;k++)
			{
				nxt[j][k]=nxt[j+1][k];
			}
			nxt[j][s[j]-'a']=j;
		}
		int res=1,pos=0;
		for(int j=0;j<t.size();j++)
		{
			
			if(pos==s.size())
			{
				pos=0;
				res++;
			}
			if(nxt[pos][t[j]-'a']==INF)
			{
				pos=0;
				res++;
				if(nxt[0][t[j]-'a']==INF)
				{
					res=-1;
					break;
				}	
			}
			pos=nxt[pos][t[j]-'a']+1;
		}
		cout<<res<<endl;
	}
	for(int i=0;i<MAX;i++)
	{
		delete[] nxt[i];
	}
	delete[] nxt;
	return 0;
}
