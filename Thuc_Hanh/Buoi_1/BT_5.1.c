/*
Cho cấu trúc dữ liệu đồ thị được cài đặt bằng phương pháp "Danh sách cung" như sau:

typedef struct  {
	 int x, y;
} Edge;
typedef struct {
	int n, m;
	Edge edges[MAX_EDGES];
} Graph;
Các cung được lưu trong danh sách edges với chỉ số từ 0, 1, 2, ..., m-1

Hàm khởi tạo đồ thị:

void init_graph(Graph* G, int n){
	G->n = n;
	G->m = 0;
}


Viết hàm add_edge(Graph* G, int x, int y) để thêm cung (x, y) vào đồ thị G.

void add_edge(Graph* G, int x, int y) {
}
*/

//code

void add_edge(Graph *G, int x, int y){
    G->edges[G->m].x = x;
    G->edges[G->m].y = y;
    G->m++;
}
