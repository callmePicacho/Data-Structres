#include<queue>
#include<iostream> 
#define null -1
using namespace std;
struct TreeNode{
	int data;  // 存值
	int left;  // 存左儿子结点 
	int right;   // 存右儿子结点 
}T[10];
//  把树整理出来 
int create(){
	int n;
	int root = 0;
	char left,right;
	cin>>n;
	if(!n)
		return null;
	for(int i=0;i<n;i++){
		T[i].data = i;
		cin>>left>>right;
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
		root +=i;
	}
	return root;
}
// 层序遍历 
void LevelorderTraversal(int root){
	// 创建队列 
	queue<struct TreeNode> q;
	struct TreeNode t;
	bool flag = false;
	
	// 如果树为空，直接打印 
	if(root == null){
		cout<<"-";
		return;	
	}
	q.push(T[root]);
	while(!q.empty()){
		t = q.front();  // 得到当前队首元素 
		q.pop();  // 出队 
		if(t.left == null && t.right == null){  // 如果为叶子结点就输出 
			if(flag)
				cout<<" ";
			else
				flag = true;
			cout<<t.data;	
		}
		if(t.left != null)  // 如果有左儿子结点，入队左儿子结点 
			q.push(T[t.left]);
		if(t.right != null)  // 如果有右儿子结点，入队右儿子结点 
			q.push(T[t.right]);
	}
} 
int main(){
	int root;
	root = create();
	LevelorderTraversal(root);
	return 0;
} 
