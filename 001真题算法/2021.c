#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// 链表数据结构
typedef struct node
{
    int element;       // 结点数据域
    struct node *link; // 结点指针域
} Node;
typedef struct singleList
{
    Node *first; // 头指针
    int n;       // 单链表中元素个数
} SingleList;

// 图数据结构
typedef struct eNode
{
    int AdjVex;
    int w;
    struct eNode *next;
} ENode;
typedef struct lGraph
{
    int e;
    int n;
    ENode **a;
} LGraph;

// 树数据结构
typedef struct bTNode
{
    int element;
    struct bTNode *lchild;
    struct bTNode *rchild;
} BTNode;
typedef struct binaryTree
{
    BTNode *root;
} BinaryTree;

// 1、给定一个单链表，判断链表是否存在环路
bool IfLoop(SingleList *L)
{
    int count = 0;
    Node *p = L->first;
    while (p)
    {
        count++;
        if (count > L->n)
            return false;
        p = p->link;
    }
    return true;
}

// 2、输入一棵二叉树和一个整数时，能打印出二叉树中结点值的和为输入整数的所有路径
void Find(BTNode *t, int sum)
{
    if (!t)
        return;
    push(S, t->element); // 将t->element进栈
    sum -= t->element;
    if (sum == 0 && !t->lchild && !t->rchild)
        Pop(S); // 找到符合的路径，将栈S弹出栈（栈S中存着路径）
    Find(t->lchild, sum);
    Find(t->rchild, sum);
    pop(S); // 未找到符合的路径，将栈S中栈顶元素弹出
}
void FindPath(BinaryTree *tree, int sum)
{
    if (!tree->root)
        return;
    Find(tree->root, sum);
}

// 3、一个有向图作为输入，若有根，确认图的根节点
void DFS(LGraph *G, int visited[], int i)
{
    if (visited[i] == 1)
        return;
    visited[i] = 1;
    ENode *p = G->a[i];
    while (p)
    {
        DFS(G, visited, p->AdjVex);
        p = p->next;
    }
}
int GetRoot(LGraph *G)
{
    int i = 0, j = 0;
    int count = 0;
    int *visited = (int *)malloc(sizeof(int) * G->n);
    for (i = 0; i < G->n; i++)
    {
        count = 0;
        for (j = 0; j < G->n; j++)
            visited[j] = 0;
        DFS(G, visited, i);
        for (j = 0; j < G->n; j++)
            count += visited[i];
        if (count == G->n)
            return i;
    }
    return -1;
}