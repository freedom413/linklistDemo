#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

/* 数据类型定义*/
typedef uint8_t nodedata;

/**
 * @brief 链表节点数据结构
 */
typedef struct node
{
    nodedata data;     // 数据
    struct node *next; // 下一个节点的指针
} node;

/**
 * @brief linklist创建节点
 * @param d 节点数据
 * @return node* 创建节点的指针
 */
node *lLNodeCraet(nodedata d)
{
    node *newnode = (node *)malloc(sizeof(node)); // 申请内存空间
    if (newnode == NULL)                          // 如果申请失败 直接提示错误退出程序
    {
        perror("malloc:error");
        exit(-1);
    }
    newnode->data = d;    // 节点的数据 一般是头节点的的数据是链表节点的个数值
    newnode->next = NULL; // 下一个数据先默认为空，等待后续处理
    return newnode;       // 返回新节点的指针
}

/**
 * @brief linklist创建头节点
 * @return node* 创建头节点的指针
 */
node *lLHeadCraet(void)
{
    return lLNodeCraet(0); // 头节点初始化节点个数为0
}

/**
 * @brief 链表尾插
 * @param pphead  指向头节点的指针
 * @param d 节点数据
 */
void lLPushBack(node **pphead, nodedata d)
{
    assert(pphead);
    node *newnode = lLNodeCraet(d); // 申请结点
    if (*pphead == NULL)            // 1.链表为空
    {
        *pphead = newnode; // 直接将头结点置为需要插入的结点
    }
    else
    {
        node *cur = *pphead; // 得到头节点
        while (cur->next)    // 找尾结点
        {
            cur = cur->next;
        }
        cur->next = newnode; // 将尾结点中存放的地址置为插入结点的地址即可
    }
}

/**
 * @brief 链表头插
 * @param pphead  指向头节点的指针
 * @param d 节点数据
 */
void lLPushFront(node **pphead, nodedata d)
{
    assert(pphead);
    node *newnode = lLNodeCraet(d);
    newnode->next = *pphead; // 将申请结点中保存的地址置为头结点的地址
    *pphead = newnode;       // 再将头结点向右移动 更新头节点 这里使用指向指针的指针才可以改变原本的头节点数据
}

/**
 * @brief 链表指定位置后面插入
 * @param pphead  指向头节点的指针
 * @param d 节点数据
 */
void lLInsertPB(node **pphead, node *pos, nodedata d)
{
    assert(pphead && pos);
    node *newnode = lLNodeCraet(d); // 申请结点
    node *next = pos->next;         // 找到插入位置的下一个结点的地址
    pos->next = newnode;            // 插入结点
    newnode->next = next;           // 连接到后面的链表
}

/**
 * @brief 链表在指定位置之前去插入一个节点
 * @param pphead  指向头节点的指针
 * @param d 节点数据
 */

void lLInsertPF(node **pphead, node *pos, nodedata d)
{
    assert(pphead);
    assert(pos);

    node *newnode = lLNodeCraet(d);
    if (*pphead == pos)
    {
        newnode->next = *pphead;
        *pphead = newnode;
    }
    else
    {
        // 找到pos的前一个位置
        node *posPrev = *pphead;
        while (posPrev->next != pos)
        {
            posPrev = posPrev->next;
        }

        posPrev->next = newnode;
        newnode->next = pos;
    }
}

/**
 * @brief 链表尾删
 * @param pphead  指向头节点的指针
 * @param d 节点数据
 */
nodedata lLPopBack(node **pphead)
{
    // 1.链表为空不能删除结点,且该指针不能为空
    assert(*pphead && pphead);

    nodedata t;
    // 2.链表中只有一个结点，直接释放该结点，然后将结点置为NULL
    if ((*pphead)->next == NULL)
    {
        t = (*pphead)->data; // 得到尾节点的数据
        free(*pphead);
        *pphead = NULL;
        return t;
    }

    // 3.链表中有一个以上结点，先找尾结点，释放掉尾结点,置为NULL
    //   但这样还不够，因为倒数第二个结点还存有尾结点的地址，所以需要将他置为NULL
    node *cur = *pphead;          // 用来标记倒数第二个结点
    node *next = (*pphead)->next; // 标记尾结点
    while (next->next)
    {
        next = next->next;
        cur = cur->next;
    }
    t = next->data;   // 得到尾节点的数据
    cur->next = NULL; // 将倒数第二个结点中存的地址置为NULL
    free(next);       // 释放尾结点
    next = NULL;
    return t;
}

