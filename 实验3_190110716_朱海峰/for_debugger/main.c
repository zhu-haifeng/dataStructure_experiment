
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int FLAG = 0;  //��ʶ�Ƿ����ɺ���������������

typedef struct Node
{
    char data;
    struct Node *lchild, *rchild;
} TreeNode, *BiTree; //�������ڵ�Ľṹ��

BiTree createBiTree()//����������
{
    char data;
    BiTree bt = NULL;
    scanf("%c",&data);
    if(data!='#'){  //�ݹ齨��������
        bt = (BiTree)malloc(sizeof(TreeNode));
        bt->data = data;
        bt->lchild = createBiTree();
        bt->rchild = createBiTree();
    }
    else{//#��ʾ��
        bt = NULL;
    }
    return bt;

}
void preOrderTraverse(BiTree p)//�������ܣ�ǰ�����
{
    if(p!=NULL){
        printf("%c",p->data);
        preOrderTraverse(p->lchild);
        preOrderTraverse(p->rchild);
    }
    return;
}
void inOrderTraverse(BiTree p)//�������ܣ��������
{
    if(p!=NULL){
        inOrderTraverse(p->lchild);
    printf("%c",p->data);
    inOrderTraverse(p->rchild);
    }

    return;
}
void postOrderTraverse(BiTree p)//�������ܣ��������
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
//�������ܣ����ݺ������������й���������������ظ��ڵ�
//����˵����post[]Ϊ�������У�s1,e1Ϊ����ĵ�һ�����һ���ڵ��±꣬in[]Ϊ�������У�s2,e2Ϊ����ĵ�һ�����һ���ڵ��±ꡣ
    int i;
    BiTree bt = NULL;
    if(e1-s1!=e2-s2){//������򳤶Ȳ�ͬ�����ܹ���
        printf("Unable to build a binary tree!\n");
        exit(1);
        return NULL;
    }
    bt = (TreeNode*)malloc(sizeof(TreeNode));
    bt->data = post[e1];
    for(i = s2;i<=e2;i++){//���������ҵ����ڵ�λ��
        if(in[i]==post[e1]){
            break;
        }
        else if(i==e2){//δ�ҵ����ڵ㣬����ʧ��
            printf("Unable to build a binary tree!\n");
            exit(1);
        }
    }
    if(i!=s2)
        bt->lchild = PostInCreate(post,s1,s1-s2+i-1,in,s2,i-1);
    else//������Ϊ�գ�ֹͣ�ݹ�
        bt->lchild = NULL;
    if(i!=e2)
        bt->rchild = PostInCreate(post,s1-s2+i,e1-1,in,i+1,e2);
    else//������Ϊ�գ�ֹͣ�ݹ�
        bt->rchild = NULL;

    return bt; //��ɾ��
}
int countLeafSum(BiTree root)
{
//�������ܣ�����Ҷ�ӽڵ���
    if(root==NULL){//��ָ��
        return 0;
    }
    if(root->lchild==NULL&&root->rchild==NULL)//Ҷ��
        return 1;
    else    //�м�ڵ㣬�ݹ���Ҷ����
        return countLeafSum(root->lchild)+countLeafSum(root->rchild);

}
int countHeight(BiTree root)
{
//�������ܣ�����������ĸ߶�,�������ĸ߶��������������������нϸߵ�һ�������ĸ߶��ټ�1

    return 0;//��ɾ��
}
void getwidth(BiTree root,int *count,int *counter)
{
//�������ܣ��õ�һ��������ÿ��Ľڵ���Ŀ��
//����˵����*counter��¼����,����count��¼ÿһ��Ľڵ���
    BiTree node[100];//���򴢴�ڵ��ַ������ԭ��������
    int first= 1;   //λ�ñ�����ÿ���һ���ڵ�
    int last = 1;   //λ�ñ���
    int i;
    node[first] = root;
    count[1] = 1;
    while(first<=last){
        for(i = 0;i<count[*counter];i++){//��һ��ڵ�����node
            if(node[first+i]->lchild){
                node[++last] = node[first+i]->lchild;
                count[*counter+1]++;
            }
            if(node[first+i]->rchild){
                node[++last] = node[first+i]->rchild;
                count[*counter+1]++;
            }
        }
        first += count[*counter];//��һ��
        (*counter)++;
    }

}
int isEquivalent(BiTree bt1,BiTree bt2)
{
   //�������ܣ��ж������Ƿ�ȼ�
    //����˵����bt1:��һ����������bt2:�ڶ���������
    if(bt1==NULL&&bt2==NULL)
        return 1;
    else if(bt1!=NULL&&bt2!=NULL){
        if(bt1->data!=bt2->data)
            return 0;
        else//�ݹ��ж�
            return(isEquivalent(bt1->lchild,bt2->lchild)&&isEquivalent(bt1->rchild,bt2->rchild));
    }
    else
        return 0;
}
void task1(BiTree bt){
    //����1��ʵ�ֶ������������򡢺������
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
    //����2��������PostInCreate�������ݺ������������й��������
    //ʹ�ú�����PostInCreate
    printf("start task (2) Input the postOrder and inOrder Sequence ,Then build the tree\n");
    char post[20];  //��������
    char in[20];    //��������
    int postlen;    //�������г���
    int inlen;      //�������г���
    printf("please input the postorder sequence\n");
    scanf("%s",post);
    printf("please input the inorder sequence\n");
    scanf("%s",in);
    *bt = PostInCreate(post,0,strlen(post)-1,in,0,strlen(in)-1);
    //�����ƺ���




    printf("preOrderTraverse:\n");
    preOrderTraverse(*bt);
    printf("\n");

}

void task3(BiTree bt){
    //����3�������������Ҷ�ڵ�����Ϳ�ȡ���ע������������ĺ����ǳ���������ƣ��������и��õİ취�õ���ȣ��Լ������ɡ���
    //ʹ�ú�����countLeafSum��countHeight��getwidth
    printf("start task (3) ------------------------------\n");
    int height = 1;     //���ĸ߶�
    int maxwidth=-1;     //���Ŀ�ȣ�Ԥ��Ϊ-1������ȣ�������ÿһ��ڵ��������ֵ��
    printf("The number of leaf nodes of the tree is:\n");
    printf("%d\n",countLeafSum(bt));
    //�����ƺ���
    int count[10] = {0};
    getwidth(bt,count,&height);
    for(int i=1;i<=height;i++){//����ҵ����Ŀ��
        if(count[i]>maxwidth)
            maxwidth = count[i];
    }

    printf("The width of the tree is:\n");
    printf("%d\n",maxwidth);
}


void task4(BiTree bt1,BiTree bt2){
    //����4���ж������������Ƿ�ȼ�
    //ʹ�ú�����isEquivalent
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
