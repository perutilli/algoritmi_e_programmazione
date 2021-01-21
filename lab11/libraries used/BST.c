#include <stdlib.h>
#include "BST.h"

struct BSTnode { 
	Quot quot;
	link p;
	link l;
	link r;
	int N;
};

struct binarysearchtree {
	link root;
	link z;
};

static link NEW(Quot quot, link p, link l, link r, int N);
static void treeFree(link h, link z);
static Quot searchR(link h, Data data, link z);
static link insertR(link h, Quot quot, link z);
static link searchNode(link h, Data data, link z);
static void quotMinMaxR(link h, link z, Data data_min, Data data_max, Quot* q_min, Quot* q_max);
static link balanceR(link h, link z);

static link NEW(Quot quot, link p, link l, link r, int N) {
	link node = malloc(sizeof(*node));
	node->quot = quot;
	node->l = l;
	node->r = r;
	return node;
}

BST BSTinit() {
	BST bst = malloc(sizeof(*bst));
	bst->root = bst->z = NEW(QUOTsetNull(), NULL, NULL, NULL, 0);
	return bst;
}

static void treeFree(link h, link z) {
	if (h == z)
		return;
	treeFree(h->l, z);
	treeFree(h->r, z);
	free(h);
}

void BSTfree(BST bst) {
	if (bst == NULL) {
		return;
	}
	treeFree(bst->root, bst->z);
	free(bst->z);
	free(bst);
}

static Quot searchR(link h, Data data, link z) {
	if (h == z)
		return QUOTsetNull();
	if (DATAcompare(data, QUOTgetData(h->quot)) < 0) {
		return searchR(h->l, data, z);
	}
	if (DATAcompare(data, QUOTgetData(h->quot)) > 0) {
		return searchR(h->r, data, z);
	}
	return h->quot;
}

static link searchNode(link h, Data data, link z) {
	if (h == z)
		return z;
	if (DATAcompare(data, QUOTgetData(h->quot)) < 0) {
		return searchNode(h->l, data, z);
	}
	if (DATAcompare(data, QUOTgetData(h->quot)) > 0) {
		return searchNode(h->r, data, z);
	}
	return h;
}

Quot BSTsearch(BST bst, Data data) {
	return searchR(bst->root, data, bst->z);
}

static link insertR(link h, Quot quot, link z) {
	if (h == z) {
		return NEW(quot, z, z, z, 0);
	}
	if (DATAcompare(QUOTgetData(quot), QUOTgetData(h->quot)) < 0) {
		h->l = insertR(h->l, quot, z);
		h->l->p = h;
	}
	if (DATAcompare(QUOTgetData(quot), QUOTgetData(h->quot)) > 0) {
		h->r = insertR(h->r, quot, z);
		h->r->p = h;
	}
	(h->N)++;
	return h;
}

void BSTinsert_leaf(BST bst, Quot quot) {
	bst->root = insertR(bst->root, quot, bst->z);
}

void BSTupdateQuot(BST bst, Data data, float val, int num) {
	link node = searchNode(bst->root, data, bst->z);
	if (node == bst->z) {
		BSTinsert_leaf(bst, QUOTnew(val, num, data));
	}
	else {
		node->quot = QUOTupdate(node->quot, val, num);
	}
}

void BSTquotMinMax(BST bst, Data data_min, Data data_max, Quot* q_min, Quot* q_max) {
	quotMinMaxR(bst->root, bst->z, data_min, data_max, q_min, q_max);
}

static void quotMinMaxR(link h, link z, Data data_min, Data data_max, Quot* q_min, Quot* q_max) {

	if (h == z) {
		return;
	}

	if (DATAisNull(data_min) || DATAcompare(QUOTgetData(h->quot), data_min) > 0) {
		quotMinMaxR(h->l, z, data_min, data_max, q_min, q_max);
	}
	if (QUOTisNull(*q_min) || (QUOTgetValue(h->quot) < QUOTgetValue(*q_min))) {
		*q_min = h->quot;
	}
	if (QUOTisNull(*q_max) || (QUOTgetValue(h->quot) > QUOTgetValue(*q_max))) {
		*q_max = h->quot;
	}
	if (DATAisNull(data_max) || DATAcompare(QUOTgetData(h->quot), data_max) < 0) {
		quotMinMaxR(h->r, z, data_min, data_max, q_min, q_max);
	}
}

link rotR(link h) {
	link x = h->l;
	h->l = x->r;
	x->r = h;
	x->N = h->N;
	h->N = 1;
	h->N += (h->l) ? h->l->N : 0;
	h->N += (h->r) ? h->r->N : 0;
	return x;
}

link rotL(link h) {
	link x = h->r;
	h->r = x->l;
	x->l = h;
	x->N = h->N;
	h->N = 1;
	h->N += (h->l) ? h->l->N : 0;
	h->N += (h->r) ? h->r->N : 0;
	return x;
}

link partR(link h, int r) {
	int t = h->l->N;
	if (t > r) {
		h->l = partR(h->l, r);
		h = rotR(h);
	}
	if (t < r) {
		h->r = partR(h->r, r - t - 1);
		h = rotL(h);
	}
	return h;
}

static link balanceR(link h, link z) {
	int r;
	if (h == z)
		return z;
	r = (h->N + 1) / 2 - 1;
	h = partR(h, r);
	h->l = balanceR(h->l, z);
	h->r = balanceR(h->r, z);
	return h;
}

void BSTbalance(BST bst) {
	bst->root = balanceR(bst->root, bst->z);
}