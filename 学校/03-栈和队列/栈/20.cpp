#include <stdio.h>
#include <stdlib.h>

#define STEmpty 1
#define STOK 0

// 栈操作代码
typedef struct LNode
{
    float data;

    struct LNode *next;
} LNode;

// 把这个节点挂在输入节点的后面
LNode *MakeNode(float data)
{
    LNode *p = (LNode *)malloc(sizeof(LNode));
    p->data = data;
    p->next = NULL;

    return p;
}
// 制造头结点
LNode *ListInit(void)
{
    return MakeNode(0);
}

// 默认传入的有应该是头结点
bool StackEmpty(LNode &L)
{
    if (L.next == NULL)
    {
        return STEmpty;
    }
    else
        return STOK;
}

// 返回的是最最后一个节点
LNode *GototheEnd(LNode &S)
{
    LNode *cur = &S;

    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    return cur;
}

// 加入节点,只能是从后面加入
void Push(LNode &S, float e)
{
    LNode *End = GototheEnd(S);

    End->next = MakeNode(e);
}

void Pop(LNode &S, float &e)
{
    // 判空
    if (StackEmpty(S))
    {
        fprintf(stderr, "stack empty");
        exit(1);
    }
    // 出栈代码
    LNode *End = &S;
    LNode *End0 = NULL;
    while (End->next != NULL)
    {
        End0 = End;
        End = End->next;
    }

    e = End->data;
    free(End);
    End0->next = NULL;
}

int main(void)
{
    LNode *head = ListInit();

    char input[50];
    scanf("%s", input);
    int i = 0;
    while (input[i] != '\0')
    {
        // 先筛数字
        if (input[i] <= '9' && input[i] >= '0')
        {
            Push(*head, (int(input[i]) - '0'));
        }
        // 筛符号
        else
        {
            if (input[i] == '+')
            {
                float a, b;
                Pop(*head, a);
                Pop(*head, b);
                float c = a + b;
                Push(*head, c);
            }
            if (input[i] == '-')
            {
                float a, b;
                Pop(*head, a);
                Pop(*head, b);
                float c = b - a;
                Push(*head, c);
            }
            if (input[i] == '*')
            {
                float a, b;
                Pop(*head, a);
                Pop(*head, b);
                float c = a * b;
                Push(*head, c);
            }
            if (input[i] == '/')
            {
                float a, b;
                Pop(*head, a);
                Pop(*head, b);
                float c = b / a;
                Push(*head, c);
            }
            if (input[i] == '%')
            {
                float a, b;
                Pop(*head, a);
                Pop(*head, b);
                float c = int(b) % int(a);
                Push(*head, c);
            }
        }

        i++;
    }

    float output;
    Pop(*head, output);
    printf("%.2f", output);

    return 0;
}