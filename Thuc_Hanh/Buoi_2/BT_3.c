/*

Có n hòn đảo và m cây cầu. Mỗi cây cầu bắt qua 2 hòn đảo. Một hôm chúa đảo tự hỏi là với các cây cầu hiện tại thì đứng ở một hòn đảo bất kỳ có thể nào đi đến được tất cả các hòn đảo khác hay không.

Hãy giúp chúa đảo viết chương trình kiểm tra.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đảo và số cây cầu.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng có 1 cây cầu bắt qua hai hòn đảo u và v.

Đầu ra (Output):

Nếu có thể đi được in ra màn hình YES, ngược lại in ra NO.

Xem thêm ví dụ bên dưới.
For example:

Input	Result

4 3      YES
1 2
2 3
3 4

4 2     NO
3 4
1 2

*/

//CODE
//Bài toán thực tế - Đồ thị liên thông - Qua đảo
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
int count=0;//Biến count toàn cục để kiểm tra -> Khi một đỉnh được duyệt count sẽ tăng lên 1 -> Nếu kết thúc giải thuật mà count = đỉnh n -> Liên thông

// Giải thuật duyệt đồ thị theo chiều sâu - Sử dụng đệ qui
void DFS_Recursion(Graph *g, int x){
    if(mark[x]==1) return; //Nếu đỉnh đã được duyệt kết thúc và không trả về gì
    mark[x]=1; //Nếu chưa duyệt thì đánh dấu đã duyệt
    count++; //Khi có một đỉnh được duyệt -> Tăng count
    List L = neighbors(g,x); //Tìm đỉnh láng giềng của đỉnh đang xét
    for(int j=1;j<=L.size;j++){
        int v = getList(&L,j); //Lấy đỉnh v kề với đỉnh đang xét ra 
        DFS_Recursion(g,v); //Tiếp tục gọi đệ qui
    }
}
bool check(){
    return n==count; //Nếu count = số đỉnh ban đầu của đồ thị -> Đồ thị liên thông -> Giải quyết được vấn đề của chúa đảo
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
    
    for(int i=1;i<=n;i++)
        mark[i]=0; //Khởi tạo tất cả các đỉnh điều chưa được duyệt
    

    DFS_Recursion(&g,1); 
    //Muốn kiểm tra đồ thị có liên thông hay không thì dựa vào tính chất -> đồ thị được gọi là liên thông thì chỉ có một thành phần liên thông
    //Nên ta chỉ gọi hàm cho đỉnh 1 nếu nó liên thông thì mặc nhiên tất cả các đỉnh trong đồ thị sẽ được duyệt

    if(check()) printf("YES"); //Liên thông 
    else printf("NO"); //Không liên thông
    
    return 0;
}
