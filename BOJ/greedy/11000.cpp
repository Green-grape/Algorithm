/*
Si에 시작해서 Ti에 끝나는 N개의 수업이 주어지는데, 최소의 강의실을 사용해서 모든 수업을 가능하게 해야 한다. 
참고로, 수업이 끝난 직후에 다음 수업을 시작할 수 있다. (즉, Ti ≤ Sj 일 경우 i 수업과 j 수업은 같이 들을 수 있다.)
이때 최소의 강의실의 수는?
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

int getMinRoomCount(vector<pair<int,int>>& lectureTimes){
    sort(lectureTimes.begin(),lectureTimes.end());
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i=0;i<lectureTimes.size();i++){
        int start=lectureTimes[i].first,end=lectureTimes[i].second;
        if(pq.empty()) pq.push(end);
        else{
            int mostFastEnd=pq.top();
            if(mostFastEnd<=start){//기존 강의실 재활용 가능
                pq.pop();
            }
            pq.push(end);
        }
    }
    return pq.size();
}

int main(){
    int lectureTimeCount;
    cin >> lectureTimeCount;
    vector<pair<int,int>> lectureTimes;
    for(int i=0;i<lectureTimeCount;i++){
        int start, end;
        cin >> start >> end;
        lectureTimes.push_back(make_pair(start,end));
    }
    cout << getMinRoomCount(lectureTimes) <<"\n";
    return 0;
}