# CÁC KHÁI NIỆM `QUAN TRỌNG` TRONG LÝ THUYẾT ĐỒ THỊ
## Định nghĩa đồ thị
>  - `Đồ thị (Graph)` G là một bộ đôi <V,E> trong đó:
>    + `V`: Tập các đỉnh(Vertex set)
>    + `E`: Tập các cung(Edge set)
## Các khái niệm cơ bản
 - `Khuyên`: là cung có 2 đầu mút trùng nhau
 - `Đa cung(cạnh bội)`: Các cung có chung đầu mút
 - `Đỉnh treo`: Đỉnh có bậc bằng 1
 - `Đỉnh cô lập`: Đỉnh có bậc bằng 0
## Các loại đồ thị
  + Đơn đồ thị (Single Graph)
    + Đơn đồ thị vô hướng thỏa:
        + Cung không có hướng
        + Không đa cung
        + Không khuyên
    + Đơn đồ thị có hướng thỏa:
        + Cung có hướng
        + Không đa cung
        + Có thể có khuyên
<hr>
   
  + Đa đồ thị (MultiGraph)
    + Đa đồ thị vô hướng thỏa:
       + Cung không có hướng
       + Không khuyên
    + Đa đồ thị có hướng:
       + Cung có hướng
       + Có thể có khuyên
<hr>
     
  + Giả đồ thị (Pseudo Graph)
      + Cung không có hướng
      + Có thể có đa cung
      + Có thể có khuyên
<hr>

 + Các loại đồ thị đặc biệt khác:
   + Đồ thị vô hướng nền: Là đồ thị vô hướng sau khi đã loại bỏ hướng của đồ thị có hướng
   + Đồ thị con: GS = <V, Es>, Es C E được xây dựng từ G là đồ thị có được sau khi loại bỏ các cung không thuộc Es.
   + Đồ thị đầy đủ:
     + Đơn đồ thị vô hướng
     + Mỗi cặp đỉnh điều có đúng 1 cung
  + Đồ thị rỗng: Có tập đỉnh và tập cạnh là rỗng
  + Đồ thị đều bậc K: Là đồ thị mà tất cả các đỉnh của nó đều có bậc k.
  + Đồ thị phân đôi và đồ thị phân đôi đầy đủ: Tìm hiểu thêm
<hr>

## Bậc của đồ thị
+ Bậc của đơn đồ thị vô hướng là `số cung liên thuộc` với nó
+ Bậc của đơn đồ thị có hướng
  + `Bậc trong`: là số mũi tên đi `vào` đỉnh 
  + `Bậc ngoài`: là số mũi tên từ đỉnh đó đi `ra`
  +`Bậc` của đơn đồ thị có hướng = `bậc trong` + `bậc ngoài`
## Đỉnh kề và đỉnh láng giềng
+ `Đỉnh kề`: đỉnh A mà được gọi là `kề` với đỉnh B khi `có đường đi` nối từ A đến B
+ `Đỉnh láng giềng`: Là tập hợp các `đỉnh kề` của đỉnh đang xét
## *Đường đi*
* `Đường đi`: là đường đi từ đỉnh a đến đỉnh b mà các đỉnh `có thể bị lặp lại`
* `Đường đi đơn`: Là đường đi từ đỉnh a đến đỉnh b mà các đỉnh `không được phép lặp lại`
## *Chu trình*
* `Chu trình`: Là đường đi có `đỉnh bắt đầu` giống với `đỉnh kết thúc` và các đỉnh `có thể bị lặp lại`
* `Chu trình đơn`: Là đường đi `có đỉnh bắt` đầu giống với `đỉnh kết thúc` *NHƯNG* các đỉnh `không được phép lặp lại`
## *Tính liên thông của đơn đồ thị vô hướng*
* Một đồ thị sẽ có `nhiều` thành phần liên thông
* Vậy đồ thị được gọi là `liên thông` thì chỉ có `duy nhất 1` thành phần liên thông mà thôi
* Yếu tố để đồ thị được gọi là liên thông thì `luôn tồn tại đường đi từ đỉnh a đến đỉnh b (với a b là hai đỉnh bất kì)`
## *Tính liên thông của đơn đồ thị có hướng*
* Ở đồ thị có hướng chúng ta sẽ nói về `liên thông mạnh` và `liên thông yếu`
* Đồ thị được gọi là `liên thông mạnh`nếu `luôn có đường đi từ đỉnh a đến đỉnh b(với a b là hai đỉnh bất kì)`
* Đồ thị được gọi là `liên thông mạnh` thì chỉ tồn tại `duy nhất 1` thành phần liên thông
* Đồ thị được gọi là `liên thông yếu` thì đồ thị `vô hướng nền` của nó `liên thông` -> Khi một đồ thị `liên thông yếu` thì sẽ `có nhiều bộ phận liên thông mạnh`


 <hr>
 
 *Made by Nguyen Huu Nhan*
