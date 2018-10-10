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

typedef struct BiTNode
{
	TElemType data;
	int pos;
	struct BiTNode *lchild ,*rchild;	//���Һ���ָ��
}BiTNode,*BiTree;

//������������ԭʼ����
KeyType arr1[] = {45,12,3,0,0,37,24,0,0,40,0,0,53,50,0,0,99,61,0,90,78,0,0,0,0};
KeyType arr2[] = {'A','B','E','\0','L','\0','\0','\0','D','H','M','\0','\0','I','\0','\0','J','\0','\0'};
KeyType arr3[] = {'-','+','a','\0','\0','*','b','\0','\0','-','c','\0','\0','d','\0','\0','/','e','\0','\0','f','\0','\0'};

int arr_i = 0;



//���������������������
int CreateBiTree(BiTree &T)
{
	KeyType ch;
	ch = arr1[arr_i++];
	if(ch == 0)
	{
		T = NULL;
	}
	else
	{
		if(!(T = (BiTNode *)malloc(sizeof(BiTNode))))
			exit(-1);
		T->data.key = ch;			//���ɸ��ڵ�
		T->pos = 32;
		CreateBiTree(T->lchild);//����������
		CreateBiTree(T->rchild);//����������
	}
	return 1;
}
//���÷�ʽ��CreatePos(T,T,p,0);
void CreatePos(BiTree T,BiTree f,BiTree &p,int flag)//flag == 1:������   flag == -1�������� 
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

int InOrderTraverse(BiTree T,int (*Visit)(TElemType e))
	//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
	//�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
{
	if(T)
	{
		if(InOrderTraverse(T->lchild,Visit))
			if(Visit(T->data))
				if(InOrderTraverse(T->rchild,Visit))
					return 1;
		return 0;
	}else
	{
		return 1;
	}
}

//***********�����˲��õݹ飬�Զ����������в�����һ�㷽��**********//
void CountLeaf(BiTree T, int &count)
	//�����������������count���ض�������Ҷ�ӽ�����Ŀ
	//conut��Ϊ���������ڴ���ʱcount��main��Ҫ����
{
	if(T)
	{
		if((!T->lchild) && (!T->rchild))	//��û��������Ҳû��������
			++count;						//��Ҷ�ӽ�����
		CountLeaf(T->lchild,count);
		CountLeaf(T->rchild,count);
	}
}// CountLeaf

int BiTreeDepth(BiTree T)
{
	int depth  , depthleft ,depthright ;
	if(!T)
	{
		depth = 0;
	}
	else
	{
		depthleft  = BiTreeDepth(T->lchild);
		depthright = BiTreeDepth(T->rchild);
		depth = (depthleft > depthright ? depthleft : depthright) + 1;
	}
	return depth;
}

//---------------------
#define QElemType BiTree

//---�������С������е���ʽ�洢�ṹ(��ͷ���)---
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;	//��ͷָ��
	QueuePtr rear;	//��βָ��
}LinkQueue;

int InitQueue(LinkQueue &Q)	//��ͷ���Ķ���
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));	//��ͷ���Ķ���
	if(!Q.front)	//�洢����ʧ��
		exit(-1);
	Q.front->next = NULL;
	return 1;
}

int DestroyQueue(LinkQueue &Q)
	//���ٶ���Q
{
	while(Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return 1;
}

int EnQueue(LinkQueue &Q, QElemType e)
	//����Ԫ��eΪQ���µĶ�βԪ��
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)		//�洢����ʧ��
		exit(-1);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}

int DeQueue(LinkQueue &Q, QElemType &e)
	//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������1
	//���򷵻�0
{
	QueuePtr p;
	if(Q.front == Q.rear)
		return 0;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return 1;
}

void PrintQueue(LinkQueue Q)
{
	QueuePtr p = Q.front->next;
	printf("\n|");
	while (p)
	{
		printf(" %d ",p->data->data.key);
		p = p->next;
	}
	printf(" |\n");
}

//ͳ��ÿ��ڵ�ĸ��� 
void countNumOfLevel(BiTree root,int depth, int &res)
{
    if(root==NULL||depth<0)
        return;
    if(depth==0){
        res++;
        return;
    }    
    countNumOfLevel(root->lchild,depth-1,res);
    countNumOfLevel(root->rchild,depth-1,res);
}

void PrintSpace(int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf(" ");
}



int LayerOrder(BiTree bt)   //��α��������� �ɹ���������1 ʧ�ܷ���0
{
    LinkQueue Q;
    BiTree p;
	int i = 0,r = 1,depth = 1;
    InitQueue(Q);
    if(bt == NULL) return 0;
    EnQueue(Q,bt);
	//PrintQueue(Q);
	while(Q.front != Q.rear)
	{
		if(DeQueue(Q,p));
		{
			++i;
			printf("(%d, %d)",p->data.key,p->pos);
			//PrintQueue(Q);
		}
		if(p->lchild)
		{
			EnQueue(Q,p->lchild);
			//PrintQueue(Q);
		}
		if(p->rchild) 
		{
			EnQueue(Q,p->rchild);
			//PrintQueue(Q);
		}
		
		if(i == r)
		{
			printf("\n");
			countNumOfLevel(bt,depth,r);
			++depth;
		}
		
	}
    return 1;
}


