#include <stdio.h>
#include <string.h>

// ���ַ�������ʽ��ʾ����
typedef struct nString{
   char strNum[1002];
   int length;
}nString;
// Ҳ�����о����洢�ṹ

nString arr[1002];

// �Ƚ������ַ��������Զ���������Զ��庯��
int cmpStr(nString fir,nString sec)
{
    int lengthD = fir.length-sec.length;
    if(lengthD>0)
        return 1;
    else if(lengthD<0)
        return 0;
    else return strcmp(fir.strNum,sec.strNum)>0;
}
int partion(int i,int j)//�ָ�
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
    return i;//���ر궨λ��
}
void QuickSort(int i, int j)//��������
{
    int k;
    if(i<j){
        k = partion(i,j);//�ָ�
        QuickSort(i,k-1);//�ݹ����
        QuickSort(k+1,j);
    }
}
// ��ʵ�������㷨,���Զ������
void resort(nString* arr,int num)
{
    QuickSort(0,num-1);
}


int main(void){
   int num;
   int caseNum = 0;
   // �ļ����뷽ʽ
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

    /* �ն����뷽ʽ
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


