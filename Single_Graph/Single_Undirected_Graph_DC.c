#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define maxe 50
typedef int dinh;
typedef int cung;
typedef struct{
    int matrix[maxv][maxe];
    dinh n; //n hang
    cung m; //m cot
}Graph;
//Ham khoi tao do thi rong
void init_Graph(Graph *g, int n, int m){
    g->n=n;
    g->m=m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            g->matrix[i][j]=0;
        }
    }
}
//In do thi
void print_Graph(Graph g){
    for(int i=1;i<=g.n;i++){
        for(int j=1;j<=g.m;j++){
            printf("%d ",g.matrix[i][j]);
        }
        printf("\n");
    }
}
//Them cung e = (x,y)
void add_Graph(Graph *g, int e, int x, int y){
    g->matrix[x][e]=1;
    g->matrix[y][e]=1;
}
//Read file
void read_File(FILE *f, Graph *g){
    int u,v;
    for(int e=1;e<=g->m;e++){
        fscanf(f,"%d%d",&u,&v);
        add_Graph(g,e,u,v);
    }
}
bool adjacent(Graph g, int x, int y){
    for(int e=1;e<=g.m;e++){
        if(g.matrix[x][e]==1 && g.matrix[y][e]==1)
            return true;
    }
    return false;
}
int degree(Graph g, int x){
    int count=0;
    for(int i=1;i<=g.m;i++){
        if(g.matrix[x][i]==1)
            count++;
    }
    return count;
}
int main(){
    Graph g;
    FILE *f = fopen("data.txt","r");
    int n,m,x,y;
    fscanf(f,"%d%d",&n,&m);
    init_Graph(&g,n,m);
    printf("\nDo thi vua khoi tao\n");
    print_Graph(g);
    printf("\nDo thi vua cap nhat tu du lieu\n");
    read_File(f,&g);
    print_Graph(g);
    printf("\nNhap hai dinh can kiem tra: "); scanf("%d%d",&x,&y);
    if(adjacent(g,x,y)) printf("\nYES");
    else printf("\nNO");
    for(int i=1;i<=g.n;i++) printf("\nDegree(%d) = %d\n",i,degree(g,i));
    return 0;
}