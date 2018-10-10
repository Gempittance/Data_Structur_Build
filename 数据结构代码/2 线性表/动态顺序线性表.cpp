#include <stdio.h>
#include <stdlib.h>
#include <malloc.h> 

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct
{
	int *elem;
	int length;
	int listsize;
}SqList;
//初始化
int InitList_Sq(SqList *L)
{
	//构造一个空的线性表L
	L->elem = (int *)malloc((LIST_INIT_SIZE)*sizeof(int));
	if(! L->elem) return 0;        //存储分配失败
	L->length = 0;                 //空表长度为0
	L->listsize = LIST_INIT_SIZE;  //初始存储的容量
	return 1;
}

//在顺序线性表L中第i个位置之前插入新的元素e
int ListInsert_Sq(SqList *L,int i,int e)
{
	//在顺序线性表L中第i个位置之前插入新的元素e
	//i的合法值为1 <= i <= ListLength_Sq(L)+1
	int *q,*p,*newbase;
	if(i < 1 || i > L->length +1 ) return 0;     //i值不合法
	if(L->length >= L->listsize ){               //当前存储空间已满，增加分配
		newbase = (int *)realloc(L->elem/*要改变大小的指针名*/
			,(L->listsize + LISTINCREMENT)*sizeof(int));
		if(! newbase) return 0;					 //存储分配失败
		L->elem = newbase;						 //新基址
		L->listsize += LISTINCREMENT;			 //增加存储容量
	} 
	q = &(L->elem[i - 1]);			         	 //q为插入位置
	for(p = &(L->elem[L->length-1]);p >= q; --p)
		*(p+1) = *p;							 //插入位置及之后的元素右移
	*q = e;										 //插入e
	L->length++;
	return 1;
}

//在顺序线性表L中删除第i个元素，并用e返回其值
int ListDelete_Sq(SqList *L,int i,int *e)
{
	//在顺序线性表L中删除第i个元素，并用e返回其值
	//i的合法值为1 <= i <= ListLength_Sq(L)
	int *p,*q;
	if ((i < 1) || (i > L->length))	
		return 0;								 //i值不合法
	p = &(L->elem[i-1]);						 //p为被删除元素的位置
	*e = *p;									 //将被删除元素的值赋给e （待定）
	q = L->elem + L->length-1;					 //移动到表尾元素的位置
	for (++p;p<=q;++p)
		*(p-1) = *p;							 //被删除元素之后的元素左移
	L->length--;
	return 1;
}

void ListPrint_Sq(SqList *L)
{
	int i = 0;
	for(i = 0;i < L->length; i++)
	{
		printf("  %d",L->elem[i]);
	}
	printf("  \n");
}

//冒泡法排序
void bubble_sort(int a[],int n)  
{
	int i = 0,change = 0,j,temp;
	for(i = n-1,change = 1;i >= 1 && change; --i)
	{
		change = 0;
		for(j = 0;j < i; ++j)
			if(a[j] > a[j+1])
			{
				temp = a[j]; a[j] = a[j+1]; a[j+1] = temp;
			}
	}
}



	int main(void)
	{
		SqList L;
		int i,e,j,r;
		int Status = InitList_Sq(&L);
		if(!Status)  printf("线性表创建失败！\n");
		for(i = 1;i < 10; i++)
		{
			e = rand()%4;
			Status = ListInsert_Sq(&L,i,e);
			if(!Status)	printf("线性表插入失败！\n");
		}

		ListPrint_Sq(&L);
		bubble_sort(L->elem, L->length);
		ListPrint_Sq(&L);

		system("pause");
	}
