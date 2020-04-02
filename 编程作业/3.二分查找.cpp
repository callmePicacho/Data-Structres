#include "stdafx.h"
#include<stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode
{
	ElementType Data[MAXSIZE];
	Position Last;/* 保存线性表中最后一个元素的位置 */
};

List CreatList();//初始化链表
Position BinarySearch(List L, ElementType X);

List CreatList()
{
	List L;
	L = (List)malloc(sizeof(struct LNode));
	L->Last = NULL;
	return L;
}

Position BinarySearch(List L, ElementType X)
{
	ElementType left = 1;
	ElementType right = L->Last;
	while (left < right)
	{
		ElementType center = (left + right) / 2;
		if (L->Data[center] < X)
			left = center + 1;
		else if (X < L->Data[center])
			right = center - 1;
		else
			return center;
	}
	return NotFound;
}

int main()
{
	List L;
	ElementType X;
	Position P;

	L = CreatList();
	for (int i = 1; i < 4; i++)
		L->Data[i] = 2 * i - 1;
	L->Last = 3;
	scanf("%d", &X);
	P = BinarySearch(L, X);
	printf("%d\n", P);

    return 0;
}
