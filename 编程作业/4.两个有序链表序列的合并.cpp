#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Merge( List L1, List L2 ){
	List L=(List)malloc(sizeof(struct Node));
	List head = L;
	List tmpL1 = L1->Next;
	List tmpL2 = L2->Next;
	while(tmpL1 && tmpL2){
		if(tmpL1->Data < tmpL2->Data){
			L->Next=tmpL1;
			tmpL1=tmpL1->Next;
		}else{
			L->Next=tmpL2;
			tmpL2=tmpL2->Next;
		}
		L=L->Next;
	}
	if(tmpL1)
		L->Next=tmpL1;
	if(tmpL2)
		L->Next=tmpL2;
	L1->Next = NULL;
	L2->Next = NULL;
	return head;
} 


















