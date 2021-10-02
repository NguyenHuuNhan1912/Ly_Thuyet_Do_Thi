# Sự khác nhau giữa giải thuật Dijkstra và Bellman-Ford
* Giải thuật Dijkstra **`không thể chạy`** được trên đồ thị có chu trình âm nhưng **`Bellman-Ford thì được`**
* Người ta thường sử dụng **`Dijkstra để tìm đường đi ngắn nhất`** còn **`Bellman-Ford là để tìm đồ thị có chứa chu trình âm hay không`**
# Cách kiểm tra đồ thị có chứa chu trình âm hay không của 2 giải thuật
* Giải thuật Dijkstra: Nếu tổng trọng số bé hơn 0 -> Đồ thị tồn tại chu trình âm -> Có nghĩa là chúng ta không cần phải code giải thuật mà chỉ dựa trên trọng số cung
* Giải thuật Bellman-Ford: Sau khi gọi giải thuật thì chúng ta for các cung thêm 1 lần nữa nếu p[v] được cải tiến -> Tồn tại chu trình âm

```
//Code kiểm tra chu trình âm của giải thuật Bellman-Ford
bool check(Graph *g){
    int k;
    for(k=0;k<g->m;k++){
		int u = g->edges[k].u;
		int v = g->edges[k].v;
		int w = g->edges[k].w;
		if(pi[u] + w < pi[v]){
			return true;
		}
	}
    return false;
}
```
```
//Code kiểm tra chu trình âm giải thuật Dijkstra với ts[] là mảng chứa các trọng số của cung
int check(int ts[]){
    int total=0;
    for(int i=1;i<=m;i++){
        total += ts[i];
    }
    return total;
}
```
