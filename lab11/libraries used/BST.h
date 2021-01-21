#ifndef QUOTBST_H
#define QUOTBST_H

#include "quot.h"
#include "time.h"

typedef struct  binarysearchtree* BST;
typedef struct BSTnode* link;

BST BSTinit();
void BSTfree(BST bst);
Quot BSTsearch(BST bst, Data data);
void BSTinsert_leaf(BST bst, Quot quot);
void BSTupdateQuot(BST bst, Data data, float val, int num);
void BSTquotMinMax(BST bst, Data data_min, Data data_max, Quot* q_min, Quot* q_max);
link rotR(link h);
link rotL(link h);
link partR(link h, int r);
void BSTbalance(BST bst);
#endif
