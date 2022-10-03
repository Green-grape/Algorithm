#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<char, int> charSeq;

bool cmp(const string &s1, const string &s2)
{ // natural sort 비교
    vector<pair<string, int>> s1Units, s2Units;
    string temp = "";

    //단위로 쪼개기
    for (int i = 0; i < s1.length(); i++)
    {
        if ('0' <= s1[i] && s1[i] <= '9')
        {
            temp += s1[i];
        }
        else
        {
            if (temp.length() != 0)
            {
                s1Units.push_back(make_pair(temp, 1));
                temp = "";
            }
            s1Units.push_back(make_pair(string(1, s1[i]), 0));
        }
    }
    if (temp.length() != 0)
    {
        s1Units.push_back(make_pair(temp, 1));
        temp = "";
    }
    for (int i = 0; i < s2.length(); i++)
    {
        if ('0' <= s2[i] && s2[i] <= '9')
        {
            temp += s2[i];
        }
        else
        {
            if (temp.length() != 0)
            {
                s2Units.push_back(make_pair(temp, 1));
                temp = "";
            }
            s2Units.push_back(make_pair(string(1, s2[i]), 0));
        }
    }
    if (temp.length() != 0)
    {
        s2Units.push_back(make_pair(temp, 1));
        temp = "";
    }

    //하나씩 비교
    for (int cur = 0; cur < s1Units.size() && cur < s2Units.size(); cur++)
    {
        pair<string, int> u1 = s1Units[cur], u2 = s2Units[cur];
        if (u1.second != u2.second)
            return u1.second > u2.second;
        if (u1.first.compare(u2.first) == 0)
            continue;
        if (u1.second == 1)
        {
            bool u1Added = false, u2Added = false;
            if (u1.first.length() != u2.first.length())
            {
                if (u1.first.length() < u2.first.length())
                {
                    u1.first = string(u2.first.length() - u1.first.length(), '0') + u1.first;
                    u1Added = true;
                }
                else
                {
                    u2.first = string(u1.first.length() - u2.first.length(), '0') + u2.first;
                    u2Added = true;
                }
            }
            if (u1.first.compare(u2.first) == 0)
            {
                if (u1Added)
                    return true;
                else if (u2Added)
                    return false;
            }
            return u1.first < u2.first;
        }
        else
        {
            return charSeq[u1.first[0]] < charSeq[u2.first[0]];
        }
    }
    return s1Units.size() < s2Units.size();
}

void solve(vector<string> &strings)
{
    char curUp = 'A', curLow = 'a';
    for (int i = 0; i < 26; i++)
    {
        charSeq[curUp++] = charSeq.size();
        charSeq[curLow++] = charSeq.size();
    }
    sort(strings.begin(), strings.end(), cmp);
}

int main()
{
    int n;
    cin >> n;
    char s[101];
    vector<string> strings;
    for (int i = 0; i < n; i++)
    {
        scanf("%s", s);
        strings.push_back(string(s));
    }
    solve(strings);
    for (int i = 0; i < n; i++)
    {
        cout << strings[i] << "\n";
    }
    return 0;
}
