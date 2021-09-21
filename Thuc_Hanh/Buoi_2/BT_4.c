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
*/

//code

//Ton ngo khong - Ly thuyet do thi
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
typedef int Vertices;
int n,m;
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//n dinh
}Graph;
//Cau truc list
typedef struct{
    int data[idx];
    int size;
}List;
//makenullLsit
void makenullList(List *l){
    l->size=0;
}
//Push
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}
//get
int getList(List *l, int index){
    return l->data[index];
}
//Khoi tao
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}
//ADD
void addGraph(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}
//Nei
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(g->matrix[x][i]==1){
            pushList(&L,i);
        }
    }
    return L;
}
//Duyet do thi de qui
int mark[maxv];
int count;
void DFS_Discursion(Graph *g, int x){
    if(mark[x]==1) return;
    //printf("%d\n",x);
    count++;
    mark[x]=1;
    List L = neighbors(g,x);
    for(int j=0;j<L.size;j++){
        int v = L.data[j];
        DFS_Discursion(g,v);
    }
}
bool check(Graph *g){
    DFS_Discursion(g,1);
    if(n==count) return true;
    return false;
}
int main(){
    Graph g;
    count=0;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    int u,v;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addGraph(&g,u,v);
    }
    for(int i=1;i<=n;i++){
        mark[i]=0;
    }
    if(check(&g)) printf("DUOC");
    else printf("KHONG");
    return 0;
}