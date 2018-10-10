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
//��ʼ��
int InitList_Sq(SqList *L)
{
	//����һ���յ����Ա�L
	L->elem = (int *)malloc((LIST_INIT_SIZE)*sizeof(int));
	if(! L->elem) return 0;        //�洢����ʧ��
	L->length = 0;                 //�ձ���Ϊ0
	L->listsize = LIST_INIT_SIZE;  //��ʼ�洢������
	return 1;
}

//��˳�����Ա�L�е�i��λ��֮ǰ�����µ�Ԫ��e
int ListInsert_Sq(SqList *L,int i,int e)
{
	//��˳�����Ա�L�е�i��λ��֮ǰ�����µ�Ԫ��e
	//i�ĺϷ�ֵΪ1 <= i <= ListLength_Sq(L)+1
	int *q,*p,*newbase;
	if(i < 1 || i > L->length +1 ) return 0;     //iֵ���Ϸ�
	if(L->length >= L->listsize ){               //��ǰ�洢�ռ����������ӷ���
		newbase = (int *)realloc(L->elem/*Ҫ�ı��С��ָ����*/
			,(L->listsize + LISTINCREMENT)*sizeof(int));
		if(! newbase) return 0;					 //�洢����ʧ��
		L->elem = newbase;						 //�»�ַ
		L->listsize += LISTINCREMENT;			 //���Ӵ洢����
	} 
	q = &(L->elem[i - 1]);			         	 //qΪ����λ��
	for(p = &(L->elem[L->length-1]);p >= q; --p)
		*(p+1) = *p;							 //����λ�ü�֮���Ԫ������
	*q = e;										 //����e
	L->length++;
	return 1;
}

//��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
int ListDelete_Sq(SqList *L,int i,int *e)
{
	//��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
	//i�ĺϷ�ֵΪ1 <= i <= ListLength_Sq(L)
	int *p,*q;
	if ((i < 1) || (i > L->length))	
		return 0;								 //iֵ���Ϸ�
	p = &(L->elem[i-1]);						 //pΪ��ɾ��Ԫ�ص�λ��
	*e = *p;									 //����ɾ��Ԫ�ص�ֵ����e ��������
	q = L->elem + L->length-1;					 //�ƶ�����βԪ�ص�λ��
	for (++p;p<=q;++p)
		*(p-1) = *p;							 //��ɾ��Ԫ��֮���Ԫ������
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

//ð�ݷ�����
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
		if(!Status)  printf("���Ա���ʧ�ܣ�\n");
		for(i = 1;i < 10; i++)
		{
			e = rand()%4;
			Status = ListInsert_Sq(&L,i,e);
			if(!Status)	printf("���Ա����ʧ�ܣ�\n");
		}

		ListPrint_Sq(&L);
		bubble_sort(L->elem, L->length);
		ListPrint_Sq(&L);

		system("pause");
	}
