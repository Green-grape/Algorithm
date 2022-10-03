#include <iostream>
#include <vector>

using namespace std;

// arr[i]=str[0~i]의 접두사도 되고 접미사도 되는 문자열의 최대 길이
vector<int> makePi(const string &str)
{
    vector<int> ret(str.length());
    int matched = 0;
    for (int i = 1; i < str.length(); i++) //시작이 1임에 주의하자!
    {
        while (matched > 0 && str[i] != str[matched]) //불일치
        {
            matched = ret[matched - 1];
        }
        if (str[i] == str[matched])
        {
            ret[i] = ++matched;
        }
    }
    return ret;
}

bool isSubStr(const string &str, const string &substr)
{
    vector<int> pi = makePi(str);
    int matched = 0;
    vector<int> ret;
    for (int i = 0; i < str.length(); i++)
    {
        while (matched > 0 && str[i] != substr[matched]) //매칭된 개수 찾기
        {
            matched = pi[matched - 1];
        }
        if (str[i] == substr[matched])
        {
            if (matched == substr.length() - 1) //전부 매칭 된 경우
            {
                ret.push_back(i - substr.length() + 1);
                matched = pi[matched]; //매칭된 크기만큼 건너뜀
            }
            else
            {
                matched++;
            }
        }
    }
    return ret.size() != 0;
}

// str.length()<=1000000, only lower case
int main()
{
    string str, substr;
    cin >> str >> substr;
    cout << isSubStr(str, substr) << "\n";
    return 0;
}