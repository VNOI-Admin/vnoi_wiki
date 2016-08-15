# Một số bài toán quy hoạch động điển hình

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

Tương tự như bài toán bố trí phòng họp, nếu sắp xếp các đơn đặt hàng theo thời điểm kết thúc, ta sẽ đưa được về bài toán **tìm dãy con có tổng lớn nhất**. Bài toán này là biến thể của bài toán tìm dãy con tăng dài nhất, ta có thể cài đặt bằng đoạn chương trình như sau:

```pascal
for i:=1 to n do 
  begin
          L[i]:=C[i];
          for j:=1 to i–1 do
               if (B[j]<=A[i]) and (L[i]<L[j]+C[i]) then L[i]:=L[j]+C[i];
  end;
```

### Dãy tam giác bao nhau

**Bài toán**:

Cho $n$ tam giác trên mặt phẳng. Tam giác $i$ bao tam giác $j$ nếu 3 đỉnh của tam giác $j$ đều nằm trong tam giác $i$ (có thể nằm trên cạnh). Hãy tìm dãy tam giác bao nhau có nhiều tam giác nhất.

**Hướng dẫn**:

Sắp xếp các tam giác tăng dần về diện tích. Khi đó tam giác $i$ sẽ bao tam giác $j$ nếu $j<i$ và 3 đỉnh của $j$ nằm trong $i$. Từ đó có thể đưa về bài toán tìm dãy “tăng” dài nhất.

Bài toán có một số biến thể khác như tìm dãy hình tam giác, hình chữ nhật… bao nhau có tổng diện tích lớn nhất.

Việc kiểm tra điểm $M$ có nằm trong tam giác $ABC$ không có thể dựa trên phương pháp tính diện tích: điểm $M$ nằm trong nếu $S(ABC) = S(ABM) + S(ACM) + S(BCM)$.

### Dãy đổi dấu

**Bài toán**:

Cho dãy $A_1, A_2,..., A_N$. Hãy tìm dãy con đổi dấu dài nhất của dãy đó. Dãy con con đổi dấu $A_{i1},A_{i2},..., A_{ik}$ phải thoả mãn các điều kiện sau:

- $A_{i1} < A_{i2} > A_{i3} <...$ hoặc $A_{i1} > A_{i2} < A_{i3} >...$
- Các chỉ số phải cách nhau ít nhất $L$: $i_2 – i_1 \ge L$, $i_3 – i_2 \ge L$, ...
- Chênh lệch giữa 2 phần tử liên tiếp nhỏ hơn $U$: $|A_{i1} – A_{i2}| \le U$, $|A_{i2} – A_{i3}| \le U$, ...

**Hướng dẫn**:

Gọi $L_i$ là số phần tử của dãy con đổi dấu có phần tử cuối cùng là $A_i$ và phần tử cuối cùng lớn hơn phần tử đứng trước. Tương tự, $P_i$ là số phần tử của dãy con đổi dấu có phần tử cuối cùng là $A_i$ và phần tử cuối cùng nhỏ hơn phần tử đứng trước.

Ta dễ dàng suy ra:
- $L_i = max(1, P_j + 1)$, với mọi $j$ thỏa mãn: $j \le i–L$ và $A_i – U \le A_j < A_i$.
- $P_i = max(1, L_j + 1)$, với mọi $j$ thỏa mãn: $j \le i–L$ và $A_i < A_j \le A_i + U$.

### Dãy số WAVIO

**Bài toán**:

Dãy số Wavio là dãy số nguyên thỏa mãn các tính chất: các phần tử đầu sắp xếp thành 1 dãy tăng dần đến 1 phần tử đỉnh sau đó giảm dần. Ví dụ dãy số `1 2 3 4 5 2 1` là 1 dãy Wavio độ dài 7. Cho 1 dãy gồm $N$ số nguyên, hãy chỉ ra một dãy con Wavio có đọ dài lớn nhất trích ra từ dãy đó.

**Hướng dẫn**:

$L1_i$ là mảng ghi độ dài lớn nhất của 1 dãy con tăng dần trích ra từ dãy $N$ phần tử kể từ phần tử 1 đến phần tử $a_i$.

$L2_i$: mảng ghi độ dài lớn nhất của dãy con giảm dần trích ra từ dãy $N$ phần tử kể từ phần tử $A_N$ đến $A_i$. Ta tìm phần tử $j$ trong 2 mảng $L1$, $L2$ thỏa mãn $L1_j + L2_j$ lớn nhất.

### Xếp các khối đá

**Bài toán**:

Cho $N$ khối đá $(N \le 5000)$.

Các khối đá đều có dạng hình hộp chữ nhật và được đặc trưng bới 3 kích thước: dài, rộng, cao. Một cách xây dựng tháp là một cách đặt một số các khối đá trong các khối đá đã cho chồng lên nhau theo quy tắc:

- Chiều cao mỗi khối đá là kích thước nhỏ nhất trong 3 kích thước.
- Các mép của khối đá được đặt song song với nhau sao cho không có phần nào của khối trên nằm chìa ra ngoài khối dưới.

Hãy chỉ ra cách để xây dựng được một cái tháp sao cho số khối đá được dùng là nhiều nhất.

# Vali

## 2.1. Mô hình

Có $n$ đồ vật, vật thứ $i$ có trọng lượng $A_i$ và giá trị $B_i$. Hãy chọn ra một số các đồ vật, mỗi vật một cái để xếp vào 1 vali có trọng lượng tối đa $W$ sao cho tổng giá trị của vali là lớn nhất.

## 2.2. Công thức

Hàm mục tiêu: $f$: tổng giá trị của vali.

Nhận xét: giá trị của vali phụ thuộc vào 2 yếu tố: có bao nhiêu vật đang được xét và trọng lượng của các vật. Do đó bảng phương án sẽ là bảng 2 chiều:
    - $L[i,j]$: tổng giá trị lớn nhất của vali khi xét từ vật 1 .. vật $i$ và trọng lượng của vali chưa vượt quá $j$. Chú ý rằng khi xét đến $L[i,j]$ thì các giá trị trên bảng phương án đều đã được tối ưu.

Tính $L[i,j]$: vật đang xét là $a_i$ với trọng lượng của vali không được quá $j$. Có 2 khả năng xảy ra:

- Nếu chọn $A_i$ đưa vào vali, trọng lượng vali trước đó phải không quá $j - A_i$. Vì mỗi vật chỉ được chọn 1 lần nên giá trị lớn nhất của vali lúc đó là $L[i-1, j- A_i] + B_i$.
- Nếu không chọn $A_i$, trọng lượng của vali là như cũ (như lúc trước khi chọn $A_i$): $L[i-1,j]$.

Tóm lại ta có $L[i,j] = \max{ L[i-1,j - A_i ] + B_i, L[i-1,j] }$.
