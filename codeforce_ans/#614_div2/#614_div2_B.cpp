#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int n;
	cin >> n;
	double result=0;
	for(int i=1;i<=n;i++)
	{
		result+=(1.0)/i;
	}
	printf("%.9lf",result);
	return 0;
}
