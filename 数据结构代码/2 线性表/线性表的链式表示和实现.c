#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

typedef struct Node
{
	ElemType data;
	struct Node * Next;		//��������struct
}LNode,*LinkList;

Status Init(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->data = 0;
	(*L)->Next = NULL;
	return OK;
}

Status GetElemt_L(LinkList L,int i,ElemType *e)
	//�����ǽ��еĲ���Ҫ���У�д����ʱ���������û��ַ
{
	LinkList p = L->Next;	//ָ���j�����
	int j = 1;				//�ӵ�һ����ʼ������
	while ( p && j < i )	//p��Ϊ����j < i
	{
		p = p->Next;
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
		p = p->Next;
		++j;
	}						
	if (!p || j > i - 1)
	{
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->Next = p->Next;
	p->Next = s;				//����������������һ��λ�����⣻���ǵڶ���һ��Ҫ�ڵ�����ǰ��
	return OK;
}
//�����мȿ��Դ���L��Ҳ������ *L   Ҳ������&L
Status ListDelete_L(LinkList L,int i,ElemType *e)
{
	LinkList p = L;
	LinkList q;
	int j = 0;
	while (p->Next && j < i-1)	//�ҵ�ɾ������ǰ�������ұ�֤���ǰ�����Next��Ϊ��
								//��Ϊ���ǰ������Next������ǿգ��޷����ɾ������
	{
		p = p->Next;
		++j;
	}
	if ((p->Next) == NULL || j > i-1)
	{
		return ERROR;
	}
	q = p->Next;
	p->Next = q->Next;
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

