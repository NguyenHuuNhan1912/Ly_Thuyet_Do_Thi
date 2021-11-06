/*
Cho một đồ thị vô hướng đơn. Hãy in ra thứ tự của các đỉnh khi duyệt đồ thị theo chiều rộng bắt đầu từ đỉnh 1.

Nếu đồ thị không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó, và cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.

Quy ước:

Các đỉnh kề của 1 đỉnh được liệt kê theo thứ tự tăng dần


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

//CODE
//Duyệt đồ thị theo chiều rộng - Queue
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100

int n,m;//Biến toàn cục lưu n đỉnh và m cung

// Khai báo cấu trúc đồ thị - GRAPH
typedef int Vertices;
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;// Đỉnh n
}Graph;

//Khai báo cấu trúc danh sách - LIST
typedef struct{
    int data[idx];
    int size;
}List;

// Khai báo cấu trúc hàng đợi - QUEUE
typedef struct{
    int front;
    int rear;
    int data[maxv];
}Queue;

/*Các hàm của hàng đợi*/

// Làm rỗng hàng đợi
void makenullQueue(Queue *q){
    q->front=0;
    q->rear=-1;
}

// Kiểm tra hàng đợi có rỗng hay không
bool emptyQueue(Queue *q){
    return q->front > q->rear;
}

// Thêm 1 phần tử vào hàng đợi
void pushQueue(Queue *q, int element){
    q->rear++;
    q->data[q->rear]=element;
}

// Truy cập phần tử trong hàng đợi
int getQueue(Queue *q){
    return q->data[q->front];
}

// Xóa vị trí phần tử trong hàng đợi đi(Vị trị này thực tế vẫn còn nhưng chúng ta không truy cập đến nữa)
void plusFront(Queue *q){
    q->front++;
}
/*Các hàm trên danh sách*/

// Làm rỗng danh sách
void makenullList(List *l){
    l->size=0;
}

//Kiểm tra danh sách có rỗng hay không
bool emptyList(List *l){
    return l->size==0;
}

// Thêm phần tử vào danh sách
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}

// Truy cập phần tử trong danh sách 
int getList(List *l, int index){
    return l->data[index-1];
}

/*Các hàm trên đồ thị*/

// Khởi tạo đồ thị
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}

// Thêm cung e = (x,y) vào đồ thị
void addEdge(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}

// Kiểm tra 2 đỉnh có kề nhau hay không
bool adjacent(Graph *g, int x, int y){
    return g->matrix[x][y]==1;
}

// Tìm đỉnh kề của 1 đỉnh
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(adjacent(g,x,i)){
            pushList(&L,i);
        }
    }
    return L;
}

int mark[maxv];//Mảng toàn cục mark để đánh dấu 1 đỉnh đã được duyệt hay chưa

// Giải thuật duyệt rộng sử dụng hàng đợi - BFS - QUEUE
List BFS(Graph *g, int x){
    List rs; //Danh sách lưu các đỉnh đã được duyệt
    makenullList(&rs);
    Queue q; 
    makenullQueue(&q);
    pushQueue(&q,x);
    while(!emptyQueue(&q)){ //Lập trong khi hàng đợi chưa rỗng
        int u = getQueue(&q);
        plusFront(&q);
        if(mark[u]==1) continue; //Nếu đỉnh u đã được duyệt thì bỏ qua các câu lệnh phía sau
        pushList(&rs,u); //Nếu u chưa duyệt thay vì in ra thì chúng ta sẽ đưa vào danh sách rs(result) -> danh sách kết quả
        mark[u]=1; //Đánh dấu u đã duyệt 
        List L = neighbors(g,u); //Tìm đỉnh láng giềng của u đưa vào danh sách L
        for(int j=1;j<=L.size;j++){
            int v = getList(&L,j); //Lấy đỉnh láng giềng u trong danh sách L ra -> Lấy đỉnh v
            if(mark[v]==0){ //Nếu v chưa được duyệt
                pushQueue(&q,v); //Đưa vào hàng đợi duyệt V
            }
        }
    }
    return rs;
}
int main(){ 
    Graph g;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    int u,v;
    for(int e=1;e<=m;e++){
        scanf("%d%d",&u,&v);
        addEdge(&g,u,v);
    }
    // Khởi tạo toàn bộ phần tử trong mảng mark bằng 0 vì chưa có đỉnh nào được duyệt
    for(int i=1;i<=n;i++) mark[i]=0;
    
    for(int i=1;i<=n;i++){
        if(mark[i]==0){ //Nếu đỉnh chưa được duyệt
            List L = BFS(&g,i); //Gọi hàm và duyệt 
            for(int j=1;j<=L.size;j++){
                int v = getList(&L,j);
                printf("%d\n",v); //in
                mark[v]=1;//Đánh dấu đã duyệt
            }
        }
    }
    return 0;
}
