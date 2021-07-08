#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 10020
#define maxm 200020
//图的定义使用链式前向星方式构建图
//当然你也可以用自己的方法构建图,如临接矩阵或者临接表
#define INF 2147483630
//int ans[maxn];
struct Edge
{
    int start, end, weight;
    //该边，同一起点的上一边在edgs中存储的下标。以next作为链式寻找同一起点的所有边
    int next;
};

struct Graph
{
    struct Edge edges[maxm];

    //head[i] 记录的是以i为起点的边集中第一条边在edges中的index,
    int head[maxn];

    //当前第几条边
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
    //提供这种存储加边方式
    graph->edges[++graph->tot].start = start;
    graph->edges[graph->tot].end = end;
    graph->edges[graph->tot].weight = weight;

    //链式前向星存储，每加一条边的时候，同一起点的边用next来做链式存储
    graph->edges[graph->tot].next = graph->head[start];
    graph->head[start] = graph->tot;
}

void visit_graph(int n, struct Graph *graph)
{
    //debug 函数，提供这种存储方式的遍历过程，方便同学们debug
    for (int i = 1; i <= n; i++) //n个起点
    {
        printf("start with %d\n", i);
        for (int j = graph->head[i]; j != -1; j = graph->edges[j].next) //遍历以i为起点的边
        {
            printf("edgs i is start:%d,end:%d,weight is:%d\n", graph->edges[j].start, graph->edges[j].end, graph->edges[j].weight);
        }
    }

    //遍历图中同一起点所有边的方法

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

    //TODO：
    int minTime[n+1];
    int maxtime = 0;
    int visited[n+1];//每个点是否确定最短时间
    int i,j;
    int k;
    int temp = INF;
    struct Edge *nowEdge;
    for(j=1;j<=n;j++){//到每点最短时间初始化；
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
        if(graph->head[k]!=-1){//如果k有出度才执行
            for(nowEdge = &(graph->edges[graph->head[k]]);; nowEdge = &(graph->edges[nowEdge->next])){//调整mintime

                if(!visited[nowEdge->end] && nowEdge->weight+minTime[k] < minTime[nowEdge->end]){

                    minTime[nowEdge->end] = nowEdge->weight+minTime[k];
                }
                if( nowEdge->next == -1)//所有出边访问完成
                    break;
            }//printf("点%d\n",k);
        }

//        for(int i=1;i<=n;i++){
//            printf("%d",minTime[i]);
//
//        }
        temp = INF;
        for(j=1;j<=n;j++){//找到最近的节点k
            //printf("j=%d, %d&&%d<%d?\n",j,!visited[j],minTime[j],temp);
            if(!visited[j]&&minTime[j]<temp){
                k = j;
                temp =minTime[j];
               // printf("\nk=%d\n",j);
            }
        }
        visited[k] = 1;
        //printf("\n点%d开始\n",k);
    }
    for(i=1;i<=n;i++){//求出到达每个点的最终时间
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
    //文件读入的方式
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

    //终端输入的方式
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
    测试输入输出形式：
输入：
4 6 1
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4

输出：
4
    */
}
