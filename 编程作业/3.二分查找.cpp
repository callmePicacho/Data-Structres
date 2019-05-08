#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L->Data = int[]{1,3,5};
    L->Last = 3;
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}

Position BinarySearch( List L, ElementType X ){
	ElementType left = 1;
	ElementType right = L->Last;
	while(left<right){
		ElementType center = (left+right)/2;  //先找中间值 
		if(L->Data[center] < X){     //比中间值大，X 在右半边 
			left = center+1;
		}else if(X < L->Data[center]){   //比中间值小，X 在左半边 
			right = center-1;
		}else  //找到了，直接返回 
			return center;
	}
	return NotFound;
} 
