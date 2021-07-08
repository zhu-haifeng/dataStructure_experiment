
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int FLAG = 0;  //标识是否能由后序中序建立二叉树

typedef struct Node
{
    char data;
    struct Node *lchild, *rchild;
} TreeNode, *BiTree; //定义树节点的结构体

BiTree createBiTree()//建立二叉树
{
    char data;
    BiTree bt = NULL;
    scanf("%c",&data);
    if(data!='#'){  //递归建立二叉树
        bt = (BiTree)malloc(sizeof(TreeNode));
        bt->data = data;
        bt->lchild = createBiTree();
        bt->rchild = createBiTree();
    }
    else{//#表示空
        bt = NULL;
    }
    return bt;

}
void preOrderTraverse(BiTree p)//函数功能：前序遍历
{
    if(p!=NULL){
        printf("%c",p->data);
        preOrderTraverse(p->lchild);
        preOrderTraverse(p->rchild);
    }
    return;
}
void inOrderTraverse(BiTree p)//函数功能：中序遍历
{
    if(p!=NULL){
        inOrderTraverse(p->lchild);
    printf("%c",p->data);
    inOrderTraverse(p->rchild);
    }

    return;
}
void postOrderTraverse(BiTree p)//函数功能：后序遍历
{
    if(p!=NULL){
        postOrderTraverse(p->lchild);
        postOrderTraverse(p->rchild);
        printf("%c",p->data);
    }
    return;
}
BiTree PostInCreate(char post[],int s1,int e1,char in[],int s2,int e2)
{
//函数功能：根据后序与中序序列构造二叉树，并返回根节点
//参数说明：post[]为后序序列，s1,e1为后序的第一和最后一个节点下标，in[]为中序序列，s2,e2为中序的第一和最后一个节点下标。
    int i;
    BiTree bt = NULL;
    if(e1-s1!=e2-s2){//中序后序长度不同，不能构造
        printf("Unable to build a binary tree!\n");
        exit(1);
        return NULL;
    }
    bt = (TreeNode*)malloc(sizeof(TreeNode));
    bt->data = post[e1];
    for(i = s2;i<=e2;i++){//中序列中找到根节点位置
        if(in[i]==post[e1]){
            break;
        }
        else if(i==e2){//未找到根节点，构造失败
            printf("Unable to build a binary tree!\n");
            exit(1);
        }
    }
    if(i!=s2)
        bt->lchild = PostInCreate(post,s1,s1-s2+i-1,in,s2,i-1);
    else//左子树为空，停止递归
        bt->lchild = NULL;
    if(i!=e2)
        bt->rchild = PostInCreate(post,s1-s2+i,e1-1,in,i+1,e2);
    else//右子树为空，停止递归
        bt->rchild = NULL;

    return bt; //可删除
}
int countLeafSum(BiTree root)
{
//函数功能：计算叶子节点数
    if(root==NULL){//空指针
        return 0;
    }
    if(root->lchild==NULL&&root->rchild==NULL)//叶子
        return 1;
    else    //中间节点，递归求叶子数
        return countLeafSum(root->lchild)+countLeafSum(root->rchild);

}
int countHeight(BiTree root)
{
//函数功能：计算二叉树的高度,二叉树的高度是其左子树或右子树中较高的一个子树的高度再加1

    return 0;//可删除
}
void getwidth(BiTree root,int *count,int *counter)
{
//函数功能：得到一个二叉树每层的节点数目。
//参数说明：*counter记录层数,数组count记录每一层的节点数
    BiTree node[100];//层序储存节点地址，队列原理层序遍历
    int first= 1;   //位置变量，每层第一个节点
    int last = 1;   //位置变量
    int i;
    node[first] = root;
    count[1] = 1;
    while(first<=last){
        for(i = 0;i<count[*counter];i++){//下一层节点进入表node
            if(node[first+i]->lchild){
                node[++last] = node[first+i]->lchild;
                count[*counter+1]++;
            }
            if(node[first+i]->rchild){
                node[++last] = node[first+i]->rchild;
                count[*counter+1]++;
            }
        }
        first += count[*counter];//下一层
        (*counter)++;
    }

}
int isEquivalent(BiTree bt1,BiTree bt2)
{
   //函数功能：判断两树是否等价
    //参数说明：bt1:第一个二叉树，bt2:第二个二叉树
    if(bt1==NULL&&bt2==NULL)
        return 1;
    else if(bt1!=NULL&&bt2!=NULL){
        if(bt1->data!=bt2->data)
            return 0;
        else//递归判断
            return(isEquivalent(bt1->lchild,bt2->lchild)&&isEquivalent(bt1->rchild,bt2->rchild));
    }
    else
        return 0;
}
void task1(BiTree bt){
    //任务1：实现二叉树先序、中序、后序遍历
    printf("start task (1) Create Tree in PreOrder\n");
    printf("preOrderTraverse\n");
    preOrderTraverse(bt);
    printf("\n");
    printf("inOrderTraverse\n");
    inOrderTraverse(bt);
    printf("\n");
    printf("postOrderTraverse\n");
    postOrderTraverse(bt);
    printf("\n");
}

void task2(BiTree *bt){
    //任务2：请利用PostInCreate函数根据后序与中序序列构造二叉树
    //使用函数：PostInCreate
    printf("start task (2) Input the postOrder and inOrder Sequence ,Then build the tree\n");
    char post[20];  //后序序列
    char in[20];    //中序序列
    int postlen;    //后序序列长度
    int inlen;      //中序序列长度
    printf("please input the postorder sequence\n");
    scanf("%s",post);
    printf("please input the inorder sequence\n");
    scanf("%s",in);
    *bt = PostInCreate(post,0,strlen(post)-1,in,0,strlen(in)-1);
    //请完善函数




    printf("preOrderTraverse:\n");
    preOrderTraverse(*bt);
    printf("\n");

}

void task3(BiTree bt){
    //任务3：计算二叉树的叶节点个数和宽度。（注：计算宽度所需的函数是出题者所设计，若你能有更好的办法得到宽度，自己设计亦可。）
    //使用函数：countLeafSum、countHeight、getwidth
    printf("start task (3) ------------------------------\n");
    int height = 1;     //树的高度
    int maxwidth=-1;     //树的宽度，预设为-1。（宽度：二叉树每一层节点数的最大值）
    printf("The number of leaf nodes of the tree is:\n");
    printf("%d\n",countLeafSum(bt));
    //请完善函数
    int count[10] = {0};
    getwidth(bt,count,&height);
    for(int i=1;i<=height;i++){//逐层找到最大的宽度
        if(count[i]>maxwidth)
            maxwidth = count[i];
    }

    printf("The width of the tree is:\n");
    printf("%d\n",maxwidth);
}


void task4(BiTree bt1,BiTree bt2){
    //任务4：判断两个二叉树是否等价
    //使用函数：isEquivalent
    printf("start task (4) Are two Bitrees equivalent?\n");
    printf("%d\n",isEquivalent(bt1,bt2));

}
int main()
{
    BiTree bt1,bt2;
    printf("Create Tree1 in PreOrder\n");
    bt1=createBiTree();

    task1(bt1);
    task2(&bt2);
    task3(bt2);
    task4(bt1,bt2);

    return 0;
}
