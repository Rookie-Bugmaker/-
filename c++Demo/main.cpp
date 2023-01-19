#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include "math.h"
#include <windows.h>

using namespace std;

double length = 10000;//数组初始有效长度默认100000
double average = 0;//求平均数
//double var = 0; //求方差
//double standard = 10; //求标准差

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

//删除抽到的但不是尾结点
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

//抽取随机数，如果抽到就删除
int get(LinkList L, int rand, int* count)
{
    //printf("第 %d 次，本次抽到:%d\n", *count + 1, rand);
    LinkList tmp = L -> next;
    LinkList tmpPre = L;
    if(tmp == NULL)
    {
        return 0;
    }
    //当不是尾结点时
    while(tmp->next != NULL)
    {
        if(rand == tmp -> data)
        {
            //删了直接返回
            DeleteNode(tmp);
            *count = *count + 1;
            //printf("抽到了新的！\n");
            return 0;
        }
        tmp = tmp->next;
        tmpPre = tmpPre->next;
    }
    //到尾结点会出循环
    //判断尾结点是否需要删除
    if(rand == tmp -> data)
    {
        tmpPre->next = NULL;
        free(tmp);
        *count = *count + 1;
        //printf("抽到了新的！\n");
        return 0;
    }
    *count = *count + 1;
    //printf("没能抽到，继续抽！\n");
    return 0;
}

int run(int types, int i)
{
    //标志位
//    int flag;
//    scanf("%d", &flag);

    //盲盒种类数
//    int types;
//    scanf("%d", &types);

    //抽取次数
    int count = types;

    //生成动态长度的盲盒种类数组
    int* array;
    array = (int*)malloc(sizeof(int) *types);

    //数组置零，还没抽到的值置为-1
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
    //重新撒种
    srand(tv.tv_usec%1000 * sys.wMilliseconds + i);


    //printf("第一次抽到了:");
    //先抽种类数次，并将抽到的置为-2(至少的情况)
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

    //创建未抽到的种类链表，使用链表原因是因为每次查询最坏都要查一遍（即这次抽取没抽到新的），顺序查询是不可避免的
    LinkList L;
    L = InitialList();
    CreateListT(L, types, array);

    //循环抽取随机数直到初始创建的未抽到种类链表为空
    while(L->next != NULL)
    {
        get(L, rand()%types, &count);
    }
    printf("抽取%d种盲盒，本次花费%d次抽全\n", types,count);
    return count;
}

double Calculate(int* total)
{

    long double sum = 0;//求和
    for (int i = 0; i <= length; i++)
    {
        sum += total[i];//求和
    }
    average = sum / length;//求平均值

//    for (int j = 0; j <= length; j++)
//    {
//        var += pow(total[j]-average,2)/length;//求方差
//    }
//
//    standard = pow(var,0.5);//求标准差

//        printf("sum = %g\n",sum);//这边打印也可以使用printf("%f\n",sum);这种打印默认出来的数是小数点后6位
//        printf("length of array[4] = %d\n",length);
//        printf("average = %g\n",average);
//        printf("var = %g\n",var);
//        printf("standard = %g\n",standard);
    return average;
}

int main()
{
    int types;
    printf("请输入本次抽取盲盒的种类数：\n");
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
        printf("目前平均值为：%3lf\n", average);
    }while(abs(average - tmpAverage) > 0.1);
    printf("%1lf ", length);
    printf("%d 种盲盒，全部抽到的次数平均值为：%3lf\n",types, average);
    return 0;
}
