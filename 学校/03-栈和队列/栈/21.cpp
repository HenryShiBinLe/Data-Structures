#include <stdio.h>
#include <stdlib.h>

#define STEmpty 1
#define STOK 0

// 栈操作代码
typedef struct LNode
{
    char data;

    struct LNode *next;
} LNode;

// 把这个节点挂在输入节点的后面
LNode *MakeNode(char data)
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

// 返回的是最最后一个节点 , 也就是栈顶的意思
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
void Push(LNode &S, char e)
{
    LNode *End = GototheEnd(S);

    End->next = MakeNode(e);
}

void Pop(LNode &S, char &e)
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

char Getop(LNode &head)
{
    LNode *p = GototheEnd(head);
    return p->data;
}

void PopPrintf(LNode &S)
{
    char output;

    LNode *cur = GototheEnd(S);

    while (cur != &S && cur->data != '(')
    {
        Pop(S, output);
        printf("%c", output);
        cur = GototheEnd(S);
    }
}

int main(void)
{
    LNode *head = ListInit();

    char input[100];
    scanf("%s", input);

    int i = 0;

    while (input[i] != '\0')
    {

        if (input[i] <= 'z' && input[i] >= '0')
        {
            printf("%c", input[i]);

            i++;
            continue;
        }

        char top = Getop(*head);
        char takeout;

        if (input[i] == ')')
        {
            PopPrintf(*head);
            // 此处需要弹出左括号
            LNode *cur;
            cur = GototheEnd(*head);

            if (cur->data == '(')
            {
                char throwaway;
                Pop(*head, throwaway);
            }
        }

        // 栈空进入
        else if (StackEmpty(*head) || input[i] == '(' || top == '(')
        {
            Push(*head, input[i]);
        }

        // 遇到右括号,开始弹出栈

        // 栈顶元素的等级较低,与进入的元素相比
        else if ((input[i] == '*' || input[i] == '/' || input[i] == '%') && (top == '+' || top == '-'))
        {
            Push(*head, input[i]);
        }

        // 栈顶元素等级较高,与进入的等级相比
        else if ((input[i] == '+' || input[i] == '-') && (top == '*' || top == '/' || top == '%'))
        {
            // 弹出当前栈的全部
            PopPrintf(*head);
            // 此处不应弹出左括号
            //  新元素进栈
            Push(*head, input[i]);
        }

        // 栈顶与进入的元素同等级
        else
        {
            Pop(*head, takeout);
            printf("%c", takeout);
            Push(*head, input[i]);
        }
        i++;
    }

    PopPrintf(*head);

    return 0;
}
