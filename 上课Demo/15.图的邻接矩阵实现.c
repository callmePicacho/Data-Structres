/*#include<stdio.h>
#include<stdlib.h>
#define MaxVertexNum 100
typedef int weightType;
typedef int Vertex;
typedef int DataType;
typedef struct GNode *ptrToGNode;
struct GNode{   // 图 
	int Nv;   // 顶点数 
	int Ne;   // 边数
	weightType G[MaxVertexNum][MaxVertexNum];
	DataType Data[MaxVertexNum]; // 存顶点的数据 
}; 
typedef ptrToGNode MGraph;
typedef struct ENode *ptrToENode;
struct ENode{  // 边 
	Vertex V1,V2;    // 有向边<V1,V2> 
	weightType Weight;  // 权重 
};
typedef ptrToENode Edge;

// 初始化图 
MGraph Create(int VertexNum){
	Vertex v,w;
	MGraph Graph;
	
	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	for(v=0;v<VertexNum;v++)
		for(w=0;w<VertexNum;w++)
			Graph->G[v][w] = 0;
	return Graph;
}

// 插入边 
MGraph Insert(MGraph Graph,Edge E){
	
	// 插入边 <V1,V2>
	Graph->G[E->V1][E->V2] = E->Weight;
	
	// 如果是无向图，还需要插入边 <V2,V1>
	Graph->G[E->V2][E->V1] = E->Weight;
	
} 

// 建图 
MGraph BuildGraph(){
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv,i;
	scanf("%d",&Nv);   // 读入顶点数 
	Graph = Create(Nv);
	scanf("%d",&(Graph->Ne));  // 读入边数 
	if(Graph->Ne != 0){   
		E = (Edge)malloc(sizeof(struct ENode));
		for(i=0;i<Graph->Ne;i++){
			scanf("%d %d %d",&E->V1,&E->V2,&E->Weight);  // 读入每个边的数据 
			Insert(Graph,E);
		}
	}
	return Graph;
}
*/ 

#include<stdio.h>
#include<stdlib.h>
#define MAXN 100
int G[MAXN][MAXN],Nv,Ne;

void BuildGraph(){
	int i,j,v1,v2,w;
	
	scanf("%d",&Nv);
	// 初始化图 
	for(i=0;i<Nv;i++) 
		for(j=0;j<Nv;j++)
			G[i][j] = 0;
	scanf("%d",&Ne);
	// 插入边 
	for(i=0;i<Ne;i++){
		scanf("%d %d %d",&v1,&v2,&w);
		G[v1][v2] = w;
		G[v2][v1] = w;
	}
}


// 遍历图
void print(){
	int i,j;
	for(i=0;i<Nv;i++){
		for(j=0;j<Nv;j++)
			printf("%d ",G[i][j]);
		printf("\n");
	}
} 

int main(){
	BuildGraph();
	print();
	return 0;
}
