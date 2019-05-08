#include<iostream>
#include<malloc.h>
const int MinData = -100000;  // 哨兵值
const int MaxSize = 1005;   // 最大个数 
using namespace std;
typedef struct HeapStruct *Heap;
struct HeapStruct{
	int *data;   // 存值的数组 
	int size;   // 当前元素个数 
	int capacity;  // 最大容量 
};

// 初始化堆
Heap Create(){
	Heap H;
	H = (Heap)malloc(sizeof(struct HeapStruct));
	H->data = (int *)malloc(sizeof(int) * (MaxSize+1));
	H->size = 0;
	H->capacity = MaxSize;
	H->data[0] = MinData;
	return H;
} 

// 排序，类似堆的"删除操作" 
void sort(Heap H,int i){
	int child,parent;
	int tmp = H->data[i];  // 拿到当前"根结点的值" 
	for(parent = i;parent*2<=H->size;parent = child){
		child = 2 * parent;
		if((child!=H->size) && (H->data[child+1] < H->data[child]))
			child++;
		if(H->data[child] >= tmp)
			break;
		else
			H->data[parent] = H->data[child]; 
	}
	H->data[parent] = tmp;
}
// 调整
void adjust(Heap H){
	int i= H->size/2;
	for(;i>0;i--){
		// 以每个有孩子结点的结点作为根结点，对其子树进行堆排序 
		sort(H,i);
	}
} 

// 遍历 
void bl(Heap H){
	for(int i=1;i<=H->size;i++){
		cout<<H->data[i]<<" ";
	}
	cout<<endl;
}


int main(){
	Heap H;
	H = Create();
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>H->data[++H->size];
	adjust(H);
	bl(H); 
	return 0;
}

/*
#include<iostream>
#include<malloc.h>
const int MinData = -100000;  // 哨兵值
const int MaxSize = 1005;   // 最大个数 
using namespace std;
typedef struct HeapStruct *Heap;
struct HeapStruct{
	int *data;   // 存值的数组 
	int size;   // 当前元素个数 
	int capacity;  // 最大容量 
};

// 初始化堆
Heap Create(){
	Heap H;
	H = (Heap)malloc(sizeof(struct HeapStruct));
	H->data = (int *)malloc(sizeof(int) * (MaxSize+1));
	H->size = 0;
	H->capacity = MaxSize;
	H->data[0] = MinData;
	return H;
} 

// 插入
void Insert(Heap H,int x){
	int i = ++H->size;  // 指向数组最后一个 
	for(;H->data[i/2]>x;i/=2)
		H->data[i] = H->data[i/2];
	H->data[i] = x;
} 

// 遍历 
void bl(Heap H){
	for(int i=1;i<=H->size;i++)
		cout<<H->data[i];
}

int main(){
	Heap H;
	H = Create();
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		int t;
		cin>>t;
		Insert(H,t);
	}
	bl(H);
	return 0;
} 
*/ 
