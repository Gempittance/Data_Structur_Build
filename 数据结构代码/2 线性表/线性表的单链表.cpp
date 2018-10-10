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
	//�����ǽ��еĲ���Ҫ���У�д����ʱ���������û��ַ
{
	LinkList p = L->next;	//ָ���j�����
	int j = 1;				//�ӵ�һ����ʼ������
	while ( p && j < i )	//p��Ϊ����j < i
	{
		p = p->next;
		++j;
	}						//pΪ�գ�˵������ѭ��������Ҳû�е���i�����   j==i
	if (!p || j > i)		//��Ϊ�˴���i   û�����ж�   ��� i==0  �� ����  ��������
							//���� i == j == 1 ���������ѭ������  ����
	{
		return ERROR;
	}
	*e = p->data;			//ͨ��Ѱַ�ı��� �õ�ַ�ڴ���Ԫ�ص�ֵ
	return OK;
}
//�����мȿ��Դ���L��Ҳ������ *L   Ҳ������&L
Status ListInsert_L(LinkList L,int i,ElemType e)	//�����޸�Ӧ�ò��� p = *L����
													//����дû�����⣬��Ϊpָ��ǰ�ڵ㣬�����޸�ֵ
							//ͷ����next����ܻ�ı䣬��˴���ͷָ��ĵ�ַ
{
	LinkList p = L;
	int j = 0;				//��Ϊ����Ѱ�ҵ��ǲ������ǰ������˴�ͷ��㿪ʼ
	LinkList s;
	while (p && j < i - 1)	//Ѱ�ҵ�i-1�����
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
	p->next = s;				//����������������һ��λ�����⣻���ǵڶ���һ��Ҫ�ڵ�����ǰ��
	return OK;
}
//�����мȿ��Դ���L��Ҳ������ *L   Ҳ������&L
Status ListDelete_L(LinkList L,int i,ElemType *e)
{
	LinkList p = L;
	LinkList q;
	int j = 0;
	while (p->next && j < i-1)	//�ҵ�ɾ������ǰ�������ұ�֤���ǰ�����Next��Ϊ��
								//��Ϊ���ǰ������Next������ǿգ��޷����ɾ������
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

