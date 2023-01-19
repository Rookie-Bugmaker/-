#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include "math.h"
#include <windows.h>

using namespace std;

double length = 10000;//�����ʼ��Ч����Ĭ��100000
double average = 0;//��ƽ����
//double var = 0; //�󷽲�
//double standard = 10; //���׼��

typedef struct LNode
{
    int data;
    struct LNode* next;
} LNode, *LinkList;

LinkList InitialList()
{
    LinkList L;
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
    return L;
}

void CreateListT(LinkList L, int types, int* array)
{
    LinkList tmp = L;
    for(int i = 0; i < types; i++)
    {
        if(array[i] == -1)
        {
            LinkList s;
            s = (LNode*)malloc(sizeof(LNode));
            s -> data = i;
            tmp->next = s;
            tmp = s;
        }
    }
    tmp->next = NULL;
}

//ɾ���鵽�ĵ�����β���
int DeleteNode(LinkList p)
{
//    if (p == NULL)
//        return false;
//    if (p->next == NULL)
//    {
//        free(p);
//        return 0;
//    }
    LinkList q = p->next;
    p->data = p->next->data;
    p->next = q->next;
    free(q);
    return 0;
}

//��ȡ�����������鵽��ɾ��
int get(LinkList L, int rand, int* count)
{
    //printf("�� %d �Σ����γ鵽:%d\n", *count + 1, rand);
    LinkList tmp = L -> next;
    LinkList tmpPre = L;
    if(tmp == NULL)
    {
        return 0;
    }
    //������β���ʱ
    while(tmp->next != NULL)
    {
        if(rand == tmp -> data)
        {
            //ɾ��ֱ�ӷ���
            DeleteNode(tmp);
            *count = *count + 1;
            //printf("�鵽���µģ�\n");
            return 0;
        }
        tmp = tmp->next;
        tmpPre = tmpPre->next;
    }
    //��β�����ѭ��
    //�ж�β����Ƿ���Ҫɾ��
    if(rand == tmp -> data)
    {
        tmpPre->next = NULL;
        free(tmp);
        *count = *count + 1;
        //printf("�鵽���µģ�\n");
        return 0;
    }
    *count = *count + 1;
    //printf("û�ܳ鵽�������飡\n");
    return 0;
}

int run(int types, int i)
{
    //��־λ
//    int flag;
//    scanf("%d", &flag);

    //ä��������
//    int types;
//    scanf("%d", &types);

    //��ȡ����
    int count = types;

    //���ɶ�̬���ȵ�ä����������
    int* array;
    array = (int*)malloc(sizeof(int) *types);

    //�������㣬��û�鵽��ֵ��Ϊ-1
    for(int i = 0; i < types; i++)
    {
        array[i] = -1;
    }

//    SYSTEMTIME sys;
//    GetLocalTime( &sys );
    struct timeval tv;
    gettimeofday(&tv,NULL);
    SYSTEMTIME sys;
    GetLocalTime( &sys );
//    cout << tv.tv_usec%1000 * sys.wMilliseconds + i;
    //��������
    srand(tv.tv_usec%1000 * sys.wMilliseconds + i);


    //printf("��һ�γ鵽��:");
    //�ȳ��������Σ������鵽����Ϊ-2(���ٵ����)
    for(int i = 0; i < types; i++)
    {
        array[rand()%types] = -2;
    }
//    for(int i = 0; i < types; i++)
//    {
//        if(array[i] == -2)
//        {
//            printf("%d ", i);
//        }
//    }
//    printf("\n");

    //����δ�鵽����������ʹ������ԭ������Ϊÿ�β�ѯ���Ҫ��һ�飨����γ�ȡû�鵽�µģ���˳���ѯ�ǲ��ɱ����
    LinkList L;
    L = InitialList();
    CreateListT(L, types, array);

    //ѭ����ȡ�����ֱ����ʼ������δ�鵽��������Ϊ��
    while(L->next != NULL)
    {
        get(L, rand()%types, &count);
    }
    printf("��ȡ%d��ä�У����λ���%d�γ�ȫ\n", types,count);
    return count;
}

double Calculate(int* total)
{

    long double sum = 0;//���
    for (int i = 0; i <= length; i++)
    {
        sum += total[i];//���
    }
    average = sum / length;//��ƽ��ֵ

//    for (int j = 0; j <= length; j++)
//    {
//        var += pow(total[j]-average,2)/length;//�󷽲�
//    }
//
//    standard = pow(var,0.5);//���׼��

//        printf("sum = %g\n",sum);//��ߴ�ӡҲ����ʹ��printf("%f\n",sum);���ִ�ӡĬ�ϳ���������С�����6λ
//        printf("length of array[4] = %d\n",length);
//        printf("average = %g\n",average);
//        printf("var = %g\n",var);
//        printf("standard = %g\n",standard);
    return average;
}

int main()
{
    int types;
    printf("�����뱾�γ�ȡä�е���������\n");
    scanf("%d", &types);
    int* total;
    total = (int*)malloc(sizeof(int)* 10000000);
    int i = 0;
    for(; i < length; i++)
    {
        total[i] = run(types, i);
    }
    double tmpAverage = Calculate(total);
    do
    {
        int count = run(types, i);
        total[i] = count;
        i++;
        length++;
        Calculate(total);
        printf("Ŀǰƽ��ֵΪ��%3lf\n", average);
    }while(abs(average - tmpAverage) > 0.1);
    printf("%1lf ", length);
    printf("%d ��ä�У�ȫ���鵽�Ĵ���ƽ��ֵΪ��%3lf\n",types, average);
    return 0;
}
