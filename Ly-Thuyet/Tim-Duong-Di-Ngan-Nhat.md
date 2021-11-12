# TÌM ĐƯỜNG ĐI NGẮN NHẤT - GIẢI THUẬT MOORE-DIJKSTRA - GIẢI THUẬT BELLMAN-FORD
## Giải thuật Dijkstra 
- Các biến hỗ trợ:
  + `pi[u]:` `Lưu đường đi ngắn nhất tạm thời của đỉnh u`
  + `p[u]:` `Lưu đỉnh cha của đỉnh u`
  + mark[u]: `Đánh dấu đỉnh u` - một đỉnh được `đánh dấu` gọi là `đỉnh chắc chắn` và ngược lại
- `Khởi tạo:`
  - `pi[u]` = oo với mọi u 
  - `p[u]` = -1 với mọi u
  - `mark[u` = 0 với mọi u
  - `pi[s]` = 0 -> Đường đi ngắn nhất từ đỉnh s đến đỉnh s bằng 0 - Ví dụ như đường đi ngắn nhất từ nhà bạn đến nhà bạn là bằng 0 vì bạn đang ở nhà của mình 
 - `Lặp n - 1 lần:`
  - `Chọn` đỉnh `chưa chắc chắn` và có pi[u] `nhỏ nhất` -> Đỉnh `chưa chắc chắn` là đỉnh `chưa được đánh dấu` đỉnh có `pi[u] nhỏ nhất` là `đỉnh pi[s] đã khởi tạo`
  - Sau khi đã chọn được thì `đánh dấu đỉnh đó`
  - Xét các `đỉnh kề v`
      + Cập nhật lại `pi[v]` cho đỉnh v `nếu` có đường đi tốt hơn ngược lại không cập nhật
      + Công thức cập nhật `pi[v] = min(pi[v],pi[u] + L[u][v])` trong đó `L[u][v]` là trọng số của đỉnh u nối với đỉnh v
 
 CODE 
 ```
 //Thuật toán tìm đường đi ngắn nhất - Moore - Dijkstra
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
 ```
 - Lưu ý:
    + Giải thuật chạy được trên đồ thị `có hướng` và `vô hướng` 
    + Giải thuật `không` có khác biệt khi áp dụng trên đồ thị `vô hướng` hoặc `có hướng` chỉ khác là khác cách `thêm cung`của có hướng hay vô hướng mà thôi
    
 [Xem bài toán cụ thể thể tại đây - CODE](https://github.com/NguyenHuuNhan1912/Ly_Thuyet_Do_Thi/blob/main/Thuc_Hanh/Buoi_3/BT_1.1.c)
 [Xem bài tập ví dụ ở đây - Giải tay](https://docs.google.com/spreadsheets/d/169EdoSieSgzVjkDSd2mgdUVyNRxbdIvsIHGbSo8-Nn0/edit?usp=sharing)
