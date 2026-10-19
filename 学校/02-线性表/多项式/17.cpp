#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define OVERFLOW -2
typedef int Status;

typedef struct data
{             // 项的表示,多项式的项作为LinkList的数据元素
    int coef; // 系数COEFFICIENT
    int expn; // 指数EXPONENT
} term, ElemType;

typedef struct LNode // 结点类型
{
    ElemType data;
    struct LNode *next;
} *Link, *Position;
typedef struct LinkList // 链表类型
{
    Link head, tail; // 分别指向线性链表中的头结点和最后一个结点
    int len;         // 指向线性链表中数据元素的个数
} LinkList;
typedef LinkList polynomial; // 用带表头结点的有序链表表示多项式

/* 请在这里填写答案 */

// 创建一个节点
LNode *MakeNode(int coef, int expn)
{
    LNode *p = (LNode *)malloc(sizeof(LNode));
    p->data.coef = coef;
    p->data.expn = expn;
    p->next = NULL;

    return p;
}

void ListInit(polynomial &pa)
{
    pa.head = MakeNode(0, 0);
    pa.len = 0;
    pa.tail = pa.head;
}
// 按照节点顺序来插入节点
// head是要插入的链表的头结点 seq 的意思是要插入的那个数字的前面一个 coef expn都是我要插入的数字的两个数据
void ListInsert(LNode *head, int seq, int coef, int expn)
{
    LNode *cur = head;
    // 走到要插入的那个节点的地方
    for (int i = 0; i < seq; i++)
    {
        cur = cur->next;
    }
    // 插入逻辑
    LNode *tmp = cur->next;
    cur->next = MakeNode(coef, expn);
    cur->next->next = tmp;
}
// 找到这节点它应该在的位置
int FindSeq(LNode *head, int expn)
{

    LNode *cur = head;
    if (cur->next == NULL)
    {
        return 0;
    }
    int seq = 0;
    //  从头节点出发,遍历整个链表,直到我找到那个比它大的那个,而它的前一位,就是我的seq
    do
    {
        if (cur->next != NULL && cur->next->data.expn < expn)
        {
            seq++;
            cur = cur->next;
        }
        else
            return seq;

    } while (1);
}

// 读入 m 项（系数、指数），在 Pa 里建出这个多项式
void CreatePolyn(polynomial &Pa, int m)
{
    // 创建头节点
    ListInit(Pa);
    LNode *head = Pa.head;
    LNode *cur_T = head;
    // 实现读入这个数字的过程
    for (int i = 0; i < m; i++)
    {
        // 把新加入的数加入的逻辑
        int coef, expn;
        scanf("%d %d", &coef, &expn);
        ListInsert(head, FindSeq(head, expn), coef, expn);
        // 增加一个长度
        Pa.len++;
    }
    // 走到最后把最后一个节点找出来
    while (cur_T->next != NULL)
    {
        cur_T = cur_T->next;
    }

    Pa.tail = cur_T;
}

// 返回 Pa 的头结点
LNode *GetHead(polynomial Pa)
{
    return Pa.head;
}

// 返回 p 的下一个结点，没有就返回 NULL
LNode *NextPos(polynomial Pa, Position ha)
{
    return ha->next;
}

void ListRemove(polynomial Pa, LNode *cur_n)
{
    LNode *prior;
    LNode *cur = Pa.head;
    while (cur != cur_n)
    {
        prior = cur;
        cur = cur->next;
    }
    prior->next = cur->next;
}

// 算 Pa + Pb，结果放回 Pa
void AddPolyn(polynomial &Pa, polynomial Pb)
{
    LNode *cur_pa = Pa.head->next;
    LNode *cur_pb = Pb.head->next;

    while (cur_pb != NULL)
    {
        int A_EQ_B = 0;
        cur_pa = Pa.head->next;
        while (cur_pa != NULL)
        {
            // pa和pb的指数是否相同
            if (cur_pa->data.expn == cur_pb->data.expn)
            {
                A_EQ_B = 1;
                // 系数相加等于0,直接移除这个节点
                if (cur_pa->data.coef + cur_pb->data.coef == 0)
                {
                    ListRemove(Pa, cur_pa);
                    Pa.len--;
                }
                // 系数相加不为0,把他们加起来
                else
                {
                    cur_pa->data.coef += cur_pb->data.coef;
                }
            }
            cur_pa = cur_pa->next;
        }
        // 整个Pa里都没有和它指数相同的项
        if (A_EQ_B == 0)
        {
            // 直接把不一样的这一项加进去
            ListInsert(Pa.head, FindSeq(Pa.head, cur_pb->data.expn), cur_pb->data.coef, cur_pb->data.expn);
            Pa.len++;
        }

        cur_pb = cur_pb->next;
    }
}

int main(void)
{
    polynomial Pa, Pb;
    int m, n;
    Position ha, hb, qa, qb;
    term a;
    scanf("%d", &m);
    CreatePolyn(Pa, m);
    scanf("%d", &n);
    CreatePolyn(Pb, n);
    AddPolyn(Pa, Pb);
    if (Pa.len == 0)
    {
        printf("0\n");
        return 0;
    }
    ha = GetHead(Pa); // ha和hb分别指向Pa和Pb的头结点
    qa = NextPos(Pa, ha);
    while (qa)
    {
        printf("%d,%d\n", qa->data.coef, qa->data.expn);
        ha = qa;
        qa = NextPos(Pa, ha);
    }
    return 0;
}