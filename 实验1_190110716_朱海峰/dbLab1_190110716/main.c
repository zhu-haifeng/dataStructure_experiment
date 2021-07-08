/********
    数据结构实验1
    线性表
    190110716朱海峰*/
#include <stdlib.h>
#include <stdio.h>
typedef struct node{
    int ClassID;
    int StuID;
    int Grade;
    struct node *next;
}StudentLinkedListNode;


/* 打印单个节点 */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{Class:%d, ID:%d, Grade:%d}",node->ClassID, node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else
    {
        printf("\n");
    }

}

/* 输出该表的成绩情况 */
void outputStudentLinkedList(StudentLinkedListNode* head){
    // 用于单个节点输出的函数printLinkedListNode已提供
    //请你实现遍历链表的逻辑
	//TODO
	StudentLinkedListNode *p;
	if(head==NULL)
        return;
	for(p = head->next;p;p=p->next){
        printLinkedListNode(p);

	}
}


/** 新建一个链表node并返回 */
StudentLinkedListNode* studentLinkedListCreate( int class_id,int student_id,int grade) {
    //tips:malloc的时候记得为转化为结构体指针
	//TODO
	StudentLinkedListNode *p;
	p = (StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));
	p->next = NULL;
	p->ClassID = class_id;
	p->StuID = student_id;
	p->Grade = grade;
	return p;
}

/** copy一个已有的node */
StudentLinkedListNode* studentLinkedListCopy(StudentLinkedListNode* src){
    StudentLinkedListNode* tempNode = studentLinkedListCreate(src->ClassID,src->StuID,src->Grade);
    return tempNode;
}



/** 按照降序插入学生的成绩情况,并返回链表头指针 */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {
//TODO
    StudentLinkedListNode *p,*q;
    if(head==NULL){//表不存在，初始化，加入表头
        head = (StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));
        head->next = NULL;
    }
    for(q = head, p = head->next;p&&node->Grade < p->Grade;q = p,p = p->next);//按降序要求找到合适位置
    q->next = (StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));//也可以用复制节点函数来完成
    q->next->ClassID = node->ClassID;
    q->next->StuID = node->StuID;
    q->next->Grade = node->Grade;
    q->next->next = p;
    return head;
}
/** 根据学号搜索某个学生的成绩情况 如果没有,请printf("this class  has no such student as id=%d",id)； */
void searchByID(StudentLinkedListNode*head ,int id){
    StudentLinkedListNode *p;
    for(p = head;p->next;p = p->next){
        if(p->next->StuID==id){//找到并打印相关成绩信息
            printf("Student %d's Grade is %d.\n",id,p->next->Grade);
            break;
        }
    }
    if(p->next==NULL){//未找到
        printf("this class  has no such student as id=%d",id);
    }
//TODO
}

/** 根据学号删除某个学生的成绩情况 如果没有,请printf("this class has no such student as id=%d",id);*/
StudentLinkedListNode* deleteByID(StudentLinkedListNode* head,int id){
    StudentLinkedListNode *p,*q;
    for(p = head;p->next;p = p->next){//顺序查找
        if(p->next->StuID==id)
            break;
    }
    if(p->next==NULL){//未找到
        printf("this class  has no such student as id=%d",id);
    }
    else{//找到并删除
        q = p->next;
        p->next = p ->next->next;
        free(q);
    }
    return head;
//TODO
}
/** 合并两个班级的成绩情况 */
StudentLinkedListNode* mergeLinkedList(StudentLinkedListNode* heads[]){
    //tips:因为传入的都是指针,为了防止拆分过程中影响了原来总链表的存储,
    //在链表node赋值的时候可以用上面提供的studentLinkedListCopy函数
    //如 node->next = temp_node 改为 node->next = studentLinkedListCopy(temp_node)
	//TODO
	StudentLinkedListNode *p1,*p2,*newhead,*pn;
	newhead = (StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));

	for(p1 = heads[0]->next,p2 = heads[1]->next,pn = newhead;p1&&p2;pn = pn->next){//归并
        if(p1->Grade > p2->Grade){
            pn->next = studentLinkedListCopy(p1);
            p1 = p1->next;
        }
        else{
            pn->next = studentLinkedListCopy(p2);
            p2 = p2->next;
        }
	}
	for(;p1;p1 = p1->next)//剩余数据直接补进去
        pn->next = studentLinkedListCopy(p1);
	for(;p2;p2 = p2->next)
        pn->next = studentLinkedListCopy(p2);
	return newhead;

}
/**翻转总表，返回头指针*/
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head){
//TODO
    StudentLinkedListNode *p,*q;
    p = head->next->next;
    head->next->next = NULL;
    for(;p;){//按原表顺序将各节点插入头节点后面
        q = p->next;
        p->next = head->next;
        head->next = p;
        p = q;
    }
    return head;
}

int main(){
        StudentLinkedListNode* Class[2]={NULL};
        StudentLinkedListNode* All=NULL;
		StudentLinkedListNode* reAll=NULL;
        printf( "+----------------+\n"
                "|数据结构实验1   |\n"
                "|线性表          |\n"
                "|190110716朱海峰 |\n"
                "+----------------+\n"
                "1.insert 2.search by StuID 3.delete by StuID  4.merge 5.reverse 6.output  \n");

        int op;
        int i;

        int tempClass;
        int tempStuId;
        int tempGrade;
        char name[10];
        StudentLinkedListNode *tempNode;
        while (scanf("%d", &op) != EOF) {
            switch (op) {
                case 1:
                    printf("How many rows of data do you need to input?\n");
                    scanf("%d",&i);
                    printf("input the i row data format as:class_id,student_id,grade\n");
                    while (i!=0){
                        scanf("%d,%d,%d", &tempClass,&tempStuId, &tempGrade);
                        tempNode = studentLinkedListCreate(tempClass, tempStuId, tempGrade);
                        Class[tempClass]=studentLinkedListAdd(Class[tempClass], tempNode);
                        i--;
                    }
                    break;
                case 2:
                    printf("input the data format as: ClassID, StuID\n");
                    scanf("%d,%d",&tempClass,&tempStuId);
                    searchByID(Class[tempClass], tempStuId);
                    break;
                case 3:
                    printf("input the data format as: ClassID, StuID\n");
                    scanf("%d,%d",&tempClass,&tempStuId);
                    Class[tempClass]=deleteByID(Class[tempClass], tempStuId);
                    break;
                case 4:
                    All=mergeLinkedList(Class);
                    outputStudentLinkedList(All);
                    break;
                case 5:
                    reAll=reverseLinkedList(All);
                    outputStudentLinkedList(reAll);
                    break;
                case 6:
                    printf("Class 0:\n");
                    outputStudentLinkedList(Class[0]);
                    printf("\nClass 1:\n");
                    outputStudentLinkedList(Class[1]);
                    break;

            }
            printf("\n###################################\n");
            printf("1.insert 2.search by studentID 3.delete by studentID 4.merge 5. reverse 6.output  \n");
    }
}
