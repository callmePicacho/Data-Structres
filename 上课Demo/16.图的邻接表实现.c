/*#include<stdio.h>
#include<stdlib.h>
#define MaxVertexNum 100
typedef int Vertex; 
typedef int DataType; 
typedef int weightType;  

typedef struct ENode *ptrToENode;
struct ENode{  // 边 
	Vertex V1,V2;    // 有向边<V1,V2> 
	weightType Weight;  // 权重 
};
typedef ptrToENode Edge;

typedef struct AdjVNode *ptrToAdjVNode;
struct AdjVNode{  // 邻接表内元素 
	Vertex AdjV;  // 邻接点下标 
	weightType Weight;  // 权值 
	ptrToAdjVNode Next;  // 下一个 
};

typedef struct VNode{  // 邻接表头 
	ptrToAdjVNode FirstEdge;  // 存每个顶点指针
	DataType Data;  // 顶点数据 
}AdjList[MaxVertexNum];

typedef struct GNode *ptrToGNode;
struct GNode{  // 图 
	int Nv;  // 顶点
	int Ne;  // 边数 
	AdjList G; // 邻接表 
}; 
typedef ptrToGNode LGraph;

// 初始化 
LGraph create(int VertexNum){
	Vertex v,w;
	LGraph Graph;
	
	Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;  // 初始化边
	Graph->Ne = 0;   // 初始化点
	
	// 每条边的 FirstEdge 指向 NULL 
	for(v=0;v<Graph->Nv;v++)
		Graph->G[v].FirstEdge = NULL;
	return Graph;
}


// 插入一条边到邻接表的顶点指针之后 
void InsertEdge(LGraph Graph,Edge E){
	ptrToAdjVNode newNode; 
	
	            //   插入边<V1,V2> 
	// 为 V2 建立新的结点 
	newNode = (ptrToAdjVNode)malloc(sizeof(struct AdjVNode));
	newNode->AdjV = E->V2;
	newNode->Weight = E->Weight;
	
	// 将 V2 插入到邻接表头 
	newNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = newNode;
	
	          //   若为无向图，插入边<V2,V1>
	newNode = (ptrToAdjVNode)malloc(sizeof(struct AdjVNode));
	newNode->AdjV = E->V1;
	newNode->Weight = E->Weight;
	
	newNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = newNode;
} 

// 建图
LGraph BuildGraph(){
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv,i;
	scanf("%d",&Nv);
	Graph = create(Nv);
	scanf("%d",&(Graph->Ne));
	if(Graph->Ne != 0){
		for(i=0;i<Graph->Ne;i++){
			E = (Edge)malloc(sizeof(struct ENode));
			scanf("%d %d %d",&E->V1,&E->V2,&E->Weight);
			InsertEdge(Graph,E);
		}
	}
	return Graph;
} 

// 打印 
void print(LGraph Graph){
	Vertex v;
	ptrToAdjVNode tmp;
	for(v=0;v<Graph->Nv;v++){
		tmp = Graph->G[v].FirstEdge;
		printf("%d ",v);
		while(tmp){
			printf("%d ",tmp->AdjV);
			tmp = tmp->Next;
		}
		printf("\n");
	}
}

int main(){
	LGraph Graph;
	Graph = BuildGraph();
	print(Graph);
	return 0;
}*/ 

#include<stdio.h>
#include<stdlib.h>
#define MaxVertexNum 100
typedef struct AdjVNode *AdjList;
struct AdjVNode{
	int weight;  // 权值 
  	int adjv;   // 下标 
	AdjList next;  // 其后一个 
};
AdjList Graph[MaxVertexNum];
int Ne,Nv;

// 建图
void BuildGraph(){
	int i;
	int v1,v2,w;
	AdjList NewNode;
	scanf("%d",&Nv);
	for(i=0;i<Nv;i++){
		Graph[i] = (AdjList)malloc(sizeof(struct AdjVNode));
		Graph[i]->adjv = i;
		Graph[i]->next = NULL;
	}
	scanf("%d",&Ne);
	for(i=0;i<Ne;i++){
		scanf("%d %d %d",&v1,&v2,&w);
		NewNode = (AdjList)malloc(sizeof(struct AdjVNode));
		NewNode->adjv = v1;
		NewNode->weight = w;
		
		NewNode->next = Graph[v2]->next;
		Graph[v2]->next = NewNode;
		
		NewNode = (AdjList)malloc(sizeof(struct AdjVNode));
		NewNode->adjv = v2;
		NewNode->weight = w;
		
		NewNode->next = Graph[v1]->next;
		Graph[v1]->next = NewNode;
	}
} 

void print(){
	AdjList tmp;
	int i;
	for(i=0;i<Nv;i++){
		tmp = Graph[i];
		while(tmp){
			printf("%d ",tmp->adjv);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

int main(){
	
	BuildGraph();
	print();
	return 0;
}

