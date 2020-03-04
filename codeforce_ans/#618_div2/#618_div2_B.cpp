#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int t;
	scanf("%d",&t);
	vector<int> nums;
	vector<int> result;
	for(int i=0;i<t;i++)
	{
		int n;
		scanf("%d",&n);
		int stu;
		for(int j=0;j<2*n;j++)
		{
			scanf("%d",&stu);
			nums.push_back(stu);	
		}
		sort(nums.begin(),nums.end());
		result.push_back(nums[n]-nums[n-1]);
		nums.clear();
	}
	for(int i=0;i<t;i++)
	{
		cout<<result[i]<<endl;
	}
	return 0;
}
