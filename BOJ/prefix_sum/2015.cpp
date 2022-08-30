#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

//복습!

vector<int> nums;
vector<int> sumTo; // sumTo[i]=0~i까지의 총합

int subSum(int i, int j)
{
    if (i > j)
        return subSum(j, i);
    if (i == 0)
        return sumTo[j];
    return sumTo[j] - sumTo[i - 1];
}

void makePresum()
{
    sumTo.resize(nums.size());
    sumTo[0] = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
        sumTo[i] = sumTo[i - 1] + nums[i];
    }
}

// i~j의 합은 sumTo[j]-sumTo[i-1]이다
//따라서 sumTo[j]-sumTo[i-1]=sum이므로 이를 이용하면 , sumTo[j]-sum=sumTo[i-1] (j>i) 이고
//따라서 sumTo[j]-sum과 같은 sumTo 배열의 값을 찾으면 된다.
long long countSum(int sum)
{
    makePresum();
    int n = nums.size();
    long long ret = 0;
    map<int, long long> count;
    for (int i = 0; i < n; i++)
    {
        if (sumTo[i] == sum)
            ret++;
        ret += count[sumTo[i] - sum];
        count[sumTo[i]]++;
    }
    return ret;
}

int main()
{
    int numCount, sum;
    cin >> numCount >> sum;
    nums.resize(numCount);
    for (int i = 0; i < numCount; i++)
    {
        scanf("%d", &nums[i]);
    }
    cout << countSum(sum) << "\n";
    return 0;
}