#include<iostream>
#define MaxVertex 505
#define INF 100000
typedef int Vertex;
int N; // 顶点数
int M; // 边
int S; // Source
int D;  // Destination 
int dist[MaxVertex];  // 距离
int cost[MaxVertex]; // 费用
bool collected[MaxVertex];  // 选中情况 
int value[MaxVertex][MaxVertex];  // 收费
int G[MaxVertex][MaxVertex];
using namespace std; 


void build(){
	Vertex v1,v2,w1,w2;
	cin>>N>>M>>S>>D;
	for(Vertex i=0;i<N;i++){
		for(Vertex j=0;j<N;j++){
			G[i][j] = INF;
			value[i][j] = INF; 
		}
		cost[i] = 0;
		collected[i] = false;
		dist[i] = INF;
	}
	for(int i=0;i<M;i++){
		cin>>v1>>v2>>w1>>w2;
		G[v1][v2] = w1;
		G[v2][v1] = w1; 
		value[v1][v2] = w2;
		value[v2][v1] = w2;
	}
}

// 初始化源点信息 
void InitSource(){
	dist[S] = 0;
	collected[S] = true;
	for(Vertex i=0;i<N;i++)
		if(G[S][i]){
			dist[i] = G[S][i];
			cost[i] = value[S][i];
		}
}

// 查找未被收录中dist最小的点 
Vertex FindMin(){
	int min = INF;
	Vertex xb = -1;
	for(Vertex i=0;i<N;i++)
		if(S!=i && !collected[i] && dist[i] < min){
			min = dist[i];
			xb = i;
		}
	return xb;
}

void Dijkstra(){
	InitSource();
	while(1){
		Vertex v = FindMin();
		if(v==-1)
			break;
		collected[v] = true;
		for(Vertex w=0;w<N;w++)
			if(!collected[w] && G[v][w])
				if(dist[v] + G[v][w] < dist[w]){  // 如果有路径更短 
					dist[w] = dist[v] + G[v][w];
					cost[w] = cost[v] + value[v][w];
				}else if(dist[v] + G[v][w] == dist[w] && cost[v] + value[v][w] < cost[w]){  // 如果路径一样长，选择费用更少 
					cost[w] = cost[v] + value[v][w];
				}
	}
}


int main(){
	build();
	Dijkstra();
	cout<<dist[D]<<" "<<cost[D];
	return 0;
}

