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
    if(check()) printf("YES");
    else printf("NO");

    return 0;
}
