#include <iostream>
#include <string>
#include <vector>

using namespace std;
bool areFriends[10][10]={false,};

int countPairing(bool paired[], int);

int main(){
    int testCount;
    int studentCount, studentPairCount;
    string pairString;
    cin >> testCount;
    for(int i=0;i<testCount;i++){
        cin >> studentCount >> studentPairCount;
        for(int j=0;j<studentPairCount;j++){
            int stu1, stu2;
            cin >> stu1 >> stu2;
            if(stu1>stu2){
                int temp=stu1;
                stu1=stu2;
                stu2=temp;
            }
            areFriends[stu1][stu2]=true;
        }
        bool paired[10]={false,};
        cout << "res: "<<countPairing(paired, studentCount)<<"\n";
        //initialize
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                areFriends[i][j]=false;
            }
        }
    }
    return 0;
}

int countPairing(bool paired[], int studentCount){
    //기저 체크
    int firstFree=-1;
    for(int i=0;i<studentCount;i++){
        if(!paired[i]){
            firstFree=i;
            break;
        }
    }
    if(firstFree==-1) return 1;

    int count=0;
    for(int pairWith=firstFree+1;pairWith<studentCount;pairWith++){
        if(!paired[firstFree] && !paired[pairWith] && areFriends[firstFree][pairWith]){
            paired[firstFree]=paired[pairWith]=true;
            count+=countPairing(paired, studentCount);
            paired[firstFree]=paired[pairWith]=false;
        }
    }
    return count;
}
