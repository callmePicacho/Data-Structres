#include<iostream>
#include<queue>
#include <algorithm>
#define MaxVertex 105
#define INF -100000
typedef int Vertex;
using namespace std;
int N; // 点
int M;  // 边
int G[MaxVertex][MaxVertex];  
int Earliest[MaxVertex];  // 时间 
int Indegree[MaxVertex]; // 入度 

// 初始化图 
void build(){
	Vertex v1,v2,w;
	cin>>N>>M;
	for(Vertex i=0;i<N;i++){
		for(Vertex j=0;j<N;j++)
			G[i][j] = INF;
	}
	for(int i=0;i<M;i++){
		cin>>v1>>v2>>w;
		G[v1][v2] = w;  // 有向图 
		Indegree[v2]++;  // 入度+1 
	}
}

void TopSort(){
	int cnt = 0;
	queue<Vertex> q;
	// 入度为0顶点入队 
	for(Vertex i=0;i<N;i++)
		if(!Indegree[i]){ 
			q.push(i);
			Earliest[i] = 0;
		} 
	while(!q.empty()){
		Vertex v = q.front();
		q.pop();
		cnt++;
		for(Vertex w=0;w<N;w++)
			if(G[v][w]!=INF){ 
				if(Earliest[w] < Earliest[v]+G[v][w])  //如果周围有时间更长，更新时间 
					Earliest[w] = max(Earliest[w],Earliest[v]+G[v][w]);
				if(--Indegree[w]==0)
					q.push(w);
			} 
	}
	if(cnt!=N)
		cout<<"Impossible";
	else{ 
		// 也许不止一个终点 
		int max = 0;
		for(Vertex i=0;i<N;i++)  
			if(max < Earliest[i]) 
				max = Earliest[i];
		cout<<max;
	}
		
}

int main(){
	build();
	TopSort();
	return 0;
}

