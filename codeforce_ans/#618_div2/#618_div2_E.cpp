#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <deque>

using namespace std;

#define er 1e-10

typedef struct node
{
	double val;
	int cnt;
}node;

int main(void)
{
	int t;
	scanf("%d", &t);
	double* a = new double[t];
	int x;
	for (int i = 0; i < t; i++)
	{
		scanf("%d", &x);
		a[i] = x;
	}
	deque<node> Q;
	Q.push_back(node{ a[0],1 });
	for (int i = 1; i < t; i++)
	{
		int total = 1;
		double temp = a[i];
		while (!Q.empty() && temp < Q.back().val + er)
		{
			temp = (Q.back().val * Q.back().cnt + temp * total) / (total + Q.back().cnt);
			total += Q.back().cnt;
			Q.pop_back();
		}
		Q.push_back(node{ temp,total });
	}
	while (!Q.empty())
	{
		node t = Q.front();
		while (t.cnt--)
		{
			printf("%.9lf\n", t.val);
		}
		Q.pop_front();
	}
	delete[] a;
