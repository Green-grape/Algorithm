/*
달리기와 자전거로 총 t킬로미터를 달리는 철인 2종 경기를 개최함 참가자 n명 번호(0~n-1)이며 각 참가자의 달리기 속도와 자전거 속도가 주어진다.
이때 n-1번째 참가자가 주최측에 뇌물을 줘서 자신이 가장 유리하도록 달리기와 자전거 경주의 길이를 조절해 달라고 요청 했을때
달리기 경주의 길이 r과 자전거 경주의 길이 t-r은?
*/
#include <vector>

double t;
int n;
std::vector<double> runVelocity;
std::vector<double> cycleVelocity;

double time(int i, double r){
    double cycle=t-r;
    return r/runVelocity[i]+cycle/cycleVelocity[i];
}

double timeDif(double r){
    double cheater=time(n-1,r);
    double fastestOther=time(0,r);
    for(int i=1;i<n-1;i++) fastestOther=std::min(fastestOther,time(i,r));
    return fastestOther-cheater;
}

double getMaxTimeDif(){
    double left=0,right=t;
    for(int it=0;it<100;it++){
        double leftTernary=(left*2+right)/3;
        double rightTernary=(left+right*2)/3;
        if(timeDif(leftTernary)>timeDif(rightTernary)){
            right=rightTernary;
        }else{
            left=leftTernary;
        }
    }
    return (left+right)/2;
}