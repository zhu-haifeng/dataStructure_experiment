#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNode{
    /** ջ�д洢�Ľڵ� */
  int id;
  struct StackNode *Next;
    /** �����������Ҫ�õı��� */
}StackNode;

typedef struct LinkStack{
    /** ջ */
  StackNode* top;
  int size;
    /** �����������Ҫ�ı��� */
}LinkStack;

LinkStack* InitStack(){
    /** ��ʼ��ջ */
  LinkStack* linkStack = (LinkStack *)malloc(sizeof(LinkStack));
  linkStack->top = NULL;
  linkStack->size = 0;
  return linkStack;
}

int StackEmpty(LinkStack *linkStack){
    /** �ж�ջ�Ƿ�Ϊ�� */
  return (linkStack->size == 0);
}

int Push(LinkStack *linkStack,int ele){
    /** ��һ���ڵ�ѹ��ջ */
    StackNode* temp = (StackNode *)malloc(sizeof(StackNode));
    temp->id = ele;
    temp->Next = linkStack->top;
    linkStack->top = temp;
    linkStack->size++;
    return 1; //��ɾ��
}

int Pop(LinkStack* linkStack){
    /** ��һ���ڵ㵯��ջ */
    StackNode* temp = linkStack->top;
    linkStack->top = temp->Next;
    linkStack->size--;
    free(temp);
    return 1;

}

int GetTop(LinkStack* linkStack){
    /** ��ջ���գ�����ջ��ջ��Ԫ�� */
    int ele = linkStack->top->id;
    return ele;
}

int SeqLegal(int in[],int out[],int num){
    /** ʵ������1:�ж�����ĳ�վ�����Ƿ��������Ľ�վ����ͨ������ջ�õ�
     ���з���1�������з���0
     */
    LinkStack *theStack = InitStack();
    int i=0,o=0;   //�ֱ��ʾ�������е�λ������
    theStack->size=0;
    while(!StackEmpty(theStack)||i<num){//ջ���ջ�𳵻���ʣ�࣬�������
        if(StackEmpty(theStack)){   //ջ���ˣ�ѹջ
            Push(theStack,in[i++]);
        }
        if(GetTop(theStack)==out[o]){//ջ������Ҫ�󣬵���
            Pop(theStack);
            o++;
        }
        else{
            if(i==num){     //�������һ���ʣ�࣬�����з���0
                return 0;
            }
            else{   //�����ϵ��ǻ���ʣ��𳵣�ѹջ
                Push(theStack,in[i++]);
            }
        }
    }
    return 1;//�����꣬ջҲ���꣬����
}

typedef struct QueueNode{
    /** ���нڵ� */
    int id;
    struct QueueNode* next;//�Ӷ�βָ���ͷ����
}QueueNode;

typedef struct Queue{
    /** ���� */
    QueueNode *front;
    QueueNode *rear;
    int size;
}LinkQueue;

LinkQueue* InitQueue(){
    /** ��ʼ������ */
    LinkQueue* linkQueue = (LinkQueue*) malloc(sizeof(LinkQueue));
    linkQueue->front = linkQueue->rear = (QueueNode *)malloc(sizeof(QueueNode));//��βָ������ͷ����������
    linkQueue->front->next = NULL;
    linkQueue -> size = 0;
    return linkQueue;
}

int QueueEmpty(LinkQueue* linkQueue){
    /** �ж϶����Ƿ�Ϊ�� */
    return (linkQueue->front == linkQueue->rear);
}

int EnQueue(LinkQueue *linkQueue,int ele){
    /** ��� */
    QueueNode* temp = (QueueNode *)malloc(sizeof(QueueNode));
    temp->id = ele;
    temp->next = NULL;
    linkQueue->rear->next = temp;
    linkQueue->rear = temp;
    return 1;//��ɾ��
}

int findClosestQueue(LinkQueue *railQueue[],int usedQueue,int curTrain){
    /**  �ҵ�����ʵĻ𳵹�� */
    // Tips���뿼�������Ҳ��������
    int closestIdx = -1;

    /** Ѱ������ʵĻ𳵹��  */
    //Tips��ÿ�������к�ߵ�Ԫ��Ҫ����ǰ�ߵ�Ԫ��

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
    /** ʵ������2:������軺��������Сֵ*/
    LinkQueue *railQueue[num]; //ָ�����飬��¼���������Ļ𳵣����������ȵĹ����ʱһ������
    for(int i = 0;i < num;i++){
        railQueue[i] = InitQueue();
    }
    int usedQueue = 0;      //��ʹ�õĶ�����
    int o,i;  //o��ʾ���ڰ��ŵĻ����
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
     ����δ��ȫ������ʱ
     �������ҵ�����ʷ��õĹ��
     ���û�
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
        // ʵ������1
        if(SeqLegal(trainIn,trainOut,trainNum)){
            printf("The output train sequence is Possible\n");
        }else{
            printf("The output train sequence is impossible\n");
        }
        // ʵ������2
        printf("To recover the order, %d buffer queue is needed:\n",minBufferQueue(trainOut, trainNum));

    }
    fclose(stdin);

    return 0;
}
