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
