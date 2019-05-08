#include<stdio.h>
#include<malloc.h>
typedef int ElementType; // ElementType 可定义为任意类型
typedef struct LNode *List;
struct LNode{
	ElementType Data;   //数据域 
	List Next;   // 下一个链表的地址 
}; 
List L;

List MakeEmpty(); //初始化链表 
int Length(List L);  // 以遍历链表的方法求链表长度 
List FindKth(int K,List L);  // 按序号查找 
List Find(ElementType X,List L);  // 按值查找 
List Insert(ElementType X,int i,List L);  //将 X 插入到第 i-1(i>0) 个结点之后 
List Delete(int i,List L); // 删除第 i(i>0) 个结点 
void Print(List L); // 输出链表元素 

// 初始化链表 
List MakeEmpty(){
	List L = (List)malloc(sizeof(struct LNode));
	L = NULL;
	return L;
}

//求表长 
int Length(List L){
	List p = L;
	int len=0;
	while(p){  // 当 p 不为空 
		p = p->Next;
		len++;
	}
	return len;
} 

// 按序查找 
List FindKth(int K,List L){
	List p = L;
	int i = 1;  //从 1 开始 
	while(p && i<K){
		p = p->Next;
		i++;
	}
	if(i == K)    // 找到了 
		return p;
	else    // 未找到 
		return NULL;
} 

// 按值查找  
List Find(ElementType X,List L){
	List p = L;
	while(p && p->Data!=X)
		p = p->Next;
	// 找到了，返回 p
	// 未找到，返回 NULL，此时 p 等于 NULL 
	return p;   
} 

/* 插入
1. 用 s 指向一个新的结点
2. 用 p 指向链表的第 i-1 个结点 
3. s->Next = p->Next，将 s 的下一个结点指向 p 的下一个结点 
4. p->Next = s，将 p 的下一结点改为 s   */
List Insert(ElementType X,int i,List L){
	List p,s;
	if(i == 1){     // 新结点插入在表头 
		s = (List)malloc(sizeof(struct LNode));
		s->Data = X;
		s->Next = L;
		return s;     //插入的结点为头结点 
	}
	p = FindKth(i-1,L);   // 找到第 i-1 个结点
	if(!p){   // 第 i-1 个结点不存在 
		printf("结点错误");
		return NULL;
	}else{
		s = (List)malloc(sizeof(struct LNode));
		s->Data = X;
		s->Next = p->Next;   //将 s 的下一个结点指向 p 的下一个结点 
		p->Next = s;   // 将 p 的下一结点改为 s
		return L;
	}
}

/* 删除
1. 用 p 指向链表的第 i-1 个结点 
2. 用 s 指向要被删除的的第 i 个结点
3. p->Next = s->Next，p 指针指向 s 后面
4. free(s)，释放空间 
*/
List Delete(int i,List L){
	List p,s;
	if(i==1){   //如果要删除头结点 
		s = L;
		if(L)   // 如果不为空 
			L = L->Next;
		else
			return NULL;
		free(s);   // 释放被删除结点 
		return L; 
	}
	p = FindKth(i-1,L);    // 查找第 i-1 个结点
	if(!p || !(p->Next)){     // 第 i-1 个或第 i 个结点不存在 
		printf("结点错误");
		return NULL;
	}else{
		s = p->Next;    // s 指向第 i 个结点 
		p->Next = s->Next;  //从链表删除 
		free(s);  // 释放被删除结点 
		return L;
	}
}

// 输出链表元素 
void Print(List L){
	List t;
	int flag = 1;
	printf("当前链表为：");
	for(t = L;t;t =t->Next){
		printf("%d  ",t->Data);
		flag = 0;
	}
	if(flag)
		printf("NULL");
	printf("\n"); 
}

int main(){
	L = MakeEmpty();
	Print(L);
	L = Insert(11,1,L);
	L = Insert(25,1,L);
	L = Insert(33,2,L);
	L = Insert(77,3,L);
	Print(L);
	printf("当前链表长度为：%d\n",Length(L));
	printf("此时链表中第二个结点的值是：%d\n",FindKth(2,L)->Data);
	printf("查找22是否在该链表中：");
	if(Find(22,L))
		printf("是！\n");
	else
		printf("否！\n");
	printf("查找33是否在该链表中：");
	if(Find(33,L))
		printf("是！\n");
	else
		printf("否！\n");
	L = Delete(1,L);
	L = Delete(3,L);
	printf("----------删除后-----\n"); 
	Print(L);
	return 0;
} 
