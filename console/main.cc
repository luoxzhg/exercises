/**
*** 题目：输入一棵二元查找树，将该二元查找树转换成一个排序的双向链表。
*** 要求不能创建任何新的结点，只调整指针的指向。
**/

struct  BiTreeNode
{
    int  data;
    BiTreeNode* pLchild;
    BiTreeNode* pRchild;
};

typedef BiTreeNode* BiTree;
typedef BiTreeNode* DList;

//!< 解决方案一：中序遍历，记录双向链表的末尾节点，逐次添加节点，最后再返回头节点。
DList  ConvertTree(BiTree pRoot);
void  ConvertNode(BiTreeNode* pCurrent, BiTreeNode*& plastNodeInList);

DList ConvertTree(BiTree pRoot)
{
    BiTreeNode* plastNodeInList = nullptr;    /// plastNodeInList 记录转换后的链表的最后一个节点，起始为 nullptr。
    ConvertNode(pRoot, plastNodeInList);

    /// 返回头指针
    BiTreeNode* pHead = plastNodeInList;
    while (pHead && pHead->pLchild)
        pHead = pHead->pLchild;
    return pHead;
}

void  ConvertNode(BiTreeNode* pCurrent, BiTreeNode*& plastNodeInList)
{
    if (nullptr == pCurrent)
        return;

    /// 递归左子树
    ConvertNode(pCurrent->pLchild, plastNodeInList);

    /// 将当前节点链接到双向链表中
    pCurrent->pLchild = plastNodeInList;
    if (plastNodeInList != nullptr)
    {
        plastNodeInList->pRchild = pCurrent;   // 双向链接
    }
    plastNodeInList = pCurrent;            /// 更新末尾节点

    /// 递归右子树
    ConvertNode(pCurrent->pRchild, plastNodeInList);
}


//!< 解决方案二：在当前节点时，先递归处理左子树后，返回当前节点的前驱(即中序遍历左子树的最后节点)；
//!< 再递归处理右子树返回当前节点的后继(即右子树中序遍历的起始节点)。然后将前驱，当前节点，后继相互链接起来。
DList  ConvertTree2(BiTree pRoot);

/// bool 值标志调整的是左子树，还是右子树；左子树返回尾指针，右子树返回头指针。
DList  ConvertNode2(BiTreeNode* pCurrent, bool asRight);

DList  ConvertTree2(BiTree pRoot)
{
    return ConvertNode2(pRoot, true);   /// 以根节点开始调整，返回双向链表的头指针
}

DList  ConvertNode2(BiTreeNode* pCurrent, bool asRight)
{
    if (pCurrent == nullptr)
        return nullptr;

    DList  pLeft = ConvertNode2(pCurrent->pLchild, false);
    DList  pRight = ConvertNode2(pCurrent->pRchild, true);
    pCurrent->pLchild = pLeft;
    pCurrent->pRchild = pRight;
    if (pLeft != nullptr)
        pLeft->pRchild = pCurrent;
    if (pRight != nullptr)
        pRight->pLchild = pCurrent;

    /// 根据当前节点是左子树根还是右子树根，返回合适的节点指针
    DList  pReturn = pCurrent;
    if (asRight) {
        while (pReturn->pLchild)
            pReturn = pReturn->pLchild;
    }
    else {
        while (pReturn->pRchild)
            pReturn = pReturn->pRchild;
    }
    return pReturn;
}
