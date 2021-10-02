/*

Viết chương trình kiểm tra một đồ thị có hướng (không có khuyên, không có đa cung) xem có chứa chu trình âm hay không.

Chu trình âm là chu trình có tổng trọng số các cung trong chu trình nhỏ hơn 0.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v, w mô tả cung (u, v) có trọng số w.

Đầu ra (Output):

In ra màn hình negative cycle nếu đồ thị có chứa chu trình âm, ngược lại in ra ok

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

3 2     ok  
1 3 1
3 1 1

7 10    ok
1 2 1
1 3 1
1 4 1
2 3 1
2 6 1
3 7 1
4 5 1
5 3 1
5 7 1
3 1 1

7 12    ok
1 2 1
1 3 1
2 4 1
2 5 1
2 6 1
3 2 1
3 5 1
3 6 1
4 7 1
5 7 1
6 4 1
2 1 1

3 3      negative cycle
1 2 4
2 3 -10
3 1 2

3 3      ok
1 2 1
2 3 1
3 1 1

*/

//code

#include <stdio.h>
#include <stdbool.h>
#define maxv 50 
#define idx 100
#define  NO_EDGE 0 
#define INFINITY 999999999 
typedef int Vertices;

int n,m;//Biến toàn cục lưu số đỉnh và số cung

//Khai báo cấu trúc đồ thị
typedef struct{
	int matrix[maxv][maxv];
	Vertices n; //Đỉnh n
}Graph;

//Khởi tạo đồ thị(Tất cả cung trong đồ thị đều bằng 0/NO_EDGE)
void initGraph(Graph *g){
	g->n=n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			g->matrix[i][j]=NO_EDGE;
		}
	}
}

//Thêm cung e =(x,y,t) vào đồ thị với t là trọng số
void addEdge(Graph *g, int x, int y, int t){
	g->matrix[x][y]=t;
}

//Hàm kiểm tra
int check(int ts[]){
    int total=0;
    for(int i=1;i<=m;i++){
        total += ts[i];
    }
    return total;
}
int main(){
    Graph g;
    scanf("%d%d",&n,&m);
    int ts[m];//Mảng lưu các trọng số của các cung trong đồ thị
    initGraph(&g);
    int u,v,t;
    for(int i=1;i<=m;i++){
          scanf("%d%d%d",&u,&v,&t);
	  ts[i] = t;
          addEdge(&g,u,v,t);
    }
    Dijkstra(&g,1);
    if(check(ts)<0) printf("negative cycle"); //Đồ thị có chứa chu trình âm
    else printf("ok"); //Đồ thị không chứa chu trình âm
	return 0;
}
