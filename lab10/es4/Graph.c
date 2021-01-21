#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

typedef struct node* link;
struct node {
    int v;
    int wt;
    link next;
};

struct graph {
	int V, E;
	int** madj;
    link* ladj;
	ST tab;
};

static int** MATRIXint(int r, int c, int val);
static Edge  EDGEcreate(int v, int w, int wt);
static void  insertE(Graph G, Edge e);
static void  insertEListAdj(Graph G, Edge e);
static link  NEW(int v, int wt, link next);
static int   LadjAdiacenti(Graph G, int v, int w);

Graph GRAPHinit(int V) {
	Graph gr = malloc(sizeof(*gr));
	gr->V = V;
    gr->E = 0;
    gr->madj = MATRIXint(V, V, 0);
    gr->ladj = malloc(gr->V * sizeof(link));
    for (int v = 0; v < gr->V; v++)
        gr->ladj[v] = NULL;
    gr->tab = STinit(V);
    return gr;
}

static int** MATRIXint(int r, int c, int val) {
    int** mat = malloc(r * sizeof(int*));

    for (int i = 0; i < r; i++) {
        mat[i] = malloc(c * sizeof(int));
        for (int j = 0; j < c; j++) {
            mat[i][j] = val;
        }
    }

    return mat;
}

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof * x);
    if (x == NULL)
        return NULL;
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

void GRAPHfree(Graph G) {
    for (int i = 0; i < G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G);
}

Graph GRAPHload(FILE* fin) {
    char label1[MAXC], label2[MAXC];
    int Vmax = 0, wt, V = 0;
    Graph G;
    while (fscanf(fin, "%*s %*s %*s %*s %*d") != EOF) {
        Vmax += 2;
    }
    G = GRAPHinit(Vmax);
    rewind(fin);
    while (fscanf(fin, "%s %*s %s %*s %d", label1, label2, &wt) != EOF) {
        if (STsearch(G->tab, label1) == -1) {
            STinsert(G->tab, label1, STsize(G->tab));
            V++;
        }

        if (STsearch(G->tab, label2) == -1) {
            STinsert(G->tab, label2, STsize(G->tab));
            V++;
        }

        GRAPHinsertE(G, STsearch(G->tab, label1), STsearch(G->tab, label2), wt);
    }

    G->V = V;
    return G;
}

static void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    if (G->madj[v][w] != 0 || v == w) {
        return; // arco già presente o cappio
    }
    G->E++;
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

void GRAPHstore(Graph G, FILE* fout) {
    int* ordineAlf, t, idx_min, wt;

    ordineAlf = malloc(G->V * sizeof(*ordineAlf));
    for (int i = 0; i < G->V; i++) {
        ordineAlf[i] = i;
    }

    for (int i = 0; i < G->V; i++) {
        idx_min = i;
        for (int j = i; j < G->V; j++) {
            if (strcmp(STsearchByIndex(G->tab, ordineAlf[j]), STsearchByIndex(G->tab, ordineAlf[idx_min])) == -1) {
                idx_min = j;
            }
        }
        t = ordineAlf[i];
        ordineAlf[i] = ordineAlf[idx_min];
        ordineAlf[idx_min] = t;
    }

    for (int i = 0; i < G->V; i++) {
        fprintf(fout, "%s:\t", STsearchByIndex(G->tab, ordineAlf[i]));
        for (int j = 0; j < G->V; j++) {
            if ((wt = G->madj[i][ordineAlf[j]]) != 0) {
                fprintf(fout, "%s %d ", STsearchByIndex(G->tab, ordineAlf[j]), wt);
            }
        }
        fprintf(fout, "\n");
    }

    free(ordineAlf);
}

static void  insertEListAdj(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;

    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->ladj[w] = NEW(v, wt, G->ladj[w]);
}

void GRAPHcreateListAdj(Graph G) {

    for (int i = 0; i < G->V; i++) {
        for (int j = i + 1; j < G->V; j++) {
            if (G->madj[i][j] != 0) {
                insertEListAdj(G, EDGEcreate(i, j, G->madj[i][j]));
            }
        }
    }
}

int GRAPHsottoGrafoCompletoMadj(Graph G, char* name1, char* name2, char* name3) {
    int id1, id2, id3;
    int** madj = G->madj;
    id1 = STsearch(G->tab, name1);
    id2 = STsearch(G->tab, name2);
    id3 = STsearch(G->tab, name3);

    return ((madj[id1][id2] != 0) && (madj[id2][id3] != 0) && (madj[id1][id3] != 0));
}

int GRAPHsottoGrafoCompletoLadj(Graph G, char* name1, char* name2, char* name3) {
    int id1, id2, id3;
    int ladj = 0;
    for (int i = 0; i < G->V; i++) {
        if (G->ladj[i] != NULL) {
            ladj = 1;
            break;
        }
    }

    if (!ladj) GRAPHcreateListAdj(G);
    
    id1 = STsearch(G->tab, name1);
    id2 = STsearch(G->tab, name2);
    id3 = STsearch(G->tab, name3);

    return (LadjAdiacenti(G, id1, id2) && LadjAdiacenti(G, id1, id3) && LadjAdiacenti(G, id2, id3));
}

static int LadjAdiacenti(Graph G, int v, int w) {
    link n;
    for (n = G->ladj[v]; n != NULL; n = n->next) {
        if (n->v == w) {
            return 1;
        }
    }
    return 0;
}