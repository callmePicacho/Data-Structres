#include<iostream>
#include<cmath>
#include<stdlib.h>
#define MAXTABLESIZE 100000
#define NOTFIND -1
typedef int ElementType;
typedef enum{     // 单元格状态 
	Legitimate,Empty
} EntryType;   // 分别对应：有合法元素和有空位 
typedef struct HashEntry Cell;
struct HashEntry{   // 单元格 
	ElementType data;  // 存值
	EntryType info;   // 存状态 
};
typedef struct HashTbl *HashTable;
struct HashTbl{  // 哈希表
	int TableSize;  // 大小 
	Cell *Cells;   // 数组 
};
using namespace std;

// 除留余数法哈希函数 
int Hash(int key,int p){
	return key%p;
}

// 查找下一个素数 
int NextPrime(int N){
	int p = N%2?N:N+1;
	int i;
	if(N<=2)
		return 2;
	else if(N<=3)
		return 3; 
	while(p <= MAXTABLESIZE){
		for(i=(int)sqrt(p);i>2;i--)
			if(!(p%i))   // 不是素数 
				break;
		if(i==2)  // 找到了
			break;
		p += 2; 
	}
	return p;
}

// 创建哈希表 
HashTable CreateTable(int TableSize){
	HashTable H;
	H = (HashTable)malloc(sizeof(struct HashTbl));
	H->TableSize = NextPrime(TableSize);
	H->Cells = (Cell *)malloc(sizeof(struct HashEntry)*H->TableSize);
	for(int i=0;i<H->TableSize;i++)
		H->Cells[i].info = Empty;
	return H;	
}

//查找
int Find(HashTable H,ElementType key){
	int NewPos,CurrentPos;
	int CNum = 0;  // 记录冲突次数 
	CurrentPos = NewPos = Hash(key,H->TableSize);
	// 如果当前状态不为空，且一直不等，一直做 
	while(H->Cells[NewPos].info != Empty && H->Cells[NewPos].data != key){
		CNum++;
		NewPos = (CurrentPos + CNum*CNum)%H->TableSize;
		if(CNum == H->TableSize/2) // 没找到
			return NOTFIND;
	}
	return NewPos;
}

int Insert(HashTable H,ElementType key){
	int pos;
	pos = Find(H,key);
	if(pos==NOTFIND) // 如果没找到 
		return NOTFIND;
	else if(H->Cells[pos].info != Legitimate){
		H->Cells[pos].info = Legitimate;
		H->Cells[pos].data = key;
	}
	return pos;
} 

int main(){
	HashTable H;
	int M,N;
	int key;
	cin>>M>>N;
	H = CreateTable(M);
	for(int i=0;i<N;i++){
		cin>>key;
		int pos = Insert(H,key);
		if(i)
			cout<<" ";
		if(pos==NOTFIND)
			cout<<"-";
		else
			cout<<pos;
	}
	return 0;
}

