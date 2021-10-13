/*
Viết chương trình xếp hạng cho đồ thị có hướng không chu trình.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v mô tả cung (u, v).

Đầu ra (Output):

In ra màn hình hạng của các đỉnh theo thứ tự của đỉnh, mỗi đỉnh trên 1 dòng:

Hạng đỉnh 1

Hạng đỉnh 2

...

Hạng đỉnh n

Xem thêm ví dụ bên dưới. Trong ví dụ đầu tiên ta có: hạng của 1 = 0, hạng của 2 = 2 và hạng của 3 = 1.

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
		scanf("%d%d%d", &u, &v);
		add_edge(&G, u, v);
	}

For example:

Input	Result
3 2   0
1 3   2
3 2   1

7 10  0
1 2   1
1 3   3
1 4   1
2 3   2
2 6   2
3 7   4
4 5   
5 3
5 7
6 7

7 12  0
1 2   2
1 3   1
2 4   4
2 5   4
2 6   3
3 2   
3 5
3 6
4 7
5 7
6 4
6 5

*/

//code

// Xếp hạng đồ thị
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
int n,m; //Biến toàn cục lưu số đỉnh và số cung
typedef int Vertices; //Đỉnh n trong đồ thị

//Khai báo cấu trúc đồ thị - GRAPH
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Đỉnh n
}Graph;

//Khai báo cấu trúc danh sách - LIST
typedef struct{
    int data[idx];
    int size;
}List;
/* Các hàm trên danh sách */

//Làm rỗng danh sách
void makenullList(List *l){
    l->size=0;
}

//Thêm một phần tử vào danh sách
void pushList(List *l, int element){
    l->data[l->size] = element;
    l->size++;
}
//Truy cập phần tử trong danh sách bắt đầu tử vị trí thứ 1 
int getList(List *l, int index){
    return l->data[index-1];
}

//Kiểm tra danh sách có rỗng hay không
bool emptyList(List *l){
    return l->size==0;
}

/* Các hàm trên đồ thị */

//Khởi tạo
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}

//Thêm cung e = (x,y) vào đồ thị có hướng
void addEdge(Graph *g, int x, int y){
    g->matrix[x][y]=1;
}

//Kiểm tra 2 đỉnh có kề nhau hay không
bool adjacent(Graph *g, int x, int y){
    return (g->matrix[x][y]==1);
}

//Tính bậc vào của một đỉnh
int degreeInput(Graph *g, int x){
    int count=0;
    for(int i=1;i<=n;i++){
        if(g->matrix[i][x]==1){
            count++;
        }
    }
    return count;
}
//Hàm sao chép phần tử từ danh sách này sang danh sách khác
void copyList(List *l1, List *l2){
    makenullList(l1);
    for(int i=1;i<=l2->size;i++){
        int value = getList(l2,i);
        pushList(l1,value);
    }
}

//Các biến toàn cục để phục vụ giải thuật xếp hạng
int rank[maxv];//Mảng toàn cục lưu hạng của từng đỉnh 
int d[maxv];//Mảng toàn cục lưu bậc vào của từng đỉnh
int k=0; //Bước lặp của giải thuật
List L1,L2;//Danh sách L1 lưu đỉnh có bậc vào bằng 0(gốc cũ), danh sách L2 lưu những đỉnh kề v của u có bậc vào bằng 0(gốc mới)

//Giải thuật xếp hạng đô thị
void ranking(Graph *g){
    int u;
    //Khởi tạo bậc vào của các đỉnh đều bằng 0
    for(u=1;u<=n;u++){
        d[u] = 0;
    }

    //Tính bậc vào của các đỉnh
    for(u=1;u<=n;u++){
        d[u] = degreeInput(g,u);
    }

    makenullList(&L1); //Khởi tạo danh sách L1 chứa các đỉnh gốc(đỉnh gốc là đỉnh có bậc vào bằng 0)
    for(u=1;u<=n;u++){
        if(d[u]==0){
            pushList(&L1,u); //Các đỉnh gốc sẽ được đưa vào L1
        }
    }

    while(!emptyList(&L1)){ //Lặp trong khi L1 chưa rỗng
        makenullList(&L2); //Khởi tạo danh sách L2 để chứa các đỉnh kề v của u có bậc vào bằng 0
        for(int i=1;i<=L1.size;i++){
            int u = getList(&L1,i); //Lấy đỉnh gốc trong danh sách L1 ra
            rank[u] = k; //Xếp hạng cho đỉnh đó bằng bước lặp k
            for(int v=1;v<=n;v++){ //Tìm đỉnh kề của đỉnh vừa được xếp hạng
                if(adjacent(g,u,v)){ //Nếu kề
                    d[v]--; //Giảm bậc của đỉnh kề tương đương với việc xóa đỉnh gốc
                    if(d[v]==0){ //Nếu đỉnh kề có bậc bằng 0 -> Đây là đỉnh gốc mới
                        pushList(&L2,v);//Đưa đỉnh gốc mới vào L2
                    }
                }
            }
        }
        copyList(&L1,&L2); //Di chuyển các đỉnh gốc mới trong L2 sang L1
        k++; //Tăng bước lặp k lên để tiếp tục xếp hạng cho các đỉnh còn lại
        //Lặp đến khi danh sách L1 rỗng tức không còn đỉnh kề nào -> Giải thuật kết thúc
    }
}
int main(){
    Graph g;
    int u,v;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    for(int e=1;e<=m;e++){
        scanf("%d%d",&u,&v);
        addEdge(&g,u,v);
    }
    ranking(&g);
    for(int i=1;i<=n;i++)
        printf("%d\n",rank[i]);
    return 0;
}
/*
NOTE: Khi áp dụng giải thuật xếp hạng vào các bài toán thực tế thì bước
lặp k có thể bắt đầu từ 1 chứ không nhất thiết phải bắt đầu bằng 0
*/
