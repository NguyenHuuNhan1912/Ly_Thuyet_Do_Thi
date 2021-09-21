/*
Hãy viết chương trình đọc đồ thị từ tập tin và hiển thị ma trận kề của đồ thị này.

Giả sử đồ thị được cho là đồ thị vô hướng đơn.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ tập tin dt1.txt với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v mô tả cung (u, v).

Đầu ra (Output):

In ra Ma trận kề (0/1) của đồ thị

Ví dụ:

Nếu đầu vào là:

4 4
1 2
1 3
2 3
3 4
Kết quả là:

0 1 1 0 
1 0 1 0 
1 1 0 1 
0 0 1 0

*/

//code

#include <stdio.h>
#define maxv 50
typedef struct{
    int matrix[maxv][maxv];
    int n;
}Graph;
void initGraph(Graph *g, int n){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}
void addEdge(Graph *g, int u, int v){
    g->matrix[u][v]=1;
    g->matrix[v][u]=1;
}
int main(){
    Graph g;
    int n,m,u,v;
    scanf("%d%d",&n,&m);
    initGraph(&g,n);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdge(&g,u,v);
    }
    for(int i=1;i<=g.n;i++){
        for(int j=1;j<=g.n;j++){
            printf("%d ",g.matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
