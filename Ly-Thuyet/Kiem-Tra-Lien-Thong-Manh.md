# KIỂM TRA ĐƠN ĐỒ THỊ CÓ HƯỚNG CÓ LIÊN THÔNG MẠNH HAY KHÔNG
+ Nếu như ở đồ thị `vô hướng` muốn `kiểm tra tính liên thông` thì chỉ cần `áp dụng` các giải thuật `duyệt đồ thị(duyệt sâu, duyệt rộng)`
+ Còn ở đồ thị `có hướng` thì chúng ta phải `kiểm tra đồ thị đó` có `liên thông mạnh` hay không nên chúng ta `phải kết hợp` cả `2 giải thuật` mới có thể kiếm tra được
+ Kiểm tra tính `liên thông mạnh` = Duyệt đồ thị `theo chiều sâu(stack or recursion)` + `Tarjan`
+ Duyệt đồ thị theo `chiều sâu` sử dụng `hàng đợi` hoặc `đệ qui` thì chúng ta `đã biết` hôm nay chúng ta sẽ tìm hiểu giải thuật `Tarjan`
# GIẢI THUẬT TARJAN
+ Các biến hỗ trợ
  + count: Biến count dùng để đếm xem đồ thị có bao nhiêu thành phần liên thông mạnh
  + k: Bước lặp k của giải thuật
  + on_stack[]: Mảng lưu trạng thái 1 đỉnh đã được đưa vào stack hay chưa
  + num[v]: Mảng num[] lưu chỉ sô của đỉnh v trong quá trình duyệt
  + min_num[v]: Chỉ số nhỏ nhất trong các chỉ số của các đỉnh trong stack mà v đi đến đó được
```
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
    k++; //tang buoc lap len
    Stack s;
    makenullStack(&s);
    pushStack(&s,x);//Dua dinh dau tien vao stack
    on_stack[x]=1;//Danh dau dinh do da dua vao stack bang bien mang on_stack
    List L = neighbors(g,x);//Tim dinh lang gieng cua dinh do
    for(int j=0;j<L.size;j++){//Xet cac dinh ke cua x
        int v = getList(&L,j);
        if(on_stack[v]==-1){//Neu dinh ke x chua co trong stack
            strong_connect(g,v);//Goi de qui duyet dinh ke cua x
            min_num[x] = min(min_num[x],min_num[v]);//Khi dut lui cap nhat lai min_num cho dinh x(min_num cha < min_num con)
        }
        else if(on_stack[v]==1){//Neu dinh v ke x da co trong stack
            min_num[x] = min(min_num[x],num[v]);//Cap nhat lai min num
        }
        //Sau khi duyet xong 1 dinh ma vong lap for o tren dung lai tuc la ta da co 1 bo phan lien thong manh
        //Neu do thi lien thong manh thi ket thuc luon chuong trinh vi do thi lien thong thi chi co 1 thanh phan lien thong
        if(num[x]==min_num[x]){
            count++;//Bien count de diem so bo phan lien thong manh cua do thi
            int value;
            do{
                value = getStack(&s);//Lay dinh o dau stack ra
                delSize(&s);//Xoa vi tri dinh do di
                on_stack[x]=-1;//danh dau dinh da lay ra khoi stack
            }while(value!=x);//Lap den khi lay duoc dinh x(Dinh cat)
        }
    }
    - Sau khi ham ket thuc
      + Bien count==1 -> Do thi lien thong manh
      + Bien count>1 -> Do thi khong lien thong manh
}
```
[Xem toàn bộ bài toán tại đây](https://github.com/NguyenHuuNhan1912/Ly_Thuyet_Do_Thi/blob/main/Thuc_Hanh/Buoi_2/BT_8.1.c)
