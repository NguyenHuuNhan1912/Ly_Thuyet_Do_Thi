# DUYỆT ĐỒ THỊ
+ `Tại sao phải duyệt đồ thị ?` -> Duyệt đồ thị để `kiểm tra tính liên thông` của đồ thị có nghĩa là duyệt để biết được `đồ thị đó có liên thông hay không`
+ Ý tưởng:
    + Bắt đầu duyệt từ 1 đỉnh bất kì đánh dấu nó đã duyệt
    + Duyệt các đỉnh kề của nó
    + Duyệt các đỉnh kề của đỉnh kề của nó
    + .......
+ Phương pháp duyệt:
    + Duyệt theo `chiều rộng`: Sử dụng `hàng đợi` -  `QUEUE`
    + Duyệt theo `chiều sâu`: Sử dung `ngăn xếp` hoặc `đệ qui` - `STACK` or `RECURSION`
+ Duyệt đồ thị theo `chiều rộng` - `QUEUE`
    + Giải thuật
        + Đưa 1 đỉnh s bất kỳ vào `hàng đợi`(VD: đỉnh 1)
        + while(Hàng đợi chưa rỗng)
            + Lấy đỉnh ở đầu `hàng đợi` ra -> gọi là đỉnh u
            + Nếu đỉnh u `đã được duyệt` thì `bỏ qua` bằng câu lệnh `continue`
            + Nếu đỉnh u `chưa được duyệt` thì duyệt u(VD: `in u ra màn hình` hoặc `đưa vào danh sách kết quả`)
            + `Đánh dấu` u `đã duyệt`
            + for(các `đỉnh kề v`của u)
                + if(v `chưa được duyệt`)
                    + Đưa v vào `hàng đợi`
 ```
 // Giải thuật duyệt rộng sử dụng hàng đợi - BFS - QUEUE
List BFS(Graph *g, int x){
    List rs; //Danh sách lưu các đỉnh đã được duyệt
    makenullList(&rs);
    Queue q; 
    makenullQueue(&q);
    pushQueue(&q,x);
    while(!emptyQueue(&q)){ //Lập trong khi hàng đợi chưa rỗng
        int u = getQueue(&q);
        plusFront(&q);
        if(mark[u]==1) continue; //Nếu đỉnh u đã được duyệt thì bỏ qua các câu lệnh phía sau
        pushList(&rs,u); //Nếu u chưa duyệt thay vì in ra thì chúng ta sẽ đưa vào danh sách rs(result) -> danh sách kết quả
        mark[u]=1; //Đánh dấu u đã duyệt 
        List L = neighbors(g,u); //Tìm đỉnh láng giềng của u đưa vào danh sách L
        for(int j=1;j<=L.size;j++){
            int v = getList(&L,j); //Lấy đỉnh láng giềng u trong danh sách L ra -> Lấy đỉnh v
            if(mark[v]==0){ //Nếu v chưa được duyệt
                pushQueue(&q,v); //Đưa vào hàng đợi duyệt V
            }
        }
    }
    return rs;
}
 ```
 [Xem toàn bộ bài toán duyệt rộng sử dụng hàng đợi tại đây](https://github.com/NguyenHuuNhan1912/Ly_Thuyet_Do_Thi/blob/main/Thuc_Hanh/Buoi_2/BT_1.1.c)
+ Duyệt đồ thị theo chiều sâu - STACK
    + Giải thuật
        + Đưa 1 đỉnh s bất kỳ vào `ngăn xếp`(VD: đỉnh 1)
        + while(ngăn xếp chưa rỗng)
            + Lấy đỉnh ở đầu `ngăn xếp` ra -> gọi là đỉnh u
            + Nếu đỉnh u `đã được duyệt` thì `bỏ qua` bằng câu lệnh `continue`
            + Nếu đỉnh u `chưa được duyệt` thì duyệt u(VD: `in u ra màn hình` hoặc `đưa vào danh sách kết quả`)
            + `Đánh dấu` u `đã duyệt`
            + for(các `đỉnh kề v` của u)
                + if(v `chưa được duyệt`)
                    + Đưa v vào `ngăn xếp`
```
// Giải thuật duyệt sâu sử dụng ngăn xếp - DFS - STACK
List DFS_Stack(Graph *g, int x){
    List rs;//Danh sách lưu các đỉnh đã được duyệt
    makenullList(&rs);
    Stack s;
    makenullStack(&s);
    pushStack(&s,x);
    while(!emptyStack(&s)){ //Lập trong khi ngăn xếp chưa rỗng
        int u = getStack(&s);
        delSize(&s);
        if(mark[u]==1) continue; //Nếu đỉnh u đã được duyệt thì bỏ qua các câu lệnh phía sau
        pushList(&rs,u); //Nếu u chưa duyệt thay vì in ra thì chúng ta sẽ đưa vào danh sách rs(result) -> danh sách kết quả
        mark[u]=1; //Đánh dấu u đã duyệt
        List L = neighbors(g,u); //Tìm đỉnh láng giềng của u đưa vào danh sách L
        for(int j=1;j<=L.size;j++){
            int v = getList(&L,j); //Lấy đỉnh láng giềng u trong danh sách L ra -> Lấy đỉnh v
            if(mark[v]==0){ //Nếu v chưa được duyệt
                pushStack(&s,v); //Đưa vào ngăp xếp duyệt v
            }
        }
    }
    return rs;
}
```
 [Xem toàn bộ bài toán duyệt sâu sử dụng ngăn xếp tại đây](https://github.com/NguyenHuuNhan1912/Ly_Thuyet_Do_Thi/blob/main/Thuc_Hanh/Buoi_2/BT_1.3.c)
+ Duyệt đồ thị theo chiều sâu - RECURSION
    + Giải thuật
        + if(u `đã duyệt`) -> thì return; -> không trả về gì -> có thể hiếu là `đỉnh đó đã được duyệt` thì `không duyệt nữa`
        + Nếu u `chưa duyệt` thì `duyệt u`(VD: `in u ra màn hình` hoặc `đưa vào danh sách kết quả`)
        + `Đánh dấu` u `đã duyệt`
        + for(Các `đỉnh kề v` của u)
            if(v `chưa duyệt`)
                `gọi đệ qui cho v`
```
// Giải thuật duyệt đồ thị theo chiều sâu - Sử dụng đệ qui
void DFS_Recursion(Graph *g, int x){
    if(mark[x]==1) return; //Nếu đỉnh đã được duyệt kết thúc và không trả về gì
    mark[x]=1; //Nếu chưa duyệt thì đánh dấu đã duyệt
    printf("%d\n",x); //In đỉnh vừa duyệt ra màn hình
    List L = neighbors(g,x); //Tìm đỉnh láng giềng của đỉnh đang xét
    for(int j=1;j<=L.size;j++){
        int v = getList(&L,j); //Lấy đỉnh v kề với đỉnh đang xét ra 
        DFS_Recursion(g,v); //Tiếp tục gọi đệ qui
    }
}
```
[Xem toàn bộ bài toán duyệt sâu sử dụng đệ qui tại đây](https://github.com/NguyenHuuNhan1912/Ly_Thuyet_Do_Thi/blob/main/Thuc_Hanh/Buoi_2/BT_1.2.c)
+ Đánh giá: 
    + Giải thuật `duyệt đệ qui` là giải thuật đơn giản và dễ hiểu
    + Giải thuật duyệt bằng `hàng đợi` và `ngăn xếp` thì tương đồng nhau chỉ `khác nhau` cách cài đặt `ngăn xếp` hay là `hàng đợi` mà thôi
