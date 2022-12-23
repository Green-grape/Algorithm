import java.util.Scanner;
import java.util.LinkedList;
import java.util.Queue;

//9328 BOJ
//같은 bfs라도 빨리 끝날수 있게 최적화

public class FindTreasure{
    char[][] board;
    boolean keys[];
    boolean isVisit[][];
    static final int[][] coord={
        {-1,0},{1,0},{0,1},{0,-1}
    };
    int getCount=0;
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int testcase=sc.nextInt();
        while(testcase>0){
            int h=sc.nextInt(), w=sc.nextInt();
            sc.nextLine();
            char[][] board=new char[h][];
            for(int i=0;i<h;i++){
                String row=sc.nextLine();
                board[i]=row.toCharArray();
            }
            String keys=sc.nextLine();
            if(keys.charAt(0)=='0') keys="";
            FindTreasure find=new FindTreasure(board, keys);
            System.out.println(find.getMaxTreasure());
            testcase--;
        }
        sc.close();
    }
    FindTreasure(char[][] board, String keys){
        this.board=board;
        this.keys=new boolean[26];
        this.isVisit=new boolean[board.length][board[0].length];
        for(int i=0;i<keys.length();i++){
            this.keys[keys.charAt(i)-'a']=true;
        }
    }
    boolean bfs(int startY, int startX){
        Queue<Pair> q=new LinkedList<Pair>();
        q.add(new Pair(startY,startX));
        isVisit[startY][startX]=true;
        while(!q.isEmpty()){
            Pair cur=q.poll();
            int y=cur.first, x=cur.second;
            for(int i=0;i<coord.length;i++){
                int nextY=y+coord[i][0], nextX=x+coord[i][1];
                if(nextY<0 || board.length<=nextY || nextX<0 || board[0].length<=nextX) continue;
                char next=board[nextY][nextX];
                if(next=='*' || isVisit[nextY][nextX]) continue;
                if('A'<=next && next<='Z'){
                    if(!keys[next-'A']) continue;
                    board[nextY][nextX]='.'; 
                }
                if('a'<=next && next<='z'){
                    if(!keys[next-'a']){
                        keys[next-'a']=true;
                        return true;
                    }
                    board[nextY][nextX]='.';
                }
                if(next=='$'){
                    getCount++;
                    board[nextY][nextX]='.';
                }
                isVisit[nextY][nextX]=true;
                q.add(new Pair(nextY, nextX));
            }
        }
        return false;
    }
    int getMaxTreasure(){
        int i=0,j=0;
        boolean noChange=true;
        //외곽 순회
        while(true){
            if(board[i][j]!='*' && !isVisit[i][j] && !('A'<=board[i][j] && board[i][j]<='Z' && !keys[board[i][j]-'A'])){
                if('a'<=board[i][j] && board[i][j]<='z') keys[board[i][j]-'a']=true;
                if(board[i][j]=='$') getCount++;
                board[i][j]='.';
                boolean isHaveNewKey=bfs(i,j);
                if(isHaveNewKey) isVisit=new boolean[board.length][board[0].length];
                noChange=false;
            }
            if(i==1 && j==0){
                if(noChange) break;
                else{
                    noChange=true;
                    i=0;j=0;
                }
            }
            if(i==0 && j<board[0].length-1) j++;
            else if(0<=i && i<board.length-1 && j==board[0].length-1) i++;
            else if(i==board.length-1 && 0<j && j<board[0].length) j--;
            else i--;
        }
        return getCount;
    }
}

class Pair{
    public int first;
    public int second;
    Pair(){
        this.first=0;
        this.second=0;
    }
    Pair(int a,int b){
        this.first=a;
        this.second=b;
    }
}