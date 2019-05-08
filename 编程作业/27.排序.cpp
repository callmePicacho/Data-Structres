#include<iostream>
#include<algorithm>
#include<queue>
using namespace std; 

// 冒泡排序 
void Bubble_sort(long A[],int N){
	for(int i=0;i<N-1;i++){  // N-1次冒泡
		bool flag = false;  // 验证是否交互过 
		for(int j=0;j<N-i-1;j++){
			if(A[j+1] < A[j]){
				flag = true; 
				swap(A[j],A[j+1]);
			}
		} 
		// 已经有序 
		if(!flag)  
			break; 
	} 
} 

// 插入排序
void Insertion_sort(long A[],int N){
	for(int i=1;i<N;i++){  // 第一个已经成序 
		long tmp = A[i];
		int j=i;
		for(;tmp<A[j-1] && j>0;j--)
			A[j] = A[j-1];
		A[j] = tmp;
	}
}

// 原始希尔排序 
void shell_sort(long A[],int N){
	for(int D=N/2;D>0;D/=2){
		for(int p=D;p<N;p++){
			long tmp = A[p];
			int k=p;
			for(;k>=D && tmp<A[k-D] ;k-=D) // j>=D 在前，因为也许 A[j-D]已经越界 
				A[k] = A[k-D];
			A[k] = tmp;
		}
	}
} 

