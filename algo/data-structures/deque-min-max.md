# Kĩ thuật sử dụng Deque tìm Min/Max trên đoạn tịnh tiến

**Nguồn bài**: [link](https://langocthuyan.wordpress.com/2014/08/12/ki-thuat-su-dung-deque-stack-2-dau-tim-minmax-tren-doan-tinh-tien/)

**Tác giả**: Yên Vũ

Kĩ thuật sử dụng Deque tìm Min/Max trên đoạn tịnh tiến xuất hiện nhiều trong các bài tập tin học, thông thường để cải tiến chương trình, làm giảm độ phức tạp. Chúng ta sẽ tìm hiểu kĩ thuật này qua một vài ví dụ cụ thể và xem xét khả năng mở rộng ứng dụng của nó trong các bài toán khác.

# Bài toán

Cho dãy số nguyên không âm $A$ có $N$ phần tử $(N \le 10^6)$. Ta cần tính $L$ và $R$ là 2 dãy số được tính từ dãy $A$ với định nghĩa như sau:

- $1 \le L_i \le i \le R_i \le N$.
- $A_i = \min{ A[L_i], A[L_i + 1], ..., A[R_i]}$.
- $R_i - L_i$ là lớn nhất (nói cách khác là số phần tử trong đoạn $[L_i, R_i]$ là lớn nhất).

Nói một cách đơn giản hơn: Với mỗi phần tử $i$ của mảng $A$, ta cần tìm đoạn $[l, r]$ dài nhất, sao cho $i \in [l, r]$ và $A_i = \min{A_l, ..., A_r}$. Với $N$ nhỏ, ta có thể giải quyết bài toán một cách đơn giản bằng cách: Với mỗi $i$, ta kiểm tra các phần tử xung quanh $i$ để mở rộng phạm vi $l$, $r$. Cụ thể:

```cpp
for (int i = 1; i <= n; i++) {
	L[i] = i;
	while (L[i] > 0 && a[i] <= a[L[i]]) --L[i];
	++L[i];

	R[i] = i;
	while (R[i] < n && a[i] <= a[R[i]]) ++R[i];
	--R[i];
}
```

Nhận xét:

- `L[i] - 1` bằng 0 hoặc là số lớn nhất mà `L[i] - 1 < i` và `A[L[i] - 1] < A[i]` **(1)**
- `R[i] + 1` bằng 0 hoặc là số nhỏ nhất mà `R[i] + 1 > i` và `A[R[i] + 1] < A[i]` **(2)**

Từ nhận xét này, ta xây dựng Deque bằng cách "lọc" lại dãy như sau: Trong quá trình duyệt dãy $A$, luôn đưa $i$ vào cuối Deque hiện tại, nhưng loại bỏ tất cả các vị trí $j$ đã được đưa vào trong Deque mà $A[j] \ge A[i]$. Như vậy, tại mọi thời điểm $i$, ta luôn có danh sách các vị trí trên Deque tạo thành dãy các số tăng dần trên $A$.

**Ví dụ**

$A = [1, 3, 5, 4, 2, 8]$

```
i = 1: Deque = [1]
i = 2: Deque = [1, 2]
i = 3: Deque = [1, 2, 3]
i = 4: Deque = [1, 2, 4]
i = 5: Deque = [1, 5]
i = 6: Deque = [1, 5, 6]
```

Code:

```cpp
for (int i = 1; i <= n; ++i){
   while (top > 0 && a[D[top]] >= a[i]) --top;  //cap nhat Deque
   D[++top] = i; //dua i vao cuoi Deque
}
```

Theo cách hoạt động của Deque, ta có:

Giả sử tại bước $i$, đã xác định được $i$ ở vị trí top trong Deque. Khi đó: `L[i] = Deque[top - 1] + 1`

Chứng minh:

Từ **(1)** ta có: `A[L[i] – 1] < A[i]`, nên `L[i] - 1` không bị loại khỏi Deque trong quá trình cập nhật lại Deque. Mặt khác, cũng từ **(1)** ta có `L[i] - 1` lớn nhất, mọi số $j \in [L[i], i-1]$ đều đã bị loại khỏi Deque do $A[j] \ge A[i]$, nên $L[i] - 1$ sẽ đứng liền sát $i$ trong Deque. Ta đưa $i$ vào vị trí cuối (top) của Deque, nên $L[i] - 1$ chính bằng $Deque[top - 1]$, hay $L[i] = Deque[top - 1] + 1$.

Vậy, ta xác định được $L$ của một phần tử bất kỳ ngay khi đưa phần tử đó vào Deque.

Bên cạnh đó, gọi $t$ là vị trí các phần tử của $A$ bị loại khỏi Deque trong quá trình cập nhật Deque. $t$ bị loại khỏi Deque tại thời điểm $i$, chứng tỏ $i$ là số đầu tiên xuất hiện trong Deque mà $A[i] < A[t]$ (vì nếu tồn tại một số $k$ thỏa mãn $t < k < i$ mà $A[k] < A[t]$ thì $t$ đã bị loại tại thời điểm $k$). Từ **(2)** suy ra $Rơ[t] + 1$ chính là $i$, hay $R[t] = i - 1$.

Vậy, ta cũng xác định được $R$ của một phần tử bất kỳ ngay khi loại phần tử đó ra khỏi Deque.

```cpp
D[0] = 0;
for (int i = 1; i <= n; ++i){
    while (top > 0 && a[D[top]] >= a[i])
         R[D[top--]] = i – 1;
    L[i] = D[top] + 1;
    D[++top] = i;
}
while (top > 0) R[D[top--]] = n;
```

Độ phức tạp của đoạn chương trình trên có thể đánh giá như sau: Với mỗi số trong dãy $A$, ta chỉ đưa vào Deque 1 lần duy nhất và cũng chỉ lấy ra khỏi Deque 1 lần duy nhất. Do vậy chi phí thực hiện chỉ là $2*N$, hay độ phức tạp của chương trình là $\mathcal{O}(n)$.

# Áp dụng

Chúng ta xem các bài tập sau đây:

## Áp dụng 1:

[VOJ - KAGAIN](http://vnoi.info/problems/show/KAGAIN/)

**Tóm tắt đề**

Cho dãy $A$ gồm $n$ phần tử.

Ta chọn các đoạn liên tiếp $[i, j]$ bất kì. “Sức mạnh” của đoạn $[i, j]$ được định nghĩa như sau: $SM[i, j] = (j – i + 1) * \min{A_i,..., A_j}$.

Yêu cầu: Cho biết $SM$ lớn nhất có thể trong dãy $A$.

**Lời Giải**

Để tìm kết quả, ta xét tất cả $n$ trường hợp có $A_k$ chính bằng min của đoạn $[i, j]$. Do ta đã cố định $min$ của đoạn $[i, j]$, sức mạnh lớn nhất đạt được khi $j - i$ là lớn nhất, nói cách khác là khi dãy dài nhất. Rõ ràng, đây chính là ứng dụng trực tiếp của mảng $L$ và $R$.

Xây dựng mảng $L$, $R$ và cập nhật kết quả bằng $(R[i] – L[i]+1) * A[i]$.

Bài tập tương tự: [VOJ - MINK](http://vnoi.info/problems/show/MINK)

## Áp dụng 2

[VOJ - QBRECT](http://vnoi.info/problems/show/QBRECT/)

**Tóm tắt đề**

Cho bảng số {0, 1} kích thước $m \* n$. Tìm diện tích hình chữ nhật lớn nhất chỉ gồm các số 1 có cạnh song song với bảng.

**Lời Giải**

Trên dòng $k$, ta xét đoạn các cột $[i, j]$ gồm các số 1 liên tiếp. Xét mỗi cột $t \in [i, j]$, ta gọi $H[t]$ là số dòng của đoạn liên tiếp dài nhất chỉ có số 1 kết thúc tại dòng $k$.

![](https://langocthuyan.files.wordpress.com/2014/08/screenshot-2014-08-12-08-28-33.png?w=300&h=170)

Khi đó: Hình chữ nhật có thể tạo bởi đoạn $[i,j]$ chính là hình có cạnh dài $(j – i + 1)$ và chiều cao bằng $\min{H_t}$. Diện tích hình chữ nhật này là (j – i + 1) * min{H[t]}.

Với mỗi dòng trên hình chữ nhật, ta làm tương tự bài KAGAIN: xét hết tất cả $m$ trường hợp có $H_t$ là min, tìm đoạn $[i, j]$ dài nhất để có được hình chữ nhật lớn nhất. Để tiện tính toán, ta chuẩn bị trước $H[t]$, thay vì là mảng một chiều ứng với cột t và tính lại với mỗi dòng $k$, ta mở rộng lưu trữ $H[k][t]$ với ý nghĩa tương tự. Tính bảng $H$ bằng quy hoạch động đơn giản:

- $H[k][t] = 0$ nếu $A[k][t] = 0$,
- Ngược lại $H[k][t] = H[k – 1][t] + 1$.

Việc chuẩn bị bảng $H$ cũng như tìm hình chữ nhật là $\mathcal{O}(n^2)$, nên ta giải quyết bài tập này với $\mathcal{O}(n^2)$.

Bài tập tương tự:

- [VOJ - CREC01](http://vnoi.info/problems/show/CREC01/)
- [VOJ - CRECT](http://vnoi.info/problems/show/CRECT/)
- [VOJ - NKGOLF](http://vnoi.info/problems/show/NKGOLF/)

Một vài bài tập khác sử dụng Kĩ thuật tịnh tiến Deque

- [VOJ - KDIFF](http://vnoi.info/problems/show/KDIFF/)
- [VOJ - BLAND](http://vnoi.info/problems/show/BLAND/)
- [VOJ - C11CIR](http://vnoi.info/problems/show/C11CIR/)
- [VOJ - VMQUABEO](http://vnoi.info/problems/show/VMQUABEO/)