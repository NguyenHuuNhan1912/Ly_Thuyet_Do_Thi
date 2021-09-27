/*

Tôn Ngộ Không là một trong các nhân vật chính của truyện Tây du ký. Khi còn ở Hoa Quả Sơn, Tôn Ngộ Không là vua của loài khỉ. Hoa Quả Sơn có rất nhiều cây ăn trái, nên loài khỉ rất thích. Do đặc tính của mình, khỉ không thích đi bộ mà chỉ thích chuyền từ cây này sang một cây khác. Tuy nhiên, nếu khoảng cách giữa hai cây quá xa thi chúng không thể chuyền qua lại được.
Đường đường là vua của loài khỉ, Tôn Ngộ Không muốn vạch ra một kế hoạch hái trái cây trên tất cả các cây có trên Hoa Quả Sơn mà không cần phải nhảy xuống đất. Tôn Ngộ Không dự định sẽ bắt đầu leo lên một cây, hái trái của cây này, sau đó chuyền qua một cây kế tiếp hái trái của này và tiếp tục như thế cho đến khi tất cả các cây đều được hái trái. Một cây có thể được chuyền qua chuyền lại nhiều lần.
Hãy giúp Tôn Ngộ Không kiểm tra xem kế hoạch này có thể thực hiện được không.

Đầu vào (Input):
Giả sử số lượng cây ăn trái ở Hoa Quả Sơn là n cây và được đánh số từ 1 đến n.

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số cây và số cặp cây có thể chuyền qua lại.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng có thể chuyền từ cây u sang cây v hoặc chuyền từ cây v sang cây u.

Đầu ra (Output):

Nếu kế hoạch của Tôn Ngộ Không có thể thực hiện được DUOC, ngược lại in ra KHONG.

Xem thêm ví dụ bên dưới. Trong ví dụ đầu tiên, Tôn Ngộ Không bắt đầu từ cây 1, chuyền qua cây 2, sau đó chuyền ngược về 1, chuyền tiếp sang 3 và sau cùng là sang 4.

For example:

Input	Result

4 3     DUOC 
2 1
1 3
3 4

4 2     KHONG    
1 2
3 4

*/

//code

#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
typedef int Vertices;

//Khai bao cau truc do thi
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Dinh n
}Graph;

int n,m;//Bien toan cuc luu so dinh va so canh

//Khai bao cau truc danh sach - LIST
typedef struct{
    int data[idx];
    int size;
}List;

/*Cac ham tren danh sach*/

//Lam rong danh sach
void makenullList(List *l){
    l->size=0;
}

//Them phan tu vao danh sach
void pushList(List *l, int x){
    l->data[l->size]=x;
    l->size++;
}

//Truy cap phan tu trong danh sach
int getList(List *l, int x){
    return l->data[x];
}
/*Cac ham tren do thi*/

//Khoi tao do thi rong
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}

//Them cung e = (x,y) vao do thi
void addGraph(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}

//Tim dinh lang gieng cua dinh x (x la dinh dinh bat ki trong do thi)
List neighbors(Graph g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(g.matrix[x][i]==1){
            pushList(&L,i);
        }
    }
    return L;
}

int count;//Bien toan cuc kiem tra do thi co lien thong hay khong
int mark[maxv];//Mang toan cuc danh dau 1 dinh da duyet vao do thi hay chua

//Duyet do thi theo chieu sau bang de qui
void DFS_Recursion(Graph *g, int x){
    if(mark[x]==1) return; //Neu dinh do da duyet thi kh duyet nua 
    mark[x]=1; //Danh dau dinh do da duyet
    count++; //Tang bien count len 1 don vi
    List L = neighbors(*g,x); //Tim dinh lang gieng cua dinh x luu vao danh sach
    for(int j=0;j<L.size;j++){
        int v = getList(&L,j); //Lay dinh ke dau tien cua dinh x trong danh sach ra
        DFS_Recursion(g,v); //Goi de qui
    }
    
}

//Kiem tra
bool check(){
    //Neu bien count = so dinh cua do thi --> Do thi vo huong lien thong
    //Do thi duoc goi la lien thong chi ton tai duy nhat 1 thanh phan lien thong
    return (n==count);
}
int main(){

    Graph g;
    int u,v;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addGraph(&g,u,v);
    }

    //Khoi tao cac phan tu trong mark ban dau = 0
    for(int i=1;i<=n;i++) mark[i]=0;

    //Goi ham de qui bat dau tu dinh 1
    DFS_Recursion(&g,1);

    //Goi ham de kiem tra
    if(check()) printf("DUOC");
    else printf("KHONG");

    return 0;
}
