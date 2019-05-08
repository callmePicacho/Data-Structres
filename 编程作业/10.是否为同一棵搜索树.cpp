#include<iostream>
#include<string>
#include<malloc.h>
using namespace std;
typedef struct TreeNode *BinTree;
struct TreeNode{
	int data;  // 存值
	BinTree left;  // 左子树
	BinTree right; // 右子树 
};

// 插入一个结点 
BinTree Insert(int x,BinTree BST){
	if(!BST){   // 如果结点为空，创建并返回 
		BST = (BinTree)malloc(sizeof(struct TreeNode));
		BST->data = x;
		BST->left = NULL;
		BST->right = NULL;
	}else{  //  如果结点不为空 
		if(x < BST->data)  // 如果 x 比当前结点的值小 
			BST->left = Insert(x,BST->left);  // 递归到左子树插入 
		else if(BST->data < x)  // 如果 x 比当前结点的值大 
			BST->right = Insert(x,BST->right);   // 递归到右子树插入
		// 如果相等，什么也不做 
	}
	return BST;
}

// 前序遍历 
void  PreOrderTraversal(BinTree BST,string &s){
	if(BST){
		 
		PreOrderTraversal(BST->left,s);  // 进入左子树 
		s += BST->data+'0';  // 将结点值保存进字符串
		PreOrderTraversal(BST->right,s);  // 进入右子树 
	}
}

int main(){
	int n,l;
	int tmp;
	cin>>n>>l;
	while(n){  // 当 n 不为空做循环 
		BinTree InitBST = NULL;
		string Initstr;
		// 每次新输入 n l 的初始插入序列 
		for(int i=0;i<n;i++){
			cin>>tmp;
			InitBST = Insert(tmp,InitBST);
		}
		// Initstr 记录初始插入序列形成的树的先序遍历结果 
		// 思考为什么不用中序记录？ 
		PreOrderTraversal(InitBST,Initstr);
		
		// 后 l 行 
		for(int i=0;i<l;i++){
			BinTree BST = NULL;
			string str;
			for(int j=0;j<n;j++){
				cin>>tmp;
				BST = Insert(tmp,BST);
			}
			// 每行的插入序列产生一个树，用 str 记录先序遍历结果 
			PreOrderTraversal(BST,str);
			
			// 再将初始序列和每次插入序列产生的值进行对比 
			if(str == Initstr)
				cout<<"Yes"<<endl;
			else
				cout<<"No"<<endl;
		}
		cin>>n>>l;
	}
	return 0;
}
