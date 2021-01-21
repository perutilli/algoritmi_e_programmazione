#pragma warning (disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"

#define maxWT INT_MAX
#define MAXC 10

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; } ;

static Edge  EDGEcreate(int v, int w, int wt);
static link  NEW(int v, int wt, link next);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);
// no_dag = 1 se grafo non è un DAG, = 0 se potrebbe esserlo 
static void dfsR(Graph G, Edge e, int* time, int* pre, int* post, int* no_dag);
static void removeEdgesDAG_R(Graph G, Edge* edges, int pos, int n_rimozioni, Edge* sol, int* mark, int peso_curr, Edge* best_sol, int* peso_max);

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

Graph GRAPHinit(int V) {
    int v;
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;

    G->V = V;
    G->E = 0;
    G->z = NEW(-1, 0, NULL);
    if (G->z == NULL)
        return NULL;
    G->ladj = malloc(G->V*sizeof(link));
    if (G->ladj == NULL)
        return NULL;
    for (v = 0; v < G->V; v++)
    G->ladj[v] = G->z;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    return G;
}

void GRAPHfree(Graph G) {
    int v;
    link t, next;
    for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = next) {
        next = t->next;
        free(t);
    }
    STfree(G->tab);
    free(G->ladj);
    free(G->z);
    free(G);
}

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;

    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    if (G == NULL)
        return NULL;

    for (i=0; i<V; i++) {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i);
    }

    while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}

void  GRAPHedges(Graph G, Edge *a) {
    int v, E = 0;
    link t;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = t->next)
            a[E++] = EDGEcreate(v, t->v, t->wt);
}

void GRAPHstore(Graph G, FILE *fout) {
    int i;
    Edge *a;

    a = malloc(G->E * sizeof(Edge));
    if (a == NULL)
        return;
    GRAPHedges(G, a);

    fprintf(fout, "%d\n", G->V);
    for (i = 0; i < G->V; i++)
        fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));

    for (i = 0; i < G->E; i++)
        fprintf(fout, "%s  %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);

}

int GRAPHgetIndex(Graph G, char *label) {
    int id;
    id = STsearch(G->tab, label);
    if (id == -1) {
        id = STsize(G->tab);
    STinsert(G->tab, label, id);
    }
    return id;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
    removeE(G, EDGEcreate(id1, id2, 0));
}

static void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;

    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->E++;
}

static void  removeE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    link x;
    if (G->ladj[v]->v == w) {
    G->ladj[v] = G->ladj[v]->next;
    G->E--;
    }
    else
        for (x = G->ladj[v]; x != G->z; x = x->next)
            if (x->next->v == w) {
                x->next = x->next->next;
                G->E--;
    }
}

static void dfsR(Graph G, Edge e, int* time, int* pre, int* post, int* no_dag) {
    link t; int v, w = e.w;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (pre[t->v] == -1) {
            dfsR(G, EDGEcreate(w, t->v, 0), time, pre, post, no_dag);
            if (*no_dag == 1) return;
        }
        else {
            v = t->v;
            if (post[v] == -1) {
                *no_dag = 1;
                return;
            }
        }
    post[w] = (*time)++;
}

int GRAPHcheckDAG(Graph G) {
    int v, time = 0, * pre, * post, no_dag;
    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    no_dag = 0;

    for (v = 0; v < G->V; v++) {
        pre[v] = -1;
        post[v] = -1;
    }

    for (v = 0; v < G->V; v++) {
        if (pre[v] == -1) {
            dfsR(G, EDGEcreate(v, v, 0), &time, pre, post, &no_dag);
            if (no_dag) break;
        }
    }


    return (!no_dag);

}

void removeToCreateDAG(Graph G) {
    int peso_max = 0, n = 0;
    int n_edges = G->E;
    Edge* edges = malloc(n_edges * sizeof(*edges));
    Edge* sol = malloc(n_edges * sizeof(*sol));
    Edge* best_sol = malloc(n_edges * sizeof(*best_sol));
    int* mark = calloc(n_edges, sizeof(*mark));
    if (GRAPHcheckDAG(G)) {
        return NULL;
    }
    GRAPHedges(G, edges);
    for (int i = 1; i < n_edges; i++) {
        removeEdgesDAG_R(G, edges, 0, i, sol, mark, 0, best_sol, &peso_max);
        if (peso_max != 0) {
            n = i;
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        GRAPHremoveE(G, best_sol[i].v, best_sol[i].w);
    }
}

static void removeEdgesDAG_R(Graph G, Edge* edges, int pos, int n_rimozioni, Edge* sol, int* mark, int peso_curr, Edge* best_sol, int* peso_max) {

    if (pos >= n_rimozioni) {
        if (GRAPHcheckDAG(G)) {
            if (peso_curr > * peso_max) {
                *peso_max = peso_curr;
                for (int i = 0; i < n_rimozioni; i++) {
                    best_sol[i] = sol[i];
                }
            }
            for (int i = 0; i < n_rimozioni; i++) {
                printf("(%d %d) %d, ", sol[i].v, sol[i].w, sol[i].wt);
            }
            printf("\n");
        }
    }


    for (int i = 0; i < G->E; i++) {
        if (mark[i] == 0) {
            sol[pos] = edges[i];
            GRAPHremoveE(G, edges[i].v, edges[i].w);
            mark[i] = 1;
            peso_curr += edges[i].wt;
            removeEdgesDAG_R(G, edges, pos + 1, n_rimozioni, sol, mark, peso_curr, best_sol, peso_max);
            mark[i] = 0;
            peso_curr -= edges[i].wt;
            GRAPHinsertE(G, edges[i].v, edges[i].w, edges[i].wt);
        }
    }
}

void TSdfsR(Graph D, int v, int* ts, int* pre, int* time) {
    link t;
    pre[v] = 0;
    for (t = D->ladj[v]; t != D->z; t = t->next)
        if (pre[t->v] == -1)
            TSdfsR(D, t->v, ts, pre, time);
    ts[(*time)++] = v;
}

void DAGrts(Graph D) {
    int v, time = 0, * pre, * ts;
    pre = malloc(D->V * sizeof(int));
    ts = malloc(D->V * sizeof(int));
    if ((pre == NULL) || (ts == NULL))
        return;

    for (v = 0; v < D->V; v++) {
        pre[v] = -1;
        ts[v] = -1;
    }
    for (v = 0; v < D->V; v++)
        if (pre[v] == -1)
            TSdfsR(D, v, ts, pre, &time);

    printf("DAG nodes in reverse topological order \n");
    for (v = 0; v < D->V; v++)
        printf("%s ", STsearchByIndex(D->tab, ts[v]));
    printf("\n");

}

void GRAPHspD(Graph G, int* vett, int id) {
    int v;
    link t;
    int* st, * mindist;
    st = malloc(G->V * sizeof(int));
    mindist = malloc(G->V * sizeof(int));
    if ((st == NULL) || (mindist == NULL))
        return;

    for (v = 0; v < G->V; v++) {
        st[v] = -1;
        mindist[v] = 0;
    }

    st[vett[id]] = vett[id];

    for (int i = id; i < G->V; i++) {
        for (t = G->ladj[v]; t != G->z; t = t->next) {
            if (mindist[v] + t->wt > mindist[t->v]) {
                mindist[t->v] = mindist[v] + t->wt;
                st[t->v] = v;
            }
        }
    }

    printf("\n Maximum distances from node %s\n", STsearchByIndex(G->tab, id));
    for (v = id; v < G->V; v++)
        printf("mindist[%s] = %d \n", STsearchByIndex(G->tab, v), mindist[v]);

}
