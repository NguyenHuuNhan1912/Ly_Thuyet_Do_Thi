#include <stdio.h>
#include <stdbool.h>
#define maxv 100
#define INFINITY 9999999
typedef struct{
	int u, v;
	int w;
}Edge;
typedef struct {
	int n,m;
	Edge edges[maxv];
}Graph;
void init_graph(Graph *G, int n){
	G->n = n;
	G->m = 0;
}
void add_edge(Graph *G, int u, int v, int w){
	G->edges[G->m].u = u;
	G->edges[G->m].v = v;
	G->edges[G->m].w = w;
	G->m++;
}
int pi[maxv];
int p[maxv];
void BellmanFord(Graph *g, int s){
	int i, j,k;
	for(i=1; i<= g->n; i++){
		pi[i] = INFINITY;
	}	
	pi[s] = 0;
	p[s] = -1;

	for(j = 1; j<g->n; j++){
		for(k=0;k<g->m;k++){
			int u = g->edges[k].u;
			int v = g->edges[k].v;
			int w = g->edges[k].w;
			if(pi[u] + w < pi[v]){
				pi[v] = pi[u] + w;
				p[v] = u;
			}
		}
	}
}

//Duyệt cung thêm 1 lần nữa nếu pi[v] được cải tiến tức là đồ thị có chu trình âm
bool check(Graph *g){
    int k;
    for(k=0;k<g->m;k++){
		int u = g->edges[k].u;
		int v = g->edges[k].v;
		int w = g->edges[k].w;
		if(pi[u] + w < pi[v]){
			return true;
		}
	}
    return false;
}
int main(){
	Graph g;
	int n,m,u,v,w;
	scanf("%d%d", &n, &m);
	init_graph(&g, n);
	for (int e=1;e<=m;e++) {
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&g,u,v,w);
	}
	BellmanFord(&g, 1);
    if(check(&g)==1) printf("YES");
    else printf("NO");
    
    // if(pi[n]>0) printf("NO");
    // else printf("YES");
}