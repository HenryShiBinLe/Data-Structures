// 5-1 循环链表的基本操作（程序填空题，40 分）  作者：吴敏华  单位：首都师范大学
// 假设循环链表中存放的是整型数据，请完善循环链表的基本操作
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;

// –––––线性表的链式存储结构–––––
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

//--------------基本操作-----------------
Status InitList(LinkList &L)
{                                        // 建立一个空的链表，L为头结点指针.
    L = (LinkList)malloc(sizeof(LNode)); // 生成头结点
    if (!L)
        return ERROR;
    L->next = L;
    L->data = 0;
    return OK;
} // InitList

Status DestroyList(LinkList &L)
{
    LinkList p, q;
    p = L->next;
    while (p != L) // 顺着环走，重新回到表头说明一圈已走完
    {
        q = p->next;
        free(p);
        p = q;
    }
    free(L);
    return OK;
}

int ListEmpty(LinkList L)
{
    if (L->next == L) // 头结点指向自己 = 空表
        return TRUE;
    else
        return FALSE;
}

Status GetElem(LinkList L, int i, ElemType &e)
{ // L为带头结点的循环单链表的头指针.
  // 当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR
    LinkList p;
    int j;
    p = L->next;
    j = 1; // 初始化,p指向第一个结点,j为计数器
    while (p != L && j < i)
    { // 顺指针向后查找,直到p指向第i个元素或绕回表头
        p = p->next;
        ++j;
    }
    if (p == L || j > i)
        return ERROR; // 第i个元素不存在
    e = p->data;      // 取第i个元素
    return OK;
} // GetElem

Status ListInsert(LinkList &L, int i, ElemType e)
{ // 在带头结点的循环链表L中第i个位置之前插入元素e
    LinkList p, s;
    int j;
    p = L;
    j = 0;
    while (p->next != L && j < i - 1)
    {
        p = p->next;
        ++j;
    } // 寻找第i-1个结点,绕回表头就停
    if (j > i - 1 || j < i - 1)
        return ERROR;                    // i 小于1或者大于表长
    s = (LinkList)malloc(sizeof(LNode)); // 生成新结点
    if (!s)
        return ERROR;
    s->data = e;
    s->next = p->next; // 插入L中
    p->next = s;
    return OK;
}

Status ListDelete(LinkList &L, int i, ElemType &e)
{ // 在带头结点的循环单链线性表L中,删除第i个元素,并由e返回其值
    int j;
    LinkList p, q;
    p = L;
    j = 0;
    while (p->next != L && j < i - 1)
    {
        p = p->next;
        ++j;
    } // 寻找第i个元素,并令p指向其前驱
    if (p->next == L || j > i - 1)
        return ERROR; // 删除位置不合理
    q = p->next;
    p->next = q->next; // 删除并释放结点
    e = q->data;
    free(q);
    return OK;
}

int main(void)
{
    return 0;
}