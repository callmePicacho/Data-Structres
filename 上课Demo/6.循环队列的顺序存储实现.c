#include<stdio.h>
#include<malloc.h>
#define MaxSize 100
typedef int ElementType;
typedef struct QNode *Queue;
struct QNode{
	ElementType Data[MaxSize];
	int front;   // 记录队头 
	int rear;    // 记录队尾 
};

Queue CreateQueue();  // 初始化队列 
void AddQ(Queue Q,ElementType item);  //  入队
int IsFull(Queue Q); // 判断队列是否已满 
ElementType DeleteQ(Queue Q);  // 出队 
int IsEmpty(Queue Q); // 判断队列是否为空 

// 初始化 
Queue CreateQueue(){
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QNode));
	Q->front = -1;
	Q->rear = -1;
	return Q;
} 

// 判断队列是否已满
int IsFull(Queue Q){
 	return ((Q->rear+1) % MaxSize == Q->front);
}

// 入队 
void AddQ(Queue Q,ElementType item){
	if(IsFull(Q)){
		printf("队列满");
		return;
	}else{ 
		Q->rear = (Q->rear+1) % MaxSize;
		Q->Data[Q->rear] = item; 
	}
}

//判断队列是否为空
int IsEmpty(Queue Q){
	return (Q->front == Q->rear);
}
 
// 出队
ElementType DeleteQ(Queue Q){
	if(IsEmpty(Q)){
		printf("队列空");
		return 0;
	}else{
		Q->front = (Q->front+1) % MaxSize;
		return Q->Data[Q->front];
	}
} 

int main(){
	Queue Q;
	Q = CreateQueue();
	AddQ(Q,3);
	printf("3入队\n");
	AddQ(Q,5);
	printf("5入队\n");
	AddQ(Q,11);
	printf("11入队\n");
	printf("%d出队\n",DeleteQ(Q));
	printf("%d出队\n",DeleteQ(Q));
	return 0;
} 




