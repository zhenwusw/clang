#include <stdio.h>

struct BSTreeNode {
  int m_nValue;
  BSTreeNode *m_pLeft;
  BSTreeNode *m_pRight;
};

// (1) solution 1
// 从根结点开始，将左子树转化成排序的左子链表
//               将右子树转化成排序的右子链表
// 链接左右子链表
//              左子树的最右(or current node) -> 当前结点 -> 右子树的最左 (or current node)
//
//
// (2) solution 2: 中序遍历
// 每访问一个结点，先假设之前访问过的结点(子树) 已是排序双向链表
//                 将当前结点指向链表末端
// ==================================================

// implementation
// ===================================================
// (1) solution 1
// 从根结点开始，将左子树转化成排序的左子链表
//               将右子树转化成排序的右子链表
// 链接左右子链表
//              左子树的最右(or current node) -> 当前结点 -> 右子树的最左 (or current node)
BSTreeNode* convert(BSTreeNode* pHeadOfTree) {
  return convertNode(pHeadOfTree, true);
}

BSTreeNode* convertNode(BSTreeNode *pNode, bool asRight) {
  // 6. if it's an empty tree
  if(!pNode) return NULL;

  BSTreeNode *pLeft = NULL;
  BSTreeNode *pRight = NULL;

  // 2. if we have left sub-tree
  if(pNode->m_pLeft) pLeft = convertNode(pNode->m_pLeft, false);
  if(pLeft) {
    pLeft->m_pRight = pNode;
    pNode->m_pLeft  = pLeft;
  }

  // 3. if we have right sub-tree
  if(pNode->m_pRight) pRight = convertNode(pNode->m_pRight, true);

  if(pRight) {
    pNode->m_pRight = pRight;
    pRight->m_pLeft = pNode;
  }

  // 4. returns right-left node (or current node)
  // 5. returns left-right node (or current node)
  BSTreeNode *pTemp = pNode;
  if(asRight){
    while(pTemp->m_pLeft){
      pTemp = pTemp->m_pLeft;
    }
  } else {
    while(pTemp->m_pRight){
      pTemp = pTemp->pRight;
    }
  }

  return pTemp;
}

// (2) solution 2: 中序遍历
// 每访问一个结点，先假设之前访问过的结点(子树) 已是排序双向链表
//                 将当前结点指向链表末端

BSTreeNode* convert(BSTreeNode* pHeadOfTree) {
  BSTreeNode *pLastNodeInList = NULL;
  convertNode(pHeadOfTree, pLastNodeInList);

  BSTreeNode *pHeadOfList = pLastNodeInList;
  while(pHeadOfList && pHeadOfList->m_pLeft) {
    pHeadOfList = pHeadOfList->m_pLeft;
  }

  return pHeadOfList;
}

// why *&, because we want to change pLastNodeInList
void convertNode(BSTreeNode* pNode, BSTreeNode*& pLastNodeInList) {
  // if pNode == NULL

  BSTreeNode *pCurrent = pNode;

  // Handle `L` in LVR
  // ... convert left sub-tree
  // this is where we `LVR` the tree
  if(pCurrent->m_pLeft != NULL)
    convertNode(pCurrent->m_pLeft, pLastNodeInList);

  //// ...
  pCurrent->m_pLeft = pLastNodeInList;
  if(pLastNodeInList != NULL) {
    pLastNodeInList->m_pRight = pCurrent;
  }

  // Handle `V` in LVR
  // `pLastNodeInList` becomes `V` for the right sub-tree
  pLastNodeInList = pCurrent;

  // Handle `R` in LVR
  if(pCurrent->m_pRight != NULL) {
    convertNode(pCurrent->m_pRight, pLastNodeInList);
  }
}

