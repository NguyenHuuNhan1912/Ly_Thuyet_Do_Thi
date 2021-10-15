/*
Peter rất thích chơi đá. Anh ta thường dùng đá để trang trí sân nhà của mình. Hiện tại Peter có n hòn đá. Dĩ nhiên mỗi hòn đá có một khối lượng nào đó. Peter muốn đặt các hòn đá này dọc theo lối đi từ cổng vào nhà của mình. Peter lại muốn sắp xếp như thế này: hòn đá nặng nhất sẽ đặt ở cạnh cổng rào, kế tiếp là hòn đá nặng thứ 2, ... hòn đá nhẹ nhất sẽ được đặt cạnh nhà. Như vậy nếu đi từ trong nhà ra cổng, ta sẽ gặp các hòn đá có khối lượng tăng dần.
Tuy nhiên, điều khó khăn đối với Peter là anh chỉ có một cây cân đĩa mà không có quả cân nào. Nói cách khác, mỗi lần cân Peter chỉ có thể biết được hòn đá nào nhẹ hơn hòn đá nào chứ không biết nó nặng bao nhiêu kg.
Sau m lần cân, Peter biết được sự khác nhau về cân nặng của m cặp. Với các thông tin này, hãy giúp Peter sắp xếp các viên đá theo thứ tự anh mong muốn.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số hòn đó và số lần cân

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng hòn đá u nhẹ hơn hòn đá v.

Đầu ra (Output):

In ra màn hình thứ tự của các hòn đá theo khối lượng tăng dần. In các số thứ tự trên cùng một dòng, mỗi số cách nhau một khoảng trắng.

Bạn có thể yên tâm là dữ liệu đầu được giả sử rằng chỉ có một kết quả quả duy nhất.

Xem thêm ví dụ bên dưới. Trong ví dụ đầu tiên ta có: hòn đá 1 nhẹ nhất, kế đến là hòn đá 3 và sau cùng là hòn đá 2.

For example:

Input	  Result
3 2     1
1 3     3
3 2     2

7 13    1
1 2     2
1 3     4
1 4     6
2 3     5
2 6     3
3 7     7
4 5
5 3
5 7
6 7
2 4
6 5
4 6
*/

// Bài toán thực tế cân đá
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
    g->matrix[x][y]=1;
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
int k=0; //Bước lặp của giải thuật, hạng của đỉnh sẽ được gán cho bước lặp sau khi xếp hạng 1 đỉnh trong đồ thị xong

//Dựa trên giải thuật ranking để tìm thứ tự topo
List topoSort(Graph *g){
    List toposort;
    makenullList(&toposort);
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
            pushList(&toposort,u); //Đưa đỉnh đó vào danh sách topo sau khi đã xếp hạng xong
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
    return toposort;
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
    List toposort = topoSort(&g);
    //In thứ tự topo có trong danh sách toposort
    for(int u=1;u<=toposort.size;u++){
        printf("%d ",getList(&toposort,u));
    }
    return 0;
}
/*
NOTE
1. Khi áp dụng giải thuật xếp hạng vào các bài toán thực tế thì bước lặp k có thể bắt đầu từ 1 chứ không nhất thiết phải bắt đầu bằng 0

2. Bài toán thực tế cân đá thực ra là:

    + Tìm danh sách theo thứ tự topo
    
    + Thứ tự topo chính là thứ tự các đỉnh được xét hạng 
    
    + Chỉ cần dựa vào giải thuật ranking sau khi xét hạng của một đỉnh ta chỉ cần đưa
    
    đỉnh đó vào một danh sách -> kết quả trả về là 1 danh sách có thứ tự topo
    
    + Tuy nhiên một đồ thị có thể có nhiều thứ tự topo: Đến khi gặp case như thế thì chúng ta chỉ cần suy luận một xíu là có thể ra được đáp án
    
    + Đồ thị có n thứ tự topo khi đồ thị đó có n đỉnh xếp hạng bằng nhau
    
*/
