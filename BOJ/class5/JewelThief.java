import java.util.Scanner;
import java.util.TreeMap;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Map;
/**
 * JewelThief
 */
public class JewelThief {
    static final int MIN_WEIGHT=1;
    Jewel[] jewels;
    TreeMap<Integer,Integer> bags;
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int jewelCnt=sc.nextInt(),bagCnt=sc.nextInt();
        Jewel[] jewels=new Jewel[jewelCnt];
        for(int i=0;i<jewels.length;i++){
            int weight=sc.nextInt(), value=sc.nextInt();
            jewels[i]=new Jewel(Math.max(weight,MIN_WEIGHT), value);
        }
        TreeMap<Integer,Integer> bags=new TreeMap<Integer,Integer>();
        for(int i=0;i<bagCnt;i++){
            int capacity=sc.nextInt();
            if(bags.get(capacity)==null){
                bags.put(capacity,1);
            }else{
                bags.put(capacity, bags.get(capacity)+1);
            }
        }
        JewelThief jt=new JewelThief(jewels, bags);
        System.out.println(jt.getMaxValue());
        sc.close();
    }
    JewelThief(Jewel[] jewels, TreeMap<Integer,Integer> bags){
        this.jewels=jewels;
        this.bags=bags;
    }
    public long getMaxValue(){
        Arrays.sort(jewels, new JewelCom());
        long ret=0;
        for(int i=0;i<jewels.length;i++){
            Map.Entry<Integer,Integer> bag=bags.higherEntry(jewels[i].weight-1);
            if(bag==null) continue;
            ret+=jewels[i].value;
            if(bag.getValue()==1){
                bags.remove(bag.getKey());
            }else{
                bags.put(bag.getKey(), bag.getValue()-1);
            }
        }
        return ret;
    }
}

//비율대로 하면 들어가지 못하는 것이 생길수 있다 pair처럼 정렬하자
class JewelCom implements Comparator<Jewel>{
    public int compare(Jewel j1, Jewel j2){
        if(j1.weight==j2.weight){
            return j2.weight-j1.weight;
        }
        return j2.value-j1.value;
    }
    public boolean equals(Jewel j1, Jewel j2){
        return compare(j1,j2)==0;
    }
}

class Jewel{
    int weight;
    int value;
    Jewel(){
        this.weight=0;
        this.value=0;
    }
    Jewel(int weight, int value){
        this.weight=weight;
        this.value=value;
    }
}