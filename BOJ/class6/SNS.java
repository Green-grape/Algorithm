import java.util.*;
import java.lang.*;

public class SNS{
    final int IS_EARLY=1;
    ArrayList<ArrayList<Integer>> adj;
    int[][] cache;
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int vertexCnt=sc.nextInt();
        ArrayList<ArrayList<Integer>> adj=new ArrayList<ArrayList<Integer>>(vertexCnt+1);
        for(int i=0;i<vertexCnt+1;i++) adj.add(new ArrayList<Integer>());
        for(int i=0;i<vertexCnt-1;i++){
            Integer v1=sc.nextInt(), v2=sc.nextInt();
            adj.get(v1).add(v2);
            adj.get(v2).add(v1);
        }
        SNS sns=new SNS(adj);
        System.out.println(Math.min(sns.getMinEarlyCnt(1,0,0),sns.getMinEarlyCnt(1,1,0)));
        sc.close();
    }
    SNS(ArrayList<ArrayList<Integer>> adj){
        this.adj=adj;
        cache=new int[adj.size()][2];
    }
    int getMinEarlyCnt(int cur, int curStatus, int prev){
        if(cache[cur][curStatus]!=0) return cache[cur][curStatus];
        int ret=0;
        if(curStatus!=IS_EARLY){
            for(int i=0;i<adj.get(cur).size();i++){
                int next=adj.get(cur).get(i);
                if(next==prev) continue;
                ret+=getMinEarlyCnt(next, IS_EARLY,cur);
            }
        }else{
            ret=1;
            for(int i=0;i<adj.get(cur).size();i++){
                int next=adj.get(cur).get(i);
                if(next==prev) continue;
                ret+=Math.min(getMinEarlyCnt(next,0,cur),getMinEarlyCnt(next, IS_EARLY,cur));
            }
        }
        cache[cur][curStatus]=ret;
        return ret;
    }
}