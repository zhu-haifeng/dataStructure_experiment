#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 10020
#define maxm 200020
//ͼ�Ķ���ʹ����ʽǰ���Ƿ�ʽ����ͼ
//��Ȼ��Ҳ�������Լ��ķ�������ͼ,���ٽӾ�������ٽӱ�
#define INF 2147483630
//int ans[maxn];
struct Edge
{
    int start, end, weight;
    //�ñߣ�ͬһ������һ����edgs�д洢���±ꡣ��next��Ϊ��ʽѰ��ͬһ�������б�
    int next;
};

struct Graph
{
    struct Edge edges[maxm];

    //head[i] ��¼������iΪ���ı߼��е�һ������edges�е�index,
    int head[maxn];

    //��ǰ�ڼ�����
    int tot;
};

struct Graph *init_graph()
{
    struct Graph *new_grapth = (struct Graph *)malloc(sizeof(struct Graph));
    new_grapth->tot = 0;
    memset(new_grapth->head, -1, sizeof(new_grapth->head));
    return new_grapth;
}

void add_edge(int start, int end, int weight, struct Graph *graph)
{
    //�ṩ���ִ洢�ӱ߷�ʽ
    graph->edges[++graph->tot].start = start;
    graph->edges[graph->tot].end = end;
    graph->edges[graph->tot].weight = weight;

    //��ʽǰ���Ǵ洢��ÿ��һ���ߵ�ʱ��ͬһ���ı���next������ʽ�洢
    graph->edges[graph->tot].next = graph->head[start];
    graph->head[start] = graph->tot;
}

void visit_graph(int n, struct Graph *graph)
{
    //debug �������ṩ���ִ洢��ʽ�ı������̣�����ͬѧ��debug
    for (int i = 1; i <= n; i++) //n�����
    {
        printf("start with %d\n", i);
        for (int j = graph->head[i]; j != -1; j = graph->edges[j].next) //������iΪ���ı�
        {
            printf("edgs i is start:%d,end:%d,weight is:%d\n", graph->edges[j].start, graph->edges[j].end, graph->edges[j].weight);
        }
    }

    //����ͼ��ͬһ������бߵķ���

    // int  index;
    // index = graph->head[startpoint];
    // while (index!=-1)
    // {
    //     /* code */
    //     //do something

    //     index = graph->edges[index].next;
    // }


}

int get_min_time(int n, int startpoint, struct Graph *graph)
{

    //TODO��
    int minTime[n+1];
    int maxtime = 0;
    int visited[n+1];//ÿ�����Ƿ�ȷ�����ʱ��
    int i,j;
    int k;
    int temp = INF;
    struct Edge *nowEdge;
    for(j=1;j<=n;j++){//��ÿ�����ʱ���ʼ����
        if(j==startpoint){
            minTime[j] = 0;
            visited[j] = 1;
        }
        else{
            minTime[j] = INF;
            visited[j] = 0;
        }
    }


    for(k=startpoint,i=2;i<=n;i++){
//        for(j=1;j<=n;j++){
//
//            printf("visited[%d]=%d\n",j,visited[j]);
//        }
        if(graph->head[k]!=-1){//���k�г��Ȳ�ִ��
            for(nowEdge = &(graph->edges[graph->head[k]]);; nowEdge = &(graph->edges[nowEdge->next])){//����mintime

                if(!visited[nowEdge->end] && nowEdge->weight+minTime[k] < minTime[nowEdge->end]){

                    minTime[nowEdge->end] = nowEdge->weight+minTime[k];
                }
                if( nowEdge->next == -1)//���г��߷������
                    break;
            }//printf("��%d\n",k);
        }

//        for(int i=1;i<=n;i++){
//            printf("%d",minTime[i]);
//
//        }
        temp = INF;
        for(j=1;j<=n;j++){//�ҵ�����Ľڵ�k
            //printf("j=%d, %d&&%d<%d?\n",j,!visited[j],minTime[j],temp);
            if(!visited[j]&&minTime[j]<temp){
                k = j;
                temp =minTime[j];
               // printf("\nk=%d\n",j);
            }
        }
        visited[k] = 1;
        //printf("\n��%d��ʼ\n",k);
    }
    for(i=1;i<=n;i++){//�������ÿ���������ʱ��
        //printf("%d",minTime[i]);
        maxtime = maxtime<minTime[i]?minTime[i]:maxtime;
    }
    //printf("\n");
    return maxtime;
}
int main()
{
    int n, m, startpoint, min_time;
    int num=1;
    //�ļ�����ķ�ʽ
    freopen("4_1_input.in", "r", stdin);
    while (scanf("%d%d%d", &n, &m, &startpoint) != EOF)
    {
        //scanf("%d%d%d", &n, &m, &startpoint);

        printf("======case%d=========\n",num++);
        struct Graph *g = init_graph();
        int start, end, weight;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &start, &end, &weight);
            add_edge(start, end, weight, g);
        }
        //visit_graph(n,g);
        min_time = get_min_time(n, startpoint, g);
        printf("min time=%d\n", min_time);
    }
    fclose(stdin);

    //�ն�����ķ�ʽ
    /*
    while(scanf("%d%d%d", &n, &m, &startpoint)!=EOF){
    //scanf("%d%d%d", &n, &m, &startpoint);
    struct Graph* g =init_graph();
    int start, end, weight;
    for (int i=1; i<=m; i++){
        scanf("%d%d%d", &start, &end, &weight);
        add_edge(start, end, weight,g);
    }

    min_time=get_min_time(n,startpoint,g);
    printf("%d\n",min_time);
    }
    */
    return 0;
    /*
    �������������ʽ��
���룺
4 6 1
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4

�����
4
    */
}
