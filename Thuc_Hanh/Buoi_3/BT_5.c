#include <stdio.h>
#define maxv 100
#define INFINITY 9999999

//Khai báo cấu trúc 1 cung đưa vào đồ thị gồm 2 đỉnh và 1 trọng số
typedef struct{
	int u, v;
	int w;
}Edge;

//Khai báo cấu trúc danh sách cung
typedef struct {
	int n,m;
	Edge edges[maxv];
}Graph;

//Khởi tạo 
void init_graph(Graph *G, int n){
	G->n = n;
	G->m = 0;
}

//Thêm cung 
void addEdge(Graph *G, int u, int v, int w){
	G->edges[G->m].u = u;
	G->edges[G->m].v = v;
	G->edges[G->m].w = w;
	G->m++;
}

int pi[maxv];//Mảng pi[] toàn cục lưu đường đi ngắn nhất tạm thờithời
int p[maxv];//Mảng p[] toàn cục lưu cha của 1 đỉnh
void BellmanFord(Graph *g, int s){
	int i, j,k;
	for(i=1; i<= g->n; i++){
		pi[i] = INFINITY;//Khởi tạo đường đi ngắn nhất của tất cả các đỉnh bằng oo
	}	
	
	pi[s] = 0;//Cho đỉnh đầu tiên có giá trị pi[] = 1 để bắt đầu thuật toán
	p[s] = -1;//Cha của đỉnh đầu tiên kh có 

	for(j = 1; j<g->n; j++){
	    //Duyệt qua các cung nếu có đường đi mới tốt hơn thì cập nhật nó
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
int main(){
	Graph G;
	int n,m,u,v,w;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (int e=1;e<=m;e++) {
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}
	BellmanFord(&G, 1);
	for(int i=1; i<=G.n;i++)
		printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
}
