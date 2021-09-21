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
typedef struct{
    int matrix[maxv][maxv];
    int n;
}Graph;
typedef struct{
    int data[idx];
    int size;
}List;
void makenullList(List *l){
    l->size=0;
}
void pushList(List *l, int x){
    l->data[l->size]=x;
    l->size++;
}
int getList(List l, int x){
    return l.data[x];
}
void initGraph(Graph *g, int n){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}
void addGraph(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}
List neighbors(Graph g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=g.n;i++){
        if(g.matrix[x][i]==1){
            pushList(&L,i);
        }
    }
    return L;
}
int count;
int mark[maxv];
void DFS_Recursion(Graph *g, int x){
    if(mark[x]==1) return;
    count++;
    mark[x]=1;
    List L = neighbors(*g,x);
    for(int j=0;j<L.size;j++){
        int v = getList(L,j);
        DFS_Recursion(g,v);
    }
    
}
void print_DFS_Recursion(Graph g){
    for(int i=1;i<=g.n;i++) mark[i]=0;
    DFS_Recursion(&g,1);
    
}
void check(Graph g){
    if(count != g.n){
        printf("NO");
    }
    else printf("YES");
}
int main(){
    Graph g;
    int n,m,u,v;
    scanf("%d%d",&n,&m);
    initGraph(&g,n);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addGraph(&g,u,v);
    }
    print_DFS_Recursion(g);
    check(g);
    return 0;
}