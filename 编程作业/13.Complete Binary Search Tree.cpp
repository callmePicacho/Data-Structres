#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#define MaxSize 2005
using namespace std;
int value[MaxSize];
int BST[MaxSize];

// 计算 n 个结点的树其左树结点个数 
int getLeftTreeSize(int n){
	int h =0;   // 保存该结点下满二叉树的层数 
	int tmp = n+1;
	while(tmp!=1){
		tmp /=2;
		h++;
	}
	int x = n-pow(2,h)+1;   // 最下面一排子叶结点个数 
	x = x<pow(2,h-1)?x:pow(2,h-1);   // 子叶结点个数最多是 2^(h-1) 
	int L = pow(2,h-1)-1+x;   // 该结点个数情况下左子树的个数 
	return L;
}

// 填充函数
void fill(int left,int right,int root){
	int n = right - left + 1;  // 确定范围内数值个数 
 	if(!n)
 		return;
 	int L = getLeftTreeSize(n);   // 找到"偏移量" 
 	BST[root] = value[left + L];    // 根结点的值应该是 左边界值 + 偏移量 
 	int leftRoot = 2 * root + 1;   // 左儿子结点位置，由于从 0 开始 
 	int rightRoot = leftRoot + 1;  // 右儿子结点位置 
 	fill(left,left+L-1,leftRoot);  // 左子树递归 
 	fill(left+L+1,right,rightRoot);   // 右子树递归 
}

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>value[i];
	}
	// 从小到大排序 
	sort(value,value+n);
	fill(0,n-1,0);
	for(int i=0;i<n;i++){
		if(i)
			cout<<" ";
		cout<<BST[i];
	}
	return 0;
} 
