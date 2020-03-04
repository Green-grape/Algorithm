#include <bits/stdc++.h>

#define mp(x,y) make_pair((x),(y))

using namespace std;

int main(void)
{
	long long x0,y0,bx,by,xs,ys,t;
	int ax,ay;
	scanf("%lld %lld %d %d %lld %lld",&x0,&y0,&ax,&ay,&bx,&by);
	scanf("%lld %lld %lld",&xs,&ys,&t);
	vector<pair<long long,long long>> n;
	long long x_p=x0,y_p=y0;
	
	while(1)
	{
		if(x_p+y_p-xs-ys>t) break;
		n.push_back(mp(x_p,y_p));
		x_p=ax*x_p+bx;
		y_p=ay*y_p+by;
	}
	int ans=0,len=n.size();
	for(int i=0;i<len;i++)
	{
		int left=i-1,right=i+1;
		long long t_c=abs(n[i].first-xs)+abs(n[i].second-ys),t_l=t+1,t_r=t+1;
		if(t_c>t) continue;
		if(left>=0) t_l=abs(n[left].first-n[i].first)+abs(n[left].second-n[i].second);
		if(right<len) t_r=abs(n[right].first-n[i].first)+abs(n[right].second-n[i].second);
		int temp_ans=1;
		while(1)
		{
			if(t_c+t_l>t && t_c+t_r>t) break;
			
			if(t_l>t_r) 
			{
				t_c+=t_r;
				t_l+=t_r;
				if(right==len-1) t_r=t+1;
				else t_r=abs(n[right].first-n[right+1].first)+abs(n[right].second-n[right+1].second);
				right++;
				temp_ans++;
			}
			else if(t_l<t_r)
			{
				t_c+=t_l;
				t_r+=t_l;
				if(left==0) t_l=t+1;
				else t_l=abs(n[left].first-n[left-1].first)+abs(n[left].second-n[left-1].second);
				left--;
				temp_ans++;
			}
			else
			{
				if(left==0 || right==len-1) temp_ans++;
				while(t_l==t_r && left>0 && right<len-1)
				{
					t_r+=abs(n[right].first-n[right+1].first)+abs(n[right].second-n[right+1].second);
					t_l+=abs(n[left].first-n[left-1].first)+abs(n[left].second-n[left-1].second);
					left--;
					right++;
					temp_ans++;
				}
				if(left==0) t_l=t+1;
				if(right==len-1) t_r=t+1;
			}
		}
		ans=max(ans,temp_ans);
	}
	cout<<ans<<endl;
	return 0;
}
