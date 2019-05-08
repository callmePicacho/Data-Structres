#include<cstdio>
#define MaxSize 10005
typedef int SetType; 
using namespace std;
// 初始化 
void Init(SetType s[],int n){
	for(int i=0;i<n;i++)
		s[i] = -1;
}

// 查找 
int Find(SetType s[],int x){
	if(s[x] < 0)  // 本身已经是根 
		return x;
	else  // 1. 找到根  2. 把根变成 x 的父结点  3.再返回根 
		return s[x] = Find(s,s[x]);
} 

// 并
void Union(SetType s[],int x1,int x2){
	// x1 规模更大，负数啊！ 
	if(s[x1] < s[x2]){
		s[x1] += s[x2];    //  两树合并，规模相加 
		s[x2] = x1;   // x2 挂到 x1 上 
	}else{
		s[x2] += s[x1];   //  两树合并，规模相加 
		s[x1] = x2;
	}
} 

//连接
void Input_connection(SetType s[]){
	int x1,x2;
	scanf("%d %d",&x1,&x2);
	int root1 = Find(s,x1-1);  // 以数组下标存值，下标与存值差 1 
	int root2 = Find(s,x2-1);
	if(root1 != root2)
		Union(s,root1,root2);
}

//检查连接
void check_connection(SetType s[]){
	int x1,x2;
	scanf("%d %d",&x1,&x2);
	int root1 = Find(s,x1-1);
	int root2 = Find(s,x2-1);
	if(root1 == root2)
		printf("yes\n");
	else
		printf("no\n");
} 

// 检查网络
void check_network(SetType s[],int n){
	int counter = 0;
	for(int i=0;i<n;i++)
		if(s[i] < 0)
			counter++;
	if(counter == 1)
		printf("The network is connected.");
	else
		printf("There are %d components.",counter);
}


int main(){
	int n;
	char in;
	scanf("%d",&n); 
	SetType s[MaxSize];
	Init(s,n);
	do{
		getchar();  // 接收每次多出来的回车 
		scanf("%c",&in);
		switch(in){
			case 'I':Input_connection(s);break;
			case 'C':check_connection(s);break;
			case 'S':check_network(s,n);break;
		}		
	}while(in != 'S');

	return 0;
} 
