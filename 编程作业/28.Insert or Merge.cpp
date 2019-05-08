#include<iostream>
using namespace std; 

bool judge(int A[],int B[],int N){
	for(int i=0;i<N;i++)
		if(A[i]!=B[i])
			return false;
	return true;
}

// 插入排序 
bool Insertion_Sort(int A[],int B[],int N){
	for(int P=1;P<N;P++){
		int tmp = A[P];
		int j = P;
		for(;j>0 && tmp < A[j-1];j--)
			A[j] = A[j-1];
		A[j] = tmp;
		if(judge(A,B,N)){  // 如果相等了，再做一轮 
			P++;
			int tmp = A[P];
			int j = P;
			for(;j>0 && tmp < A[j-1];j--)
				A[j] = A[j-1];
			A[j] = tmp;
			return false;
		}
	}
	return true; 
}


void Merge(int A[],int tmpA[],int L,int R,int RightEnd){
	// L = 左边起始位置，R = 右边起始位置，RightEnd = 右边终点位置 
	int NumSize = RightEnd-L+1;   //  排序个数  
	int LeftEnd = R-1;   // 左边终止位置 
	int tmp = L; 
	// 排序 
	while(L <= LeftEnd && R <= RightEnd){
		if(A[L] <= A[R])
			tmpA[tmp++] = A[L++];
		else
			tmpA[tmp++] = A[R++];
	} 
	// 如果左边有剩 
	while(L <= LeftEnd)
		tmpA[tmp++] = A[L++];
	// 如果右边有剩 
	while(R <= RightEnd)
		tmpA[tmp++] = A[R++];
	//  导回 A 数组 
	for(int i=0;i<NumSize;i++)
		A[RightEnd--] = tmpA[--tmp];
}

void Merge_pass(int A[],int tmpA[],int N,int length){
	int i;
	// 每次 2*length 为一组排序单元 
	for(i=0;i<=N-2*length;i+=2*length)
		Merge(A,tmpA,i,i+length,i+length*2-1);
	// 处理剩下的不够一组的排序单元 
	if(i+length < N)   // 如果左边够了，但是右边不齐，再次进入排序 
		Merge(A,tmpA,i,i+length,N-1);
	else   // 如果左边都不够，直接导给 tmpA 
		for(int j=i;j<N;j++)
			tmpA[j] = A[j];			
}

// 归并排序
bool Merge_Sort(int A[],int B[],int N){
	int tmpA[N];
	int length = 1;
	while(length < N){
		Merge_pass(A,tmpA,N,length);  // 一趟归并 
		length *=2;
		if(judge(A,B,N)){   // 如果相等了，再做一轮 
			Merge_pass(A,tmpA,N,length);
			return false;
		}
	} 
	return true;
}

// 输出 
void output(int A[],int N){
	for(int i=0;i<N;i++){
		if(i)
			cout<<" ";
		cout<<A[i]; 
	} 
} 

int main(){
	int N;
	cin>>N;
	int A[N],tmpA[N];
	for(int i=0;i<N;i++){
		cin>>A[i];
		tmpA[i] = A[i];
	}
	int B[N];
	for(int i=0;i<N;i++)
		cin>>B[i];
	// 用 tmpA 数组做归并排序，判断是否是归并排序 
	if(!Merge_Sort(tmpA,B,N)){
		cout<<"Merge Sort"<<endl;
		output(tmpA,N);
		return 0;
	}
	// 用 A 数组做插入排序，判断是否是插入排序
	if(!Insertion_Sort(A,B,N)){
		cout<<"Insertion Sort"<<endl;
		output(A,N);
		return 0;
	}
	return 0;
}