// Hibbard增量序列希尔排序 
void Hibbard_shell_sort(long A[],int N){
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
// Sedgewick增量序列哈希排序 
void Sedgewick_shell_sort(long A[],int N){
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

/***************堆排序开始***************/

// 调整成最大堆 
void PrecDown(long A[],int i,int N){
	int parent,child;
	long tmp = A[i];
	// 从 0 开始存，所以关系有变化 
	for(parent = i;parent*2+1<N;parent = child){
		child = parent*2+1;
		if((child!=N-1) && (A[child] < A[child+1]))
			child++;
		if(A[child] <= tmp)
			break;
		else
			A[parent] = A[child];
	}
	A[parent] = tmp;
}

// 堆排序 
void Heap_sort(long A[],int N){
	// 先调整成最大堆 
	for(int i=N/2;i>=0;i--)
		PrecDown(A,i,N);
	for(int i=N-1;i>0;i--){
		swap(A[0],A[i]); // 每次把当前最大堆根元素选择出来 
		PrecDown(A,0,i);  // 再次调整最大堆 
	}
} 

/***************堆排序结束***************/

/***************stl堆排序开始***************/
priority_queue<long,vector<long>,less<long> > q; // 定义一个最大堆 

void STL_Heap_sort(long A[],int N){
	// 数据读入最大堆 
	for(int i=0;i<N;i++)
		q.push(A[i]);
	// 依次出队 
	for(int i=N-1;i>=0;i--){
		A[i] = q.top();
		q.pop();
	}
} 
/***************stl堆排序结束***************/

/***************递归归并排序开始***************/
/*
// 归并实现 
void Merge(long A[],long tmpA[],int L,int R,int RightEnd){
	// L = 左边元素开始位置 ，R = 右边元素开始位置 ，RightEnd = 右边结束终点位置
	int NumSize = RightEnd-L+1; // 元素个数
	int LeftEnd = R-1;  // 左边元素终点位置
	int tmp = L;  // tmp 数组开始位置 
	while( L <= LeftEnd && R <= RightEnd ){
		if(A[L] <= A[R]) // 从小到大排序，选小的 
			tmpA[tmp++] = A[L++];
		else
			tmpA[tmp++] = A[R++];
	} 
	// 也许左没走完 
	while( L <= LeftEnd )
		tmpA[tmp++] = A[L++];
	// 也许右边没走完 
	while( R <= RightEnd)
		tmpA[tmp++] = A[R++];
	// 再导回 A ,tmp此时已经越界，所以要先减再用 
	for(int i=0;i<NumSize;i++)
		A[RightEnd--] = tmpA[--tmp];
}

// 分治 
void Msort(long A[],long tmpA[],int L,int RightEnd){
	if(L < RightEnd){
		int center = ( L + RightEnd )/2;
		Msort(A,tmpA,L,center);
		Msort(A,tmpA,center+1,RightEnd);
		Merge(A,tmpA,L,center+1,RightEnd);
	}
}

void Merge_sort(long A[],int N){
	long tmpA[N];
	Msort(A,tmpA,0,N-1);
}
*/
/***************递归归并排序结束***************/

/***************非递归归并排序开始***************/
// 归并实现 ，最后不把元素倒回A 
void Merge1(long A[],long tmpA[],int L,int R,int RightEnd){
	// L = 左边元素开始位置 ，R = 右边元素开始位置 ，RightEnd = 右边结束终点位置
	int NumSize = RightEnd-L+1; // 元素个数
	int LeftEnd = R-1;  // 左边元素终点位置
	int tmp = L;  // tmp 数组开始位置 
	while( L <= LeftEnd && R <= RightEnd ){
		if(A[L] <= A[R]) // 从小到大排序，选小的 
			tmpA[tmp++] = A[L++];
		else
			tmpA[tmp++] = A[R++];
	} 
	// 也许左没走完 
	while( L <= LeftEnd )
		tmpA[tmp++] = A[L++];
	// 也许右边没走完 
	while( R <= RightEnd)
		tmpA[tmp++] = A[R++];
}

// 一趟归并 
void Merge_pass(long A[],long tmpA[],int N,int length){
	int i;
	// 每 2*length 一个单元归并 
	for(i=0;i<N-2*length;i+=2*length)
		Merge1(A,tmpA,i,i+length,i+2*length-1);
	// 处理剩余不足一个单元的值 
	if(i+length < N)  // 剩下两个子列，左边够，右边不够 
		Merge1(A,tmpA,i,i+length,N-1);
	else    //  剩下一个子列，左边都不够 
		for(int j=i;j<N;j++)
			tmpA[j] = A[j];
}


void Merge_sort(long A[],int N){
	int length = 1;
	long tmpA[N];
	// 保证每次两趟归并，最终结果一定存在 A中 
	while(length < N){
		Merge_pass(A,tmpA,N,length);
		length *=2;
		Merge_pass(tmpA,A,N,length);
		length *=2;
	}
}

/***************非递归归并排序结束***************/

/*********************快速排序开始*******************************************/ 
// 选主元 
long getPivot(long A[],int L,int R){
	int center = (L+R)/2;
	if(A[R] < A[center])
		swap(A[R],A[center]);
	if(A[R] < A[L])
		swap(A[R],A[L]);
	if(A[center] < A[L])
		swap(A[center],A[L]);
	swap(A[center],A[R-1]);
	return A[R-1];
}

void QucikSort(long A[],int Left,int Right){
	int cutoff = 50;
	if( cutoff <= Right - Left ){  // 如果规模大用快排 
		int pivot = getPivot(A,Left,Right);
		int i = Left;      
		int j = Right-1; 
		for(;;){
			// 从前往后找比 pivot 小的 
			while(A[++i] < pivot);
			// 从后往前找比 pivot 大的 
			while(A[--j] > pivot);
			if(j <= i)
				break;
			swap(A[i],A[j]);
		}
		// 将主元放在合适位置 
		swap(A[i],A[Right-1]);
		QucikSort(A,Left,i-1);
		QucikSort(A,i+1,Right);
	}else   // 否则用插入排序 
		Insertion_sort(A+Left,Right-Left+1);
}

void Quick_sort(long A[],int N){
	QucikSort(A,0,N-1);
}

/*********************快速排序结束**********************************/ 

int main(){
	int N;
	cin>>N;
	long A[N];
	for(int i=0;i<N;i++)
		cin>>A[i];
	Quick_sort(A,N);
	for(int i=0;i<N;i++){
		if(i)
			cout<<" ";
		cout<<A[i];
	}
	return 0;
} 
