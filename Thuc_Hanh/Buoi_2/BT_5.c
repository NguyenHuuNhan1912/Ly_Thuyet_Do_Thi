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
typedef int Vertices;
int n,m;//Biến toàn cục lưu số đỉnh và số cung

//Cấu trúc đồ thị
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Dinh n
}Graph;

/*Các hàm trên danh sách*/

//Cấu trúc danh sách
typedef struct{
    int data[idx];
    int size;
}List;

//Làm rỗng danh sách
void makenullList(List *l){
    l->size=0;
}

//Thêm phần tử vào danh sách
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}
//Truy cập phần tử trong danh sách
int getList(List *l, int index){
    return l->data[index];
}

//Khởi tạo đồ thị
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}

//Thêm cung e = (x,y) vào đồ thị 
void addGraph(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}

//Tìm đỉnh láng giềng của 1 đỉnh bất kì trong đồ thị 
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

int test;//Biến toàn cục để kiểm tra đồ thị có chứa chu trình hay không
int mark[maxv];//Mảng toàn cục để đánh dấu các phần tử đã duyệt

//Duyệt đồ thị theo chiều sâu đệ qui đồng thời kiểm tra chu trình
void DFS_Recursion(Graph *g, int x, int p){

    if(mark[x]==1) return; //Nếu đỉnh x có trong đồ thị thì kết thúc hàm

    /*Trong trường hợp này thông thường sẽ in ra đỉnh x để biết là đỉnh x đã duyệt
    nhưng chúng ta sử dụng duyệt sâu để kiểm tra đồ thị có chứa chi trình 
    hay không nên không cần in đỉnh x ra*/

    //printf("%d\n",x); 

    mark[x]=1; //Đánh dấu x đã duyệt
    List L =  neighbors(g,x); //Tìm các đỉnh kề v của x và lưu vào danh sách
    for(int j=0;j<L.size;j++){
        int v = getList(&L,j); //Lấy đỉnh kề đầu tiên của đỉnh x trong danh sách ra
        if(v==p) continue; // Nếu đỉnh kề v của x đã bằng đỉnh cha thì bỏ qua
        if(mark[v]==1){
            test = 1; //Đã tồn tại chu trình
            return;//Thoát hàm
        }
        DFS_Recursion(g,v,x);//Nếu không thỏa 2 câu điều kiện trên thì gọi đệ qui
    }
}

//Hàm kiểm tra và trả về kết quả
bool check(){
   return (test==1);//Test bằng 1 --> Đồ thị có tồn tại chu trình
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

    test = 0;//Biến test để kiểm tra đồ thị có chứa chu trình hay không

    //Khởi tạo các phần tử trong mark bằng 0 
    for(int i=1;i<=n;i++)
        mark[i]=0;

    //Duyệt tất cả các đỉnh của đồ thị để kiểm tra chu trình
    for(int i=1;i<=n;i++)
        DFS_Recursion(&g,i,0);
    
    if(check()) printf("YES");
    else printf("NO");
	
    return 0;
}
