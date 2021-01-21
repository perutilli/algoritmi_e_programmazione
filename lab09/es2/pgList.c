#include "pgList.h"

typedef struct node* link;

struct node {
	pg_t val;
	link next;
};

struct pgList_s {
	link head;
	int n;
};

link newNode(pg_t val, link next);

pgList_t pgList_init() {
	pgList_t pg_list = malloc(sizeof(*pg_list));
	pg_list->head = NULL;
	pg_list->n = 0;
	return pg_list;
}

void pgList_free(pgList_t pgList) {
	link n, t;
	for (n = pgList->head; n != NULL; n = t) {
		t = n->next;
		pg_clean(&(n->val));
		free(n);
	}
}

void pgList_read(FILE* fp, pgList_t pgList) {
	pg_t pg;
	while (pg_read(fp, &pg) != EOF) {
		pgList_insert(pgList, pg);
	}
}

void pgList_print(FILE* fp, pgList_t pgList, invArray_t invArray) {
	link node;
	for (node = pgList->head; node != NULL; node = node->next) {
		pg_print(fp, &(node->val), invArray);
		fprintf(fp, "\n");
	}
}

void pgList_insert(pgList_t pgList, pg_t pg) {
	pgList->head = newNode(pg, pgList->head);
}

void pgList_remove(pgList_t pgList, char* cod) {
	link n, p, t;
	if (pg_codCompare(&(pgList->head->val), cod) == 0) {
		t = pgList->head->next;
		pg_clean(&(pgList->head->val));
		free(pgList->head->next);
		pgList->head = t;
		return;
	}

	for (p = pgList->head, n = p->next; n != NULL; p = n, n = n->next) {
		if (pg_codCompare(&(n->val), cod) == 0) {
			t = n->next;
			pg_clean(&(n->val));
			free(n);
			p->next = t;
			return;
		}
	}
}

pg_t* pgList_searchByCode(pgList_t pgList, char* cod) {
	link node;
	for (node = pgList->head; node != NULL; node = node->next) {
		if (pg_codCompare(&(node->val), cod) == 0) {
			return (&(node->val));
		}
	}
}

link newNode(pg_t val, link next) {
	link node = malloc(sizeof(*node));
	node->next = next;
	node->val = val;
	return node;
}
