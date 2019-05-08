#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<queue> 
#define MaxVertex 105
struct Node{  // 存鳄鱼下标 
	int hor;   // 横坐标 
	int ver;  // 纵坐标
	bool visit;  // 是否被访问
	bool safe;  // 是否能上岸 
	bool jump;  // 第一步能否跳上去 
};
int N;   // 鳄鱼数 
int D;   // 跳跃距离
bool isSafe;  // 是否上岸 
Node G[MaxVertex];
using namespace std;
const double diameter=15;

// 计算两点距离 
double getLen(int x1,int y1,int x2,int y2){
	return sqrt(pow(x1-x2,2.0)+pow(y1-y2,2.0));
}

// 计算该鳄鱼能否到岸边 
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
		if(ashore((G[i].hor),(G[i].ver)))
			G[i].safe = true; // 将情况置为 true
		else
			G[i].safe = false; 
	}
}

// 确认哪些鳄鱼是可以第一步跳上去的 
void getJump(){
	for(int i=0;i<N;i++){
		// 如果该鳄鱼位置和"湖中心"相邻（跳跃距离+半径） 
		if(getLen(G[i].hor,G[i].ver,0,0)<=D+diameter/2)
			G[i].jump = true;
		else
			G[i].jump = false;
	}
}

// 初始化 
void Init(){
	cin>>N>>D;
	int x,y;
	for(int i=0;i<N;i++){
		cin>>x>>y;
		G[i].hor = x;
		G[i].ver = y;
		G[i].visit = false;
	}
	getSafe();
	getJump();
	isSafe = false;
}
/*
void DFS(int v){
	if(G[v].safe){ 
		isSafe = true;
		return;
	} 
	G[v].visit = true;
	for(int i=0;i<N;i++){
		// 距离如果小于 D，且未跳过，则能跳
		if(getLen(G[v].hor,G[v].ver,G[i].hor,G[i].ver)<=D && !G[i].visit)
			DFS(i);
	}
}
*/
void BFS(int v){
	queue<Node> q;
	Node tmp;
	G[v].visit = true;
	// 第一只鳄鱼入队 
	q.push(G[v]);
	while(!q.empty()){
		tmp = q.front();
		q.pop();
		// 能上岸 
		if(tmp.safe){
			isSafe = true;
			return;
		}
		for(int i=0;i<N;i++){
			// 距离如果小于 D，且未跳过，则能跳
			if(getLen(tmp.hor,tmp.ver,G[i].hor,G[i].ver)<=D && !G[i].visit){
				G[i].visit = true;
				q.push(G[i]);
			}
		}
	}
}

// 遍历所有第一步能跳到的鳄鱼 
void listCompoent(){
	for(int i=0;i<N;i++)
		if(G[i].jump){
		//	DFS(i); 
			BFS(i);
		}
	if(isSafe)
		cout<<"Yes"<<endl;
	else
		cout<<"No"<<endl;
}


int main(){
	Init();
	listCompoent();
	return 0;
}
