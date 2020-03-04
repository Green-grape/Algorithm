#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int l;
	string s;
	cin >> l >> s;
	bool* ori_cor=new bool[l]{0,};
	bool* cha_cor=new bool[l]{0,};
	bool check=1;
	for(int i=1;i<l;i++)
	{
		if(s[i-1]<=s[i])
		{
			cha_cor[i]=cha_cor[i-1];
			ori_cor[i]=cha_cor[i-1];
		}
		else
		{
			cha_cor[i]=!cha_cor[i-1];
			ori_cor[i]=!cha_cor[i-1];
			int j=i;
			while(j>0 && cha_cor[j-1]!=cha_cor[j] && s[j-1]>s[j])
			{
				swap(cha_cor[j-1],cha_cor[j]);
				swap(s[j-1],s[j]);
				j--;
			}
			if(s[j-1]>s[j])
			{
				cout<<"NO"<<endl;
				break;
				check=0;
			}
		}	
	}
	if(check)
	{
		cout<<"YES"<<endl;
		for(int i=0;i<l;i++)
		{
			cout<<ori_cor[i];
		}
	}
	delete[] ori_cor;
	delete[] cha_cor;
	return 0;
}
