/*
Thuyền trưởng Haddock (truyện Tintin) là một người luôn say xỉn. Vì thế đôi khi Tintin không biết ông ta đang say hay tỉnh. Một ngày nọ, Tintin hỏi ông ta về cách uống. Haddock nói như thế này: Có nhiều loại thức uống (soda, wine, water, …), tuy nhiên Haddock lại tuân theo quy tắc “để uống một loại thức uống nào đó cần phải uống tất cả các loại thức uống tiên quyết của nó”. Ví dụ: để uống rượu (wine), Haddock cần phải uống soda và nước (water) trước. Vì thế muốn say cũng không phải dễ !

Cho danh sách các thức uống và các thức uống tiên quyết của nó. Hãy xét xem Haddock có thể nào say không ? Để làm cho Haddock say, ông ta phải uống hết tất cả các thức uống.

Ví dụ 1:

soda wine
water wine
Thức uống tiên quyết được cho dưới dạng a b, có nghĩa là để uống b bạn phải uống a trước. Trong ví dụ trên để uống wine, Haddock phải uống soda và water trước. Soda và water không có thức uống tiên quyết nên Haddock sẽ SAY.

Ví dụ 2:

soda wine
water wine
wine water
Để uống wine, cần uống water. Tuy nhiên để uống water lại cần wine. Vì thế Haddock không thể uống hết được các thức uống nên ông ta KHÔNG SAY.

Để đơn giản ta có thể giả sử các thức uống được mã hoá thành các số nguyên từ 1, 2, … và dữ liệu đầu vào được cho có dạng như sau (ví dụ 1):

3 2
1 2
3 2
Có loại thức uống (soda: 1, wine: 2 và water: 3) và có 2 điều kiện tiên quyết

1 -> 2 và 3 -> 2.

Với ví dụ 2, ta có dữ liệu:

3 3
1 2
3 2
2 3
Viết chương trình đọc dữ liệu các thức uống và kiểm tra xem Haddock có thể say không. Nếu có in ra “YES”, ngược lại in ra “NO”.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím (stdin) với định dạng:

Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số thức uống và số điều kiện tiên quyết .
m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng thức uống u là tiên quyết của thức uống v.
Đầu ra (Output):

Nếu Haddock có thể say in ra YES, ngược lại in ra NO.
*/

//code
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
int mark[maxv];
int index;
typedef int Vertices;
int n,m;//So dinh va so cung 
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Dinh n
}Graph;
//Cau truc danh sach - List
typedef struct{
    int data[idx];
    int size;
}List;
//lam rong
void makenullList(List *l){
    l->size=0;
}
//Them phan tu
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}
//Truy cap phan tu
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
//Add
void addGraph(Graph *g, int x, int y){
    g->matrix[x][y]=1;
}
//Lang gieng cua 1 dinh 
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
void dfs(Graph* G, int x) {
    if(mark[x]==2) return;
    //print("%d\n",x)
    mark[x] = 2;
    List L = neighbors(G, x);
    for(int j=0;j<L.size;j++){
        int v = getList(&L, j);
        if(mark[v] == 2){
            index = 1; // Ton tai chu trinh
            return;
        }
        dfs(G, v);
    }
    mark[x]=1;
}
int check(Graph* G) {
    for(int i=1;i<=G->n;i++){
        mark[i] = 0;
    }
    index = 0;
    for(int j=1;j<=G->n;j++){
        dfs(G, j);    
    }
    return index;
}

int main(){
    Graph g;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    int u,v;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&u,&v);
        addGraph(&g,u,v);
    }
    if (check(&g)==1) printf("NO");
    else printf("YES");
    
    return 0;
}
