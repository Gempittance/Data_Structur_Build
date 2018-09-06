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

typedef struct BSTNode
{
	TElemType data;
	int pos;
	int bf;								//结点的平衡因子
	struct BSTNode *lchild ,*rchild;	//左右孩子指针
}BSTNode,*BSTree;

//创建二叉树的原始数据
KeyType arr1[] = {45,12,3,0,0,37,24,0,0,40,0,0,53,50,0,0,99,61,0,90,78,0,0,0,0};
KeyType arr2[] = {'A','B','E','\0','L','\0','\0','\0','D','H','M','\0','\0','I','\0','\0','J','\0','\0'};
KeyType arr3[] = {'-','+','a','\0','\0','*','b','\0','\0','-','c','\0','\0','d','\0','\0','/','e','\0','\0','f','\0','\0'};

int arr_i = 0;



//按照先序遍历创建二叉树
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
		T->data.key = ch;			//生成根节点
		T->pos = 32;
		CreateBiTree(T->lchild);//构造左子树
		CreateBiTree(T->rchild);//构造右子树
	}
	return 1;
}
//调用方式：CreatePos(T,T,p,0);
void CreatePos(BSTree T,BSTree f,BSTree &p,int flag)//flag == 1:右子树   flag == -1：左子树 
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

void R_Rotate(BSTree &p)	//LL平衡旋转
	//对以*p为根的二叉排序树作右旋处理，处理之后p指向新的树根结点，
	//即旋转处理之前的左子树的根节点
{
	BSTree lc = p->lchild;	//lc指向的*p的左子树根节点
	p->lchild = lc->rchild;	//lc的右子树挂接为*p的左子树
	lc->rchild = p;			//p指向新的根节点
	p = lc;					//将原来的根节点变为它的左子树
}

void L_Rotate(BSTree &p)	//RR平衡旋转
	//对以*p为根的二叉排序树作左旋处理，处理之后p指向新的树根结点，
	//即旋转处理之前的右子树的根节点
{
	BSTree rc = p->rchild;	//rc指向*p的右子树根节点
	p->rchild = rc->rchild;	//rc的右子树挂接为*p的右子树
	rc->rchild = p;			//rc的右子树挂接根节点
	p = rc;					//将原来的根节点变为它的右子树
}


int main(void)
{



	return 0;
}
