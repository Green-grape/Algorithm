import java.util.*;

//Map이라서 느림

public class PartialSum{
    long[] nums, partialSum;
    TreeMap<Pair,Long> sums;
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int numCnt=sc.nextInt(), modCnt=sc.nextInt(), sumCnt=sc.nextInt();
        long[] nums=new long[numCnt+1];
        for(int i=1;i<=numCnt;i++){
            nums[i]=sc.nextLong();
        }
        PartialSum psum=new PartialSum(nums);
        for(int i=0;i<modCnt+sumCnt;i++){
            int op=sc.nextInt();
            if(op==1){
                int idx=sc.nextInt();long num=sc.nextLong();
                psum.changeNum(idx, num);
            }
            else if(op==2){
                int start=sc.nextInt(), end=sc.nextInt();
                System.out.println(psum.getSum(start, end));
            }else{
                int v=sc.nextInt(), c=sc.nextInt();
                
            }
        }
        sc.close();
    }
    private long getInitSum(int start, int end){
        return partialSum[end]-partialSum[start]+nums[start];
    }
    private void makeTree(int start, int end){
        if(start>end) return;
        sums.put(new Pair(start,end), getInitSum(start, end));
        if(start==end) return;
        int leftStart=start, leftEnd=(start+end)/2, rightStart=(start+end)/2+1, rightEnd=end;
        if(leftStart<=leftEnd) makeTree(leftStart, leftEnd);
        if(rightStart<=rightEnd) makeTree(rightStart, rightEnd);
    }

    PartialSum(long[] nums){
        this.nums=nums;
        this.sums=new TreeMap<Pair,Long>(new PairCom<Pair>());
        partialSum=new long[nums.length];
        partialSum[1]=nums[1];
        for(int i=2;i<partialSum.length;i++){
            partialSum[i]=partialSum[i-1]+nums[i];
        }
        makeTree(1, nums.length-1);
    }
    private void setTree(int start, int end, int idx, long add){
        if(start>end) return;
        sums.put(new Pair(start, end), sums.get(new Pair(start,end))+add);
        if(start==end) return;
        int leftStart=start, leftEnd=(start+end)/2, rightStart=(start+end)/2+1, rightEnd=end;
        if(leftStart<=idx && idx<=leftEnd) setTree(leftStart, leftEnd, idx, add);
        if(rightStart<=idx && idx<=rightEnd) setTree(rightStart, rightEnd, idx, add);
    }
    public void changeNum(int idx, long num){
        long dif=num-nums[idx];
        setTree(1, nums.length-1, idx, dif);
        nums[idx]=num;
    }
    private long getSumRange(int start, int end, int findStart, int findEnd){
        //nums의 start, end구간의 합을 찾는다 findStart, findEnd는 세그먼트 트리에 저장된 합의 범위이다.
        if(start>end || start>findEnd || end<findStart) return 0;
        if(start==findStart && end==findEnd) return sums.get(new Pair(start,end));
        int mid=(findStart+findEnd)/2;
        if(mid<start) return getSumRange(start, end, mid+1, findEnd);
        if(end<=mid) return getSumRange(start, end, findStart, mid);
        return getSumRange(start, mid, findStart, mid)+getSumRange(mid+1, end, mid+1, findEnd);
    }
    public long getSum(int start, int end){
        return getSumRange(start,end,1,nums.length-1);
    }
}

class PairCom<T> implements Comparator<T>{
    public int compare(Object o1, Object o2){
        Pair p1=(Pair)o1, p2=(Pair)o2;
        if(p1.first!=p2.first) return ((Long)(p2.first-p1.first)).intValue();
        return ((Long)(p2.second-p1.second)).intValue();
    }
}

class Pair{
    public Long first,second;
    Pair(long first, long second){
        this.first=first;
        this.second=second;
    }
}