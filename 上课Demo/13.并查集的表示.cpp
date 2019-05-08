#include<iostream>
#include<cstring>
#define MaxSize 1000
typedef int ElementType;
typedef struct{
	ElementType Data; // 存值
	int parent;  // 指向父结点 
}SetType;
using namespace std;

// 查找 
int Find(SetType s[],ElementType x){
	int i;  
	// 找到数组中该值对应的下标 
	for(i=0;i<MaxSize && s[i].Data!=x;i++);
	if(MaxSize <= i) // 如果没有找到，返回 -1 
		return -1;
	// 找到该结点的根结点 
	for(;s[i].parent >= 0;i = s[i].parent); 
	return i; // 返回根结点在数组 s 中的下标 
}

// 并 
void Union(SetType s[],ElementType x1,ElementType x2){
	int root1 = Find(s,x1);  // 找到 x1 的根结点下标 
	int root2 = Find(s,x2);  // 找到 x2 的根结点下标 
	// 如果根结点的下标不同，说明不是一个集合
	if(root1 != root2){   
		s[root1].parent = root2;   // 把 x1 挂到 x2 的集合 
	}
}

int main(){
	SetType s[MaxSize];
	// 初始化数组，父结点全部指向 -1 
	for(int i=0;i<MaxSize;i++){
		s[i].Data = i+1;
		s[i].parent = -1;
	}
	cout<<Find(s,5)<<endl;
	Union(s,3,5);
	cout<<Find(s,4)<<endl;
	cout<<Find(s,3)<<endl;
	Union(s,1,3);
	Union(s,2,4);
	Union(s,8,6);
	cout<<Find(s,6)<<endl;
	cout<<Find(s,8)<<endl;
	return 0;
}
