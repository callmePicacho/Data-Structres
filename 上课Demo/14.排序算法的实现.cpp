#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cmath> 
#define NumSize 20
int A[NumSize];
using namespace std;

// 生成随机数 
void Random(){
	for(int i=0;i<NumSize;i++)
		A[i] = rand()%NumSize+1;
}

// 输出 
void output(){
	for(int i=0;i<NumSize;i++)
		cout<<A[i]<<" ";
	cout<<endl;
}

// 冒泡排序
void Bubble_sort(int N){
	for(int p = N-1;p>=0;p--){    // 总共 n-1 趟 
		bool flag = false;     
		for(int j=0;j<p;j++){  // 一趟排序 
			if(A[j+1] < A[j]){
				swap(A[j],A[j+1]);
				flag = true;
			}
		}
		if(!flag)   // 如果全程无交换，可以此次排序了 
			break;
	}
} 

// 插入排序 
void Insertion_sort(int A[],int N){
	for(int p = 1;p<N;p++){
		int tmp = A[p];   // 取出一个数 
		int j = p;
		for(;tmp<A[j-1] && j > 0;j--)  // 找到这个数适合的位置 
			A[j] = A[j-1];  // “腾“出位置 
		A[j] = tmp;  //  把合适大小的数放入 
	} 
}

// 原始希尔排序 
void shell_sort(int N){
	for(int D=N/2;D>0;D/=2){
		for(int p=D;p<N;p+=D){
			int tmp = A[p];
			int j = p;
			for(;j>=D && tmp<A[j-D] ;j-=D)  // j>=D 在前，因为也许 A[j-D]已经越界 
				A[j] = A[j-D];
			A[j] = tmp;
		}
	}
} 

// Hibbard增量序列希尔排序 
void Hibbard_shell_sort(int N){
	int add[]={32767,16383,8191,4095,2047,1023,511,255,127,63,31,15,7,3,1,0};
	int i=0;
	for(int D=add[i];D>0;D=add[++i]){
		for(int p=D;p<N;p++){
			long tmp = A[p];
			int k=p;
			for(;k>=D && tmp<A[k-D] ;k-=D) // j>=D 在前，因为也许 A[j-D]已经越界 
				A[k] = A[k-D];
			A[k] = tmp;
		}
	}
}

// Sedgewick增量序列希尔排序
void Sedgewick_shell_sort(int N){
	int add[]= {587521,260609,146305,64769,36289,16001,8929,3905,2161,929,505,209,109,41,19,5,1,0};
	int i=0;
	for(int D=add[i];D>0;D=add[++i]){
		for(int p=D;p<N;p++){
			long tmp = A[p];
			int k = p;
			for(;k>=D && tmp<A[k-D];k-=D)
				A[k] = A[k-D];
			A[k] = tmp;
		}
	} 
}

/********************堆排序开始******************************/ 
// 调整成最大堆 
void PrecDown(int i,int N){
	int child,parent;
	int tmp = A[i];  // 拿到当前"根"结点的值
	// 下标从 0 开始，注意结束范围和父子结点之间的关系 
	for(parent = i;parent*2+1<=N-1;parent = child){
		child = 2*parent + 1;  
		if((child!=N-1) && (A[child] < A[child+1])) // 选最大的 
			child++;
		if(A[child] <= tmp)
			break;
		A[parent] = A[child];
	}
	A[parent] = tmp;
}

void swap(int &a,int &b){
	int t =a;
	a = b;
	b = t;
}

// 堆排序
void Heap_sort(int N){
	// buildHeap 
	for(int i=N/2;i>=0;i--) 
		PrecDown(i,N);
	for(int i=N-1;i>0;i--){
		swap(A[0],A[i]);
		PrecDown(0,i);
	} 
} 
/*******************堆排序结束******************************/ 


/********************归并排序（递归）开始******************************/ 
// 归并排序实现 
void Merge(int A[],int tmpA[],int L,int R,int RightEnd){
	// L = 左边起始位置，R = 右边起始位置，RightEnd = 右边终点位置 
	int LeftEnd = R-1;   // 左边终点位置 
	int tmp = L;   //  存放结果的开始位置 
	int NumElements = RightEnd - L + 1;  // 归并个数 
	while(L<=LeftEnd && R<=RightEnd){
		if(A[L] <= A[R])
			tmpA[tmp++] = A[L++];
		else
			tmpA[tmp++] = A[R++];
	}
	// 左边有剩 
	while(L<=LeftEnd)
		tmpA[tmp++] = A[L++];
	// 右边有剩 
	while(R<=RightEnd)
		tmpA[tmp++] = A[R++];
	//  导回结果 
	for(int i=0;i<NumElements;i++,RightEnd--)
		A[RightEnd] = tmpA[RightEnd];
} 

