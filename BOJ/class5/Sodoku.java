import java.util.Scanner;

public class Sodoku{
    static final int N=9;
    int[][] board;
    int[] columnUsed;
    int[] rowUsed;
    int[] squareUsed;
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int[][] board=new int[N][N];
        for(int i=0;i<N;i++){
            String nums=sc.nextLine();
            for(int j=0;j<nums.length();j++){
                board[i][j]=(int)nums.charAt(j)-48;
            }
        }
        Sodoku sodoku=new Sodoku(board);
        sodoku.play(0,0);
        sc.close();
    }
    private int getSquareIdex(int i, int j){
        return (i/3)*3+(j/3);
    }
    Sodoku(int[][] board){
        this.board=board;
        columnUsed=new int[N];
        rowUsed=new int[N];
        squareUsed=new int[N];
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(board[i][j]!=0){
                    rowUsed[i]|=(1<<board[i][j]);
                    columnUsed[j]|=(1<<board[i][j]);
                    squareUsed[getSquareIdex(i, j)]|=(1<<board[i][j]);
                }
            }
        }
    }
    boolean insert(int num, int y, int x){
        if((rowUsed[y] & (1<<num))==0  && (columnUsed[x] & (1<<num))==0 && (squareUsed[getSquareIdex(y, x)] & (1<<num))==0){
            rowUsed[y]|=(1<<num);
            columnUsed[x]|=(1<<num);
            squareUsed[getSquareIdex(y, x)]|=(1<<num);
            board[y][x]=num;
            return true;
        }
        return false;
    }
    void delete(int num, int y, int x){
        rowUsed[y]=rowUsed[y] & (~(1<<num));
        columnUsed[x]=columnUsed[x] & (~(1<<num));
        squareUsed[getSquareIdex(y, x)]=squareUsed[getSquareIdex(y, x)] & (~(1<<num));
        board[y][x]=0;
    }
    void play(int i, int j){
        if(i==N){
            for(int y=0;y<N;y++){
                for(int x=0;x<N;x++){
                    System.out.print(board[y][x]);
                }
                System.out.println();
            }
            System.exit(0);
        }
        if(board[i][j]!=0){
            if(j==N-1) play(i+1,0);
            else play(i,j+1);
        }else{
            for(int num=1;num<=9;num++){
                if(insert(num,i,j)){
                    if(j==N-1) play(i+1,0);
                    else play(i,j+1);
                    delete(num,i,j);
                }
            }
        }
    }
}