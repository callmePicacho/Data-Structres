#include<iostream>
#include<algorithm>
using namespace std;
void output(int A[],int N); 

// 判断是否相等 
bool judge(int A[],int B[],int N){
	for(int i=0;i<N;i++)
		if(A[i]!=B[i])
			return false;
	return true;
} 

// 插入排序 
bool Insertion_Sort(int A[],int B[],int N){
	for(int p=1;p<N;p++){
		int tmp = A[p];
		int k = p;
		for(;k>0 && tmp < A[k-1];k--)
			A[k] = A[k-1];
		A[k] = tmp;
		if(judge(A,B,N)){// 如果相等，多做一轮
			p++; 
			int tmp = A[p];
			int k = p;
			for(;k>0 && tmp < A[k-1];k--)
				A[k] = A[k-1];
			A[k] = tmp;
			return false;
		}
	}
	return true;
}

void PrecDown(int A[],int i,int N){
	int tmp = A[i]; // 取得当前"根"
	int parent,child;
	for(parent=i;parent*2+1<N;parent = child){
		child = 2*parent +1;
		if((child!=N-1) && (A[child] < A[child+1]))
			child++;
		if(A[child] <= tmp)
			break;
		A[parent] = A[child];
	} 
	A[parent] = tmp;
}

// 堆排序 
bool Heap_Sort(int A[],int B[],int N){
	for(int i=N/2;i>=0;i--)
		PrecDown(A,i,N);
	for(int i=N-1;i>0;i--){
		swap(A[0],A[i]);
		PrecDown(A,0,i);
		if(judge(A,B,N)){  // 如果相等，多做一轮 
			swap(A[0],A[--i]);
			PrecDown(A,0,i);
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
	if(!Heap_Sort(tmpA,B,N)){  // 如果是堆排序 
		cout<<"Heap Sort"<<endl;
		output(tmpA,N);
		return 0;
	}
	if(!Insertion_Sort(A,B,N)){  // 如果是插入排序 
		cout<<"Insertion Sort"<<endl;
		output(A,N);
		return 0;
	}
	return 0;
} 
