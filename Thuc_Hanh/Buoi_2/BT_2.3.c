/*
Cho một đồ thị vô hướng đơn. Hãy dựng (các) cây DUYỆT ĐỒ THỊ khi duyệt đồ thị theo chiều sâu (dùng NGĂN XẾP) bắt đầu từ đỉnh 1.

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
Sử dụng 1 stack lưu các cặp <u, parent>. Khi xét đỉnh v (là kề của u) để đưa vào stack, ta đưa cả <v, u> vào stack. Lúc này u được xem như là parent của v.
typedef struct {
    int u;
    int parent;
} ELEMENT_TYPE;
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

//CODE

// Duyệt đồ thị theo chiều sâu - Stack
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100

int n,m;//Biến toàn cục lưu n đỉnh và m cung

// Khai báo cấu trúc đồ thị
typedef int Vertices;
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Đỉnh n
}Graph;

// Khai báo cấu trúc danh sách - LIST
typedef struct{
    int data[idx];
    int size;
}List;

// Khai báo cấu trúc ngắn xếp - STACK
typedef struct{
    int data[idx];
    int size;
}Stack;

/*Các hàm của ngăn xếp*/

// Làm rỗng ngăn xếp
void makenullStack(Stack *s){
    s->size=0;
}

// Kiểm tra ngăn xếp có rỗng hay không
bool emptyStack(Stack *s){
    return s->size==0;
}

// Thêm 1 phần tử vào ngăn xếp
void pushStack(Stack *s, int element){
    s->data[s->size]=element;
    s->size++;
}

//Truy cập phần tử trong ngăn xếp
int getStack(Stack *s){
    return s->data[s->size-1];
}

// Xóa vị trí phần tử trong ngăn xếp đi(Vị trị này thực tế vẫn còn nhưng chúng ta không truy cập đến nữa)
void delSize(Stack *s){
    s->size--;
}

/*Các hàm trên danh sách*/

// Làm rỗng danh sách
void makenullList(List *l){
    l->size=0;
}

// Kiểm tra danh sách có rỗng hay không
bool emptyList(List *l){
    return l->size==0;
}

// Thêm 1 phần tử vào danh sách
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}

// Truy cập đến phần tử có vị trí index trong danh sách
int getList(List *l, int index){
    return l->data[index-1];
}

/*Các hàm trên đồ thị*/

// Khởi tạo đồ thị
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            g->matrix[i][j]=0;
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

// Tìm tất cả đỉnh láng giềng(đỉnh kề) của đỉnh x
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
int parent[maxv]; //Mảng toàn cục parent để lưu đỉnh cha của toàn bộ đỉnh trong đồ thị

// Giải thuật duyệt sâu sử dụng ngăn xếp - DFS - STACK
List DFS_Stack(Graph *g, int x){
    List rs;//Danh sách lưu các đỉnh đã được duyệt
    makenullList(&rs);
    Stack s;
    makenullStack(&s);
    pushStack(&s,x);
    parent[x]=0; //Nếu đỉnh đang xét là đỉnh gốc thì đỉnh cha của đỉnh gốc là 0
    while(!emptyStack(&s)){ //Lập trong khi ngăn xếp chưa rỗng
        int u = getStack(&s);
        delSize(&s);
        if(mark[u]==1) continue; //Nếu đỉnh u đã được duyệt thì bỏ qua các câu lệnh phía sau
        pushList(&rs,u); //Nếu u chưa duyệt thay vì in ra thì chúng ta sẽ đưa vào danh sách rs(result) -> danh sách kết quả
        mark[u]=1; //Đánh dấu u đã duyệt
        List L = neighbors(g,u); //Tìm đỉnh láng giềng của u đưa vào danh sách L
        for(int j=1;j<=L.size;j++){
            int v = getList(&L,j); //Lấy đỉnh láng giềng u trong danh sách L ra -> Lấy đỉnh v
            if(mark[v]==0){ //Nếu v chưa được duyệt
                pushStack(&s,v); //Đưa vào ngăp xếp duyệt v
                parent[v]=u; //Vì đây là Stack nên sẽ khác Queue ở chỗ này -> không cần if(parent[v]==-1)
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
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdge(&g,u,v);
    }
    // Khởi tạo toàn bộ phần tử trong mảng mark bằng 0 vì chưa có đỉnh nào được duyệt
    for(int i=1;i<=n;i++){
        mark[i]=0;
        parent[i]=-1;
    }
    
    for(int i=1;i<=n;i++){
        if(mark[i]==0){ //Nếu đỉnh chưa được duyệt
            List L = DFS_Stack(&g,i); //Gọi hàm và duyệt 
            for(int j=1;j<=L.size;j++){
                int v = getList(&L,j);
                // printf("%d\n",v); 
                //Đề yêu cầu chỉ in đỉnh cha của các đỉnh ra thôi nên không cần in thứ tự duyệt của đồ thị
                mark[v]=1; //Đánh dấu đã duyệt
            }
        }
    }

    //In các đỉnh cha của các đỉnh trong đồ thị
    for(int i=1;i<=n;i++)
        printf("%d %d\n",i,parent[i]); //Đỉnh i có đỉnh cha là parent[i]
    return 0;
}
