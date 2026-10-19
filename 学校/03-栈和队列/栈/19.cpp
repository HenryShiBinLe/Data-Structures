// 顺序栈的基本操作

#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100 // 存储空间初始分配
#define STACKINCREMENT 10   // 存储空间分配增量
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int SElemType;

typedef struct
{
    SElemType *base;
    SElemType *top;

    int stacksize;
} SqStack;

Status InitStack(SqStack &s)
{
    s.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s.base)
        exit(OVERFLOW); // 存储分配失败
    s.top = s.base;
    s.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack s, SElemType &e)
{
    if (s.base == s.top) // 栈是空的
        return ERROR;
    e = *(s.top - 1);
    return OK;
}

Status Push(SqStack &s, SElemType e)
{ // 插入元素e为新的栈顶元素
    if (s.top - s.base >= s.stacksize)
    { // 栈满,追加存储空间
        s.base = (SElemType *)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!s.base)
            exit(OVERFLOW); // 存储分配失败
        s.top = s.base + s.stacksize;
        s.stacksize += STACKINCREMENT;
    };
    *(s.top++) = e;
    return OK;
}

Status StackEmpty(SqStack s)
{
    if (s.base == s.top)
        return OK;
    else
        return ERROR;
}

Status Pop(SqStack &s, SElemType &e)
{
    if (s.base == s.top) // 判断栈是否为空
        return ERROR;
    e = *(s.top-- - 1);

    return OK;
}

int main(void)
{
    return 0;
}