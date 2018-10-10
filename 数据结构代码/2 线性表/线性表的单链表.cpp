#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

typedef struct Node
{
	ElemType data;
	struct Node * next;	
}LNode,*LinkList;

Status Init(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->data = 0;
	(*L)->next = NULL;
	return OK;
}

LinkList GetElem_L1(LinkList L1, ElemType key) 
{ 
	LinkList p = L1->next; 
	while (p && p->data != key)      
		p = p->next; 
	return p; 
} // GetElem_L1 


Status GetElemt_L(LinkList L,int i,ElemType *e)
	//当我们进行的操作要进行，写操作时，传递引用或地址
{
	LinkList p = L->next;	//指向第j个结点
	int j = 1;				//从第一个开始往后找
	while ( p && j < i )	//p不为空且j < i
	{
		p = p->next;
		++j;
	}						//p为空，说明链表循环结束，也没有到第i个结点   j==i
	if (!p || j > i)		//因为此处对i   没有做判断   如果 i==0  或 负数  条件成立
							//对于 i == j == 1 的情况则不用循环正好  返回
	{
		return ERROR;
	}
	*e = p->data;			//通过寻址改变了 该地址内存中元素的值
	return OK;
}
//链表中既可以传递L，也可以是 *L   也可以是&L
Status ListInsert_L(LinkList L,int i,ElemType e)	//这样修改应该不对 p = *L出错
													//这样写没有问题，因为p指向当前节点，可以修改值
							//头结点的next域可能会改变，因此传递头指针的地址
{
	LinkList p = L;
	int j = 0;				//因为我们寻找的是插入结点的前驱，因此从头结点开始
	LinkList s;
	while (p && j < i - 1)	//寻找第i-1个结点
	{
		p = p->next;
		++j;
	}						
	if (!p || j > i - 1)
	{
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;				//对于以上三步：第一步位置任意；但是第二步一定要在第三步前面
	return OK;
}
//链表中既可以传递L，也可以是 *L   也可以是&L
Status ListDelete_L(LinkList L,int i,ElemType *e)
{
	LinkList p = L;
	LinkList q;
	int j = 0;
	while (p->next && j < i-1)	//找到删除结点的前驱，并且保证这个前驱结点Next域不为空
								//因为如果前驱结点的Next域如果是空，无法完成删除操作
	{
		p = p->next;
		++j;
	}
	if ((p->next) == NULL || j > i-1)
	{
		return ERROR;
	}
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}

int main(void)
{
	LinkList L1;int e;
	Init(&L1);
	printf("%d\n",ListInsert_L(L1,1,11));
	printf("%d\n",ListInsert_L(L1,2,22));
	printf("%d\n",ListInsert_L(L1,3,33));
	printf("%d\n",ListInsert_L(L1,4,44));
	GetElemt_L(L1,1,&e);
	printf("%d\n",e);
	GetElemt_L(L1,2,&e);
	printf("%d\n",e);
	ListDelete_L(L1,2,&e);
	GetElemt_L(L1,2,&e);
	printf("%d\n",e);


	return 0;
}

