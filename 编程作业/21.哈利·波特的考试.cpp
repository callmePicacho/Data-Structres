/*#include<iostream>
#define MaxVertex 105
#define INF 100000
typedef int Vertex;
int G[MaxVertex][MaxVertex];  // 图 
int N;  // 动物数（顶点） 
int M;  // 咒语条数（边） 
int dist[MaxVertex][MaxVertex];  // 距离
bool collected[MaxVertex][MaxVertex];  // 选中状态 
using namespace std;

// 初始化 
void build(){
	Vertex v1,v2;
	int w;
	cin>>N>>M;
	for(Vertex i=1;i<=N;i++){
		for(Vertex j=1;j<=N;j++){ 
			G[i][j] = 0;   // 初始化图
			dist[i][j] = INF;  // 初始化距离
			collected[i][j] = false;  // 初始选中状态 
		}
		dist[i][0] = INF;  // 特意将每个源点第一个距离初始成 INF 
	}
	for(int i=0;i<M;i++){
		cin>>v1>>v2>>w;
		G[v1][v2] = w; 
		G[v2][v1] = w;
	}
} 

// 查找未被选中的顶点中距离最小的一个 
Vertex FindMin(Vertex s){
	Vertex min = 0;
	for(Vertex i = 1;i<=N;i++)
		if(i!=s && dist[s][i] < dist[s][min] && !collected[s][i])
			min = i;
	return min; 
}

int FindMax(Vertex s){
	int max = 0;
	for(Vertex i = 1;i<=N;i++)
		if(max < dist[s][i])
			max = dist[s][i];
	return max;
}

// 设置源点距离，且该点周围点更新状态 
void prepare(Vertex s){
	dist[s][s] = 0;
	collected[s][s] = true;
	for(Vertex i=1;i<=N;i++)
		if(G[s][i])
			dist[s][i] = G[s][i];
} 

int Dijkstra(Vertex s){
	prepare(s);  // 准备 
	while(1){
		Vertex v = FindMin(s);
		if(!v)
			break;
		collected[s][v] = true;
		for(Vertex w=1;w<=N;w++)
			if(G[v][w] && !collected[s][w])
				if(dist[s][v] + G[v][w] < dist[s][w])
					dist[s][w] = dist[s][v] + G[v][w];
	} 
	// 找到自己最难变的咒语长度 
	return FindMax(s);
}

int main(){
	build();
	int min = INF;
	int xb = 0;
	int max;
	for(Vertex s=1;s<=N;s++){
		max = Dijkstra(s);
		if(max < min){ 
			min = max;
			xb = s; 
		} 
		if(min==INF){
			cout<<0<<endl;
			return 0;
		}
	}
	cout<<xb<<" "<<min<<endl;
	return 0;
}*/



#include<iostream>
#define MaxVertex 105
#define INF 100000
typedef int Vertex;
int G[MaxVertex][MaxVertex];  // 图 
int N;  // 动物数（顶点） 
int M;  // 咒语条数（边） 
int dist[MaxVertex][MaxVertex];  // 距离
using namespace std;

// 初始化 
void build(){
	Vertex v1,v2;
	int w;
	cin>>N>>M;
	for(Vertex i=1;i<=N;i++)
		for(Vertex j=1;j<=N;j++)
			G[i][j] = INF;   // 初始化图
	for(int i=0;i<M;i++){
		cin>>v1>>v2>>w;
		G[v1][v2] = w; 
		G[v2][v1] = w;
	}
}

void Floyd(){
	// 初始化 dist 数组 
	for(Vertex i=1;i<=N;i++)
		for(Vertex j=1;j<=N;j++) 
			dist[i][j] = G[i][j];
	for(Vertex k=1;k<=N;k++)
		for(Vertex i=1;i<=N;i++)
			for(Vertex j=1;j<=N;j++)
				if(dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
}

// 查找每个源点到其他点的最大值 
int FindMax(Vertex s){
	int max = 0;
	for(Vertex i=1;i<=N;i++)
		if(s!=i && max < dist[s][i])
			max = dist[s][i];
	return max;
}

// 查找每个源点到其他点的最大值中最小的距离 
void FindMin(){
	int ItemMax;
	int min = INF;
	int animal; 
	for(Vertex i=1;i<=N;i++){
		ItemMax = FindMax(i);
		if(ItemMax == INF){
			cout<<0<<endl;
			return;
		}
		if(ItemMax < min){ 
			min = ItemMax;
			animal = i;
		}
	}
	cout<<animal<<" "<<min<<endl;
}

int main(){
	build();
	Floyd();
	FindMin();
	return 0;
}

