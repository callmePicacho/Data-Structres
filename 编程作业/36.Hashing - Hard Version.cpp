#include<queue>
#include<iostream>
#include<vector>
#include<map>
#define INF -100000
#define MaxVertex 1005
int G[MaxVertex][MaxVertex];
int Indegree[MaxVertex];  // 入度 
int value[MaxVertex];  // 存值 
int N;  // 总值
using namespace std;
priority_queue<int,vector<int>,greater<int> > q;   // 定义最小堆 
map<int,int> m;

// 插入边 
void Insert(){
	for(int i=0;i<N;i++){ 
		if(0 <= value[i]){
			m.insert(pair<int,int>(value[i],i));   // 存下标与值的映射关系 
			int remainder = value[i]%N;  // 余数 
			if(remainder==i)
				Indegree[i] = 0;
			else if(remainder != i){
				Indegree[i] = (i - remainder < 0)?(i - remainder + N):(i - remainder);
				for(int j=remainder;j!=i;j=(j+1)%N)
					G[j][i] = 1;
			}
		}
	}
}

// 初始化图 
void build(){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			G[i][j] = INF;
	Insert();
}

// 拓扑排序 
void TopSort(){
	for(int i=0;i<N;i++)
		if(!Indegree[i] && 0 < value[i])
			q.push(value[i]);
	bool flag = true;
	while(!q.empty()){
		int tmpValue = q.top(); 
		int v = m[tmpValue];  // 找回下标 
		q.pop();
		if(flag)
			flag = false;
		else
			cout<<" ";
		cout<<tmpValue;
		for(int w=0;w<N;w++)
			if(G[v][w]!=INF){  // 如果连通 
				if(--Indegree[w]==0)
					q.push(value[w]);
			}
	}
}


int main(){
	cin>>N;
	int i=0;
	for(int i=0;i<N;i++)
		cin>>value[i];
	build();

	TopSort();
	return 0;
}
