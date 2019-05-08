#include<iostream>
using namespace std;
/* 方法一：确定子列的开头和结尾，再遍历累加，时间复杂度 O(n^3)*/
int MaxSubseqSum1(int n,int a[]){
	int max = 0;
	for(int i=0;i<n;i++){
		for(int k=0;k<i;k++){		
			int tmpSum = 0;
			for(int j=k;j<=i;j++){
				tmpSum+=a[j]; 
			}
			if(max < tmpSum)
				max = tmpSum;
		}
	}
	return max;
}
/* 方法二：确定子列的结尾，逐个减去子列前的数，时间复杂度 O(n^2)*/ 
int MaxSubseqSum2(int n,int a[]){
	int sum[100000+5];
	int max = 0;
	sum[0]=a[0];
	for(int i=1;i<n;i++)
		sum[i]=sum[i-1]+a[i];
	for(int i=0;i<n;i++){
		int tmpSum = sum[i];
		for(int j=0;j<=i;j++){
			if(max < tmpSum)
				max = tmpSum;
			tmpSum-=a[j]; 
		}
	}
	return max;
}
/* 方法二：确定子列的首部，逐个累加，时间复杂度 O(n^2)*/ 
int MaxSubseqSum3(int n,int a[]){
	int max = 0;
	for(int i=0;i<n;i++){
		int tmpSum = 0;
		for(int j=i;j<n;j++){
			tmpSum+=a[j];
			if(max < tmpSum)
				max = tmpSum;
		}
	}
	return max;
}
/* 方法三：直接累加，如果累加到当前的和为负数，置当前值或0，时间复杂度为 O(n)*/ 
int MaxSubseqSum5(int n,int a[]){
	int max = 0;
	int tmpSum=0;
	for(int i=0;i<n;i++){
		tmpSum+=a[i];
		if(tmpSum<0){
			tmpSum=0;
		}else if(max < tmpSum){
			max = tmpSum;
		}
	}
	return max;
}

/* 方法四：递归分成两份，分别求每个分割后子列的最大和，时间复杂度为 O(n*logn)*/
/* 返回三者中最大值*/
int Max3(int A,int B,int C){
	return (A>B)?((A>C)?A:C):((B>C)?B:C);
}
/* 分解成更小规模求解*/
int DivideAndConquer(int a[],int left,int right){
	
	/*递归结束条件，子列只有一个数字*/
	if(left == right){
		if(0 < a[left])
			return a[left];
		return 0;
	}
	
	/* 分别找到左右最大子列和*/ 
	int center = (left+right)/2; 
	int MaxLeftSum = DivideAndConquer(a,left,center);
	int MaxRightSum = DivideAndConquer(a,center+1,right);
	
	/* 再分别找左右跨界最大子列和*/
	int MaxLeftBorderSum = 0;
	int LeftBorderSum = 0;
	for(int i=center;i>=left;i--){
		LeftBorderSum += a[i];
		if(MaxLeftBorderSum < LeftBorderSum)
			MaxLeftBorderSum = LeftBorderSum;	
	}
	int MaXRightBorderSum = 0;
	int RightBorderSum = 0;
	for(int i=center+1;i<=right;i++){
		RightBorderSum += a[i];
		if(MaXRightBorderSum < RightBorderSum)
			MaXRightBorderSum = RightBorderSum;
	}
	
	/*最后返回分解的左边最大子列和，右边最大子列和，和跨界最大子列和三者中最大的数*/
	return Max3(MaxLeftSum,MaxRightSum,MaXRightBorderSum+MaxLeftBorderSum);
}
int MaxSubseqSum4(int n,int a[]){
	return DivideAndConquer(a,0,n-1);
}
int main(){
	int n;
	int a[100000+5];
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<MaxSubseqSum1(n,a);
	cout<<MaxSubseqSum2(n,a);
	cout<<MaxSubseqSum3(n,a);
	cout<<MaxSubseqSum4(n,a);
	cout<<MaxSubseqSum5(n,a);
	return 0;
} 

