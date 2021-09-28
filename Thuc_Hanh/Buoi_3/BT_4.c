/*
Mê cung số (number maze)

Cho một mê cung số được biểu diễn bằng một mảng 2 chiều chứa các con số từ 0 đến 9 (xem
hình bên dưới).

0 3 1 2 9
7 3 4 9 9
1 7 5 5 3
2 3 4 2 5

Một con robot được đặt tại góc trên bên trái của mê cung và muốn đi đến góc dưới bên phải của mê cung. Con robot có thể đi lên, xuống, qua trái và qua phải 1 ô. Chi phí để đi đến một ô bằng với con số bên trong ô đó.
Hãy tìm cách giúp con robot đi đến ô góc dưới phải sao cho tổng chi phí thấp nhất.

Đường đi có chi phí thấp nhất cho ví dụ này là 24.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

Dòng dầu chứa 2 số nguyên M N (M: số hàng, N: số cột)
M dòng tiếp theo mô tả các số trong mê cung

Đầu ra (Output):

In ra màn hình chi phí thấp nhất để con robot đi từ góc trên bên trái về góc dưới bên phải. Ví dụ trên, cần in ra màn hình: 24.
Xem thêm các ví dụ bên dưới.

Gợi ý:

Mô hình hoá bài toán về đồ thị có hướng

Đỉnh ~ ô
Cung ~ hai ô cạnh nhau
Trọng số cung (u, v) = giá trị của ô tương ứng với đỉnh v.
Xem tài liệu thực hành để biết cách đặt tên cho các ô.

For example:

Input       Result

4 5         24
0 3 1 2 9
7 3 4 9 9
1 7 5 5 3
2 3 4 2 5

3 3         18
1 2 3
2 4 4
1 4 10

4 3         17
1 2 2
2 1 4
4 2 1
8 4 10

*/

//code

#include<stdio.h>
#define maxv 100
#define INFINITY 999999
#define NO_EDGE 0
typedef int Vertices;

//Khai báo cấu trúc đồ thị
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Đỉnh n
}Graph;

//Khởi tạo 
void initGraph(Graph *g, int n){
    int i,j;
    g->n=n;
    for(i=1;i<=g->n;i++)
        for(j=1;j<=g->n;j++)
            g->matrix[i][j] = 0;
}

//Hàm tìm giá trị nhỏ nhất
int min(int a, int b){
    return (a<b) ? a: b;
} 

int mark[maxv]; //Mảng toàn cục để đánh dấu các đỉnh
int pi[maxv]; //Mảng toàn cục để lưu đường đi ngắn nhất tạm thời
int p[maxv]; //Mảng toàn cục để lưu đỉnh cha của một đỉnh
int w[maxv]; //Mảng w để lưu tất cả trọng số của các ô bắt đầu từ ô thứ 1 đến n

//Thuật toán tìm đường đi ngắn nhất
void Dijkstra(Graph *g, int x){

    int i,j,k;
    for(i=1;i<=g->n;i++){
        pi[i] = INFINITY; //Khởi tạo đường đi ngắn nhất tạm thời của tất cả các đỉnh bằng vô cực
        mark[i]=0; //Khởi tạo chưa có đỉnh nào được đánh dấu( Đỉnh chưa đánh dâu có chỉ số bằng 0)
    }

    pi[x] = w[x];
    p[x] = -1;//Đỉnh cha của đỉnh đầu tiên gán bằng -1 tức đỉnh 1 không có đỉnh cha

    //Tìm đỉnh chưa đánh dấu(mark[x]==0) và có pi[x] nhỏ nhất để xét
    for(k=1;k<=g->n;k++){
        int min_pi = INFINITY;
        for(j=1;j<=g->n;j++){
            if(mark[j] == 0 && pi[j] < min_pi){
                min_pi = pi[j];
                i=j;
            }
        }

        mark[i]=1;//Sau khi đã tìm được đỉnh có pi[index] nhỏ nhất thì đánh dấu đỉnh đó đã được duyệt
        
        for(j=1;j<=g->n;j++){
            int v = g->matrix[i][j];
            //Nếu v là đỉnh kề của đỉnh x (tức đường đi từ x tới v có trọng số khác 0/NO_EDGE) và mark[v] chưa được duyệt
            if( v !=  NO_EDGE  && mark[j]==0){ 
                int pi_before = pi[j];//pi_before để lưu đường đi ngắn nhất tạm thời trước đó
                int pi_after = min(pi[j],pi[i]) + g->matrix[i][j]; //pi_after là đường đi ngắn nhất tạm thời vừa mới tính được
                //Nếu đường đi ngắn nhất tạm thời sau < đường đi ngắn nhất tạm thời trước đó
                if(pi_after < pi_before ){
                    pi[j]=pi_after;//Cập nhật lại đường đi ngắn nhất tạm thời = đường đi ngắn nhất tạm thời vừa tìm được
                    p[j]=i;//Sau khi cập nhật xong thì lưu đỉnh cha của đỉnh vừa cập nhật 
                }
                /*Nếu câu điều kiện phía trên không thực hiện thì đường đi ngắn nhất tạm thời sau không 
                lớn hơn đường đi ngắn nhất tạm thời trước đó thì không cập nhật mà chỉ lưu đỉnh cha của đỉnh đó*/
                p[j]=i;    
            }
        }
    }
}
int main(){
    Graph g;
    int m,n,u,v;
    int i_ke,j_ke;

    scanf("%d %d",&m,&n); // Nhap M : so hang , N : so cot

    initGraph(&g,m*n); //Khởi tạo tổ hợp gồm n*m hàng và n*m cột

    //Nhập giá trị cho từng ô tức trọng số của đồ thị rồi lưu vào mảng w 
    for(int i=1;i<=(n*m);i++){
        scanf("%d",&u);
        w[i]=u;
    }

    //Thuật toán tìm đỉnh kề của một đỉnh
    for(int i=0;i<m;i++){
         for(int j=0;j<n;j++){
            //Mỗi ô trong ma trận có thể nhiều nhất 4 ô khác nếu 
            int di[] = {-1,1,0,0};
            int dj[] = {0,0,-1,1};
            //Duyệt qua các ô kề của o(i,j)
            for(int k=0;k<4;k++){
                i_ke = i+di[k];
                j_ke = j + dj[k];
                //Kiểm tra o(i_ke,j_ke) có nằm trong mê cung không tức là nằm trong phạm vi (0,0) và (M-1, N-1).
                if((i_ke>=0) && (i_ke<m) && (j_ke>=0) && (j_ke<n)){
                    v = i_ke * n + j_ke + 1;
                    u = i * n + j + 1;
                    g.matrix[u][v] = w[v]; //Kết quả là tìm được các đỉnh kề trong mê cung và gán trọng số
                }
            }
        }
    }

    Dijkstra(&g,1);

    printf("%d ",pi[g.n]);
    
    return 0;
}