#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
    int coef, expn;
    struct LNode *next;
} LNode;

typedef struct
{
    LNode *head; // 指向头结点
    int len;
} LinkList;

// 造一个节点，返回它的地址
LNode *MakeNode(int coef, int expn)
{
    LNode *p = (LNode *)malloc(sizeof(LNode));
    p->coef = coef;
    p->expn = expn;
    p->next = NULL;
    return p;
}

// 传链表结构体的地址进来，通过 list-> 修改它
void ListInit(LinkList *list)
{
    list->head = MakeNode(0, 0); // 头结点
    list->len = 0;
}

int GetSeq(LinkList *list, int expn)
{
    int seq = 0;
    LNode *cur = list->head;
    if (cur->next == NULL)
    {

        return 0;
    }
    do
    {
        if (cur->next != NULL && expn > cur->next->expn)
        {
            cur = cur->next;
            seq++;
        }
        else
            return seq;

    } while (1);
}

// 在第 seq 个节点之后插入（seq = 0 表示插在头结点后面），成功返回 1，失败返回 0
int ListInsert(LinkList *list, int coef, int expn, int seq)
{
    if (seq < 0 || seq > list->len)
        return 0;

    LNode *cur = list->head;
    for (int i = 0; i < seq; i++)
        cur = cur->next;

    LNode *s = MakeNode(coef, expn);
    s->next = cur->next;
    cur->next = s;
    list->len++;
    return 1;
}

void ListPrint(LinkList *list)
{
    if (list->head->next == NULL)
    {
        printf("0 0");
        /* code */
    }

    for (LNode *p = list->head->next; p != NULL; p = p->next)
    {
        if (p == list->head->next)
        {
            printf("%d %d", p->coef, p->expn);
            /* code */
        }
        else
            printf(" %d %d", p->coef, p->expn);
    }
}

void GetD(LinkList *list, LinkList *out)
{
    LNode *cur = list->head->next;
    while (cur != NULL)
    {
        cur->coef = cur->coef * cur->expn;
        cur->expn -= 1;
        int seq = GetSeq(out, cur->expn);
        ListInsert(out, cur->coef, cur->expn, seq);

        // printf("======current num=========\n");
        // printf("%d %d\n", cur->coef, cur->expn);

        // printf("=======seq==========\n");
        // printf("%d\n", seq);

        // printf("========out========\n");
        // ListPrint(out);

        cur = cur->next;
    }
}

int main(void)
{
    LinkList L;
    ListInit(&L);

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int c, e;
        scanf("%d %d", &c, &e);
        if (e == 0)
        {
            continue;
        }

        ListInsert(&L, c, e, L.len);
    }

    LinkList out;
    ListInit(&out);
    GetD(&L, &out);

    ListPrint(&out);
    return 0;
}