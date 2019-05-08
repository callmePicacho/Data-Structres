#include<iostream>
#include<malloc.h>
#define null -1
using namespace std;
struct TreeNode{
	char data;    // 存值 
	int left;   // 左子树的下标 
	int right;  // 右子树的下标 
}T1[10],T2[10];
// 返回根结点 
int create(struct TreeNode T[]){
	int n;
	int root = 0;
	char left,right;
	cin>>n;
	if(!n)
		return null;
	for(int i=0;i<n;i++){
		cin>>T[i].data>>left>>right;
		if(left=='-')
			T[i].left = null;
		else{
			T[i].left = left-'0';
			root -= T[i].left;
		}
		if(right=='-')
			T[i].right = null;
		else{
			T[i].right = right-'0';
			root -= T[i].right;
		}
		// 0 累加到 n-1 
		root +=i;	
	}
	return root;
}
// 判断是否同构
bool judge(int R1,int R2){
	if(R1 == null && R2 == null)   // 都为空 
		return true;
	if(R1 == null && R2 != null || R1 != null && R2 == null)    // 一个为空，一个不为空
		return false;
	if(T1[R1].data != T2[R2].data)   // 值不同
		return false;
	if((T1[R1].left != null && T2[R2].left != null )&&(T1[T1[R1].left].data == T2[T2[R2].left].data))  // 左儿子不为空且值相等
		return judge(T1[R1].left,T2[R2].left) && judge(T1[R1].right,T2[R2].right);
	else   // 左儿子不为空且值不等  或者 某一个左儿子为空 
		return judge(T1[R1].right,T2[R2].left) && judge(T1[R1].left,T2[R2].right);
} 
int main(){
	int R1,R2;
	R1 = create(T1);
	R2 = create(T2);
	if(judge(R1,R2))
		cout<<"Yes";
	else
		cout<<"No";
	return 0;
} 
