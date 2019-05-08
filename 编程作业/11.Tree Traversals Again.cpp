#include<iostream>
#include<stack>
#include<string>
#include<stdio.h>
#include<malloc.h>
using namespace std;
typedef struct TreeNode *Tree;
struct TreeNode{
	string data;
	Tree left;   // 左子树 
	Tree right;  // 右子树 
};
// 初始化一个树结点 
Tree create(){
	Tree T;
	T = (Tree)malloc(sizeof(struct TreeNode));
	T->left = NULL;
	T->right = NULL;
	return T; 
}

// 根据中序遍历整理出这棵树 
Tree restore(Tree T){
	int n;
	string str;
	stack<Tree> s;
	Tree node = T;
	bool flag = false;
	string value;
	scanf("%d\n",&n);
	// 根节点赋值 
	getline(cin,str);
	value = str.substr(5);  // 从第五个开始截取
	node->data = value;
	// 根结点入栈 
	s.push(node); 
	for(int i=1;i<2*n;i++){
		getline(cin,str);
		if(str=="Pop"){// 如果是 pop 操作
			node = s.top();
			s.pop(); 
		}else{   // push
			value = str.substr(5);  // 从第五个开始截取
			Tree tmp = create();
			tmp->data = value;
			if(!node->left){// 如果左儿子空，新结点就是左儿子 
				node->left = tmp;
				node = node->left; 
			}else if(!node->right){  // 如果右儿子空，新结点就是右儿子 
				node->right = tmp;
				node = node->right;
			}
			s.push(tmp);
		}
	}
	return T;
}

// 后序递归遍历
void bl(Tree T,bool &flag){
	if(T){
		bl(T->left,flag);
		bl(T->right,flag);
		if(!flag)
			flag = true;
		else
			cout<<" ";
		cout<<T->data;
	}
} 
int main(){
	Tree T;
	bool flag = false;
	string str;
	T = create();
	T = restore(T);
	bl(T,flag);
	return 0;
} 
