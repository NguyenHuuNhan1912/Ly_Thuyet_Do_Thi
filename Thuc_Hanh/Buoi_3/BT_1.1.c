/*

Cho đồ thị có hướng G = <V, E> có n đỉnh và m cung (n < 100, m < 500). Mỗi cung được gán một trọng số w (0 < w <= 100).

Viết chương trình tìm đường đi ngắn nhất từ đỉnh 1 đến n.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m.

- m dòng tiếp theo mỗi dòng chứa 3 số nguyên u, v, w mô tả cung (u, v) có trọng số w.

Đầu ra (Output):

In ra màn hình chiều dài của đường đi ngắn nhất từ 1 đến n. Nếu không có đường đi từ 1 đến n, in ra -1.

Xem thêm ví dụ bên dưới.

Chú ý:

Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &c);
		add_edge(&G, u, v, w);
	}

For example:

Input	Result
3 3     4
1 2 9
2 3 4
1 3 4

3 1    -1
1 2 5

6 9    20 
1 2 7
1 3 9
1 5 14
2 3 10
2 4 15
3 4 11
3 5 2
4 6 6
5 6 9

*/

//code

#include <stdio.h>
#include <stdbool.h>
#define maxv 50 
#define idx 100
#define  NO_EDGE 0 
#define INFINITY 999999999 
typedef int Vertices;

int n,m;//Biến toàn cục lưu số đỉnh và số cung

//Khai báo cấu trúc đồ thị
typedef struct{
	int matrix[maxv][maxv];
	Vertices n; //Đỉnh n
}Graph;

//Khởi tạo đồ thị(Tất cả cung trong đồ thị đều bằng 0/NO_EDGE)
void initGraph(Graph *g){
	g->n=n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			g->matrix[i][j]=NO_EDGE;
		}
	}
}

//Thêm cung e =(x,y,t) vào đồ thị với t là trọng số
void addEdge(Graph *g, int x, int y, int t){
	g->matrix[x][y]=t;
}

//Hàm tìm giá trị nhỏ nhất
int min(int a, int b){
    return (a<b) ? a: b;
}

int mark[maxv]; //Mảng toàn cục để đánh dấu các đỉnh
int pi[maxv]; //Mảng toàn cục để lưu đường đi ngắn nhất tạm thời
int p[maxv]; //Mảng toàn cục để lưu đỉnh cha của một đỉnh

//Thuật toán tìm đường đi ngắn nhất
void Dijkstra(Graph *g, int x){

	int i,j,k;
	for(i=1;i<=n;i++){
		pi[i] = INFINITY; //Khởi tạo đường đi ngắn nhất tạm thời của tất cả các đỉnh bằng vô cực
		mark[i]=0; //Khởi tạo chưa có đỉnh nào được đánh dấu( Đỉnh chưa đánh dâu có chỉ số bằng 0)
	}

	pi[x] = 0;//Xét đỉnh đầu tiên nên ta thay đổi pi của đỉnh đầu tiên từ vô cực sang 0 để bắt đầu thuật toán
	p[x] = -1;//Đỉnh cha của đỉnh đầu tiên gán bằng -1 tức đỉnh 1 không có đỉnh cha

	//Tìm đỉnh chưa đánh dấu(mark[x]==0) và có pi[x] nhỏ nhất để xét
	for(k=1;k<=n;k++){
		int min_pi = INFINITY;
		for(j=1;j<=n;j++){
			if(mark[j] == 0 && pi[j] < min_pi){
				min_pi = pi[j];
				i=j;
			}
		}

		mark[i]=1;//Sau khi đã tìm được đỉnh có pi[index] nhỏ nhất thì đánh dấu đỉnh đó đã được duyệt
		
		for(j=1;j<=n;j++){
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
    	scanf("%d%d",&n,&m);
	initGraph(&g);
	int u,v,t;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&t);
		addEdge(&g,u,v,t);
	}
	Dijkstra(&g,1);
	if(pi[n]==INFINITY) printf("-1");
	else printf("%d",pi[n]);
	return 0;
}
