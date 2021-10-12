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

#include <stdio.h>
#define maxv 50
#define idx 100
int n,m;//Biến toàn cục lưu số đỉnh và số cung
typedef int Vertices;
//Khai báo cấu trúc đồ thị
typedef struct {
    int matrix[maxv][maxv];
    Vertices n; //Đỉnh n
}Graph;  

//Khai báo cấu trúc danh sách
typedef struct {
    int data[idx];
    int size;
} List;

//Khởi tạo danh sách rỗng
void makenullList(List *l) {
    l->size=0;
}

//Thêm một phần tử vào danh sách
void pushList(List *l, int x) {
    l->data[l->size] = x;
    l->size++;
}

//Lấy phần tử trong danh sách bắt đầu vị trí thứ 1
int getList(List *l, int i) {
    return l->data[i-1];
}

//Khởi tạo đồ thị
void initGraph(Graph *g){
    g->n = n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            g->matrix[i][j]=0;
}

//Thêm cung e = (x,y) vào đồ thị
void addEdge(Graph *g, int x,int y){
    g->matrix[x][y]=1;
}

//Tính bậc vào của 1 đỉnh
int degreeInput(Graph *g, int x){
	int count=0;
	for(int i=1;i<=n;i++){
		if(g->matrix[i][x]==1){
			count++;
		}
	}
	return count;
}

//Hàm copy danh sách
void copyList(List *s1, List *s2){
    int i, x;
    makenullList(s1);
    for(i=1;i<=s2->size;i++){
        x=getList(s2,i);
        pushList(s1,x);
    }
}
//Các biến hỗ trợ thuật toán xếp hạng đồ thị 
int rank[maxv]; //Mảng toàn cục lưu hạng của một đỉnh
int d[maxv]; //Mảng toàn cục lưu bậc của một đỉnh
int k=0; // Bước lập k
List S1, S2; // Danh sách s1 lưu các đỉnh gốc cũ, danh sách s2 lưu các đỉnh gốc mới

//Thuật toán xếp hạng đồ thị
void ranking(Graph *g){

    int u;
    for(u=1;u<=n;u++){
        d[u] = 0; //Khởi tạo bậc của tất cả các đỉnh ban đầu bằng 0
    }
	
	//Tính bậc vào của tất cả các đỉnh trong đồ thị 
	for(u=1;u<=n;u++){
		d[u] = degreeInput(g,u);
	}
    
    makenullList(&S1);//Khởi tạo danh sách chứa các đỉnh gốc ở bước lặp k

    for(u=1;u<=n;u++){
		if(d[u] == 0){ //Chọn đỉnh gốc có bậc vào bằng 0 vừa tính ở trên
			pushList(&S1, u); //Đưa đỉnh đó vào danh sách s1
		}
	}   

    int i;
    while(S1.size > 0){ //Lặp trong khi S1 chưa rỗng
        makenullList(&S2); //Khởi tạo danh sách S2 để lưu các đỉnh v kề u mà có bậc gốc = 0
        for(i=1;i<=S1.size;i++){
            int u = getList(&S1,i); //Lấy đỉnh u trong S1 ra
            rank[u] = k; //Tính hạng của đỉnh u = bước lặp k
            for (int v=1;v<=n;v++){//Tìm các đỉnh v kề u
				if(g->matrix[u][v] == 1){ //Nếu v là đỉnh kề của u
                    d[v]--; //Giảm bậc của v đi việc này tương đương như xóa gốc u ra khỏi đồ thị
                	if(d[v] == 0) //Sau khi giảm bậc nếu v là bậc gốc thì đưa v vào S2
                    	pushList(&S2, v);//Đưa v vào s2
                }
			} 
        }
        copyList(&S1, &S2); //Lấy các đỉnh trong s2 đưa vào s1 để tiếp tục xét
        k++;//Tăng bước lặp k để tiếp tục thuật toán
    }
}
int main (){
    Graph g;
    int u, v, e;
    scanf("%d%d", &n, &m);
    initGraph(&g);
    for (e = 0; e < m; e++) {
        scanf("%d%d", &u, &v);
        addEdge(&g, u, v);
    }
    ranking(&g);
    for(u=1;u<=n;u++)
        printf("%d \n",rank[u]);
    return 0;
}
