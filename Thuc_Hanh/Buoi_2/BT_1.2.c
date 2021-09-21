/*
Cho một đồ thị vô hướng đơn. Hãy in ra thứ tự của các đỉnh khi duyệt đồ thị theo chiều sâu (sử dụng ĐỆ QUY) bắt đầu từ đỉnh 1.

Nếu đồ thị không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó, và cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.

Quy ước:

Các đỉnh kề của 1 đỉnh được liệt kê theo thứ tự tăng dần.


Đầu vào (Input):
Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng mô tả cung (u, v).

Đầu ra (Output):

In ra các đỉnh theo thứ tự duyệt, mỗi đỉnh trên 1 dòng.

Xem thêm các ví dụ bên dưới.



Hướng dẫn đọc dữ liệu và chạy thử chương trình
Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
*/

//code
//Duyet do thi theo chieu rong(Su dung hang doi)
#include <stdio.h>
#include <stdbool.h>
typedef int Vertices;
#define maxv 50
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;
}Graph;
typedef struct{
    int data[maxv];
    int size;
}List;
void makenullList(List *l){
    l->size=0;
}
//Them 1 phan tu vao danh sach
void pushList(List *l, int x){
    l->data[l->size]=x;
    l->size++;
}
//Lay phan tu trong danh sach
int getList(List l, int x){
    return l.data[x];
}
//Khoi tao do thi
void initGraph(Graph *g, int n){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}
//Them cung 
void addGraph(Graph *g, int u, int v){
    g->matrix[u][v]=1;
    g->matrix[v][u]=1;
}
//Tim dinh lang gieng
List neighbors(Graph g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=g.n;i++){
        if(g.matrix[x][i]==1){
            pushList(&L,i);
        }
    }
    return L;
}
//Duyet do thi theo chieu rong su dung DEQUI
int mark[maxv];
int father[maxv];
//Thuat toan duyet do thi theo chieu sau bang de qui(Recursion)
void DFS_Recursion(Graph *g, int x, int p){
    if(mark[x]==1) return;
    printf("%d\n",x);
    mark[x]=1;
    List L = neighbors(*g,x);
    for(int j=0;j<L.size;j++){
        int v = getList(L,j);
        DFS_Recursion(g,v,x);
    }
}
//in
void print_result_Recursion(Graph g){
    for(int i=1;i<=g.n;i++){
        mark[i]=0;
    }
    for(int i=1;i<=g.n;i++) DFS_Recursion(&g,i,0);
}
int main(){
    Graph g;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	initGraph(&g, n);
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		addGraph(&g, u, v);
	}
	 print_result_Recursion(g);
    return 0;
}