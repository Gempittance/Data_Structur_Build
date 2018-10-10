#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//------------
#define  EQ(a, b)	((a)==(b))	//a,bΪ��ֵ��
#define  LT(a, b)	((a)< (b))
#define  LQ(a, b)	((a)<=(b))

#define KeyType int
#define InfoType char

typedef struct
{
	KeyType key;	//����Ԫ���в��ҵĹؼ���
	InfoType* info;	//����Ԫ���е�������Ϣ
}ElemType;

typedef struct
{
	ElemType *elem;	//����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ����
	int length;		//����
}SSTable;
//------------

//�������Ķ�������洢��ʾ
#define TElemType ElemType

typedef struct BSTNode
{
	TElemType data;
	int pos;
	int bf;								//����ƽ������
	struct BSTNode *lchild ,*rchild;	//���Һ���ָ��
}BSTNode,*BSTree;

//������������ԭʼ����
KeyType arr1[] = {45,12,3,0,0,37,24,0,0,40,0,0,53,50,0,0,99,61,0,90,78,0,0,0,0};
KeyType arr2[] = {'A','B','E','\0','L','\0','\0','\0','D','H','M','\0','\0','I','\0','\0','J','\0','\0'};
KeyType arr3[] = {'-','+','a','\0','\0','*','b','\0','\0','-','c','\0','\0','d','\0','\0','/','e','\0','\0','f','\0','\0'};

int arr_i = 0;



//���������������������
int CreateBiTree(BSTree &T)
{
	KeyType ch;
	ch = arr1[arr_i++];
	if(ch == 0)
	{
		T = NULL;
	}
	else
	{
		if(!(T = (BSTNode *)malloc(sizeof(BSTNode))))
			exit(-1);
		T->data.key = ch;			//���ɸ��ڵ�
		T->pos = 32;
		CreateBiTree(T->lchild);//����������
		CreateBiTree(T->rchild);//����������
	}
	return 1;
}
//���÷�ʽ��CreatePos(T,T,p,0);
void CreatePos(BSTree T,BSTree f,BSTree &p,int flag)//flag == 1:������   flag == -1�������� 
{
	if(T)						//���Ҳ��ɹ�
	{
		//T->pos = f->pos + (flag * f->pos / 2);//������㲻��
		T->pos = flag * f->data.key;
		CreatePos(T->lchild,T,p,-1);
		CreatePos(T->rchild,T,p,1);
	}

}

int Visit(TElemType e)
{
	if(!e.key)
		return 0;
	printf("%d ",e.key);
	return 1;
}

void R_Rotate(BSTree &p)	//LLƽ����ת
	//����*pΪ���Ķ�����������������������֮��pָ���µ�������㣬
	//����ת����֮ǰ���������ĸ��ڵ�
{
	BSTree lc = p->lchild;	//lcָ���*p�����������ڵ�
	p->lchild = lc->rchild;	//lc���������ҽ�Ϊ*p��������
	lc->rchild = p;			//pָ���µĸ��ڵ�
	p = lc;					//��ԭ���ĸ��ڵ��Ϊ����������
}

void L_Rotate(BSTree &p)	//RRƽ����ת
	//����*pΪ���Ķ�����������������������֮��pָ���µ�������㣬
	//����ת����֮ǰ���������ĸ��ڵ�
{
	BSTree rc = p->rchild;	//rcָ��*p�����������ڵ�
	p->rchild = rc->rchild;	//rc���������ҽ�Ϊ*p��������
	rc->rchild = p;			//rc���������ҽӸ��ڵ�
	p = rc;					//��ԭ���ĸ��ڵ��Ϊ����������
}


int main(void)
{



	return 0;
}
