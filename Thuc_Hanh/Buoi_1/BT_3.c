/*
Cho cấu trúc dữ liệu đồ thị được khai báo sử dụng ma trận đỉnh - đỉnh như sau:

typedef struct {
    int A[100][100];
    int n;
} Graph;
Giả sử đồ thị vô hướng, không chứa khuyên, không chứa đa cung

Viết hàm int deg(Graph* G, int x) để tính bậc của đỉnh x.

int deg(Graph* G, int x) {
}
*/

//code
int deg(Graph *G, int x) {
    int count=0;
    for(int i=1;i<=G->n;i++){
        if(G->A[i][x]==1){
            count++;
        }
    }
    return count;
}