/**
 * @brief 链表头删
 * @param pphead  指向头节点的指针
 * @param d 节点数据
 */
nodedata lLPopFront(node **pphead)
{
    assert(*pphead && pphead); // 链表为空不能删除

    nodedata t;
    t = (*pphead)->data;
    node *next = (*pphead)->next; // 记录第二个结点的地址
    free(*pphead);                // 释放头结点
    *pphead = next;               // 将指针指向第二个结点
    return t;
}

/**
 * @brief 链表指定位置删除
 * @param pphead  指向头节点的指针
 * @param d 节点数据
 */
nodedata lLErase(node **pphead, node *pos)
{
    assert(pphead && pos);
    nodedata t;
    if (*pphead == pos) // 如果头结点是要删除的结点
    {
        t = (*pphead)->data;
        *pphead = (*pphead)->next;
        free(pos);
        pos = NULL;
        return t;
    }
    else
    {
        node *cur = *pphead;
        while (cur->next != pos) // 找到要删除的结点
        {
            cur = cur->next;
        }
        t = cur->data;
        cur->next = pos->next; // 将需要删除的结点的上一个结点的next指向需要删除的下一个结点
        free(pos);
        pos = NULL;
        return t;
    }
}

/**
 * @brief 链表查找
 * @param pphead  指向头节点的指针
 * @param d 节点数据
 */
node *lLFind(node *phead, nodedata d)
{
    while (phead)
    {
        if (phead->data == d)
        {
            return phead;
        }
        phead = phead->next;
    }
    return NULL;
}

/**
 * @brief 销毁链表
 * @param pphead  指向头节点的指针
 * @param d 节点数据
 */
void lLDestory(node **pphead)
{
    assert(pphead);
    while (*pphead)
    {
        node *next = (*pphead)->next;
        free(*pphead);
        *pphead = next;
    }
}

/**
 * @brief 链表打印
 * @param pphead  指向头节点的指针
 * @param d 节点数据
 */
void lLPrint(node *phead)
{
    node *cur = phead; // 一般不直接移动头指针，而是创建一个指针变量来移动
    while (cur)        // 当指针为空时结束循环
    {
        printf("%d->", cur->data); // 打印该结点的数据
        cur = cur->next;           // 将指针指向下一个结点
    }
    printf("NULL\n");
}

int main(void)
{
    node *Head = NULL;

    lLPushFront(&Head, 0); // 创建头节点

    lLPushFront(&Head, 1); // 头插数据1
    lLPushFront(&Head, 2);
    lLPushFront(&Head, 3);
    lLPushFront(&Head, 4);
    lLPushFront(&Head, 5);

    lLPushBack(&Head, 99);  // 尾插数据99
    lLPushFront(&Head, 66); // 头插数据66

    node *index1 = lLFind(Head, 4); // 查找数据为4的节点

    lLInsertPB(&Head, index1, 12); // 在数据为4的节点后插入12
    lLInsertPF(&Head, index1, 13); // 在数据为4的节点前插入13

    node *index2 = lLFind(Head, 2); // 查找数据为2的节点

    lLPushBack(&Head, 91);  // 尾插数据91
    lLPushFront(&Head, 61); // 头插数据61
    lLPushBack(&Head, 92);  // 尾插数据92
    lLPushFront(&Head, 62); // 头插数据62
    lLPopBack(&Head);       // 尾删
    lLPopFront(&Head);      // 头删

    lLErase(&Head, index2); // 删除指定节点

    lLPrint(Head); // 遍历打印节点

    return 0;
}