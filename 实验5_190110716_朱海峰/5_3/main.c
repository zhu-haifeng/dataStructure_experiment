#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
int partion(int i,int j,int* arr)//分割
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
void QuickSort(int i, int j,int* arr)//快排
{
    int k;
    if(i<j){
        k = partion(i,j,arr);
        QuickSort(i,k-1,arr);
        QuickSort(k+1,j,arr);
    }
}
//对起始时间与终止时间进行排序，参数可自行填写
void sort(int *start,int *end,int M)
{
    QuickSort(0,M-1,start);
    QuickSort(0,M-1,end);
//    for(int i=0;i<M;i++)
//        printf("%d->%d\n",start[i],end[i]);
}

//计算空闲人数最多的起始时间和终止时间，参数可自行填写
void findPeriod(int *start,int *end,int M,int N)
{//调了四个小时，这tm根本不叫什么算法，太笨了这方法
    struct time_Point
    {//每个时间段
        int num1,//开始时人数，无新增用不到则直接为零即可
            num2;//结束时人数，什么情况都有值
        int time;//当前时间
    };
    int maxnum = -1;//记录最多人数
    int last   = -1;//记录最后一次人最多的开始时间
    int p,  //时间点指针
        i,  //start 指针
        j;  //end 指针
    int NUM=0;//暂存现有人数
    struct time_Point* TIME = (struct time_Point*)malloc(2*M*sizeof(struct time_Point));
    memset(TIME,0,2*M*sizeof(struct time_Point));
    TIME[0].time = start[0];
    TIME[0].num1  = TIME[0].num2 = ++NUM;
    for(i=1,p=0,j=0;i<M;){//录入每个时间段的人数信息
        if(start[i]<=end[j]){
            if(start[i]>TIME[p].time)//下一个时间段
                TIME[++p].time = start[i];
            TIME[p].num1 = TIME[p].num2 = ++NUM;
            i++;
        }
        else{
            if(end[j]>TIME[p].time)//下一个时间段
                TIME[++p].time = end[j];
            TIME[p].num2  = --NUM;
            j++;
        }
    }
    for(p++;j<M;j++,p++){//剩余的end录入
        TIME[p].time = end[j];
        TIME[p].num2 = --NUM;
    }
    for(int i=0;i<p;i++){//找到最多的人数
        if(TIME[i].num1>=maxnum){
            maxnum = TIME[i].num1;
            last = i;////记录最后一次人最多的开始时间，方便后面打印逗号
        }
    }
    for(int i=0;i<p;i++){
        if(TIME[i].num1==maxnum){
            if(TIME[i].num2==maxnum)//该时间段无人又进又出
                printf("%d %d",TIME[i].time,TIME[i+1].time);
            else                    //该时间段有人又进又出
                printf("%d %d",TIME[i].time,TIME[i].time);
            if(i!=last)
                printf(",");
            else
                printf("\n");
        }
    }
    free(TIME);//释放内存
}


int main()
{
   int N, M; //分别存储时间的段数和学生的个数
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

   /* 终端输入
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

