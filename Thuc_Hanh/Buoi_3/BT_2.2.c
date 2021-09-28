/*

"Ngưu Lang là vị thần chăn trâu của Ngọc Hoàng Thượng đế, vì say mê một tiên nữ phụ trách việc dệt vải tên là Chức Nữ nên bỏ bễ việc chăn trâu, để trâu đi nghênh ngang vào điện Ngọc Hư. Chức Nữ cũng vì mê tiếng tiêu của Ngưu Lang nên trễ nải việc dệt vải. Ngọc Hoàng giận dữ, bắt cả hai phải ở cách xa nhau, người đầu sông Ngân, kẻ cuối sông.
Mỗi năm một lần, Sau đó, Ngọc Hoàng thương tình nên ra ơn cho hai người mỗi năm được gặp nhau vào ngày 7 tháng Bảy âm lịch. Khi tiễn biệt nhau, Ngưu Lang và Chức Nữ khóc sướt mướt. Nước mắt của họ rơi xuống trần hóa thành cơn mưa và được người dưới trần gian đặt tên là mưa ngâu." (Theo wikipedia.com)
Để gặp được nhau vào ngày 7/7, Ngưu Lang và Chức Nữ phải nhờ đến bầy quạ đen bắt cầu (gọi là Ô kiều) cho mình đi qua để gặp nhau.
Sông Ngân Hà có n ngôi sao, giả sử được đánh số từ 1 đến n. Ngưu Lang ở tại ngôi sao Ngưu (Altair), được đánh số 1, còn Chức Nữ ở tại ngôi sao Chức Nữ (Vega) được đánh số n. Để bắt được một cây cầu từ ngôi sao này sang ngôi sao kia cần một số lượng quạ nào đó. Một khi con quạ ở cây cầu nào thì phải ở đó cho đến khi Ngưu Lang và Chức Nữ gặp được nhau.
Quạ thì càng ngày càng hiếm, nên Ngưu Lang và Chức Nữ phải tính toán sao cho số lượng quạ ít nhất có thể.

Hãy giúp Ngưu Lang và Chức Nữ viết chương trình tính xem cần phải nhờ đến ít nhất bao nhiêu con quạ để bắt cầu cho họ gặp nhau.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số ngôi sao và số cặp sao có thể bắt cầu.

- m dòng tiếp theo mỗi dòng chứa 3 số nguyên u v q nói rằng để bắt 1 cây cầu bắt qua hai ngôi sao u và v cần phải tốn q con quạ.

Đầu ra (Output):

In ra màn hình số lượng quạ cần thiết.

Xem thêm ví dụ bên dưới.

For example:

Input	Result

4 3     8
1 2 5
2 3 2
3 4 1

4 3     7
1 2 3
2 4 4
1 4 10

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
