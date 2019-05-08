#include<iostream>
#include<queue>
#include <algorithm>
#define MaxVertex 105
#define INF 100000
typedef int Vertex;
using namespace std;
int N; // 点
int M;  // 边
int G[MaxVertex][MaxVertex];  
int Earliest[MaxVertex];  // 最早完成时间 
int latest[MaxVertex];  // 最晚完成时间 
int Indegree[MaxVertex]; // 入度 
int Outdegree[MaxVertex];  // 出度 
int Max;   // 最长时间 

// 初始化图 
void build(){
	Vertex v1,v2,w;
	cin>>N>>M;
	for(Vertex i=1;i<=N;i++)
		for(Vertex j=1;j<=N;j++)
			G[i][j] = INF;
	for(int i=0;i<M;i++){
		cin>>v1>>v2>>w;
		G[v1][v2] = w;  // 有向图 
		Indegree[v2]++;  // 入度+1
		Outdegree[v1]++;  // 出度+1 
	}
}

// 倒推得到活动最晚完成时间 
void GetLastest(){
	
}

// 拓扑排序，找到完成项目最短时间 
bool TopSort(){
	int cnt = 0;
	queue<Vertex> q;
	// 入度为0顶点入队 
	for(Vertex i=1;i<=N;i++)
		if(!Indegree[i]){ 
			q.push(i);
			Earliest[i] = 0;
		} 
	while(!q.empty()){
		Vertex v = q.front();
		q.pop();
		cnt++;
		for(Vertex w=1;w<=N;w++)
			if(G[v][w]!=INF){ 
				if(Earliest[w] < Earliest[v]+G[v][w])  //如果周围有时间更长，更新时间 
					Earliest[w] = max(Earliest[w],Earliest[v]+G[v][w]);
				if(--Indegree[w]==0)
					q.push(w);
			} 
	}
	if(cnt!=N)
		return false;
	else{ 
		// 也许不止一个终点 
		Max = 0;
		for(Vertex i=1;i<=N;i++)
			if(Max < Earliest[i])
				Max = Earliest[i];
		return true;
	}
		
}

int main(){
	build();
	if(!TopSort())
		cout<<0;
	else{
		cout<<Max<<endl;
		
	}
	return 0;
}


