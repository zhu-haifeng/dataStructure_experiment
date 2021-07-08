#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNode{
    /** 栈中存储的节点 */
  int id;
  struct StackNode *Next;
    /** 可自由添加需要用的变量 */
}StackNode;

typedef struct LinkStack{
    /** 栈 */
  StackNode* top;
  int size;
    /** 可自由添加需要的变量 */
}LinkStack;

LinkStack* InitStack(){
    /** 初始化栈 */
  LinkStack* linkStack = (LinkStack *)malloc(sizeof(LinkStack));
  linkStack->top = NULL;
  linkStack->size = 0;
  return linkStack;
}

int StackEmpty(LinkStack *linkStack){
    /** 判断栈是否为空 */
  return (linkStack->size == 0);
}

int Push(LinkStack *linkStack,int ele){
    /** 将一个节点压入栈 */
    StackNode* temp = (StackNode *)malloc(sizeof(StackNode));
    temp->id = ele;
    temp->Next = linkStack->top;
    linkStack->top = temp;
    linkStack->size++;
    return 1; //可删除
}

int Pop(LinkStack* linkStack){
    /** 将一个节点弹出栈 */
    StackNode* temp = linkStack->top;
    linkStack->top = temp->Next;
    linkStack->size--;
    free(temp);
    return 1;

}

int GetTop(LinkStack* linkStack){
    /** 若栈不空，返回栈的栈顶元素 */
    int ele = linkStack->top->id;
    return ele;
}

int SeqLegal(int in[],int out[],int num){
    /** 实验内容1:判断输入的出站序列是否可由输入的进站序列通过进出栈得到
     可行返回1，不可行返回0
     */
    LinkStack *theStack = InitStack();
    int i=0,o=0;   //分别表示出入序列的位置坐标
    theStack->size=0;
    while(!StackEmpty(theStack)||i<num){//栈不空或火车还有剩余，程序继续
        if(StackEmpty(theStack)){   //栈空了，压栈
            Push(theStack,in[i++]);
        }
        if(GetTop(theStack)==out[o]){//栈顶符合要求，弹出
            Pop(theStack);
            o++;
        }
        else{
            if(i==num){     //不符合且火车无剩余，不可行返回0
                return 0;
            }
            else{   //不符合但是还有剩余火车，压栈
                Push(theStack,in[i++]);
            }
        }
    }
    return 1;//火车排完，栈也退完，可行
}

typedef struct QueueNode{
    /** 队列节点 */
    int id;
    struct QueueNode* next;//从队尾指向对头方向
}QueueNode;

typedef struct Queue{
    /** 队列 */
    QueueNode *front;
    QueueNode *rear;
    int size;
}LinkQueue;

LinkQueue* InitQueue(){
    /** 初始化队列 */
    LinkQueue* linkQueue = (LinkQueue*) malloc(sizeof(LinkQueue));
    linkQueue->front = linkQueue->rear = (QueueNode *)malloc(sizeof(QueueNode));//队尾指针做表头，不存数据
    linkQueue->front->next = NULL;
    linkQueue -> size = 0;
    return linkQueue;
}

int QueueEmpty(LinkQueue* linkQueue){
    /** 判断队列是否为空 */
    return (linkQueue->front == linkQueue->rear);
}

int EnQueue(LinkQueue *linkQueue,int ele){
    /** 入队 */
    QueueNode* temp = (QueueNode *)malloc(sizeof(QueueNode));
    temp->id = ele;
    temp->next = NULL;
    linkQueue->rear->next = temp;
    linkQueue->rear = temp;
    return 1;//可删除
}

int findClosestQueue(LinkQueue *railQueue[],int usedQueue,int curTrain){
    /**  找到最合适的火车轨道 */
    // Tips：请考虑如若找不到的情况
    int closestIdx = -1;

    /** 寻找最合适的火车轨道  */
    //Tips：每个队列中后边的元素要大于前边的元素

    // Todo
    int i;
    for(i = 0;i<usedQueue;i++){
        if(curTrain>railQueue[i]->rear->id){
            return i;
        }
    }
    return closestIdx;
}

int minBufferQueue(int out[],int num){
    /** 实验内容2:求解所需缓冲轨道的最小值*/
    LinkQueue *railQueue[num]; //指针数组，记录各缓存轨道的火车，有与火车数相等的轨道数时一定可行
    for(int i = 0;i < num;i++){
        railQueue[i] = InitQueue();
    }
    int usedQueue = 0;      //已使用的队列数
    int o,i;  //o表示正在安排的火车序号
    for(o = 0;o<num;o++){
        if( i = findClosestQueue(railQueue,usedQueue,out[o])==-1){
            EnQueue(railQueue[usedQueue++],out[o]);
            //printf("%d\t%d\n",usedQueue,out[o]);
        }
        else{
            EnQueue(railQueue[i],out[o]);
            //printf("%d\t%d\n",i,out[o]);
        }
    }

    /**
     当火车未完全安排完时
     从其中找到最合适放置的轨道
     放置火车
     */

    // Todo

    return usedQueue;
}

int main()
{

    int trainNum;
    int count = 0;
    freopen("TestTrain.in", "r", stdin);

    while(scanf("%d",&trainNum)!=EOF){
        count++;
        int trainIn[trainNum];
        int trainOut[trainNum];
        for(int i = 0;i < trainNum;i++){
            scanf("%d",&trainIn[i]);
        }
        for(int i = 0;i < trainNum;i++){
            scanf("%d",&trainOut[i]);
        }
        printf("====Case %d====\n",count);
        // 实验内容1
        if(SeqLegal(trainIn,trainOut,trainNum)){
            printf("The output train sequence is Possible\n");
        }else{
            printf("The output train sequence is impossible\n");
        }
        // 实验内容2
        printf("To recover the order, %d buffer queue is needed:\n",minBufferQueue(trainOut, trainNum));

    }
    fclose(stdin);

    return 0;
}
