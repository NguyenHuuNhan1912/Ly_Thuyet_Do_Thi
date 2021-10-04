# Xếp hạng đồ thị
## Để xếp hạng được 1 đồ thị thì đồ thị đó phải thỏa 3 điều kiện
1. Đồ thị phải **`Có hướng`**
1. Đồ thị **`Không tồn tại chu trình`**
1. Đồ thị tồn tại ít nhất 1 **`thứ tự topo`**
</hr>

## Có 2 giải thuật để xếp hạng đồ thị 
### Giải thuật thứ nhất (GT1) - Giải thuật này **`không tối ưu`** sẽ rất khó và dễ sai khi số đỉnh và số cung trong đồ thị quá lớn
#### Nội dung giải thuật như sau - Giải thuật xếp hạng - GT1
* u là gốc có bậc vào bằng 0 -> rank[u] = 0
* Ngược lại rank[u] = số cung trên đường đi dài nhất từ một đỉnh gốc đến đỉnh u
### Giải thuật thứ hai (GT2) - Giải thuật này sẽ **`tối ưu`** và xử lí được các loại đồ thị có số đỉnh và số cung lớn
* Xếp hạng cho các đỉnh gốc -> Hạng đỉnh gốc = 0
* Loại bỏ đỉnh gốc ra khỏi đồ thị -> Đồ thị sẽ xuất hiện gốc mới
* Xếp hạng cho gốc mới -> Hạng gốc mới bằng 1
* Loại bỏ gốc mới đó ra khỏi đồ thị
* Tiếp tục quá trình trên đến khi đồ thị chỉ còn 1 đỉnh duy nhất -> Xếp hạng cho đỉnh đó -> Giải thuật kết thúc
## Nói về GT2 chúng ta thấy có bước xóa 1 gốc ra khỏi đồ thị vậy nếu vào code mà chúng ta xóa gốc đi thật thì sẽ rất khó quản lí và dễ sai thay vì xóa 1 gốc nó sẽ tương đương việc giảm 1 bậc vào của các đỉnh kề của đỉnh đang xét -> Như thế thì thuật toán chúng ta không cần phải xóa gốc mà chỉ cần giảm bậc vào là được
### Các biến cần sử dụng của GT2
* d[u]: Lưu bậc vào của đỉnh u
* s[k]: Danh sách các gốc ở bước k
* Rank[u]: Hạng của đỉnh u
* k: Bước lặp
### CODE
```
Tính bậc vào của các đỉnh và lưu tất cả vào d[u]
Đưa các gốc(Các đỉnh có bậc vào bằng 0) vào s[0]
Khởi tạo biến k = 0 
While(s[k] != Rỗng)
       Làm rỗng s[k+1]
       for(Các đỉnh u trong danh sách s[u])
            rank[u] = k;
            for(Các đỉnh kề v của u)
                d[v]--;//Bước này giảm bậc = xóa 1 gốc ra khỏi đồ thị
                if(d[v] == 0)
                  Đưa v vào s[k+1]
       k++//Tăng k lên nếu s[k] rỗng -> Giải thuật kết thúc
```
**[Xem bài tập mẫu ở đây](https://docs.google.com/spreadsheets/d/1pbiCp2ymAAHOYI1oPuYjZadiuNJW4SNVillljT0EdNU/edit?usp=sharing)**
