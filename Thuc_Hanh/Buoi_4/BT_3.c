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
int n,m; //Biến toàn cục n đỉnh và m cung
typedef int Vertices;

//Khai báo cấu trúc đồ thị
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Đỉnh n
}Graph;

//Khai báo cấu trúc danh sách
typedef struct{
    int data[idx];
    int size;
}List;

/*Các hàm trên danh sách*/

//Làm rỗng 
void makenullList(List *l){
    l->size=0;
}

//Kiểm tra danh sách có rỗng hay không
bool emptyList(List *l){
    return (l->size==0);
}

//Thêm một phần tử vào danh sách
void pushList(List *l, int element){
    l->data[l->size] = element;
    l->size++;
}

//Truy cập một phần tử trong danh sách bắt đầu từ vị trí thứ 1
int getList(List *l, int index){
    return l->data[index-1];
}

/*Các hàm thao tác trên đồ thị*/
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            g->matrix[i][j]=0;
}

//Thêm cung e = (x,y) vào đồ thị có hướng
void addEdge(Graph *g, int x, int y){
    //Bé x muốn có kẹo nhiều hơn bé y
    //Nếu đi từ x vào y thì bé y sẽ nhiều hơn bé x vì số bậc vào y > x 
    //Vậy nên chúng ta sẽ thêm cung ngược lại
    g->matrix[y][x]=1;
}

//Kiểm tra hai đỉnh có kề nhau hay không
bool adjacent(Graph *g, int x, int y){
    return g->matrix[x][y]==1;
}

//Tính số bậc vào của 1 đỉnh trong đồ thị - bậc vào là bậc có mũi tên đi vào đỉnh
int degreeInput(Graph *g, int x){
    int count=0;
    for(int i=1;i<=n;i++){
        if(adjacent(g,i,x)){
            count++;
        }
    }
    return count;
}

//Tìm đỉnh láng giềng của một đỉnh
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

//Sao chép phần tử của danh sách này sang danh sách khác
void copyList(List *l1, List *l2){
    makenullList(l1);
    for(int i=1;i<=l2->size;i++){
        int value = getList(l2,i);
        pushList(l1,value);
    }
}

//Các biến toàn cục để phục vụ cho giải thuật xếp hạng đồ thị
int rank[maxv]; //Mảng rank[] để lưu hạng của tất cả các đỉnh trong đồ thị
int d[maxv]; //Mảng d-Degree  để lưu số bậc vào của tất cả các đỉnh trong đồ thị
List L1,L2; //Danh sách L1 lưu những đỉnh có bậc vào bằng 0(gốc cũ), danh sách L2 lưu những đỉnh kề v của u có bậc vào bằng 0(gốc mới)
int k=1;//Bước lặp của giải thuật sở dĩ bắt đầu bằng 1 vì đề bài có nói là các em được đánh số từ 1 đến n 

//Giải thuật xếp hạng đồ thị
void ranking(Graph *g){
    int u;
    for(u=1;u<=n;u++) d[u]=0; //Khởi tạo các đỉnh có bậc vào điều bằng 0
    for(u=1;u<=n;u++) d[u] = degreeInput(g,u); //Tính bậc vào cho các đỉnh rồi lưu vào mảng d[]
    makenullList(&L1); //Khởi tạo danh sách L1 lưu những đỉnh gốc(đỉnh có bậc vào bằng 0)
    for(u=1;u<=n;u++) if(d[u]==0) pushList(&L1,u); //Những đỉnh nào là đỉnh gốc sẽ được cho vào danh sách L1(Gốc cũ)
    while(!emptyList(&L1)){ //Duyệt trong khi L1 chưa rỗng
        makenullList(&L2); //Khởi tạo danh sách L2 để chứa các đỉnh kề v của u có bậc vào bằng 0(Gốc mới)
        for(int i=1;i<=L1.size;i++){ //Duyệt các đỉnh gốc vừa được thêm trong danh sách L1
            int u = getList(&L1,i); //Lấy đỉnh gốc ra
            rank[u] = k; //Xếp hạng cho đỉnh gốc bằng bước lặp k
            List L = neighbors(g,u); //Tìm đỉnh kề của đỉnh vừa được xếp hạng
            for(int j=1;j<=L.size;j++){ //Duyệt các đỉnh kề
                int v = getList(&L,j); //Lấy đỉnh kề
                d[v]--; //Giảm bậc đỉnh kề đi 1 tương đương với việc xóa đỉnh gốc u(gốc mới) ra khỏi đồ thị
                if(d[v]==0){ //Nếu đỉnh kề v là đỉnh gốc(gốc mới)
                    pushList(&L2,v); //Đưa đỉnh gốc mới vào danh sách L2
                }
            }
        }
        copyList(&L1,&L2);//Sao chép các đỉnh gốc mới trong L2 sang L1
        k++;//Tăng bước lặp lên để xếp hạng cho các đỉnh tiếp theo trong danh sách L1
        //Khi nào danh sách L2 rỗng tức đỉnh gốc cũ không có đỉnh kề thì hiển nhiên -> Giải thuật kết thúc -> vì lúc này L1 đã rỗng
    }
}
int main(){
    Graph g;
    int u,v;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdge(&g,u,v);
    }
    ranking(&g);
    int sum=0;
    for(int u=1;u<=n;u++){
        printf("%d\n",rank[u]);
        sum += rank[u];
    }
    printf("%d",sum);
    return 0;
}
/*
NOTE:
  -  Bài toán thực tế này áp dụng giải thuật xếp hạng nhưng có 3 chỗ cần biến đổi
  
    1. Vì các bé được đánh số từ 1 đến n nên bước lặp sẽ lặp từ 1 đến n thay vì từ 0 đến n
    
    2. Đề bài có nói bé a muốn kẹo nhiều hơn bé b tức là hàm addEdge phải đi từ b vào a(g->matrix[b][a]==1) thì lúc này bậc vào của a mới lớn hơn b
    
    3. Cuối cùng là tính tổng các số kẹo mà cô giáo Trang cần phát tức là tính tổng các hạng của các đỉnh có trong đồ thị
*/




