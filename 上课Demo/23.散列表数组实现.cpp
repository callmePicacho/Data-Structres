#include<iostream>
#include<stdlib.h>
#include<cmath>
#define MAXTABLESIZE 100000   // 定义允许开辟的最大散列表长度 
typedef int Index;
typedef int ElementType; 
typedef Index Position;
typedef enum{   // 分别对应：有合法元素、空、有已删除元素 
	Legitimate,Empty,Deleted
} EntryType;  // 定义单元状态类型 

typedef struct HashEntry Cell;
struct HashEntry{   //  哈希表存值单元 
	ElementType Data;  // 存放元素
	EntryType Info;  // 单元状态	
};

typedef struct HashTbl *HashTable;
struct HashTbl{  // 哈希表结构体 
	int TableSize;   // 哈希表大小 
	Cell *Cells;   // 哈希表存值单元数组 
};

using namespace std;

int NextPrime(int N);  // 查找素数 
HashTable CreateTable( int TableSize); // 创建哈希表 
Index Hash(int Key,int TableSize);   // 哈希函数 

// 查找素数 
int NextPrime(int N){
	int p = (N%2)?N+2:N+1;  // 从大于 N 的下个奇数开始
	int i;
		
	while(p <= MAXTABLESIZE){
		for(i = (int)sqrt(p);i>2;i--)
			if(!(p%i))  // p 不是素数 
				break;
		if(i==2) 
			break; 
		p += 2;  // 继续试探下个奇数 
	}
	return p;
}

// 创建哈希表 
HashTable CreateTable( int TableSize){
	HashTable H;
	int i;
	H = (HashTable)malloc(sizeof(struct HashTbl));
	// 保证哈希表最大长度是素数 
	H->TableSize = NextPrime(TableSize);
	// 初始化单元数组
	H->Cells = (Cell *)malloc(sizeof(Cell)*H->TableSize);
	// 初始化单元数组状态 
	for(int i=0;i<H->TableSize;i++)
		H->Cells[i].Info = Empty;
	return H;
}

// 平方探测查找 
Position Find(HashTable H,ElementType Key){
	Position CurrentPos,NewPos; 
	int CNum = 0 ;   // 记录冲突次数
	CurrentPos = NewPos = Hash(Key,H->TableSize);
	// 如果当前单元状态不为空，且数值不等，则一直做 
	while(H->Cells[NewPos].Info != Empty && H->Cells[NewPos].Data != Key){
		if(++CNum % 2 ){ // 冲突奇数次发生 
			NewPos = CurrentPos + (CNum+1)/2*(CNum+1)/2;
			// 如果越界，一直减直到再次进入边界 
			while(H->TableSize <= NewPos){
				NewPos -= H->TableSize; 
			}
		}else{  // 冲突偶数次发生 
			NewPos = CurrentPos - CNum/2*CNum/2;
			// 如果越界，一直加直到再次进入边界 
			while(NewPos < 0){
				NewPos += H->TableSize; 
			}
		}
	} 
	return NewPos;
}

// 插入
bool Insert( HashTable H,ElementType Key,int i){
	Position Pos = i;
	Pos = Find(H,Key);
	// 如果单元格状态不是"存在合法元素" 
	if( H->Cells[Pos].Info != Legitimate){
		H->Cells[Pos].Info = Legitimate;
		H->Cells[Pos].Data = Key;
	}
	return true;
} 

// 除留余数法哈希函数 
Index Hash(int Key,int TableSize){
	return Key % TableSize;
}


void output(HashTable H){
	for(int i=0;i<H->TableSize;i++)
		cout<<i<<" "<<H->Cells[i].Data<<endl;
} 

int main(){
	HashTable H = CreateTable(9);
	int N;
	cin>>N;
	for(int i=0;i<N;i++){
		int tmp;
		cin>>tmp;
		Insert(H,tmp,i);
	}
	output(H);
	return 0;
}
