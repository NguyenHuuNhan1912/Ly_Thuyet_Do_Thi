/*
Cô giáo Trang chuẩn bị kẹo để phát cho các bé mà cô đang giữ. Dĩ nhiên môi bé đều có một tên gọi rất dễ thương ví dụ: Mạnh Phát, Diễm Quỳnh, Đăng Khoa, ... Tuy nhiên, để đơn giản vấn đề ta có thể giả sử các em được đánh số từ 1 đến n.
Cô giáo muốn rằng tất cả các em đều phải có kẹo. Cô lại biết thêm rằng có một số bé có ý muốn hơn bạn mình một chút vì thế các em ấy muốn kẹo của mình nhiều hơn của bạn.
Hãy viết chương trình giúp cô tính xem mỗi em cần được chia ít nhất bao nhiêu kẹo và tổng số kẹo ít nhất mà cô phải chuẩn bị là bao nhiêu.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số bé và số cặp bé mà trong đó có 1 bé muốn có kẹo hơn bạn mình..

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên a, b nói rằng bé a muốn có kẹo nhiều hơn bé b.

Đầu ra (Output):

In ra màn hình số kẹo ít nhất của từng em, mỗi em trên một dòng.

Dòng cuối cùng in tổng số kẹo ít nhất mà cô giáo Trang cần phải chuẩn bị

Chú ý:

Xem thêm các ví dụ để hiểu thêm về đầu vào và đầu ra.

For example:

Input	  Result
3 2     3
1 3     1
3 2     2
        6
        
7 10    1
2 1     2
3 1     4
4 1     2
3 2     3
6 2     3
7 3     3
5 4     5
3 5     20
7 5 
7 6

*/

//Chia kẹo
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
    //Bé x muốn có kẹo nhiều hơn bé y
    //Nếu đi từ x vào y thì bé y sẽ nhiều hơn bé x vì số bậc vào y > x 
    //Vậy nên chúng ta sẽ thêm cung ngược lại
    g->matrix[y][x]=1;
    
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
int k=1; //Bước lặp của giải thuật sở dĩ bắt đầu bằng 1 vì đề bài có nói là các em được đánh số từ 1 đến n 
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
    int count=0;
    for(int i=1;i<=n;i++){
        printf("%d\n",rank[i]);
        count += rank[i];
    }
    printf("%d",count);
        
    return 0;
}
/*
NOTE:
  -  Bài toán thực tế này áp dụng giải thuật xếp hạng nhưng có 3 chỗ cần biến đổi
  
    1. Vì các bé được đánh số từ 1 đến n nên bước lặp sẽ lặp từ 1 đến n thay vì từ 0 đến n
    
    2. Đề bài có nói bé a muốn kẹo nhiều hơn bé b tức là hàm addEdge phải đi từ b vào a(g->matrix[b][a]==1) thì lúc này bậc vào của a mới lớn hơn b
    
    3. Cuối cùng là tính tổng các số kẹo mà cô giáo Trang cần phát tức là tính tổng các hạng của các đỉnh có trong đồ thị
*/




