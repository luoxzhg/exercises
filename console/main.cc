/**
*** ��Ŀ������һ�ö�Ԫ�����������ö�Ԫ������ת����һ�������˫������
*** Ҫ���ܴ����κ��µĽ�㣬ֻ����ָ���ָ��
**/

struct  BiTreeNode
{
    int  data;
    BiTreeNode* pLchild;
    BiTreeNode* pRchild;
};

typedef BiTreeNode* BiTree;
typedef BiTreeNode* DList;

//!< �������һ�������������¼˫�������ĩβ�ڵ㣬�����ӽڵ㣬����ٷ���ͷ�ڵ㡣
DList  ConvertTree(BiTree pRoot);
void  ConvertNode(BiTreeNode* pCurrent, BiTreeNode*& plastNodeInList);

DList ConvertTree(BiTree pRoot)
{
    BiTreeNode* plastNodeInList = nullptr;    /// plastNodeInList ��¼ת�������������һ���ڵ㣬��ʼΪ nullptr��
    ConvertNode(pRoot, plastNodeInList);

    /// ����ͷָ��
    BiTreeNode* pHead = plastNodeInList;
    while (pHead && pHead->pLchild)
        pHead = pHead->pLchild;
    return pHead;
}

void  ConvertNode(BiTreeNode* pCurrent, BiTreeNode*& plastNodeInList)
{
    if (nullptr == pCurrent)
        return;

    /// �ݹ�������
    ConvertNode(pCurrent->pLchild, plastNodeInList);

    /// ����ǰ�ڵ����ӵ�˫��������
    pCurrent->pLchild = plastNodeInList;
    if (plastNodeInList != nullptr)
    {
        plastNodeInList->pRchild = pCurrent;   // ˫������
    }
    plastNodeInList = pCurrent;            /// ����ĩβ�ڵ�

    /// �ݹ�������
    ConvertNode(pCurrent->pRchild, plastNodeInList);
}


//!< ������������ڵ�ǰ�ڵ�ʱ���ȵݹ鴦���������󣬷��ص�ǰ�ڵ��ǰ��(��������������������ڵ�)��
//!< �ٵݹ鴦�����������ص�ǰ�ڵ�ĺ��(�������������������ʼ�ڵ�)��Ȼ��ǰ������ǰ�ڵ㣬����໥����������
DList  ConvertTree2(BiTree pRoot);

/// bool ֵ��־��������������������������������������βָ�룬����������ͷָ�롣
DList  ConvertNode2(BiTreeNode* pCurrent, bool asRight);

DList  ConvertTree2(BiTree pRoot)
{
    return ConvertNode2(pRoot, true);   /// �Ը��ڵ㿪ʼ����������˫�������ͷָ��
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

    /// ���ݵ�ǰ�ڵ����������������������������غ��ʵĽڵ�ָ��
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
