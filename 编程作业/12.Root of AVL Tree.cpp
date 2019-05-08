#include<iostream>
#include<malloc.h>
typedef struct AVLNode *AVLTree;
struct AVLNode{
	int data;     // 存值 
	AVLTree left;  // 左子树 
	AVLTree right;  // 右子树 
	int height;  // 树高 
};
using namespace std;

// 返回最大值 
int Max(int a,int b){
	return a>b?a:b;
}

// 返回树高，空树返回 -1 
int getHeight(AVLTree A){
	return A==NULL?-1:A->height;
}

// LL单旋
// 把 B 的右子树腾出来挂给 A 的左子树，再将 A 挂到 B 的右子树上去 
AVLTree LLRotation(AVLTree A){
	/*
			A	
		   /
		  B
	     /
	    C
	*/
	// 此时根节点是 A 
	AVLTree B = A->left;  // B 为 A 的左子树  
	A->left = B->right;   // B 的右子树挂在 A 的左子树上 
	B->right = A;     //  A 挂在 B 的右子树上 
	A->height = Max(getHeight(A->left),getHeight(A->right)) + 1;
	B->height = Max(getHeight(B->left),A->height) + 1;
	return B;  // 此时 B 为根结点了 
	/*
		B
	   / \
	  C   A 
	*/
}

// RR单旋
AVLTree RRRotation(AVLTree A){
	/*
			A	
		     \
		      B
	          \ 
	           C
	*/
	// 此时根节点是 A 
	AVLTree B = A->right;
	A->right = B->left;
	B->left = A;
	A->height = Max(getHeight(A->left),getHeight(A->right)) + 1;
	B->height = Max(getHeight(B->left),A->height) + 1;
	return B;  // 此时 B 为根结点了 
	/*
		B
	   / \
	  A   C 
	*/
}

// LR双旋 
AVLTree LRRotation(AVLTree A){
	/*
		A
	   /
	  B
	   \
	   C
	*/
	// 先 RR 单旋
	A->left = RRRotation(A->left);
	/*
	*/
	// 再 LL 单旋 
	return LLRotation(A);
}

// RL双旋
AVLTree RLRotation(AVLTree A){
	// 先 LL 单旋
	A->right = LLRotation(A->right);
	// 再 RR 单旋 
	return RRRotation(A); 
}

AVLTree Insert(AVLTree T,int x){
	if(!T){  // 如果该结点为空，初始化结点 
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->data = x;
		T->left = NULL;
		T->right = NULL;
		T->height = 0;
	}else{  // 否则不为空， 
		if(x < T->data){  // 左子树 
			T->left = Insert(T->left,x);
			if(getHeight(T->left)-getHeight(T->right)==2){  // 如果左子树和右子树高度差为 2 
				if(x < T->left->data)  // LL 单旋 
					T = LLRotation(T); 
				else if(T->left->data < x)  // LR双旋
					T = LRRotation(T); 
			}
		}else if(T->data < x){
			T->right = Insert(T->right,x);
			if(getHeight(T->right)-getHeight(T->left)==2){
				if(x < T->right->data)  // RL 双旋 
					T = RLRotation(T); 
				else if(T->right->data < x)  // RR单旋
					T = RRRotation(T); 
			}
		}
	}
	//更新树高 
	T->height = Max(getHeight(T->left),getHeight(T->right)) + 1;
	return T;
} 


int main(){
	AVLTree T=NULL;
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		int tmp;
		cin>>tmp;
		T = Insert(T,tmp);
	}
	cout<<T->data;
	return 0;
}
