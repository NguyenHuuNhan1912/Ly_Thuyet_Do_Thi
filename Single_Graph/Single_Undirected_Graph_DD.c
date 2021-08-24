//Do thi don vo huong bieu dien bang ma tran dinh dinh
#include <stdio.h>
#include <stdbool.h>
#include <D:\LTDT\Library\List.c>
#include <D:\LTDT\Library\Queue.c>
#include <D:\LTDT\Library\Stack_LTDT.c>
#define MAXV 100
typedef int Vertices;
//Khai bao cau truc do thi
typedef struct{
    int matrix[MAXV][MAXV];
    Vertices n;
}Graph;
//Ham khoi tao do thi
void init_Graph(Graph *g, int n){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}

//Them them 1 cung vao do thi
void add_Graph(Graph *g, int u, int v){
    g->matrix[u][v]=1;
    g->matrix[v][u]=1;
}

//Ham doc du lieu tu file
void read_File(FILE *f, Graph *g, int m){
    int u,v;
    for(int i=1;i<=m;i++){
        fscanf(f,"%d%d",&u,&v);
        add_Graph(g,u,v);
    }
}

//Ham in do thi
void print_Graph(Graph g){
    for(int i=1;i<=g.n;i++){
        for(int j=1;j<=g.n;j++){
            printf("%d ",g.matrix[i][j]);
        }
        printf("\n");
    }
}

//Ham kiem tra hai dinh co ke nhau hay khong
bool adjacent(Graph g, int x, int y){
    return (g.matrix[x][y]==1);
}

//Ham tinh bac cua 1 dinh
int degree(Graph g, int x){
    int count=0;
    for(int i=1;i<=g.n;i++){
        if(g.matrix[i][x]==1) count++;
    }
    return count;
}

//In bac cua tat ca cac dinh trong do thi
void print_degree(Graph g){
    for(int i=1;i<=g.n;i++){
        printf("\nDegree(%d) = %d\n",i,degree(g,i));
    }
}

//Danh sach dinh lang gieng cua bac x
List neighbors(Graph g, int x){
    List L;
    makenull_List(&L);
    for(int i=1;i<=g.n;i++){
        if(g.matrix[i][x]==1){
            push_List(&L,i);
        }
    }
    return L;
}

//Ham in cac dinh lang gieng cua toan bo dinh trong do thi
void print_Neighbors(Graph g){
    for(int i=1;i<=g.n;i++){
        List L = neighbors(g,i);
        printf("\nNeighbors(%d) = { ",i);
        for(int j=0;j<L.size;j++){
            if(j==L.size-1) printf("%d ",get_List(L,j));
            else printf("%d, ",get_List(L,j));
        }
        printf("}\n");
    }
}

//Ham tra ve danh sach thu tu duyet cua dinh(su dung hang doi - Queue)
List BFS_Queue(Graph *g, int x, int father[]){
    List rs;
    makenull_List(&rs);
    Queue q;
    makenull_Queue(&q);
    int mark[MAXV];
    for(int i=1;i<=g->n;i++) mark[i]=0;
    push_Queue(&q,x);
    father[x]=0;
    while(!empty_Queue(q)){
        int u = get_Queue(&q); plus_Front(&q);
        if(mark[u]==1) continue;
        push_List(&rs,u);
        mark[u]=1;
        List L = neighbors(*g,u);
        for(int i=0;i<L.size;i++){
            int v = get_List(L,i);
            if(mark[v]==0){
                push_Queue(&q,v);
                if(father[v]==-1){
                    father[v]=u;
                }
            }
        }
    }
    return rs;
}

//Ham tra ve danh sach thu tu duyet cua dinh(su dung ngan xep - Stack)
List DFS_Stack(Graph *g, int x, int father[]){
    List rs;
    makenull_List(&rs);
    Stack s;
    makenull_Stack(&s);
    int mark[MAXV];
    for(int i=1;i<=g->n;i++) mark[i]=0;
    push_Stack(&s,x);
    father[x]=0;
    while(!empty_Stack(&s)){
        int u = get_Stack(&s); delete_size(&s);
        if(mark[u]==1) continue;
        push_List(&rs,u);
        mark[u]=1;
        List L = neighbors(*g,u);
        for(int j=0;j<L.size;j++){
            int v = get_List(L,j);
            if(mark[v]==0){
                push_Stack(&s,v);
                father[v]=u;
            }
        }
    }
    return rs;
}

//Ham in thu tu duyet va nut cha cua dinh(Ap dung in voi thuat toan DFS va BFS)
void print_result_DFS_OR_BFS(Graph g){
    int md[MAXV],father[MAXV];
    for(int i=1;i<=g.n;i++){
        md[i]=0;
        father[i]=-1;
    }
    for(int i=1;i<=g.n;i++){
        if(md[i]==0){
            List L =DFS_Stack(&g,i,father);
            printf("\nDuyet = { ");
            for(int j=0;j<L.size;j++){
                int v = get_List(L,j);
                if(j==L.size-1) printf("%d ",v);
                else printf("%d, ",v);
                md[v]=1;
            }
            printf("}\n");
        }
    }
    for(int i=1;i<=g.n;i++) printf("\nFather[%d] = %d\n",i,father[i]);
}
int mark[MAXV];
int father[MAXV];
//Thuat toan duyet do thi theo chieu sau bang de qui(Recursion)
void DFS_Recursion(Graph *g, int x, int p){
    if(mark[x]==1) return;
    printf("%d\n",x);
    father[x]=p;
    mark[x]=1;
    List L = neighbors(*g,x);
    for(int j=0;j<L.size;j++){
        int v = get_List(L,j);
        DFS_Recursion(g,v,x);
    }
}

//Ham in thu tu duyet va nut cha cua dinh(Ap dung in voi thuat toan DFS de qui)
void print_result_Recursion(Graph g){
    for(int i=1;i<=g.n;i++){
        mark[i]=0;
        father[i]=-1;
    }
    for(int i=1;i<=g.n;i++) DFS_Recursion(&g,i,0);
    for(int i=1;i<=g.n;i++) printf("Father[%d] = %d\n",i,father[i]);
}
int main(){
    Graph g;
    int n,m,x,y;
    FILE *f = fopen("data.txt","r");
    fscanf(f,"%d%d",&n,&m);
    init_Graph(&g,n);
    printf("\nDo thi vua khoi tao\n");
    print_Graph(g);
    read_File(f,&g,m);
    printf("\nDo thi vua cap nhat du lieu tu file\n");
    print_Graph(g);
    // printf("Nhap 2 dinh can kiem tra: "); scanf("%d%d",&x,&y);
    // if(adjacent(g,x,y)) printf("\nYES");
    // else printf("\nNO");
    print_degree(g);
    print_Neighbors(g);
    printf("\nDuyet\n");
    // print_result_DFS_OR_BFS(g);
    print_result_Recursion(g);
    return 0;
}

