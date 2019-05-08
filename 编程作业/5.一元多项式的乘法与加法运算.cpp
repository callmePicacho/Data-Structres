#include<stdio.h>
#include<stdlib.h>
typedef struct Node *List;
struct Node{
	List Next;
	int z;   // 指数 
	int x;  // 系数 
};

// 读入链表 
List Read(){
	List L = (List)malloc(sizeof(struct Node));
	List head = L;
	int n;
	int i=0;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		int x;
		int z;
		List t = (List)malloc(sizeof(struct Node));
		scanf("%d %d",&x,&z);
		t->x = x;
		t->z = z;
		L->Next = t;
		L = L->Next;
	}
	L->Next = NULL;
	return head->Next;
}

// 实现加法运算 
List addition(List L1,List L2){
	List tmpL1 = L1;
	List tmpL2 = L2;
	List add=(List)malloc(sizeof(struct Node));
	add->Next = NULL;
	List head = add;
	List t;
	while(tmpL1 && tmpL2){
		t = (List)malloc(sizeof(struct Node));
		if(tmpL1->z == tmpL2->z){  //指数相等，系数相加  
			t->x = tmpL1->x + tmpL2->x;
			t->z = tmpL1->z;
			tmpL1 = tmpL1->Next;
			tmpL2 = tmpL2->Next;
		}else if(tmpL1->z < tmpL2->z){   // L2 结点指数更大，把 L2 结点加入链表 
			t->x = tmpL2->x;
			t->z = tmpL2->z;
			tmpL2 = tmpL2->Next;
		}else if(tmpL2->z < tmpL1->z){   // L1 结点指数更大，把 L1 结点加入链表 
			t->x = tmpL1->x;
			t->z = tmpL1->z;
			tmpL1 = tmpL1->Next;
		}
		add->Next = t;
		add = add->Next; 
	}
	if(tmpL1)   // 若 L1 不等于 NULL，将剩下结点加入其后 
		add->Next = tmpL1;
	else if(tmpL2)  // 同理 
		add->Next = tmpL2;
	return head->Next; // head 结点只有指针域存值 
}

// 实现乘法运算 
List multiplication(List L1,List L2){
	List tmpL1 = L1;
	List tmpL2 = L2;
	List mul=(List)malloc(sizeof(struct Node));
	mul->Next = NULL;
	List head = mul;
	List t;
	for(;tmpL1;tmpL1=tmpL1->Next)
		for(tmpL2 = L2;tmpL2;tmpL2=tmpL2->Next){
			t = (List)malloc(sizeof(struct Node));
			t->x = tmpL1->x * tmpL2->x;  // 系数相乘
			t->z = tmpL1->z + tmpL2->z;  // 指数相加
			t->Next = NULL;
			head = addition(t,mul);  // 将新增结点和之前已经排好序的结点排序 
			mul = head; // 重新确定开头 
		}
	return head;
}
void Print(List L){
	List t = L;
	int flag = 1;
	for(;t;t = t->Next){
		if(!flag && t->x)   //控制空格输出
			printf(" ");
		if(t->x){   // 如果系数为 0，不输出 
			printf("%d %d",t->x,t->z);
			flag =0;		
		}
	}
	if(flag)
		printf("0 0");
	printf("\n");
}
int main(){
	List L1,L2,add,mul;
	L1 = Read();
	L2 = Read();
	add = addition(L1,L2);
	mul = multiplication(L1,L2);
	Print(mul);
	Print(add);
	return 0;
} 
