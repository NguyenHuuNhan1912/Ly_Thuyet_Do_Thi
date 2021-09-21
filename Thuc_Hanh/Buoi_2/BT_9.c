/*
Trong một thành phố có N địa điểm được nối với nhau bằng M con đường 1 chiều và 2 chiều. Yêu cầu tối thiểu của một thành phố là từ địa điểm này bạn phải có thể đi đến một địa điểm khác bất kỳ.

Hãy viết chương trình kiểm tra xem các con đường của thành phố có thoả mãn yêu cầu tối thiểu này không. Nếu có in ra OKIE, ngược lại in ra NO.

(nguồn: UVA Online Judge, Problem 11838)

Dữ liệu đầu vào có dạng như sau:

4 5
1 2 1
1 3 2
2 4 1
3 4 1
4 1 2
Trong ví dụ này, có 4 địa điểm và 5 con đường, mỗi con đường có dạng a b p,  trong đó a, b là các địa điểm; và nếu p = 1, con đường đang xét là đường 1 chiều, ngược lại nó là đường 2 chiều.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím (stdin) với định dạng:

- Dòng đầu tiên chứa 2 số nguyên N và M, tương ứng là số địa điểm và số con đường.

- M dòng tiếp theo mỗi dòng chứa 3 số nguyên a, b, p. Nếu p = 1, con đường (a, b) là con đường 1 chiều, ngược lại nếu p = 2, con đường (a, b) là con đường 2 chiều.

Đầu ra (Output):

In ra màn hình OKIE nếu các con đường của thành phố có thoả mãn yêu cầu, ngược lại in ra NO.

Xem thêm ví dụ bên dưới.

Gợi ý:

Xây dựng đồ thị có hướng từ dữ liệu các con đường và các địa điểm
Địa điểm ~ đỉnh
Đường 1 chiều ~ cung
Đường 2 chiều ~ 2 cung
Áp dụng giải thuật kiểm tra đồ thị có liên thông mạnh hay không.
*/

//code
//Kiem tra do thi co lien thong manh hay khong - Don do thi co huong - ma tran dinh dinh
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
typedef int Vertices;
int n,m;//Bien toan cuc luu so dinh va so cung 
//Khai bao cau truc do thi - GRAPH
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//
}Graph;
//Khai bao cau truc ngan xep - STACK
typedef struct{
    int data[maxv];
    int size;
}Stack;
//Lam rong
void makenullStack(Stack *s){
    s->size=0;
}
//Them phan tu vao ngap xep
void pushStack(Stack *s, int element){
    s->data[s->size] = element;
    s->size++;
}
//Lay phan tu cua ngan xep
int getStack(Stack *s){
    return s->data[s->size-1];
}
void delSize(Stack *s){
    s->size--;
}
//Khai bao cau truc danh sach - LIST
typedef struct{
    int data[idx];
    int size;
}List;
//Lam rong
void makenullList(List *l){
    l->size=0;
}
int emptyList(List *l){
    return l->size==0;
}
//Them phan tu vao danh sach
void pushList(List *l, int element){
    l->data[l->size] = element;
    l->size++;
}
//Truy cap phan tu trong danh sach
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
//Them cung 
void addEdges(Graph *g, int x, int y){
    g->matrix[x][y]=1;
}
//In do thi
void printGraph(Graph g){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%d ",g.matrix[i][j]);
        }
        printf("\n");
    }
}
//Tim dinh lang gieng
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
//Cac bien mang toan cuc de thuc hien viec kiem tra
int count=0,k=1;
int num[maxv],min_num[maxv],on_stack[maxv];
//Ham tim gia tri nho nhat
int min(int a, int b){
    return (a<b) ? a : b;
}
void strong_connect(Graph *g, int x){
    //Cho num va min num bang chi so k
    num[x] = min_num[x] = k;
    k++;
    Stack s;
    makenullStack(&s);
    //Dua dinh dau tien vao stack
    pushStack(&s,x);
    //Danh dau dinh do da dua vao stack bang bien mang on_stack
    on_stack[x]=1;
    //Tim dinh lang gieng cua dinh do
    List L = neighbors(g,x);
    //Xet cac dinh ke cua x
    for(int j=0;j<L.size;j++){
        int v = getList(&L,j);
        //Neu dinh ke x chua co trong stack
        if(num[v]==-1){
            //Goi de qui duyet dinh ke cua x
            strong_connect(g,v);
            //Khi dut lui cap nhat lai min_num cho dinh x(min_num cha < min_num con)
            min_num[x] = min(min_num[x],min_num[v]);
        }
        //Neu dinh v ke x da co trong stack
        else if(on_stack[v]==1){
            //Cap nhat lai min num
            min_num[x] = min(min_num[x],num[v]);
        }
        //Sau khi duyet xong 1 dinh ma vong lap for o tren dung lai tuc la ta da co 1 bo phan lien thong manh
        //Neu do thi lien thong manh thi ket thuc luon chuong trinh vi do thi lien thong thi chi co 1 thanh phan lien thong
        if(num[x]==min_num[x]){
            count++;//Bien count de diem so bo phan lien thong manh cua do thi
            int value;
            do{
                //Lay dinh o dau stack ra
                value = getStack(&s);
                delSize(&s);
                //danh dau dinh da lay ra khoi stack
                on_stack[x]=0;
            }while(value!=x);//Lap den khi lay duoc dinh x(Dinh cat)
        }
    }
}
int main(){
    Graph g;
    int u,v,y;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&y);
        if(y==1) addEdges(&g,u,v);
        else if(y==2){
            addEdges(&g,u,v);
            addEdges(&g,v,u);
        }
        
    }

    for(int i=1;i<=n;i++){
        num[i] = -1;
        min_num[i] = 0;
    }
    for(int i=1;i<=n;i++){
        if(num[i]==-1){
            strong_connect(&g,i);
        }
    }

    if(count==n || count==1) printf("OKIE");
    else printf("NO");    
    
    
    return 0;
}
