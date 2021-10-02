/*

Áp dụng giải thuật Bellman – Ford kiểm tra xem một đồ thị có hướng có chứa chu trình âm hay không, nếu ta tìm đường đi ngắn nhất từ đỉnh s đến các đỉnh còn lại. In kết quả YES (nếu đồ thị có chu trình âm) hoặc NO (trường hợp ngược lại).

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 3 số nguyên u, v, w nói rằng cung (u, v) có trọng số w.

- Dòng cuối cùng chứa đỉnh s.

Đầu ra (Output):

In ra màn hình YES nếu phát hiện chu trình âm, ngược lại in ra NO.

Xem thêm ví dụ bên dưới.

Chú ý:

Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
For example:

Input	Result
4 4		YES
1 2 1
2 3 -1
3 4 -1
4 1 -1
2

8 13	YES
1 2 4
1 3 4
3 5 4
3 6 -2
4 1 3
4 3 2
5 4 1
5 7 -2
6 2 3
6 5 -3
7 6 2
7 8 2
8 5 -2
1

8 13	NO
1 2 4	
1 3 4
3 5 4
3 6 2
4 1 3
4 3 2
5 4 1
5 7 5
6 2 3
6 5 -3
7 6 2
7 8 2
8 5 -2
1

*/
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
