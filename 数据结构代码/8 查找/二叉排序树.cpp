#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//------------
#define  EQ(a, b)	((a)==(b))	//a,b为数值型
#define  LT(a, b)	((a)< (b))
#define  LQ(a, b)	((a)<=(b))

#define KeyType int
#define InfoType char

typedef struct
{
	KeyType key;	//数据元素中查找的关键字
	InfoType* info;	//数据元素中的其他信息
}ElemType;

typedef struct
{
	ElemType *elem;	//数据元素存储空间基址，建表时按实际长度分配，0号单元留空
	int length;		//表长度
}SSTable;
//------------

//二叉树的二叉链表存储表示
#define TElemType ElemType

typedef struct BiTNode
{
	TElemType data;
	int pos;
	struct BiTNode *lchild ,*rchild;	//左右孩子指针
}BiTNode,*BiTree;

//创建二叉树的原始数据
KeyType arr1[] = {45,12,3,0,0,37,24,0,0,40,0,0,53,50,0,0,99,61,0,90,78,0,0,0,0};
KeyType arr2[] = {'A','B','E','\0','L','\0','\0','\0','D','H','M','\0','\0','I','\0','\0','J','\0','\0'};
KeyType arr3[] = {'-','+','a','\0','\0','*','b','\0','\0','-','c','\0','\0','d','\0','\0','/','e','\0','\0','f','\0','\0'};

int arr_i = 0;



//按照先序遍历创建二叉树
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
		T->data.key = ch;			//生成根节点
		T->pos = 32;
		CreateBiTree(T->lchild);//构造左子树
		CreateBiTree(T->rchild);//构造右子树
	}
	return 1;
}
//调用方式：CreatePos(T,T,p,0);
void CreatePos(BiTree T,BiTree f,BiTree &p,int flag)//flag == 1:右子树   flag == -1：左子树 
{
	if(T)						//查找不成功
	{
		//T->pos = f->pos + (flag * f->pos / 2);//间隔计算不对
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
	//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
	//中序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。
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

//***********给出了采用递归，对二叉树树进行操作的一般方法**********//
void CountLeaf(BiTree T, int &count)
	//先序遍历二叉树，以count返回二叉树中叶子结点的数目
	//conut作为计数器，在传参时count在main中要清零
{
	if(T)
	{
		if((!T->lchild) && (!T->rchild))	//既没有左子树也没有右子树
			++count;						//对叶子结点计数
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

//---单链队列——队列的链式存储结构(带头结点)---
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;	//队头指针
	QueuePtr rear;	//队尾指针
}LinkQueue;

int InitQueue(LinkQueue &Q)	//带头结点的队列
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));	//带头结点的队列
	if(!Q.front)	//存储分配失败
		exit(-1);
	Q.front->next = NULL;
	return 1;
}

int DestroyQueue(LinkQueue &Q)
	//销毁队列Q
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
	//插入元素e为Q的新的队尾元素
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)		//存储分配失败
		exit(-1);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}

int DeQueue(LinkQueue &Q, QElemType &e)
	//若队列不空，则删除Q的对头元素，用e返回其值，并返回1
	//否则返回0
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

//统计每层节点的个数 
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



int LayerOrder(BiTree bt)   //层次遍历二叉树 成功遍历返回1 失败返回0
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
	//在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素，
	//若查找成功，则返回指向该数据结点的指针，否则返回空指针
{
	if((!T) || EQ(key,T->data.key))
		return T;							//查找结束
	else if(LT(key, T->data.key))
		return (SearchBST1(T->lchild,key));	//在左子树中继续查找
	else
		return (SearchBST1(T->rchild,key));	//在右子树中继续查找
}



int SearchBST2(BiTree T,KeyType key,BiTree f,BiTree &p)
	//在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素，
	//若查找成功，指针p指向该数据元素的结点，并返回1，否则p指向查找路径
	//上访问的最后一个结点并返回0，指针f指向T的双亲，且初始调用值是NULL
{
	if(!T)						//查找不成功
	{
		p = f;
		return 0;
	}
	else if(EQ(key,T->data.key))//查找成功
	{
		p = T;
		return 1;
	}else if(LT(key,T->data.key))//在左子树继续查找
	{
		return SearchBST2(T->lchild,key,T,p);
	}
	else						//在右子树继续查找
	{
		return SearchBST2(T->rchild,key,T,p);
	}
}

void PrintSearchBST(BiTree T1)
{
	if(T1)
		printf("查到的结果：%d。\n", T1->data.key);
	else
		printf("未查到结果。\n");
}

int InsertBST(BiTree &T, ElemType e)
	//当二叉排序树T中不存在关键字等于e.key的数据元素时，插入e并返回1，
	//否则返回0.
{
	BiTree p, s;	
	if(!SearchBST2(T,e.key,NULL,p))
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data.key = e.key;
		s->lchild = s->rchild = NULL;
		if(!p)
			T = s;						//被插节点*s为新的根节点
		else if(LT(e.key,p->data.key))	//判断插入的结点key值和插入位置双亲结点大小，判断插入左边还是右边
			p->lchild = s;				//被插节点*s为新的左孩子节点
		else
			p->rchild = s;				//被插节点*s为新的右孩子节点
		return 1;
	}

	return 0;	//树中已存在关键字相同的结点，不必插入
}

//目标是找要删除结点的前驱，用前驱代替要删除的结点，调整次序，使中序遍历次序不受到影响
int Delete(BiTree &p)
	//从二叉排序树中删除结点p，并重接它的左或右子树
{
	BiTree q, s;
	if(!p->rchild)		//右子树空则只需重接它的左子树 包含叶子结点删除情况
	{
		q = p;
		p = p->lchild;
		free(q);
	}else if(!p->lchild)//只需重接它的右子树
	{
		q = p;
		p = p->rchild;
		free(q);
	}else				//左右子树均不空
	{
		q = p;
		s = p->lchild;
		while (s->rchild)
		{
			q = s;
			s = s->rchild;	//s指向左子树，然后向右走到尽头，也就是被删除结点的“前驱”
		}
		p->data = s->data;	//将前驱结点的数据复制给要删除的结点
		if(q != p)
			q->rchild = s->lchild;	//前驱代替要删除的结点
		else
			q->lchild = s->lchild;	//左子树代替要删除的结点
		free(s);
	}
	return 1;
}

int DeleteBST(BiTree &T, KeyType key)
	//若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素的结点，
	//并返回1,否则返回0.
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