//-----------




BiTree SearchBST1(BiTree T,KeyType key)
	//�ڸ�ָ��T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ�أ�
	//�����ҳɹ����򷵻�ָ������ݽ���ָ�룬���򷵻ؿ�ָ��
{
	if((!T) || EQ(key,T->data.key))
		return T;							//���ҽ���
	else if(LT(key, T->data.key))
		return (SearchBST1(T->lchild,key));	//���������м�������
	else
		return (SearchBST1(T->rchild,key));	//���������м�������
}



int SearchBST2(BiTree T,KeyType key,BiTree f,BiTree &p)
	//�ڸ�ָ��T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ�أ�
	//�����ҳɹ���ָ��pָ�������Ԫ�صĽ�㣬������1������pָ�����·��
	//�Ϸ��ʵ����һ����㲢����0��ָ��fָ��T��˫�ף��ҳ�ʼ����ֵ��NULL
{
	if(!T)						//���Ҳ��ɹ�
	{
		p = f;
		return 0;
	}
	else if(EQ(key,T->data.key))//���ҳɹ�
	{
		p = T;
		return 1;
	}else if(LT(key,T->data.key))//����������������
	{
		return SearchBST2(T->lchild,key,T,p);
	}
	else						//����������������
	{
		return SearchBST2(T->rchild,key,T,p);
	}
}

void PrintSearchBST(BiTree T1)
{
	if(T1)
		printf("�鵽�Ľ����%d��\n", T1->data.key);
	else
		printf("δ�鵽�����\n");
}

int InsertBST(BiTree &T, ElemType e)
	//������������T�в����ڹؼ��ֵ���e.key������Ԫ��ʱ������e������1��
	//���򷵻�0.
{
	BiTree p, s;	
	if(!SearchBST2(T,e.key,NULL,p))
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data.key = e.key;
		s->lchild = s->rchild = NULL;
		if(!p)
			T = s;						//����ڵ�*sΪ�µĸ��ڵ�
		else if(LT(e.key,p->data.key))	//�жϲ���Ľ��keyֵ�Ͳ���λ��˫�׽���С���жϲ�����߻����ұ�
			p->lchild = s;				//����ڵ�*sΪ�µ����ӽڵ�
		else
			p->rchild = s;				//����ڵ�*sΪ�µ��Һ��ӽڵ�
		return 1;
	}

	return 0;	//�����Ѵ��ڹؼ�����ͬ�Ľ�㣬���ز���
}

//Ŀ������Ҫɾ������ǰ������ǰ������Ҫɾ���Ľ�㣬��������ʹ������������ܵ�Ӱ��
int Delete(BiTree &p)
	//�Ӷ�����������ɾ�����p�����ؽ��������������
{
	BiTree q, s;
	if(!p->rchild)		//����������ֻ���ؽ����������� ����Ҷ�ӽ��ɾ�����
	{
		q = p;
		p = p->lchild;
		free(q);
	}else if(!p->lchild)//ֻ���ؽ�����������
	{
		q = p;
		p = p->rchild;
		free(q);
	}else				//��������������
	{
		q = p;
		s = p->lchild;
		while (s->rchild)
		{
			q = s;
			s = s->rchild;	//sָ����������Ȼ�������ߵ���ͷ��Ҳ���Ǳ�ɾ�����ġ�ǰ����
		}
		p->data = s->data;	//��ǰ���������ݸ��Ƹ�Ҫɾ���Ľ��
		if(q != p)
			q->rchild = s->lchild;	//ǰ������Ҫɾ���Ľ��
		else
			q->lchild = s->lchild;	//����������Ҫɾ���Ľ��
		free(s);
	}
	return 1;
}

int DeleteBST(BiTree &T, KeyType key)
	//������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�صĽ�㣬
	//������1,���򷵻�0.
{
	if(!T)
		return 0;
	else{
		if(EQ(key, T->data.key))
			return Delete(T);
		else if(LT(key,T->data.key))
			return DeleteBST(T->lchild, key);
		else
			return DeleteBST(T->rchild, key);
	}
}


int main(void)
{
	BiTree T,T1 = NULL, p = NULL;
	ElemType e;	e.key = 40;
	int count = 0,depth,flag = 0;
	CreateBiTree(T);
	CreatePos(T,T,p,flag);
	LayerOrder(T);
	printf("---------------------\n");
	DeleteBST(T,37);
	CreatePos(T,T,p,flag);
	LayerOrder(T);
	
	


	return 0;
}