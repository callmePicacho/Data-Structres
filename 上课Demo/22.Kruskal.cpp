#include<iostream>
#include<string>
#include<vector>
#include<queue>
#define INF 100000
#define MaxVertex 105
typedef int Vertex; 
int G[MaxVertex][MaxVertex];
int parent[MaxVertex];   // 并查集最小生成树 
int Nv;    // 结点 
int Ne;    // 边 
int sum;  // 权重和 
using namespace std; 
struct Node{
	Vertex v1;
	Vertex v2;
	int weight; // 权重 
	// 重载运算符成最大堆 
	bool operator < (const Node &a) const
	{
		return weight>a.weight;
	}
};
vector<Node> MST;  // 最小生成树 
priority_queue<Node> q;   // 最小堆 

// 初始化图信息 
void build(){
	Vertex v1,v2;
	int w;
	cin>>Nv>>Ne;
	for(int i=1;i<=Nv;i++){
		for(int j=1;j<=Nv;j++)
			G[i][j] = 0;  // 初始化图
		parent[i] = -1;
	}
	// 初始化点
	for(int i=0;i<Ne;i++){
		cin>>v1>>v2>>w;
		struct Node tmpE;
		tmpE.v1 = v1;
		tmpE.v2 = v2;
		tmpE.weight = w;
		q.push(tmpE); 
	}
}

//  路径压缩查找 
int Find(int x){
	if(parent[x] < 0)
		return x;
	else
		return parent[x] = Find(parent[x]);
} 

//  按秩归并 
void Union(int x1,int x2){
	if(parent[x1] < parent[x2]){
		parent[x1] += parent[x2];
		parent[x2] = x1;
	}else{
		parent[x2] += parent[x1];
		parent[x1] = x2;
	}
} 

void Kruskal(){
	// 最小生成树的边不到 Nv-1 条且还有边 
	while(MST.size()!= Nv-1 && !q.empty()){
		Node E = q.top();  // 从最小堆取出一条权重最小的边
		q.pop(); // 出队这条边 
		if(Find(E.v1) != Find(E.v2)){  // 检测两条边是否在同一集合 
			sum += E.weight; 
			Union(E.v1,E.v2);     // 并起来 
			MST.push_back(E);
		}
	}
	
} 


void output(){
	cout<<"被收录顺序："<<endl; 
	for(Vertex i=0;i<Nv;i++)
		cout<<MST[i].weight<<" ";
	cout<<"权重和为："<<sum<<endl; 
	for(Vertex i=1;i<=Nv;i++)
		cout<<parent[i]<<" ";
	cout<<endl;
}


int main(){
	build();
	Kruskal();
	output();
	return 0;
} 
