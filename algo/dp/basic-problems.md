# Một số bài toán quy hoạch động điển hình

**Tác giả**: Nguyễn Khánh Việt

# 1. Dãy con đơn điệu dài nhất

## 1.1. Mô hình

Cho dãy $A_1,A_2,..., A_n$. Hãy tìm một dãy con tăng có nhiều phần tử nhất của dãy.

**Đặc trưng**:

- Các phần tử trong dãy kết quả chỉ xuất hiện 1 lần. Vì vậy phương pháp làm là ta sẽ dùng vòng `For` duyệt qua các phần tử $A$ trong dãy, khác với các bài toán của mô hình 4 (đặc trưng là bài toán đổi tiền), các phần tử trong dãy có thể được chọn nhiều lần nên ta thực hiện bằng phương pháp cho giá trị cần quy đổi tăng dần từng đơn vị.
- Thứ tự của các phần tử được chọn phải được giữ nguyên so với dãy ban đầu.

Đặc trưng này có thể mất đi trong một số bài toán khác tùy vào yêu cầu cụ thể. Chẳng hạn bài: Tam giác bao nhau (xem ở dưới).

## 1.2. Công thức QHĐ

Hàm mục tiêu: $f$: độ dài dãy con.

Vì độ dài dãy con chỉ phụ thuộc vào một yếu tố là dãy ban đầu nên bảng phương án là bảng một chiều. Gọi $L_i$ là độ dài dãy con tăng dài nhất, các phần tử lấy trong miền từ $A_1$ đến $A_i$ và phần tử  cuối cùng là $A_i$.

Nhận xét với cách làm này ta đã chia 1 bài toán lớn (dãy con của $n$ số) thành các bài toán con cùng kiểu có kích thước nhỏ hơn (dãy con của dãy $i$ số). Vấn đề là công thức truy hồi để phối hợp kết quả của các bài toán con.

Ta có công thức QHĐ để tính $L_i$ như sau:

- $L_1 = 1$. (Hiển nhiên)
- $L_i = max(1, L_j + 1)$ với mọi phần tử $j$ thỏa mãn: $0<j<i$ và $A_j \le A_i$

Tính $L_i$: phần tử đang được xét là $A_i$. Ta tìm đến phần tử $A_j < A_i$ có $L_j$ lớn nhất. Khi đó nếu bổ sung $A_i$ vào sau dãy con $...A_j$ ta sẽ được dãy con tăng dần dài nhất xét từ $A_1...A_i$.

## 1.3. Cài đặt

Bảng phương án là một mảng một chiều $L$ để lưu trữ các giá trị của hàm QHĐ $L_i$. Đoạn chương trình tính các giá trị của mảng $L$ như sau:

```pascal
for i:= 1 to n do 
   begin
         L[i]:=1;
         for j:=1 to i–1 do
              if (A[j]<=A[i]) and (L[i]<L[j]+1) then L[i]:=L[j]+1;
   end;
```

Như vậy độ phức tạp bộ nhớ của bài toán là $O(n)$, độ phức tạp thời gian là $O(n^2)$.

Có một số phương pháp cài đặt tốt hơn so với phương pháp trên, cho chi phí thời gian là $O(nlogn)$, một trong những cách đó là dùng [[Segment Tree|algo/data-structures/segment-tree-extend]].

## 1.4. Một số bài toán khác

Bài toán dãy con đơn điệu tăng dài nhất có biến thể đơn giản nhất là bài toán dãy con đơn điệu giảm dài nhất, tuy nhiên chúng ta có thể coi chúng như là một. Sau đây là một số bài toán khác.

### Bố trí phòng họp (mất tính thứ tự so với dãy ban đầu)

**Bài toán**:

Có $n$ cuộc họp, cuộc họp thứ $i$ bắt đầu vào thời điểm $A_i$ và kết thúc ở thời điểm $B_i$. Do chỉ có một phòng hội thảo nên 2 cuộc họp bất kì sẽ được cùng bố trí phục vụ nếu khoảng thời gian làm việc của chúng chỉ giao nhau tại đầu mút. Hãy bố trí phòng họp để phục vụ được nhiều cuộc họp nhất.

**Hướng dẫn**:

Sắp xếp các cuộc họp tăng dần theo thời điểm kết thúc $B_i$. Thế thì cuộc họp $i$ sẽ bố trí được sau cuộc họp $j$ khi và chỉ khi $j<i$ và $B_j \le A_i$. Yêu cầu bố trí được nhiều cuộc họp nhất có thể đưa về việc tìm dãy các cuộc họp dài nhất thoả mãn điều kiện trên.

### Cho thuê máy

**Bài toán**:

Trung tâm tính toán hiệu năng cao nhận được đơn đặt hàng của $n$ khách hàng. Khách hàng $i$ muốn sử dụng máy trong khoảng thời gian từ $a_i$ đến $b_i$ và trả tiền thuê là $c_i$. Hãy bố trí lịch thuê máy để tổng số tiền thu được là lớn nhất mà thời gian sử dụng máy của 2 khách hàng bất kì được phục vụ đều không giao nhau (cả trung tâm chỉ có một máy cho thuê).

**Hướng dẫn**:

Tương tự như bài toán bố trí phòng họp, nếu sắp xếp các đơn đặt hàng theo thời điểm kết thúc, ta sẽ đưa được về bài toán tìm dãy con có tổng lớn nhất. Bài toán này là biến thể của bài toán tìm dãy con tăng dài nhất, ta có thể cài đặt bằng đoạn chương trình như sau:
