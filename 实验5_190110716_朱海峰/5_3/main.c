#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
int partion(int i,int j,int* arr)//�ָ�
{
    int pivot = arr[i];
    while(i<j){
        for(;i<j&&arr[j]>=pivot;j--);
        if(i<j)
            arr[i++] = arr[j];
        for(;i<j&&arr[i]<pivot;i++);
        if(i<j)
            arr[j--] = arr[i];
    }
    arr[i] = pivot;
    return i;
}
void QuickSort(int i, int j,int* arr)//����
{
    int k;
    if(i<j){
        k = partion(i,j,arr);
        QuickSort(i,k-1,arr);
        QuickSort(k+1,j,arr);
    }
}
//����ʼʱ������ֹʱ��������򣬲�����������д
void sort(int *start,int *end,int M)
{
    QuickSort(0,M-1,start);
    QuickSort(0,M-1,end);
//    for(int i=0;i<M;i++)
//        printf("%d->%d\n",start[i],end[i]);
}

//�����������������ʼʱ�����ֹʱ�䣬������������д
void findPeriod(int *start,int *end,int M,int N)
{//�����ĸ�Сʱ����tm��������ʲô�㷨��̫�����ⷽ��
    struct time_Point
    {//ÿ��ʱ���
        int num1,//��ʼʱ�������������ò�����ֱ��Ϊ�㼴��
            num2;//����ʱ������ʲô�������ֵ
        int time;//��ǰʱ��
    };
    int maxnum = -1;//��¼�������
    int last   = -1;//��¼���һ�������Ŀ�ʼʱ��
    int p,  //ʱ���ָ��
        i,  //start ָ��
        j;  //end ָ��
    int NUM=0;//�ݴ���������
    struct time_Point* TIME = (struct time_Point*)malloc(2*M*sizeof(struct time_Point));
    memset(TIME,0,2*M*sizeof(struct time_Point));
    TIME[0].time = start[0];
    TIME[0].num1  = TIME[0].num2 = ++NUM;
    for(i=1,p=0,j=0;i<M;){//¼��ÿ��ʱ��ε�������Ϣ
        if(start[i]<=end[j]){
            if(start[i]>TIME[p].time)//��һ��ʱ���
                TIME[++p].time = start[i];
            TIME[p].num1 = TIME[p].num2 = ++NUM;
            i++;
        }
        else{
            if(end[j]>TIME[p].time)//��һ��ʱ���
                TIME[++p].time = end[j];
            TIME[p].num2  = --NUM;
            j++;
        }
    }
    for(p++;j<M;j++,p++){//ʣ���end¼��
        TIME[p].time = end[j];
        TIME[p].num2 = --NUM;
    }
    for(int i=0;i<p;i++){//�ҵ���������
        if(TIME[i].num1>=maxnum){
            maxnum = TIME[i].num1;
            last = i;////��¼���һ�������Ŀ�ʼʱ�䣬��������ӡ����
        }
    }
    for(int i=0;i<p;i++){
        if(TIME[i].num1==maxnum){
            if(TIME[i].num2==maxnum)//��ʱ��������ֽ��ֳ�
                printf("%d %d",TIME[i].time,TIME[i+1].time);
            else                    //��ʱ��������ֽ��ֳ�
                printf("%d %d",TIME[i].time,TIME[i].time);
            if(i!=last)
                printf(",");
            else
                printf("\n");
        }
    }
    free(TIME);//�ͷ��ڴ�
}


int main()
{
   int N, M; //�ֱ�洢ʱ��Ķ�����ѧ���ĸ���
   int caseNum = 0;
   int start[1002];
   int end[1002];

   freopen("5_3_input.in", "r", stdin);
   while(scanf("%d %d",&N,&M)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < M;i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       sort(start, end, M);
       findPeriod(start, end, M, N);
   }
   fclose(stdin);

   /* �ն�����
   while(scanf("%d %d",&N,&M)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < M;i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       sort(start, end, M);
       findPeriod(start, end, M, N);
   }
   */
}

