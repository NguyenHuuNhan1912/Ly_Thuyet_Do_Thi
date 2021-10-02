/*
Cho đồ thị đơn, vô hướng G = <V, E> có n đỉnh và m cung (n < 100, m < 500). Mỗi cung được gán một trọng số w (0 < w <= 100).

Viết chương trình tìm đếm xem có bao nhiêu đường đi ngắn nhất từ đỉnh 1 đến n.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m.

- m dòng tiếp theo mỗi dòng chứa 3 số nguyên u, v, w mô tả cung (u, v) có trọng số w.

Đầu ra (Output):

In ra màn hình chiều dài của đường đi ngắn nhất từ 1 đến n và số đường đi có chiều dài bằng với chiều dài dường đi ngắn nhất. Nếu không có đường đi từ 1 đến n, in ra -1 0.

Trong ví dụ đầu tiên có 2 đường đi từ 1 đến 3 là: 1 - 2 - 3 và 1 - 3. Cả hai đường đi này đều ngắn nhất và có chiều dài bằng 6.

Xem thêm ví dụ bên dưới.

Gợi ý:

Ngoài pi[v], ta định nghĩa thêm cnt[v]: số đường đi ngắn nhất từ s đến v.

Mỗi lần cập nhật pi[v] ta chú ý cập nhật lại cnt[v]. Nếu đường đi mới qua u tốt hơn thì cnt[v] = cnt[u]. Nếu bằng nhau thì cộng thêm: cnt[v] += cnt[u].

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
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}

For example:

Input	Result
3 3  	6 2
1 2 2
2 3 4
1 3 6

3 1	-1 0
1 2 5

6 9	20 1
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
	g->matrix[y][x]=t;
}

//Hàm tìm giá trị nhỏ nhất
int min(int a, int b){
    return (a<b) ? a: b;
}

int mark[maxv]; //Mảng toàn cục để đánh dấu các đỉnh
int pi[maxv]; //Mảng toàn cục để lưu đường đi ngắn nhất tạm thời
int p[maxv]; //Mảng toàn cục để lưu đỉnh cha của một đỉnh
int cnt[maxv]; //Mảng toàn cục lưu số đường đi ngắn nhấtnhất

//Thuật toán tìm đường đi ngắn nhất
void Dijkstra(Graph *g, int x){

	int i,j,k;
	for(i=1;i<=n;i++){
		pi[i] = INFINITY; //Khởi tạo đường đi ngắn nhất tạm thời của tất cả các đỉnh bằng vô cực
		mark[i]=0; //Khởi tạo chưa có đỉnh nào được đánh dấu( Đỉnh chưa đánh dâu có chỉ số bằng 0)
	}

	pi[x] = 0;//Xét đỉnh đầu tiên nên ta thay đổi pi của đỉnh đầu tiên từ vô cực sang 0 để bắt đầu thuật toán

	p[x] = -1;//Đỉnh cha của đỉnh đầu tiên gán bằng -1 tức đỉnh 1 không có đỉnh cha
    
    cnt[x] =1;//Khởi tạo đường đi ngắn nhất của 1 đỉnh bắt đầu là 1
    
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
			    int pi_before = pi[j];
			    int pi_after = min(pi[i],pi[j]) + g->matrix[i][j];
			    if (pi_after < pi_before){
 					pi[j] = pi_after;
 					cnt[j] = cnt[i];//nếu pi sau tốt hơn pi trước (pi có nghĩa là đường đi)
					p[j] = i;
 				}
 				else if(pi_after == pi_before){
 				    cnt[j] += cnt[i];//nếu pi bằng nhau tức là tồn tại con đường khác -> số đường đi ngắn nhất tăng lên 1
 				    p[j]=i;
 				}
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
    
	if(pi[n]==INFINITY) printf("-1 0");
	else printf("%d %d",pi[n],cnt[n]);
	return 0;
}