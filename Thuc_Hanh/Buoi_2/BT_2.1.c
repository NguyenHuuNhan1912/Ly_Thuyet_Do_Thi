/*
Cho một đồ thị vô hướng đơn. Hãy dựng (các) cây DUYỆT ĐỒ THỊ khi duyệt đồ thị theo chiều rộng bắt đầu từ đỉnh 1.

Nếu đồ thị không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó, và cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.

Quy ước:

Các đỉnh kề của 1 đỉnh được liệt kê theo thứ tự tăng dần

Đầu vào (Input):
Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng mô tả cung (u, v).

Đầu ra (Output):

In ra cây duyệt đồ thị theo định dạng:

1 <đỉnh cha của 1>
2 <đỉnh cha của 2>
....
i <đỉnh cha của i>
...
n <đỉnh cha của n>

Quy ước: Nếu 1 đỉnh không có đỉnh cha (nó là đỉnh gốc của cây) thì đỉnh cha của nó là 0.

Xem thêm các ví dụ bên dưới.



Gợi ý:

Sử dụng mảng parent[u] để lưu đỉnh cha của đỉnh u.
Trong quá trình duyệt, thay vì in các đỉnh ra màn hình, ghi nhận lại đỉnh cha của các đỉnh.
Khi duyệt xong lần lượt in ra u và parent[u] (u chạy từ 1 đến n).


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
typedef struct{
    int data[maxv];
    int front;
    int rear;
}Queue;
//Khoi tao
void makenullQueue(Queue *q){
    q->front=0;
    q->rear=-1;
}
//Kiem tra hang doi rong
bool emptyQueue(Queue *q){
    return (q->front > q->rear);
}
//them phan tu vao hang doi
void pushQueue(Queue *q, int x){
    q->rear++;
    q->data[q->rear]=x;
}
//Lay phan tu ra
int getQueue(Queue *q){
    return q->data[q->front];
}
void plusFront(Queue *q){
    q->front++;
}
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
//Duyet do thi theo chieu rong su dung queue
List BFS(Graph *g, int x, int ft[]){
    List rs;
    makenullList(&rs);
    Queue q;
    int mark[maxv];
    for(int i=1;i<=g->n;i++) mark[i]=0;
    makenullQueue(&q);
    pushQueue(&q,x);
    ft[x]=0;
    while(!emptyQueue(&q)){
        int u = getQueue(&q);
        plusFront(&q);
        if(mark[u]==1) continue;
        pushList(&rs,u);
        mark[u]=1;
        List L = neighbors(*g,u);
        for(int j=0;j<L.size;j++){
            int v = getList(L,j);
            if(mark[v]==0){
                pushQueue(&q,v);
                if(ft[v]==-1){
                    ft[v]=u;
                }
            }
        }
    }
    return rs;
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
     int md[maxv],ft[maxv];
    for(int i=1;i<=g.n;i++){
        md[i]=0;
        ft[i]=-1;
    }
    for(int i=1;i<=g.n;i++){
        if(md[i]==0){
            List L = BFS(&g,i,ft);
            for(int j=0;j<L.size;j++){
                int v = getList(L,j);
                md[v]=1;
            }   
        }
    }
    for(int i=1;i<=g.n;i++){
        printf("%d %d\n",i,ft[i]);
    }
    return 0;
}
