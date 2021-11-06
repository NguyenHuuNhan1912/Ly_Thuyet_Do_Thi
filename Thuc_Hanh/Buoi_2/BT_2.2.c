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

//Duyệt và dựng cây đồ thị theo chiều sâu - Đệ qui - Recursion
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100

int n,m; //Biến toàn cục lưu n đỉnh và m cung

//Khai báo cấu trúc đồ thị
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

/*Các hàm trên danh sách*/

//Làm rỗng danh sách
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

// Truy cập phần tử trong danh sách bắt đâu từ vị trí thứ 1 (Mảng bắt đầu bằng 0 nên index phải trừ đi 1)
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

// Tìm đỉnh láng giềng(đỉnh kề) của một đỉnh
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
int parent[maxv];//Mảng parent lưu đỉnh cha của tất cả các đỉnh trong đồ thị
// Giải thuật duyệt đồ thị theo chiều sâu - Sử dụng đệ qui
void DFS_Recursion(Graph *g, int x, int p){
    if(mark[x]==1) return; //Nếu đỉnh đã được duyệt kết thúc và không trả về gì
    mark[x]=1; //Nếu chưa duyệt thì đánh dấu đã duyệt
    //printf("%d\n",x); Đề bài yêu cầu chỉ cần in ra cha nên không cần phải in thứ tự duyệt
    parent[x]=p; //Đỉnh đầu tiên được xét là đỉnh 1 nên cha của đỉnh 1 theo quy ước lúc này = p = 0, các lần lặp sau p có thể sẽ thay đổi
    List L = neighbors(g,x); //Tìm đỉnh láng giềng của đỉnh đang xét
    for(int j=1;j<=L.size;j++){
        int v = getList(&L,j); //Lấy đỉnh v kề với đỉnh đang xét ra 
        DFS_Recursion(g,v,x); //Tiếp tục gọi đệ qui đỉnh cha của đỉnh đang đang xét là đỉnh trước đó(Lúc này p đã không còn là 0 mà đã là x)
    }
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
    
    for(int i=1;i<=n;i++){
        mark[i]=0; //Khởi tạo tất cả các đỉnh điều chưa được duyệt
        parent[i]=-1; //Khởi tạo tất cả các đỉnh có đỉnh cha bằng null(-1)
    }
        
    for(int i=1;i<=n;i++)
         DFS_Recursion(&g,i,0); //Gọi hàm để duyệt và đỉnh cha của đỉnh đầu tiền là 0
    
    for(int i=1;i<=n;i++)
        printf("%d %d\n",i,parent[i]); //In ra các đỉnh và đỉnh cha của các đỉnh đó
    return 0;
}
