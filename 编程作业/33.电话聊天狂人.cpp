#include<iostream>
#include<stdlib.h>
#include<string>
#include<cmath>
#define MAXTABLESIZE 1000000
using namespace std;
typedef string ElementType;
typedef struct LNode *List;
struct LNode{  // 单链表 
	ElementType number;  // 电话号码 
	int Count;  // 计数 
	List Next;   
};

typedef struct HashTbl *HashTable;
struct HashTbl{   // 哈希表 
	int TableSize;  // 哈希表大小
	List Heads;   // 头结点 
}; 

// 除留余数法哈希函数 
int Hash(int key,int p){
	return key%p;
}
 
int NextPrime(int N){
	int p = (N%2)?N+2:N+1;
	int i;
	while(p <= MAXTABLESIZE){
		for(i = (int)sqrt(1.0*p);i>2;i--)
			if(!(p%i))   // 不是素数 
				break;  
		if(i==2)  // 找到了 
			break; 
		p += 2;  // 去找下个素数 
	}
	return p; 
}

// 初始化哈希表 
HashTable CreateTable(int TableSize){
	HashTable H;
	H = (HashTable)malloc(sizeof(struct HashTbl));
	H->TableSize = NextPrime(TableSize);
	
	// 结构体中含字符串必须动态分配地址空间 
	H->Heads = new LNode[H->TableSize];
	for(int i=0;i<H->TableSize;i++){
		H->Heads[i].Next = NULL;
		H->Heads[i].Count = 0; 
	}
	return H;
} 

// 查找 
List Find(HashTable H,ElementType key){
	List p;
	int pos;
	// 以电话号码最后五位散列
	pos = Hash(atoi(key.substr(6,5).c_str()),H->TableSize);

	p = H->Heads[pos].Next;
	while(p && key != p->number)
		p = p->Next;
	return p;
}

// 插入 
bool Insert(HashTable H,ElementType key){
	List p,NewCell;
	int pos;
	p = Find(H,key);
	if(!p){   // p为空 
		
		NewCell = new LNode();
		NewCell->number = key;
		NewCell->Count = 1;   
		pos = Hash(atoi(key.substr(6,5).c_str()),H->TableSize);  // 找到散列地址 
	
		// 将新结点插入到链表头 
		NewCell->Next = H->Heads[pos].Next; 
		H->Heads[pos].Next = NewCell;
		return true;
	}else{
		p->Count++;   // 已经存在，计数+1 
		return false;
	}
}

void ScanAndOutput(HashTable H){
	List p; 
	int MaxCnt=0;  // 最大通话次数 
	string Minphone; // 最小号码 
	int PCnt=0;   // 并列人数 
	// 扫描链表 
	for(int i=0;i<H->TableSize;i++){
		p = H->Heads[i].Next;
		while(p){
			if(MaxCnt < p->Count){
				MaxCnt = p->Count;
				Minphone = p->number;
				PCnt = 1;
			}else if( p->Count == MaxCnt ){
				if(p->number < Minphone )
					Minphone = p->number;
				PCnt++;
			} 
			p = p->Next; 
			
		}
	}
	cout<<Minphone<<" "<<MaxCnt;
	if(1 < PCnt)
		cout<<" "<<PCnt;
}

int main(){
	HashTable H;
	int N;
	ElementType key;
	cin>>N;
	H = CreateTable(2*N);
	for(int i=0;i<N;i++){
		cin>>key;		Insert(H,key);
		cin>>key;		Insert(H,key);
	}
	ScanAndOutput(H);
	return 0;
} 
