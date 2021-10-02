/*
Cho đồ thị có hướng G = <V, E> có n đỉnh và m cung (n < 100, m < 500). Mỗi cung được gán một trọng số w (-100 < w <= 100).

Viết chương trình tìm đường đi ngắn nhất từ đỉnh 1 đến các đỉnh còn lại.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

Dòng đầu tiên chứa 2 số nguyên n và m.
m dòng tiếp theo mỗi dòng chứa 3 số nguyên u, v, w mô tả cung (u, v) có trọng số w.
Dữ liệu được đảm bảo không tồn tại chu trình âm.

Đầu ra (Output):

In ra màn hình các giá trị pi và p của các đỉnh theo thứ tự 1, 2, ..., n.

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
		scanf("%d%d%d", &u, &v, &c);
		add_edge(&G, u, v, w);
	}
	
For example:

Input	Result
3 3     pi[1] = 0, p[1] = -1  
1 2 9   pi[2] = 9, p[2] = 1
2 3 4	pi[3] = 4, p[3] = 1
1 3 4

8 13	pi[1] = 0, p[1] = -1
1 2 4	pi[2] = 4, p[2] = 1
1 3 4	pi[3] = 4, p[3] = 1
3 5 4	pi[4] = 4, p[4] = 5
3 6 2	pi[5] = 3, p[5] = 6
4 1 3	pi[6] = 6, p[6] = 3
4 3 2	pi[7] = 8, p[7] = 5
5 4 1	pi[8] = 10, p[8] = 7
5 7 5
6 2 3
6 5 -3
7 6 2
7 8 2
8 5 -2

6 9	pi[1] = 0, p[1] = -1
1 2 7	pi[2] = 7, p[2] = 1
1 3 9	pi[3] = 9, p[3] = 1
1 5 14	pi[4] = 20, p[4] = 3
2 3 10	pi[5] = 11, p[5] = 3
2 4 15	pi[6] = 20, p[6] = 5
3 4 11
3 5 2
4 6 6
5 6 9

*/
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
void initGraph(Graph *g, int n){
	g->n = n;
	g->m = 0;
}

//Thêm cung 
void addEdge(Graph *g, int u, int v, int w){
	g->edges[g->m].u = u;
	g->edges[g->m].v = v;
	g->edges[g->m].w = w;
	g->m++;
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
	Graph g;
	int n,m,u,v,w;
	scanf("%d%d", &n, &m);
	initGraph(&g, n);
	for (int e=1;e<=m;e++) {
		scanf("%d%d%d",&u,&v,&w);
		addEdge(&g,u,v,w);
	}
	BellmanFord(&g, 1);
	for(int i=1; i<=g.n;i++)
		printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
}
