/********
    ���ݽṹʵ��1
    ���Ա�
    190110716�캣��*/
#include <stdlib.h>
#include <stdio.h>
typedef struct node{
    int ClassID;
    int StuID;
    int Grade;
    struct node *next;
}StudentLinkedListNode;


/* ��ӡ�����ڵ� */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{Class:%d, ID:%d, Grade:%d}",node->ClassID, node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else
    {
        printf("\n");
    }

}

/* ����ñ�ĳɼ���� */
void outputStudentLinkedList(StudentLinkedListNode* head){
    // ���ڵ����ڵ�����ĺ���printLinkedListNode���ṩ
    //����ʵ�ֱ���������߼�
	//TODO
	StudentLinkedListNode *p;
	if(head==NULL)
        return;
	for(p = head->next;p;p=p->next){
        printLinkedListNode(p);

	}
}


/** �½�һ������node������ */
StudentLinkedListNode* studentLinkedListCreate( int class_id,int student_id,int grade) {
    //tips:malloc��ʱ��ǵ�Ϊת��Ϊ�ṹ��ָ��
	//TODO
	StudentLinkedListNode *p;
	p = (StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));
	p->next = NULL;
	p->ClassID = class_id;
	p->StuID = student_id;
	p->Grade = grade;
	return p;
}

/** copyһ�����е�node */
StudentLinkedListNode* studentLinkedListCopy(StudentLinkedListNode* src){
    StudentLinkedListNode* tempNode = studentLinkedListCreate(src->ClassID,src->StuID,src->Grade);
    return tempNode;
}



/** ���ս������ѧ���ĳɼ����,����������ͷָ�� */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {
//TODO
    StudentLinkedListNode *p,*q;
    if(head==NULL){//�����ڣ���ʼ���������ͷ
        head = (StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));
        head->next = NULL;
    }
    for(q = head, p = head->next;p&&node->Grade < p->Grade;q = p,p = p->next);//������Ҫ���ҵ�����λ��
    q->next = (StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));//Ҳ�����ø��ƽڵ㺯�������
    q->next->ClassID = node->ClassID;
    q->next->StuID = node->StuID;
    q->next->Grade = node->Grade;
    q->next->next = p;
    return head;
}
/** ����ѧ������ĳ��ѧ���ĳɼ���� ���û��,��printf("this class  has no such student as id=%d",id)�� */
void searchByID(StudentLinkedListNode*head ,int id){
    StudentLinkedListNode *p;
    for(p = head;p->next;p = p->next){
        if(p->next->StuID==id){//�ҵ�����ӡ��سɼ���Ϣ
            printf("Student %d's Grade is %d.\n",id,p->next->Grade);
            break;
        }
    }
    if(p->next==NULL){//δ�ҵ�
        printf("this class  has no such student as id=%d",id);
    }
//TODO
}

/** ����ѧ��ɾ��ĳ��ѧ���ĳɼ���� ���û��,��printf("this class has no such student as id=%d",id);*/
StudentLinkedListNode* deleteByID(StudentLinkedListNode* head,int id){
    StudentLinkedListNode *p,*q;
    for(p = head;p->next;p = p->next){//˳�����
        if(p->next->StuID==id)
            break;
    }
    if(p->next==NULL){//δ�ҵ�
        printf("this class  has no such student as id=%d",id);
    }
    else{//�ҵ���ɾ��
        q = p->next;
        p->next = p ->next->next;
        free(q);
    }
    return head;
//TODO
}
/** �ϲ������༶�ĳɼ���� */
StudentLinkedListNode* mergeLinkedList(StudentLinkedListNode* heads[]){
    //tips:��Ϊ����Ķ���ָ��,Ϊ�˷�ֹ��ֹ�����Ӱ����ԭ��������Ĵ洢,
    //������node��ֵ��ʱ������������ṩ��studentLinkedListCopy����
    //�� node->next = temp_node ��Ϊ node->next = studentLinkedListCopy(temp_node)
	//TODO
	StudentLinkedListNode *p1,*p2,*newhead,*pn;
	newhead = (StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));

	for(p1 = heads[0]->next,p2 = heads[1]->next,pn = newhead;p1&&p2;pn = pn->next){//�鲢
        if(p1->Grade > p2->Grade){
            pn->next = studentLinkedListCopy(p1);
            p1 = p1->next;
        }
        else{
            pn->next = studentLinkedListCopy(p2);
            p2 = p2->next;
        }
	}
	for(;p1;p1 = p1->next)//ʣ������ֱ�Ӳ���ȥ
        pn->next = studentLinkedListCopy(p1);
	for(;p2;p2 = p2->next)
        pn->next = studentLinkedListCopy(p2);
	return newhead;

}
/**��ת�ܱ�����ͷָ��*/
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head){
//TODO
    StudentLinkedListNode *p,*q;
    p = head->next->next;
    head->next->next = NULL;
    for(;p;){//��ԭ��˳�򽫸��ڵ����ͷ�ڵ����
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
                "|���ݽṹʵ��1   |\n"
                "|���Ա�          |\n"
                "|190110716�캣�� |\n"
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
