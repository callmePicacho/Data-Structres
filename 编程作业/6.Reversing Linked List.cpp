#include<stdio.h>
#include<iostream>
#define MaxSize 100005
using namespace std;
int main(){
	int Data[MaxSize];
	int Next[MaxSize];
	int list[MaxSize];
	int FirstAdd,N,K;
	scanf("%d %d %d",&FirstAdd,&N,&K);
	for(int i=0;i<N;i++){
		int tmpAdd,tmpData,tmpNext;
		scanf("%d %d %d",&tmpAdd,&tmpData,&tmpNext);
		Data[tmpAdd] = tmpData;
		Next[tmpAdd] = tmpNext;
	}
	int sum=0;   // 累计有效结点数 
	while(FirstAdd!=-1){   // 当尾结点为 -1 时结束 
		list[sum++] = FirstAdd;   // 记录所有Address
		FirstAdd = Next[FirstAdd];  // 找下一个结点 
	}
	for(int i=0;i<sum-sum%K;i+=K){  // 每 K 个结点一个区间 
		for(int j=0;j<K/2;j++){  // 反转链表
			int t = list[i+j];
			list[i+j] = list[i+K-j-1];
			list[i+K-j-1] = t; 
		}
	}
	for(int i=0;i<sum-1;i++)
		printf("%05d %d %05d\n",list[i],Data[list[i]],list[i+1]);
	printf("%05d %d -1\n",list[sum-1],Data[list[sum-1]]);
	return 0;
}
