#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#define MAX 0x3f3f3f3f

int arr[2002];

//请实现排序算法,可自定义参数
int partion(int i,int j)//分割
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
void QuickSort(int i, int j)//快排
{
    int k;

    if(i<j){
        k = partion(i,j);
        QuickSort(i,k-1);
        QuickSort(k+1,j);
    }
}
void resort(int* arr,int num)
{
    QuickSort(0,num-1);
//    for(int i=0;i<num;i++)
//        printf("%d ",arr[i]);
//        printf("\n");
}

//找到最邻近数字对,可自定义参数
void findClosestPair(int *arr, int num)
{
    int i;
    int minD=MAX;
    int last=0;
    int* flag = (int*)malloc(sizeof(int)*num);
    memset(flag,0,sizeof(int)*num);
    for(i=0;i<num-1;i++){
        if(abs(arr[i]-arr[i+1])<=minD){
            minD = abs(arr[i]-arr[i+1]);
            last = i;
        }

    }
    for(i=0;i<num-1;i++){
        if(abs(arr[i]-arr[i+1])==minD){
            printf("%d %d",arr[i],arr[i+1]);
            if(i!=last)
                printf(",");
            else
                printf("\n");
        }
    }
    free(flag);
}


int main(){
    int num;
    int caseNum = 0;

    // 文件输入方式
    freopen("5_1_input.in", "r", stdin);
    while(scanf("%d",&num)!=EOF){
        caseNum++;
        printf("==== Case %d ====\n",caseNum);
        for(int i = 0; i < num; i++){
            scanf("%d",&arr[i]);
        }
        resort(arr, num);
        findClosestPair(arr, num);
    }
    fclose(stdin);

    /*
     终端输入方式
    while(scanf("%d",&num)!=EOF){
        caseNum++;
        printf("==== Case %d ====\n",caseNum);
        for(int i = 0; i < num; i++){
            scanf("%d",&arr[i]);
        }
        resort(arr, num);
        findClosestPair(arr, num);
    }
     */

    return 0;
}
