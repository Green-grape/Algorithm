/*
지민이는 항구에서 일한다. 그리고 화물을 배에 실어야 한다. 모든 화물은 박스에 안에 넣어져 있다. 
항구에는 크레인이 N대 있고, 1분에 박스를 하나씩 배에 실을 수 있다. 모든 크레인은 동시에 움직인다.
각 크레인은 무게 제한이 있다. 
이 무게 제한보다 무거운 박스는 크레인으로 움직일 수 없다. 
모든 박스를 배로 옮기는데 드는 시간의 최솟값을 구하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getMinTimeToMove(vector<int>& crains, vector<int>& goods){
    sort(crains.begin(),crains.end());
    sort(goods.begin(), goods.end());
    if(crains[crains.size()-1]<goods[goods.size()-1]) return -1; //옮기는게 불가능한 경우
    vector<bool> isMoved(goods.size(),false);
    int ret=0, movedCount=0;;
    while(true){
        int i=goods.size()-1;
        for(int j=crains.size()-1;j>=0;j--){
            while(i>=0){
                if(!isMoved[i] && crains[j]>=goods[i]){
                    isMoved[i]=true;
                    movedCount++;
                    i--;
                    break;
                }
                i--;
            }
        }
        ret++;
        if(movedCount==isMoved.size()) break;
    }
    return ret;
}

int main(){
    int crainCount, goodCount;
    cin >> crainCount;
    vector<int> crains(crainCount);
    for(int i=0;i<crainCount;i++) cin >> crains[i];
    cin  >> goodCount;
    vector<int> goods(goodCount);
    for(int i=0;i<goodCount;i++) cin >> goods[i];
    cout << getMinTimeToMove(crains, goods) <<"\n";
    return 0;
}