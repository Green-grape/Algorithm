#include <bits/stdc++.h>

using namespace std;

#define INF 10000000000

int make_heap_tree(int,int,int,int*,vector<int>);
int range_min(int,int,int,int,int,int*,vector<int>);

int main(void)
{
	int t;
	scanf("%d",&t);
	vector<int> result;
	for(int i=0;i<t;i++)
	{
		int n,m,k;
		scanf("%d %d %d",&n,&m,&k);
		int mind_control=min(m-1,k);
		vector<int> ma;
		vector<int> nums;
		for(int j=0;j<n;j++)
		{
			int num;
			scanf("%d",&num);
			nums.push_back(num);
		}
		for(int j=0;j<m;j++)
		{
			ma.push_back(max(nums[j],nums[j+n-m]));
		}
		int* tree=new int[ma.size()*4];
		make_heap_tree(0,ma.size()-1,0,tree,ma);
		int temp_result=0;
		for(int j=0;j<=mind_control;j++)
		{
			temp_result=max(temp_result,range_min(0,ma.size()-1,0,j,j+m-1-mind_control,tree,ma));
		}
		result.push_back(temp_result);
		delete[] tree;
	}
	for(int i=0;i<t;i++)
	{
		cout<<result[i]<<endl;
	}
	return 0;
}

int make_heap_tree(int start,int end,int node,int* tree,vector<int> a)
{
	if(start==end) return tree[node]=a[start];
	int mid=(start+end)/2;
	return tree[node]=min(make_heap_tree(start,mid,node*2+1,tree,a),make_heap_tree(mid+1,end,2*node+2,tree,a));
}

int range_min(int start,int end,int node,int left,int right,int* tree, vector<int> a)
{
	if(end<left || right<start) return INF;
	else if(left<=start && end<=right) return tree[node];
	int mid=(start+end)/2;
	return min(range_min(start,mid,node*2+1,left,right,tree,a),range_min(mid+1,end,node*2+2,left,right,tree,a));
}
