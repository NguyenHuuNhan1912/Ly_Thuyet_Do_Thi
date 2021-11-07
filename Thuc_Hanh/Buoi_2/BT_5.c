/*
Cho G=<V, E> là một đồ thị vô hướng đơn (không có khuyên, không có đa cung). Hãy viết chương trình kiểm tra xem có chứa chu trình hay không.

Chu trình là một đường đi đơn cung có đỉnh đầu trùng với đỉnh cuối.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v mô tả cung (u, v).

Đầu ra (Output):

In ra màn hình YES nếu đồ thị có chứa chu trình, ngược lại in ra NO

Xem thêm ví dụ bên dưới.

Hướng dẫn đọc dữ liệu và chạy thử chương trình
Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.

Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
For example:

Input	Result
3 2     NO
1 3
2 3

7 9     YES
1 2
1 3
1 4
2 3
2 6
3 5
3 7
4 5
5 7

7 9     YES
1 2
1 3
2 4
2 5
2 6
3 5
3 6
4 7
5 7

3 2     NO
1 2
2 3

4 3     NO
1 2
2 3
2 4

*/

//code

#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
int n,m;
typedef int Vertices;
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;
}Graph;
typedef struct{
    int data[idx];
    int size;
}List;
void makenullList(List *l){
    l->size=0;
}
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}
int getList(List *l, int index){
    return l->data[index-1];
}
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            g->matrix[i][j]=0;
}
void addEdge(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}
bool adjacent(Graph *g, int x, int y){
    return g->matrix[x][y]==1;
}
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
int mark[maxv];
int key=0;
void DFS_Recursion(Graph *g, int x, int p){
    mark[x]=1;
    List L = neighbors(g,x);
    for(int j=1;j<=L.size;j++){
        int v = getList(&L,j);
        if(v==p) continue;
        if(mark[v]==1){
            key=1;
            return;
        }
        DFS_Recursion(g,v,x);
    }
}
bool check(Graph *g){
    for(int i=1;i<=n;i++)
        mark[i]=0;
    for(int i=1;i<=n;i++){
        if(mark[i]==0){
            DFS_Recursion(g,i,0);
        }
    }
    return key;
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
    if(check(&g)) printf("YES");
    else printf("NO");
    return 0;
}
