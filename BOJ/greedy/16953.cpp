/*정수 A를 B로 바꾸려고 한다. 가능한 연산은 다음과 같은 두 가지이다.

2를 곱한다.
1을 수의 가장 오른쪽에 추가한다. 
A를 B로 바꾸는데 필요한 연산의 최솟값을 구해보자.
*/

#include <iostream>

using namespace std;

int main(){
    int cur, target;
    cin >> target>> cur;
    int ret=1;
    while(cur!=target){
        if(cur%10==1){
            cur/=10;
        }
        else if(cur%2==0){
            cur/=2;
        }
        else{
            ret=-1;
            break;
        }
        if(cur<target){
            ret=-1;
            break;
        }
        ret++;
    }
    cout << ret <<"\n";
    return 0;
}