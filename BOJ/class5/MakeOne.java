import java.util.Scanner;
import java.util.ArrayList;

public class MakeOne{
    Pair[] next;
    final int INF=987654321;
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();
        MakeOne makeOne=new MakeOne(n);
        int minCal=makeOne.getMinCal(n).first;
        ArrayList<Integer> ret=new ArrayList<Integer>();
        makeOne.reconstruct(n,ret);
        System.out.println(minCal);
        for(int i=0;i<ret.size();i++){
            System.out.print(ret.get(i)+" ");
        }
        sc.close();
    }
    MakeOne(int n){
        next=new Pair[n+1];
        for(int i=1;i<n+1;i++){
            next[i]=new Pair(-1,-1);
        }
    }
    Pair getMinCal(int cur){
        if(cur==1) return new Pair();
        if(next[cur].first!=-1) return next[cur];
        int retCal=INF, retNext=0;
        if((cur%3)==0){
            int cand=1+getMinCal(cur/3).first;
            if(cand<retCal){
                retCal=cand;
                retNext=cur/3;
            }
        }
        if((cur%2)==0){
            int cand=1+getMinCal(cur/2).first;
            if(cand<retCal){
                retCal=cand;
                retNext=cur/2;
            }
        }
        int cand=1+getMinCal(cur-1).first;
        if(cand<retCal){
            retCal=cand;
            retNext=cur-1;
        }
        //System.out.println(cur+" "+retCal+" "+retNext);
        next[cur].first=retCal;
        next[cur].second=retNext;
        return next[cur];
    }
    void reconstruct(int cur, ArrayList<Integer> arr){
        if(cur<1) return;
        arr.add(cur);
        reconstruct(next[cur].second,arr);
    }
}

class Pair{
    int first;
    int second;
    Pair(){
        this.first=0;
        this.second=0;
    }
    Pair(int a,int b){
        this.first=a;
        this.second=b;
    }
}