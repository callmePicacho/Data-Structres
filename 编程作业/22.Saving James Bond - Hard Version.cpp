#include<iostream>
#include<cmath>
#define INF 100000 
#define MaxVertex 105
typedef int Vertex;
int G[MaxVertex][MaxVertex]; // 图
int dist[MaxVertex];  // 距离
int path[MaxVertex];  // 路径 
bool collected[MaxVertex];  // 收录情况 
int N;  // 顶点
int D;  // 一跳距离 
struct Node{  // 存位置
	int hor;  // 横坐标
	int ver;  // 纵坐标 
};
Node pos[MaxVertex];  // 存放鳄鱼位置 
const double diameter=15;  // 直径 
using namespace std;

// 无向无权图 
// 0.判断能上岸鳄鱼的集合 
// 1.判断各个点是否连接
// 2.转换为图 

// 计算两点距离 
double getLen(int x1,int y1,int x2,int y2){
	return sqrt(pow(x1-x2,2.0)+pow(y1-y2,2.0));
}
// 判断鳄鱼能否上岸 
bool ashore(int x,int y){
	// 分别计算当前结点与岸边的距离
	// 即与 (x,50),(x,-50),(50,y),(-50,y) 的距离  
	if(abs(x-50)<=D || abs(x+50)<=D || abs(y+50)<=D || abs(y-50)<=D)
		return true;
	return false;
}

// 确认鳄鱼是否安全("能上岸") 
void getSafe(){
	for(int i=0;i<N;i++){
		// 如果该鳄鱼位置和"岸边"相邻 
		// 连通 
		if(ashore((pos[i].hor),(pos[i].ver))){
			G[N+1][i] = 1;
			G[i][N+1] = 1;
		}
	}
}

// 确认哪些鳄鱼是可以第一步跳上去的 
void getJump(){
	for(int i=0;i<N;i++)
		// 如果该鳄鱼位置和"湖中心"相邻（跳跃距离+半径） 
		if(getLen(pos[i].hor,pos[i].ver,0,0)<=D+diameter/2){
			G[N][i] = 1;
			G[i][N] = 1;
		}
}

// 鳄鱼间的情况 
void getConn(){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			// 如果鳄鱼间距离小于一跳距离，则彼此连通 
			if(i!=j && getLen(pos[i].hor,pos[i].ver,pos[j].hor,pos[j].ver)<=D){
				G[i][j] = 1;
				G[j][i] = 1;
			}
}

// 初始化 
void Init(){
	cin>>N>>D;
	int x,y;
	// 录入位置 
	for(int i=0;i<N;i++){
		cin>>x>>y;
		pos[i].hor = x;
		pos[i].ver = y;
	}
	// 007 算顶点，岸也算顶点
	// 初始化图，007连通情况存 G[N]，岸连通情况存 G[N+1] 
	for(Vertex i=0;i<=N+1;i++){
		for(Vertex j=0;j<=N+1;j++)
			G[i][j] = INF;  // 初始无穷大
		dist[i] = INF;  // 初始化距离
		path[i] = -1;  // 初始化路径
		collected[i] = false; // 初始化收录状态 
	} 
	// 初始化边
	// 岸连通情况 
	getSafe();
	// 007连通情况 
	getJump();
	// 鳄鱼彼此连通情况 
	getConn(); 
}


// 查找未收录dist最小的点
Vertex FindMin(Vertex s){
	int min = INF;
	Vertex xb=-1;
	for(Vertex i=0;i<=N+1;i++)
		if(s!=i && !collected[i] && dist[i] < min){
			min = dist[i];
			xb = i;
		}
	return xb;
} 

// 初始化源点信息 
void InitSource(Vertex s){
	dist[s] = 0;
	collected[s] = true;
	for(Vertex i=0;i<=N+1;i++)
		if(G[s][i]!=INF){
			dist[i] = G[s][i];
			path[i] = s;
		}
}

void Dijkstra(Vertex s){
	InitSource(s);
	while(1){
		Vertex v = FindMin(s);
		if(v==-1)
			break;
		collected[v] = true;
		for(Vertex w=0;w<=N+1;w++)
			if(!collected[w] && G[v][w]!=INF)
				if(dist[v] + G[v][w] < dist[w]){
					dist[w] = dist[v] + G[v][w];
					path[w] = v;
				}
	}
} 

// 输出路径 
void outputPath(){
	// 如果不通 
	
	
	if(dist[N+1] == INF){
		cout<<0<<endl;
		return;
	}
	Vertex v = path[N+1];
	cout<<dist[N+1]<<endl;
	while(v!=-1){
		cout<<pos[v].hor<<" "<<pos[v].ver<<endl;
		v = path[v];
	}
	
}

int main(){
	Init();
	Dijkstra(N);
	outputPath(); 
	return 0;
} 



