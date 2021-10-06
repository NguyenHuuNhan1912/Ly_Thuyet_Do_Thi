# CÂY VÔ HƯỚNG TRONG LÝ THUYẾT ĐỒ THỊ
## Đinh nghĩa: `Cây` vô hướng là cây thỏa 3 điều kiện sau:
* Đồ thị `vô hướng`
* Đồ thị `liên thông`
* Đồ thị `không có chu trình`
## `Rừng` là `đồ thị vô hướng` và `không có chu trình`
## Có 7 định lí để chứng minh 1 đồ thị có phải là 1 cây hay không 
* Định lí 1: Không đa cung
* Định lí 2: `Cây` có `n đỉnh` sẽ `có n-1 cung`
* Định lí 3: `Đồ thị` liên thông có `n đỉnh` và `n-1` cung cũng là `cây`
* Định lí 4: `Đồ thị` liên thông `tối thiếu` là cây (Đồ thị liên thông tối thiểu là khi bỏ 1 cung bất kì trong đồ thị thì đồ thị đó mất đi tính liên thông)
* Định lí 5: `Đồ thị` có n đỉnh, n-1 cung và `không có chu trình` gọi là `cây`
* Định lí 6: 1 cây luôn có ít nhất 2 đỉnh treo (đỉnh treo là đỉnh có bậc bằng 1)
* Định lí 7: ...
# CÂY KHUNG 
## Định nghĩa:
* `Cây khung` là 1 `đồ thị con` sinh ra từ 1 đồ thị cha, `1 cây cha` có thể sinh ra `nhiều cây con`, và cây con chính là `cây` thỏa 3 điều kiện được định nghĩa như trên
* Đồ thị cha sinh ra `nhiều đồ` thị con mà `đồ thị con là cây khung` thì tất nhiên sẽ có `nhiều cây khung` *NHƯNG* cây khung nào tổng trọng số nhỏ nhất được gọi là `cây khung tối thiểu`
* `Đặc biệt` trong một đồ thị có thể có `nhiều cây cung tối thiểu` như `tìm đường đi ngắn nhất` thì có thể tồn tại `2 đường đi ngắn nhất` trên 1 bản đồ
# ÁP DỤNG CÂY KHUNG TỐI THIỂU ĐỂ GIẢI QUYẾT BÀI TOÁN XÂY DỰNG ĐƯỜNG ĐI - GIẢI THUẬT KRUSKAL
## Nội dung bài toán như sau: có n ngôi nhà cần đi đến 1 trường học hãy xây dựng đường đi để số con đường là ít nhất và chi phí thấp nhất
* Phân tích bài toán ta thấy:
  * Mô hình hóa bài toán thành đồ thị: n ngôi nhà là n đỉnh và các con đường là n cung  ->  Bản chất bài toán là tìm 1 cây khung bên trong 1 đồ thị
  * Tìm số đường đi ít nhất: Loại bỏ những con đường tạo thành chu trình -> tức là từ một đồ thị cha ban đầu ta sẽ tìm được các đồ thị con(cây khung) 
  * Tìm chi phí thấp nhất: Sau khi đã tìm ra các cây khung đó thì ta chọn cây khung có trọng số nhỏ nhất(Cây khung tối thiểu) hay còn được gọi là chi phí thấp nhất và đó là kết quả bài toán
* Nội dung giải thuật
```
1. Sắp xếp trọng số các cung trong đồ thị từ nhỏ đến lớn
2. Lần lượt thêm các cung có trọng số đã sắp xếp từ nhỏ đến lớn vào đồ thị
3. Nếu thêm cung nào mà đồ thị tạo thành chu trình thì không thêm -> Chỉ thêm những cung không tạo thành chu trình -> Thỏa điều kiện của cây
4. Sau khi thêm tất cả các cung thì ta sẽ được 1 cây khung tối thiếu và đó chính là đáp án của bài toán
```
 <hr>
 Made by Nguyen Huu Nhan
