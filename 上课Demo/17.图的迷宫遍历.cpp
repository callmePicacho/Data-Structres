#include<stdio.h>
#include<stdlib.h>
#include<queue>
#define col 12
#define row 10
int Graph[row][col];  // 存地图 
bool visit[row][col];  // 存访问状态 
int times[row][col];   // 存访问次数 
typedef struct Node *coordinate;
struct Node{    // 坐标 
	int hor; // 横坐标 
	int ver; // 纵坐标 
};
using namespace std;

// 初始化图 
void Init(){
	int tmp[row][col]= {{1,1,1,0,1,1,1,0,1,1,1,0},
				        {1,0,1,1,0,0,1,0,1,0,0,0},
				        {1,0,0,0,1,0,0,0,1,0,1,1},
				        {1,0,1,1,1,1,1,1,1,0,0,1},
				        {0,0,1,0,0,1,0,1,1,1,1,0},
				        {1,1,1,0,1,1,0,0,0,1,1,1},
				        {1,1,0,1,1,1,1,0,0,1,0,0},
				        {0,0,0,1,0,0,1,0,1,0,1,1},
				        {0,1,1,0,1,1,1,0,1,0,1,0},
				        {0,0,0,0,0,1,1,0,1,0,1,1}};
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++){
			times[i][j] = 1000;  // 初始化成大数，往小更新 
			Graph[i][j] = tmp[i][j];
			if(Graph[i][j])  // 为 1 可以访问 
				visit[i][j] = true;
			else
				visit[i][j] = false;
		}
}


// 初始化坐标 
coordinate create(int i,int j){
	coordinate C = (coordinate)malloc(sizeof(struct Node));
	C->hor = i;
	C->ver = j;
	return C;
}

int min(int t1,int t2){
	return t1<t2?t1:t2;
}

// 定义 上左、上、上右、右、右下、下、左下、左 八个位置 

int x[] = {-1,-1,-1,0,1,1,1,0};
int y[] = {-1,0,1,1,1,0,-1,-1};
void BFS(){
	queue<coordinate> q;
	coordinate tmp;
	// 起点入队列 
	tmp = create(0,0);
	visit[0][0] = false;
	times[0][0] = 0;
	q.push(tmp);
	while(!q.empty()){
		 // 取出队列中的下标和步数 
		 coordinate nowNode = q.front();
		 int xx = nowNode->hor;
		 int yy = nowNode->ver;
		 int nowtimes = times[xx][yy];
		 q.pop();  // 出队 
		 // 得到其周围八个点的坐标 
		 for(int i=0;i<8;i++){
		 	int newx = xx + x[i];
		 	int newy = yy + y[i];
		 	// 如果在范围内 
		 	if((newx>=0 && newx<row) &&(newy>=0 && newy<col) && visit[newx][newy] ){ 
		 		visit[newx][newy] = false;  // 设置状态 
	 			tmp = create(newx,newy);   
	 			times[newx][newy] = min(times[newx][newy],nowtimes+1);  // 更新步数 
	 			q.push(tmp);  // 入队 
		 	}
		 }
	}
}
int main(){
	Init();
	BFS();
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++)
			if(times[i][j]==1000)
				printf(" -1");
			else 
				printf("%3d",times[i][j]);
		printf("\n");
	}
	return 0;
}