// 分治 
void Msort(int A[],int tmpA[],int L,int RightEnd){
	// L = 左边起始位置，RightEnd = 右边终点位置 
	// 如果还有元素 
	if( L < RightEnd){
		int center = (L+RightEnd)/2;
		Msort(A,tmpA,L,center);  // 左半边 
		Msort(A,tmpA,center+1,RightEnd);  // 右半边
		Merge(A,tmpA,L,center+1,RightEnd);  // center+1 是右边起点 
	}
} 
/*
// 归并排序（递归） 
void Merge_sort(int A[],int N){
	int tmpA[N];
	Msort(A,tmpA,0,N-1);
}*/

/********************归并排序（递归）结束******************************/ 

/********************归并排序（非递归）结束******************************/ 

void Merge1(int A[],int tmpA[],int L,int R,int RightEnd){
	// L = 左边起始位置，R = 右边起始位置，RightEnd = 右边终点位置 
	int LeftEnd = R-1;   // 左边终点位置 
	int tmp = L;   //  存放结果的开始位置 
	int NumElements = RightEnd - L + 1;  // 归并个数 
	while(L<=LeftEnd && R<=RightEnd){
		if(A[L] <= A[R])
			tmpA[tmp++] = A[L++];
		else
			tmpA[tmp++] = A[R++];
	}
	// 左边有剩 
	while(L<=LeftEnd)
		tmpA[tmp++] = A[L++];
	// 右边有剩 
	while(R<=RightEnd)
		tmpA[tmp++] = A[R++];
} 
void Merge_pass(int A[],int tmpA[],int N,int length){
	// length = 当前有序子列长度
	int i;
	for(i=0;i<=N-2*length;i+=length*2)
		Merge1(A,tmpA,i,i+length,i+2*length-1);
	if(i+length<N)
		Merge1(A,tmpA,i,i+length,N-1);
	else
		for(int j=i;j<N;j++)
			tmpA[j] = A[j];
}

void Merge_sort(int A[],int N){
	int length = 1;
	int tmpA[N];
	while(length<N){
		Merge_pass(A,tmpA,N,length);
		length *=2;
		Merge_pass(tmpA,A,N,length);
		length *=2;
	}
} 
/********************归并排序（非递归）结束******************************/ 

/*********************快速排序开始*******************************************/ 

// 获得主元 
int GetPivot(int L,int R){
	int center = (L+R)/2;
	// 排序  A[L] < A[center] < A[R] 
	if(A[R] < A[center])
		swap(A[R],A[center]);
	if(A[R] < A[L])
		swap(A[R],A[L]);
	if(A[center] < A[L])
		swap(A[L],A[center]);
	// 把主元藏在 R-1 
	swap(A[center],A[R-1]);
	return A[R-1];
}

// 快排实现 
void Quicksort(int Left,int Right){
	int cutoff = 100;
	if( cutoff <= Right-Left){
		int Pivot = GetPivot(Left,Right);
		int i = Left;
		int j = Right-1;
		while(1){
			while(A[++i] < Pivot);
			while(A[--j] > Pivot);
			if(i < j)
				swap(A[i],A[j]);
			else
				break;
		}
		swap(A[i],A[Right-1]);
		Quicksort(Left,i-1);
		Quicksort(i+1,Right);
	}else
		Insertion_sort(A+Left,Right-Left+1);
}

void Quick_sort(int N){
	Quicksort(0,N-1);
}
/*********************快速排序结束************************/ 

/*********************桶排序开始********************/ 
void Bucket_Sort(int N){
	int count[1000];
	// 范围多大桶就多少 
	for(int i=0;i<1000;i++){
		count[i] = 0;
	}
	// 每个值倒入桶中 
	for(int i=0;i<N;i++)
		count[A[i]]++;
	// 收集 
	for(int i=0;i<N;i++)
		if(count[i]){
			for(int j=0;j<count[i];j++)
				cout<<i<<" ";
		}
}

/*********************桶排序开始******************/ 

int main(){
	Random(); // 生成随机数 
	output();  // 输出数组元素 
//	Bubble_sort(NumSize);   // 冒泡排序 
//	Insertion_sort(NumSize);   // 插入排序 
//	shell_sort(NumSize);   // 希尔排序  
//	Heap_sort(NumSize);   // 堆排序 
//	Merge_sort(A,NumSize);   // 归并排序 
//	Hibbard_shell_sort(NumSize);	
//	Sedgewick_shell_sort(NumSize);
//	Quick_sort(NumSize);
	Bucket_Sort(NumSize);
//	output(); 
	return 0;
}







