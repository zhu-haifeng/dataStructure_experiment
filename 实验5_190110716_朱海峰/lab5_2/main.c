#include <stdio.h>
#include <string.h>

// 以字符串的形式表示数字
typedef struct nString{
   char strNum[1002];
   int length;
}nString;
// 也可自行决定存储结构

nString arr[1002];

// 比较两个字符串，可自定义参数或自定义函数
int cmpStr(nString fir,nString sec)
{
    int lengthD = fir.length-sec.length;
    if(lengthD>0)
        return 1;
    else if(lengthD<0)
        return 0;
    else return strcmp(fir.strNum,sec.strNum)>0;
}
int partion(int i,int j)//分割
{
    nString pivot = arr[i];

    while(i<j){
        for(;i<j&&cmpStr(arr[j],pivot);j--);
        if(i<j){
            strcpy(arr[i].strNum,arr[j].strNum);
            arr[i++].length = arr[j].length;
        }

        for(;i<j&&cmpStr(pivot,arr[i]);i++);
        if(i<j){
            strcpy(arr[j].strNum,arr[i].strNum);
            arr[j++].length = arr[i].length;
        }

    }
    arr[i].length = pivot.length;
    strcpy(arr[i].strNum,pivot.strNum);
    return i;//返回标定位置
}
void QuickSort(int i, int j)//快速排序
{
    int k;
    if(i<j){
        k = partion(i,j);//分割
        QuickSort(i,k-1);//递归快排
        QuickSort(k+1,j);
    }
}
// 请实现排序算法,可自定义参数
void resort(nString* arr,int num)
{
    QuickSort(0,num-1);
}


int main(void){
   int num;
   int caseNum = 0;
   // 文件输入方式
   freopen("5_2_input.in", "r", stdin);
   while(scanf("%d",&num)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < num; i++){
           scanf("%s",arr[i].strNum);
           arr[i].length = strlen(arr[i].strNum);
       }
       resort(arr, num);
       for(int i = 0; i < num; i++){
           printf("%s\n",arr[i].strNum);
       }
   }
   fclose(stdin);

    /* 终端输入方式
   while(scanf("%d",&num)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < num; i++){
           scanf("%s",arr[i].strNum);
           arr[i].length = strlen(arr[i].strNum);
       }
       resort(arr, num);
       for(int i = 0; i < num; i++){
           printf("%s\n",arr[i].strNum);
       }
   }
   */
}


