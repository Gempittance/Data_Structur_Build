#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define Status int
#define OVERFLOW -1
#define OK 1
#define ERROR 0


#define ElemType int
typedef struct
{
	ElemType * elem;
	int length;
	int listsize;
}SqList;

Status InitList(SqList &L)
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem)
		exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

void Destroy(SqList &L)
{
	free(L.elem);  
	L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
}

int LocateElem(SqList L,ElemType e)
{
	int i;
	for(i = 0;i < L.length;i++)
	{
		if(L.elem[i] == e)
			return i+1;
	}
	return 0;
}

void UnionList(SqList &La,SqList Lb)
{
	int La_en = La.length;
	int Lb_len = Lb.length;
	int i;
	for(i = 0;i < Lb_len ;i++)
	{
		ElemType e = Lb.elem[i];
		if(!LocateElem(La,e))
		{
			La.length++;
			La.elem[La.length-1] = e;
		}
	}
}

Status ListInsert(SqList &L, int i,ElemType e)
{
	ElemType *p, *q, *newbase;
	if(i < 1 || i > L.length + 1)
	{
		printf("i不合法，不能插入！\n");
		return ERROR;
	}
	if(L.length >= L.listsize)
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if(!newbase)
			return ERROR;
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	p = &L.elem[i-1];
	for(q = &L.elem[L.length-1]; q >= p; --q)
		*(q+1) = *q;
	*p = e;
	++L.length;
	return OK;
}


void visit(ElemType e)
{
	printf("%d ",e);
}

void TraverseList(SqList La, void (*pvist)(ElemType ))
{
	int i;
	for(i = 0; i < La.length; ++i)
	{
		pvist(La.elem[i]);
	}
	printf("\n");
}

Status ListDelete(SqList &L,int i,ElemType &e)
{
	ElemType *p, *q;
	int k = 0;
	if(i < 1 || i > L.length)
	{
		printf("删除位置有误!\n");
		return ERROR;
	}
	e = L.elem[i-1];
	for(k = i-1; k < L.length-1; ++k)
	{
		L.elem[k] = L.elem[k+1];
	}
	--L.length;
	return OK;
}

void DeleteMin(SqList &L)
{
	int i, min = 0;
	ElemType e = L.elem[0];
	for(i = 1; i < L.length; ++i)
	{
		if(L.elem[i] < e)
		{
			e = L.elem[i];
			min = i;
		}
	}
	ListDelete(L,min+1, e);
}

void ListPrint(SqList L)
{
	int i;
	ElemType e;
	for(i = 0; i < L.length; ++i)
	{
		printf("%d ",L.elem[i]);
	}
	printf("\n");

}


//1 2 2 3 4 5 6 7
int main(void)
{
	SqList L;
	int i;
	ElemType e;
	ElemType data[9] = {11,-22,-33,3,-88,21,77,0,-9}; 
	InitList(L);
	for (i = 1; i <= 9; i++)
	{
		ListInsert(L,i,data[i-1]);
	}
	printf("插入完成后 L = : ");
	ListPrint(L);
	ListDelete(L, 2, e);
	printf("删除第 2 个后L = : ");
	ListPrint(L);
	DeleteMin(L);
	printf("删除L中最小值后L = : ");
	ListPrint(L);
	DeleteMin(L);
	printf("删除L中最小值后L = : ");
	ListPrint(L);
	DeleteMin(L);
	printf("删除L中最小值后L = : ");
	ListPrint(L);
	

	
	

	return 0;
}



