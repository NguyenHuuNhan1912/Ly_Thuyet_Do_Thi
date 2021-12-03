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
int degree_Input(Graph *g, int x){
    int count=0;
    for(int i=1;i<=n;i++)
        if(adjacent(g,i,x))
            count++;
    return count;
}
int degree_Output(Graph *g, int x){
    int count=0;
    for(int i=1;i<=n;i++)
        if(adjacent(g,x,i))
            count++;
    return count;
}
// List neighbors(Graph *g, int x){
//     List L;
//     makenullList(&L);
//     for(int i=1;i<=n;i++)
//         if(adjacent(g,x,i))
//             pushList(&L,i);
    
//     return L;
// }
int main(){
    Graph g;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    int u,v;
    for(int e=1;e<=m;e++){
        scanf("%d%d",&u,&v);
        addEdge(&g,u,v);
    }
    //
    return 0;
}
