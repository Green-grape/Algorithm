import java.util.Scanner;
import java.lang.Math;

public class Game2048 {
    int[][] board;
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int boardSize=sc.nextInt();
        int[][] board=new int[boardSize][boardSize];
        for(int i=0;i<boardSize;i++){
            for(int j=0;j<boardSize;j++){
                board[i][j]=sc.nextInt();
            }
        }
        Game2048 game=new Game2048(board);
        System.out.println(game.play(0));
        sc.close();
    }
    Game2048(int[][] board){
        this.board=board;
    }
    private void move(String dir){
        if(dir.charAt(0)=='x'){
            if(dir.charAt(1)=='+'){
                for(int i=0;i<board.length;i++){
                    int[] newRow=new int[board[i].length];
                    int newRowIdx=newRow.length-1;
                    for(int j=board[i].length-1;j>=0;j--){
                        if(board[i][j]==0) continue;
                        if(newRow[newRowIdx]==0){
                            newRow[newRowIdx]=board[i][j];
                            continue;
                        }
                        if(newRow[newRowIdx]==board[i][j]){
                            newRow[newRowIdx--]*=2;
                        }else{
                            newRow[--newRowIdx]=board[i][j];
                        }
                    }
                    for(int j=0;j<newRow.length;j++){
                        board[i][j]=newRow[j];
                    }
                }
            }
            if(dir.charAt(1)=='-'){
                for(int i=0;i<board.length;i++){
                    int[] newRow=new int[board[i].length];
                    int newRowIdx=0;
                    for(int j=0;j<board[i].length;j++){
                        if(board[i][j]==0) continue;
                        if(newRow[newRowIdx]==0){
                            newRow[newRowIdx]=board[i][j];
                            continue;
                        }
                        if(newRow[newRowIdx]==board[i][j]){
                            newRow[newRowIdx++]*=2;
                        }else{
                            newRow[++newRowIdx]=board[i][j];
                        }
                    }
                    for(int j=0;j<newRow.length;j++){
                        board[i][j]=newRow[j];
                    }
                }
            }
        }
        if(dir.charAt(0)=='y'){
            if(dir.charAt(1)=='+'){
                for(int j=0;j<board.length;j++){
                    int[] newCol=new int[board[j].length];
                    int newColIdx=newCol.length-1;
                    for(int i=board.length-1;i>=0;i--){
                        if(board[i][j]==0) continue;
                        if(newCol[newColIdx]==0){
                            newCol[newColIdx]=board[i][j];
                            continue;
                        }
                        if(newCol[newColIdx]==board[i][j]){
                            newCol[newColIdx--]*=2;
                        }else{
                            newCol[--newColIdx]=board[i][j];
                        }
                    }
                    for(int i=0;i<newCol.length;i++){
                        board[i][j]=newCol[i];
                    }
                }
            }
            if(dir.charAt(1)=='-'){
                for(int j=0;j<board.length;j++){
                    int[] newCol=new int[board[j].length];
                    int newColIdx=0;
                    for(int i=0;i<board.length;i++){
                        if(board[i][j]==0) continue;
                        if(newCol[newColIdx]==0){
                            newCol[newColIdx]=board[i][j];
                            continue;
                        }
                        if(newCol[newColIdx]==board[i][j]){
                            newCol[newColIdx++]*=2;
                        }else{
                            newCol[++newColIdx]=board[i][j];
                        }
                    }
                    for(int i=0;i<newCol.length;i++){
                        board[i][j]=newCol[i];
                    }
                }
            }
        }
    }
    public int play(int playCnt){
        if(playCnt==5){
            int ret=0;
            for(int i=0;i<board.length;i++){
                for(int j=0;j<board[i].length;j++){
                    //System.out.print(board[i][j]+" ");
                    ret=Math.max(ret,board[i][j]);
                }
                //System.out.println();
            }
            return ret;
        }
        int ret=0;
        int[][] prevBoard=new int[board.length][board.length];
        for(int i=0;i<prevBoard.length;i++){
            prevBoard[i]=board[i].clone();
        }
        String[] moves={"y+","y-","x+","x-"};
        for(int i=0;i<moves.length;i++){
            move(moves[i]);
            ret=Math.max(ret,play(playCnt+1));
            for(int j=0;j<prevBoard.length;j++){
                board[j]=prevBoard[j].clone();
            }
        }
        return ret;
    }
    
}
